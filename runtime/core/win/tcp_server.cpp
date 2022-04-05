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

}