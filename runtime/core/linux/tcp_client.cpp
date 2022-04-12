#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main() {
  // create a socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    return -1;
  }
  // create a hint structure for the server we're connecting with
  int port = 5400;
  string ipAddr = "127.0.0.1";

  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(port);
  inet_pton(AF_INET, ipAddr.c_str(), &hint.sin_addr);
  // connect to the server on the socket
  int connRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
  if (connRes == -1) {
    return 1;
  }
  // while loop:
  char buf[4096];
  string userInput;

  do {
    // enter client lines of text
    cout << "barca> ";
    getline(cin, userInput);
    // send a buffer to the server
    int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
    // verify response
    if (sendRes == -1) {
      cout << "Não foi possível se comunicar com o servidor\r\n";
      continue;
    }
    // wait for response
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096, 0);

    // display response
    cout << "barca-server> " << string(buf, bytesReceived) << "\r\n";

  } while(true);
  // close the socket
  close(sock);
  
  return 0;
}