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
  std::string paths[12] = {
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
    "C:\\Barca\\1.0\\client\\bin",
    "C:\\Barca\\1.0\\client\\lib",
  };
  // generating folder structure
  for(int i = 0; i < 12; i++){
    if(!CreateDirectory(paths[i].c_str(), NULL)) {
      fprintf(stderr, "ERRO: %d\n", GetLastError());
    }
  }
  // specifying files
  std::string files[13] = {
    "C:\\Barca\\bin\\serial.txt",
    "C:\\Barca\\uninstall.c",
    "C:\\Barca\\1.0\\LICENSE.txt",
    "C:\\Barca\\1.0\\releases-barca.html",
    "C:\\Barca\\1.0\\bin\\barca",
    "C:\\Barca\\1.0\\cmd\\ssh-agent.cmd",
    "C:\\Barca\\1.0\\installer\\server\\start.cpp",
    "C:\\Barca\\1.0\\installer\\server\\adduser.exe",
    "C:\\Barca\\1.0\\installer\\server\\locales.exe",
    "C:\\Barca\\1.0\\bin\\barca-shell.exe",
    "C:\\Barca\\1.0\\bin\\barca.exe",
    "C:\\Barca\\1.0\\bin\\barca.c",
    "C:\\Barca\\uninstall.c",
  };
  // generating files structure
  for(int i = 0; i < 13; i++){
    file = fopen(files[i].c_str(), "w+");
    fputs("----------------------------------------------------------\n", file);
    fputs("                                                          \n", file);
    fputs("                                                          \n", file);
    fputs("               Copyright © Project Barca                  \n", file);
    fputs("                                                          \n", file);
    fputs("                                                          \n", file);
    fputs("  Email: annibalhsouza@gmail.com    Author: Aníbal Souza  \n", file);
    fputs("----------------------------------------------------------\n\n\n", file);
  }
}
