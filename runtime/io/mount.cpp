#define _UNIX03_SOURCE
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <dirent.h>
#include <dir.h>

using namespace std;

FILE *file;

void mountDirEngine() {
  char bwcAdd[256];
  // take the value of the userprofile variable and store it in the env array
  GetEnvironmentVariable("userprofile", bwcAdd, sizeof(bwcAdd));
  // concatenates
  strcat(bwcAdd,"\\.bwc");
  // create Barca Web Cloud directory
  mkdir(bwcAdd);
  std::string pathsBWC[10] = {
    strcat(bwcAdd,"\\.bwc\\license.txt"), 
    strcat(bwcAdd,"\\.bwc\\cache"), 
    strcat(bwcAdd,"\\.bwc\\cache\\logs.txt"), 
    strcat(bwcAdd,"\\.bwc\\cache\\profile.json"), 
    strcat(bwcAdd,"\\.bwc\\cache\\settings.json"), 
    strcat(bwcAdd,"\\.bwc\\cache\\settings.toml"), 
    strcat(bwcAdd,"\\.bwc\\bin\\barca-cloud.exe"),
    strcat(bwcAdd,"\\.bwc\\bin\\uninstall.exe"),
    strcat(bwcAdd,"\\.bwc\\bin\\bwc-cli.exe"),
    strcat(bwcAdd,"\\.bwc\\lib\\barca.cloud.api"),
  };
  // generating folder structure
  for(int y = 0; y < 10; y++){
    if(!CreateDirectory(pathsBWC[y].c_str(), NULL)) {
      fprintf(stderr, "ERRO: %d\n", GetLastError());
    }
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
}

int main() {
  mountDirEngine();
  return 0;
}