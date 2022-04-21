#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netdb.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "./../../socketwrapper.h"

using namespace std;

SocketWrapper::SocketWrapper() {
	// clearing master and read sets
	FD_ZERO(&master_fds);
	FD_ZERO(&read_fds);
}
SocketWrapper::~SocketWrapper() {
}

int SocketWrapper::socket_bind(int port){
  // listener socket descriptor
	int listener_fd;
  // holds wanted settings for the listener socket
	struct addrinfo hints;
  // a list of possible information to create socket
	struct addrinfo *server_info_list;
	// all the other fields in the addrinfo struct (hints) must contain 0
	memset(&hints, 0, sizeof hints);
	// initialize connection information
  // supports IPv4 and IPv6
	hints.ai_family = AF_UNSPEC;
  // reliable Stream (TCP)
	hints.ai_socktype = SOCK_STREAM;
  // assign local host address to socket
	hints.ai_flags = AI_PASSIVE;

	// get address information
	int err;
	err = getaddrinfo(NULL, to_string(port).c_str(), &hints, &server_info_list);
	if (err != 0){
		cerr << "getaddrinfo: " << gai_strerror(err) << endl;
		exit(EXIT_STATUS);
	}

	// go over list and try to create socket and bind
	addrinfo* p;
	for(p = server_info_list;p != NULL; p = p->ai_next) {
		// create the socket - system call that returns the file descriptor of the socket
		listener_fd = socket(p->ai_family, p->ai_socktype,p->ai_protocol);
    if (listener_fd == -1) {
      //try next
      continue;
    }
    // make sure the port is not in use. Allows reuse of local address (and port)
    int yes = 1;
    if (setsockopt(listener_fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
      perror("setsockopt");
      exit(EXIT_STATUS);
    }

    // bind socket to specific port (p->ai_addr holds the address and port information)
    if (bind(listener_fd, p->ai_addr, p->ai_addrlen) == -1) {
			close(listener_fd);
      //try next
			continue; 
		}
    //success
    break; 
	}

	// no one from the list succeeded - failed to bind
	if (p == NULL)  {
    cerr << "failed to bind" << endl;
    exit(EXIT_STATUS);
	}

	// if we got here we successfully created a socket to listen on
	// free list as we no longer need it
	freeaddrinfo(server_info_list);

	//return the listener socket descriptor
	return listener_fd;
}

void SocketWrapper::start_listen(int listener_fd, int backlog) {
	// listen on the given port for incoming connections (Maximum BACKLOG waiting connections in queue)
	if (listen(listener_fd, backlog) == -1){
		perror("listen");
		exit(EXIT_STATUS);
	}
}

void SocketWrapper::set_nonblock(int socket) {
	int flags;
	// save current flags
	flags = fcntl(socket, F_GETFL, 0);
	if (flags == -1)
		perror("fcntl");
	// set socket to be non-blocking
	if (fcntl(socket, F_SETFL, flags | O_NONBLOCK) == -1)
		perror("fcntl");
}

void SocketWrapper::create_sets(int listener_fd) {
	// clear master and read sets
  FD_ZERO(&master_fds);
  FD_ZERO(&read_fds);
  // add the listener socket descriptor to the master set
  FD_SET(listener_fd, &master_fds);
}

void SocketWrapper::start_select(int max_fd, int timeout_sec, int timeout_usec) {
  // set timeout values (for waiting on select())
	struct timeval timeout = {timeout_sec, timeout_usec};
	// copy all available (open) sockets to the read set
	read_fds = master_fds;

	// select - 	modifies read_fds set to show which sockets are ready for reading
	// if none are ready, it will timeout after the given timeout values
	int sel = select(max_fd+1, &read_fds, NULL, NULL, &timeout);
	if (sel == -1) {
		perror("select");
		exit(EXIT_STATUS);
	}
}

int SocketWrapper::check_new_connection(int listener_fd, int max_fd) {
	// check if listener socket is in read set (has changed and has an incoming connection to accept)
	if (FD_ISSET(listener_fd,&read_fds)){
		int client_fd;
		struct sockaddr_storage their_addr;
		socklen_t addr_size = sizeof their_addr;

		// accept the incoming connection, save the socket descriptor (client_fd)
		client_fd = accept(listener_fd, (struct sockaddr *)&their_addr, &addr_size);
		if (client_fd == -1){
			perror("accept");
		}
		else { 
      // if connection accepted
			// set this socket to be non-blocking
			set_nonblock(client_fd);
			// add socket to the master set
			FD_SET(client_fd, &master_fds);
			// update max_fd
			if (client_fd > max_fd)
				max_fd = client_fd;
			// show incoming connection
			if (their_addr.ss_family == AF_INET){
				// IPv4
				char ip_as_string[INET_ADDRSTRLEN];
				inet_ntop(their_addr.ss_family,&((struct sockaddr_in *)&their_addr)->sin_addr,ip_as_string, INET_ADDRSTRLEN);
				cout << "Nova conexão do IP: " << ip_as_string << " on socket " << client_fd << endl;
			} else if(their_addr.ss_family == AF_INET6){
				// IPv6
				char ip_as_string[INET6_ADDRSTRLEN];
				inet_ntop(their_addr.ss_family,&((struct sockaddr_in6 *)&their_addr)->sin6_addr,ip_as_string, INET6_ADDRSTRLEN);
				cout << "Nova conexão do IP: " << ip_as_string << " on socket " << client_fd << endl;
			}
		}
	}
	return max_fd;
}

int SocketWrapper::receive_data(int client_fd, int buffer_size, string& data){
	//set buffer with given buffer_size
	char buf[buffer_size];

	// check if socket is in read set (has data or has closed the connection)
	if (FD_ISSET(client_fd, &read_fds)) {
		int bytes;
		// receive data
		bytes = recv(client_fd, buf, sizeof buf, 0);

		// connection has been closed by client
		if (bytes <= 0){
			if (bytes == -1)
				perror("recv");
			// close socket
			close(client_fd);
			// remove from master set
			FD_CLR(client_fd, &master_fds);
		}
		// some data received - bytes > 0
		else{
			// add NUL terminator
			buf[bytes] = '\0';
			if (buf[bytes-1] == '\n')
			    buf[bytes-1] = '\0';
			// assign received data to the given string
			data.assign(buf);
		}
		return bytes;
	}
	// socket is not in read set
	return -1;
}

void SocketWrapper::respond_ok(int client_fd) {
	// send "OK" to given client
	char respond[4] = "OK\n";
  if (send(client_fd, respond, sizeof respond, 0) == -1) {
    perror("send");
  }
}

void SocketWrapper::close_all(int max_fd) {
	// close all socket descriptors, this will terminate all connections
  for (int i=0; i < max_fd+1; i++){
    // if socket is in the master set it means it is still open - so close it
    if (FD_ISSET(i, &master_fds))
      close(i);
  }
}