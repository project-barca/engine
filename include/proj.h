#ifndef PROJ_H
#define PROJ_H
#include <windows.h>
#include <iostream>
#include "directory.h"
#include <future>

class Proj {
  public:
    // backUp your projects, files and folders
    int backUp(char* dir, int (*func)(std::string, std::string)) {
      const char* newDir = R"(C:\\Barca\\1.0\\data)";
      Directory directory;
      std::cout << directory.setCurrentPath(newDir) << '\n';
      // call the function setBackUp asynchronously to check whether the number is prime or not:
      std::future<int> setBackUp = std::async (
        func, "./proj.backup.bat", 
        "@echo off\n\nrem for each file in your folder\nfor %%a in (\".\\*\") do (\n  rem check if the file has an extension and if it is not our script\n  if \"%%~xa\" NEQ \"\" if \"%%~dpxa\" NEQ \"%~dpx0\" (\n    rem check if extension folder exists, if not it is created\n    if not exist \"%%~xa\" mkdir \"%%~xa\"\n    rem move the file to directory\n    move \"%%a\" \"%%~dpa%%~xa\"\n  )\n)");
      setBackUp.get();

      return EXIT_SUCCESS;
    };
};

#endif
