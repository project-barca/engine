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
// encrypt a file
int encryptFile(const std::string fileName) {
  char ch;
  fstream fps, fpt;
  // open a file in read mode
  fps.open(fileName, fstream::in);
  if(!fps){
    cout << "\nError ao tentar encontrar o arquivo";
    return 0;
  }
  // open a file in write mode
  fpt.open("tmp.txt", fstream::out);
  if(!fpt) {
    cout << "\nOcorreu um erro ao tentar abrir o arquivo tmp";
    return 0;
  }
  // read file character by character
  while(fps>>std::noskipws>>ch) {
    ch = ch+100;
    fpt<<ch;
  }
  fps.close();
  fpt.close();
  fps.open(fileName, fstream::out);
  if(!fps) {
    cout<<"\nErro ao tentar abrir o arquivo";
    return 0;
  }
  fpt.open("tmp.txt", fstream::in);
  if(!fpt) {
    cout<<"\nError ao tentar abrir arquivo temporario";
    return 0;
  }
  while(fpt >> std::noskipws >> ch)
      fps<<ch;
  fps.close();
  fpt.close();
  cout << "\n'" << fileName << "' Criptografado!";
  cout << endl;

  return EXIT_SUCCESS;
}
// decrypt a file with authentication
int decryptFile(const std::string fileName, const std::string keyName) {
  char ch;
  fstream fps, fpt;

  fps.open(fileName, fstream::out);
  if(!fps) {
    cout<<"\nError ao tentar abrir arquivo";
    return 0;
  }
  fpt.open(keyName, fstream::in);
  if(!fpt) {
    cout<<"\nOcorreu algum erro ao tentar abrir o arquivo chave de descriptografia";
    return 0;
  }
  while(fpt>>std::noskipws>>ch) {
    ch = ch-100;
    fps<<ch;
  }
  fps.close();
  fpt.close();
  cout<<"\n'"<< fileName <<"' Descriptografado";
  cout<<endl;

  return EXIT_SUCCESS;
}

#endif
