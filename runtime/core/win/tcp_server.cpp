#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "WS2_32.lib")

using namespace std;

void main() {
  // initialize WinSock
  WSADATA wsData;
  WORD vr = MAKEWORD(2, 2);

  int WSOK = WSAStartup(vr, &WSData);
  if (WSOK != 0) {
    cerr << "Não foi possível inicializar o Winsock" << endl;
  }
  // create a socket
  SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
  if (listening == INVALID_SOCKET) {
    cerr << "Não foi possível criar um socket" << endl;
    return;
  }
  // bind the ip address and port to a socket
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(54000);
  hint.sin_addr.S_un.S_addr = INADDR_ANY;

  bind(listening, (sockaddr*)&hint, sizeof(hint));

}