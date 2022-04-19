#define _UNIX03_SOURCE
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <dirent.h>
#include <dir.h>

#include "../../include/file.h"

using namespace std;

FILE *file;
int newFile(); 

void mountDirEngine() {
  char bwcAdd[256];
  // take the value of the userprofile variable and store it in the env array
  GetEnvironmentVariable("userprofile", bwcAdd, sizeof(bwcAdd));
  // concatenates
  strcat(bwcAdd,"\\.bwc");
  // create Barca Web Cloud directory
  mkdir(bwcAdd);
  // specifying paths to barca engine
  std::string pathsBWC[3] = {
    "\\.bwc\\cache",
    "\\.bwc\\bin",
    "\\.bwc\\lib",
  };
  // generating folder structure .bwc
  for(int y = 0; y < 3; y++){
    memset(bwcAdd, 0, sizeof(bwcAdd));
    GetEnvironmentVariable("userprofile", bwcAdd, sizeof(bwcAdd));
    strcat(bwcAdd, pathsBWC[y].c_str());
    mkdir(bwcAdd);
  };
  // specifying paths to barca engine
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
  system("pause");
}

int main() {
  mountDirEngine();
  return 0;
}