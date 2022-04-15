#define _UNIX03_SOURCE
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

FILE *file;

void mountDirEngine() {
  // specifying paths
  std::string paths[3] = {
    "C:\\Barca", 
    "C:\\Barca\\1.0", 
    "C:\\Barca\\1.0\\log",
    "C:\\Barca\\1.0\\bin",
    "C:\\Barca\\1.0\\lib",
    "C:\\Barca\\1.0\\data",
    "C:\\Barca\\1.0\\locales",
    "C:\\Barca\\1.0\\client",
    "C:\\Barca\\1.0\\installer",
    "C:\\Barca\\1.0\\installer\\server",
    "C:\\Barca\\1.0\\client\\bin"
    "C:\\Barca\\1.0\\client\\lib"
  };
  // generating folder structure
  for(int i = 0; i < 3; i++){
    if(!CreateDirectory(paths[i].c_str(), NULL)) {
      fprintf(stderr, "ERRO: %d\n", GetLastError());
    }
  }

}
