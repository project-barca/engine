#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <windows.h>
#include <iostream>
#include <dirent.h>

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
    string setCurrentPath(std::string path) {
      const char* newDir = R"(C:\\Barca\\1.0\\data)";

      if (!SetCurrentDirectory(newDir)) {
        std::cerr << "Error ao tentar definir diretório atual" << GetLastError();
      }
      std::cout << "Diretório Atual: " << newDir << '\n';

      return newDir;
    };
    // LIST FOLDERS & FILES IN DIRECTORY
    int listContent(std::string path) {
      const char* newPath = path.c_str();
      struct dirent *d;
      DIR *dr;
      dr = opendir(newPath);
      if(dr!=NULL) {
        for(d=readdir(dr); d!=NULL; d=readdir(dr)) {
          cout<<d->d_name<<endl;
        }
        closedir(dr);
      }
      else
        cout<<"\nError ao tentar exibir diretório";
      cout<<endl;
      return 0;
    }
};

#endif
