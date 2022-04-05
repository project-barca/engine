//For Windows
// #ifdef _WIN32
// #ifdef _WIN64
#ifdef OS_WINDOWS
int betriebssystem = 1;
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <ws2def.h>
#pragma comment(lib, "Ws2_32.lib")
#include <windows.h>
#include <string.h>
#include <string>
#include <io.h>
#include <iostream>
//For Unix
#else
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#endif

using namespace std;
int main() {
  // create an endpoint for communication
  // the socket(domain, type, protocol) function takes three arguments:
  //
  // 1_domain:
  //   - AF_INET for IPv4 network protocol (IPv4 only)
  //   - AF_INET6 for IPv6 (and in some cases IPv4 compatible)
  //   - AF_UNIX to local socket (using a special filesystem node)
  // 2_type:
  //   - SOCK_STREAM (Reliable Stream Oriented Service or Stream Sockets)
  //   - SOCK_DGRAM (datagram service or datagram sockets)
  //   - SOCK_SEQPACKET (Reliable Sequenced Packet Service)
  //   - SOCK_RAW (raw protocols on top of the network layer)
  // 3_protocol:
  //   - IPPROTO_TCP this protocol is connection-oriented and a connection between client and server is established before data can be sent.
  //   - IPPROTO_UDP this protocol allows very fast communication but low reliability
  //   - IPPROTO_SCTP unlike UDP and TCP, the protocol supports multihoming and redundant paths to increase resilience and reliability.
  //   - IPPROTO_DCCP is a new transport layer protocol that implements bidirectional unicast connections, unreliable congestion control of datagrams.
  int listening = socket(AF_INET, SOCK_STREAM, 0);
  // check if socket was created successfully
  if (listening == -1) {
    std::cerr << "Não foi possível criar um socket";
    return -1;
  }
  // when a socket is created with socket(domain, type, protocol), it only receives a porthole family, but not an assigned address.
  //
  // the bind(sockfd, my_addr, addrien) function takes three arguments:
  //   - sockfd, a descriptor representing the socket.
  //   - my_addr, a pointer to a sockaddr structure representing the address to bind to.
  //   - addrien, a field of type socklen_t specifying the size of the sockaddr structure.
  //
  // bind() returns 0 on success and -1 if an error occurs.
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  // assign hosts for small networks
  hint.sin_port = htons(54000);
  // set version 4 network address with any available ip to a link
  inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
  // check if the info link is bound to the socket
  if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1) {
    std::cerr << "Não foi possível vincular ao IP/port";
    return -2;
  }
  // after a socket has been associated with an address, listen() prepares it for
  // incoming connections. However, this is only necessary for the stream-oriented (connection-oriented) data modes, i.e.
  // for socket types (SOCK_STREAM, SOCK_SEQPACKET).
  //
  // the listen(sockfd, backlog) function takes two arguments:
  //  - sockfd, a valid socket descriptor.
  //  - backlog, an integer representing the number of pending connections that can be queued up at any one time.
  //    The operating system usually places a cap on this value.
  if (listen(listening, SOMAXCONN) == -1) {
    std::cerr << "Não foi possível receber a conexão";
    return -3;
  }
  // accept a customer call
  sockaddr_in client;
  socklen_t clientSize = sizeof(client);
  char host[NI_MAXHOST];
  char svc[NI_MAXSERV];
  // the function accept() creates a new socket for each connection and removes the connection from the listening queue. 
  //
  // the accept(sockfd, cliaddr, addrlen) function takes three arguments:
  //  - sockfd, the descriptor of the listening socket that has the connection queued.
  //  - cliaddr, a pointer to a sockaddr structure to receive the client's address information.
  //  - addrlen, a pointer to a socklen_t location that specifies the size of the client address structure passed to accept(). 
  //    When accept() returns, this location contains the size (in bytes) of the structure.
  //
  // obs: accept() returns the new socket descriptor for the accepted connection, or the value -1 if an error occurs. 
  //      All further communication with the remote host now occurs via this new socket.
  //
  int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
  // check if client socket is in error
  if (clientSocket == -1) {
    std::cerr << "Error Socket Client!";
    return -4;
  }
  close(listening);
  // clear the buffer to hosts
  memset(host, 0, NI_MAXHOST);
  memset(svc, 0, NI_MAXSERV);
  // the getnameinfo() function translates a socket address to a node name and service location. 
  // The function looks up an IP address and port number provided by the caller in 
  // the DNS and system-specific database, and returns text strings for both in buffers provided by the caller.
  int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

  if (result) {
    std::cout << host << " conectado em " << svc << endl;
  } else {
    inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
    std::cout << host << " conectado em " << ntohs(client.sin_port) << endl;
  }
  // while receiving display message, echo message
  char buf[4096];
  while (true) {
    // clear the buffer
    memset(buf, 0, 4096);
    // wait for a message client
    int bytesRecv = recv(clientSocket, buf, 4096, 0);
    // check if bytes received is in error
    if (bytesRecv == -1) {
      std::cerr << "Houve um problema de conexão" << endl;
      break;
    }
    // check if the client has disconnected
    if (bytesRecv == 0) {
      std::cout << "O cliente se desconectou" << endl;
      break;
    }
    // display data stream that customer sent
    std::cout << "barca-client:  " << string(buf, 0, bytesRecv) << endl;
    // return to client bytes received
    send(clientSocket, buf, bytesRecv +1, 0);
  }
  close(clientSocket);
  return 0;
}