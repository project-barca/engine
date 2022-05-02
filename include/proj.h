#ifndef PROJ_H
#define PROJ_H
#include <windows.h>
#include <iostream>
// #include "file.h"
#include "directory.h"
#include <future>

class Proj {
  public:
    // ORGANIZE FILES IN SPECIFIC PROJECT FOLDER
    int organizeFiles(char* dir, int (*func)(std::string, std::string)) {
      const char* ex = R"(C:\\Barca)";
      Directory directory;
      // std::cout << directory.getCurrentPath() << '\n';
      std::cout << directory.setCurrentPath(ex) << '\n';
      
      // call the function fnprime() asynchronously to check whether the number is prime or not:
      // std::future<string> setDir = std::async (directory.setCurrentPath, ex);
      // setDir.get();
      std::string s = directory.setCurrentPath(ex);
      char ch = './barca.proj.bat';

      s.push_back(ch);
      std::cout << s;


      std::cout << "Organizando arquivos. . .\n";
    
          
      // concatenates
      // strcat(dir,"\\barca.proj.bat");
      

      func("./barca.proj.bat", "@echo off\n\ncd \"C:\\Program Files\\Microsoft\"\nstart barca.exe");



      return EXIT_SUCCESS;
    };
};

#endif
