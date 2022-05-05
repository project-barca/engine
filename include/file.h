#ifndef NEWFILE_H
#define NEWFILE_H

#include <iostream>
#include <fstream>
#include <Windows.h>

using std::cout; using std::ofstream;
using std::endl; using std::string;
using std::cerr; using std::fstream;

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

int rmFile(const std::string fileName) {
  const char* fil = fileName.c_str();
  int fileDeleted = remove(fil);
  if (fileDeleted == 0) {
    cout << "Arquivo removido";
  } else {
    cerr << "Arquivo não encontrado";
    return -1;
  }
  return 0;
}

#endif
