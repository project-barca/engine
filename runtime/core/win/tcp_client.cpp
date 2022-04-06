#include <iostream>
#include <string>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void main() {
  // IP Address of the server
  string ipAddr = "127.0.0.1";
  // listening port on the server  
  int port = 54000;
  // initialize winSock
  WSAData data;
  WORD vr = MAKEWORD(2, 2);
  int wsResult = WSAStartup(vr, &data);
  if (wsResult != 0) {
    cerr << "Não foi possível iniciar o Winsock" << wsResult << endl;
    return;
  }
  // create a socket
  SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
  // check if socket is valid
  if (sock == INVALID_SOCKET) {
    cerr << "Não foi possível criar o socket" << WSAGetLastError() << endl;
    WSACleanup();
    return;
  }
  // hint structure
  sockaddr_in hint;
  hint.sin_family == AF_INET;
  hint.sin_port = htons(port);
  inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
  // connect to server
  int connRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
  if (connResult == SOCKET_ERROR) {
    cerr << "Não foi possível conectar ao servidor" << WSAGetLastError() << endl;
    closesocket(sock);
    WSACleanup();
    return;
  }
  // while loop to send and receive data
  char buf[4096];
  string userInput;

  do {
    // prompt the user for some text
    cout << "barca> ";
    getline(cin, userInput);
    // make sure the user has typed in something
    if (userInput.size() > 0) {
      // send the text
      int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
      if (sendResult != SOCKET_ERROR) {
        // wait for response
        ZeroMemory(buf, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived > 0) {
          // response to console
          cout << "server> " << string(buf, 0, bytesReceived) << endl;
        }
      }
    }
  } while (userInput.size() > 0);
  // close down everything
  closesocket(sock);
  WSACleanup();
}