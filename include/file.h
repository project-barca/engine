#ifndef NEWFILE_H
#define NEWFILE_H

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using std::cout; using std::ofstream;
using std::endl; using std::string;
using std::cerr; using std::fstream;

// create a file with content
int newFile(const std::string fileName, const std::string content) {
  string text(content);
  string filename2(fileName);
  fstream outfile;

  outfile.open(filename2, std::ios_base::app);
  if (!outfile.is_open()) {
    cerr << "Falha ao tentar abrir o arquivo" << filename2 << '\n';
  } else {
    outfile.write(text.data(), text.size());
    cerr << "Arquivo adicionado!" << endl;
  }

  return EXIT_SUCCESS;
}
// remove a file
int rmFile(const std::string fileName) {
  const char* fil = fileName.c_str();
  int fileDeleted = remove(fil);
  if (fileDeleted == 0) {
    cout << "Arquivo removido";
  } else {
    cerr << "Arquivo não encontrado";
    return -1;
  }
  return EXIT_SUCCESS;
}
// read a file
int rdFile(const std::string fileName) {
  const char* fil = fileName.c_str();
  std::string line;
  std::ifstream file(fil);
  if(file.is_open()) {
    while(getline(file, line)) {
      std::cout << line << '\n';
    }
    file.close();
  }
  else std::cout << "Não foi possível encontrar o arquivo: " << fileName;
  return EXIT_SUCCESS;
}

#endif
