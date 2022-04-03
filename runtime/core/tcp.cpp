#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

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
    cerr << "Não foi possível criar um socket";
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
  //assign hosts for small networks
  hint.sin_port = htons(54000);
  // set version 4 network address with any available ip to a link
  inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
  // check if the info link is bound to the socket
  if (bind(listening, AF_INET, (sockaddr*)&hint, sizeof(hint)) == -1) {
    cerr << "Não foi possível vincular ao IP/port";
    return -2;
  }
  // mark the socket for listening in
  if (listen(listening, SOMAXCONN) == -1) {
    cerr << "Não foi possível receber a conexão";
    return -3;
  }
  // accept a customer call
  sockaddr_in client;
  socklen_t clientSize = sizeof(client);
  char host[NI_MAXHOST];
  char svc[NI_MAXSERV];

  int clientSocket = accept(listening, (sockaddr*)&client, &clientSize)

  return 0;
}