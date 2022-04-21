#ifndef SOCKETWRAPPER_H_
#define SOCKETWRAPPER_H_

#define EXIT_STATUS 1

 // this class is a wrapper for a TCP server routine using Berkeley Sockets.
 // It is divided into methods for each relevant step in the TCP server routine
 // in order to make things simpler and more easy to use.
 // This class assumes that the server only maintains a socket set for reading data received from clients.

class SocketWrapper {
	public:
		
		// constructor.
		// initializes relevant fd_sets
		SocketWrapper();
		
		// destructor. Nothing to destruct.
		virtual ~SocketWrapper();

		// this method get local address information,
		// creates a listener sockets and binds it to the given port.
		// Returns the listener socket file descriptor.
		int socket_bind(int);

		// this method receives listener socket and backlog number.
		// It sets the socket to start listening for incoming connections
		// with maximum backlog number of incoming connections waiting to be accepted.
		void start_listen(int,int);

		// this method receives a socket and sets it to be non-blocking.
		void set_nonblock(int);

		// this method initializes the relevant sets and adds the given socket to the master set.
		void create_sets(int);

		// this method receives the maximum socket descriptor number (max_fd) and timeout values.
		// It checks if sockets descriptors (up to max_fd) are ready for read / write / accept connections,
		// and sets the read_fds set accordingly.
		// If none are ready it will timeout after the given timeout values.
		void start_select(int,int,int);

		// this method a listener socket and the maximum socket descriptor number (max_fd).
		// It checks if the socket is in the read_fds set (meaning that it has a incoming connection waiting to be accepted).
		// If it is, it accepts the incoming connection and adding its socket descriptor to the master set.
		// Updates and returns the new max_fd (if changed).
		int check_new_connection(int,int);
		
		// this method receives a socket, buffer size, and a reference to data string.
		// It checks if the socket is in the read_fds set (meaning it has incoming data to receive or it has ended the connection).
		// If the socket has ended the connection, it closes the file descriptor and delete it from the master set.
		// If the socket has incoming data, it reads it (up to buffer_size) and assign it to the given string.
		// It returns the number of bytes received or -1 if the socket is not in the read_fds set.
		int receive_data(int, int, std::string&);

		// this method send "OK" to the given socket.
		void respond_ok(int);
		
		// this method closes all active sockets.
		// The active sockets are the one that are in the master_fd set.
		void close_all(int);

	private:
		// socket descriptor set that holds the sockets that are ready for read
		fd_set read_fds;
		// socket descriptor set that hold all the available (open) sockets
		fd_set master_fds;
};

#endif