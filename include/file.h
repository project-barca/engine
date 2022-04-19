#ifndef NEWFILE_H
#define NEWFILE_H

#include <iostream>
#include <fstream>
#include <Windows.h>
#include "file.h"

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

#endif
