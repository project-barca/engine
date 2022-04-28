#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <windows.h>
#include <iostream>

class Directory {
  public:
    // GET CURRENT DIRECTORY
    string getCurrentPath() {
      const int bufferSize = MAX_PATH;
      // store the current directory  
      char actualDir[bufferSize]; 
      // get the current directory, and store it
      if (!GetCurrentDirectory(bufferSize, actualDir)) {
        std::cerr << "Error ao tentar obter diretório atual" << GetLastError();
      };
      std::cout << "Diretório atual: " << actualDir << '\n';

      return actualDir;
    };
    // SET NEW DIRECTORY
    string setCurrentPath(char path) {
      const char* newDir = R"(C:\\Barca)";
      if (!SetCurrentDirectory(newDir)) {
        std::cerr << "Error ao tentar definir diretório atual" << GetLastError();
      }
      std::cout << "Diretório Atual: " << newDir << '\n';

      return newDir;
    };

};

#endif
