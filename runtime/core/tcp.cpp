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
  inet_pton(); // define loopback localhost 127.0.0.1

  return 0;
}