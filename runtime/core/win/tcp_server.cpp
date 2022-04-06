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
}