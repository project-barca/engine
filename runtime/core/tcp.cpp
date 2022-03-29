#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main() {
  // create a socket
  int listening = socket(AF_INET, SOCK_STREAM, 0);
  // check if socket was created successfully
  if (listening == -1) {
    cerr << "Não foi possível criar um socket";
  }
  // bind the socket to a IP/PORT
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  //assign hosts for small networks
  hint.sin_port = htons(54000);
  // set version 4 network address with any available ip to a link
  inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
  // check if the info link is bound to the socket
  if (bind(listening, AF_INET, &hint, sizeof(hint)) == -1) {
    cerr << "Não foi possível vincular ao IP/port";
    return -2;
  }
  // mark the socket for listening in
  if (listen(listening, SOMAXCONN) == -1) {
    cerr << "Não foi possível receber a conexão";
    return -3;
  }
  
  return 0;
}