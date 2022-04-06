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
  listen(listening, SOMAXCONN);
  // wait for a connection
  sockaddr_in client;
  int clientSize = sizeof(client);
  SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
  // client's remote name
  char host[NI_MAXHOST];
  // service (i.e. port) the client is connect on
  char service[NI_MAXHOST];
  // clear the buffer
  ZeroMemory(host, NI_MAXHOST);
  ZeroMemory(service, NI_MAXHOST);
  
  if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0){
    cout << host << " connected on port " << service << endl;
  }else{
    inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
    cout << host << " conected on port " << ntohs(client.sin_port) << endl;
  }
  // close listening socket
  closesocket(listening);
  // loop for accept connection and resend message back to client
  char buf[4096];
  while (true) {
    ZeroMemory(buf, 4096);
    // wait for client to send data
    int bytesReceived = recv(clientSocket, buf, 4096, 0);
    if (bytesReceived == SOCKET_ERROR) {
      cerr << "Error recv()" << endl;
      break;
    }
    if (bytesReceived == 0) {
      cout << "Cliente desconectado" << endl;
      break;
    }
    // echo message back to client
    send(clientSocket, buf, bytesReceived + 1, 0);
  }
}