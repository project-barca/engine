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
      char oldDir[bufferSize]; 
      // get the current directory, and store it
      if (!GetCurrentDirectory(bufferSize, oldDir)) {
        std::cerr << "Error ao tentar obter diretório atual" << GetLastError();
      }
      std::cout << "Diretório atual: " << oldDir << '\n';

      return oldDir;
    };
};

#endif
