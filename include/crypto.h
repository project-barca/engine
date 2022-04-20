#ifndef ENCRYPTANDDECRYPT_H
#define ENCRYPTANDDECRYPT_H

#include <bits/stdc++.h>

void encryptAndDecryptXOR(char text[]) {
  char xorKey = 'P';
  int len = strlen(text);
  for (int i = 0; i < len; i++) {
    text[i] = text[i] ^ xorKey;
    printf("%c",text[i]);
  }
};

class Cypher {
  public:
    // VIGENERE CIPHER
    string generateKeyVigenere(string str, string key) {
      int x = str.size();

      for (int i = 0; ; i++) {
        if (x == i)
          i = 0;
        if (key.size() == str.size())
          break;
        key.push_back(key[i]);
      }
      return key;
    };

    string cipherTextVigenere(string str, string key) {
      string cipher_text;
      for (int i = 0; i < str.size(); i++) {
        // converting in range 0-25
        char x = (str[i] + key[i]) %26;
        // convert into alphabets(ASCII)
        x += 'A';
        cipher_text.push_back(x);
      }
      return cipher_text;
    };

    string originalTextVigenere(string cipher_text, string key){
      string orig_text;
  
      for (int i = 0 ; i < cipher_text.size(); i++) {
        // converting in range 0-25
        char x = (cipher_text[i] - key[i] + 26) %26;
        // convert into alphabets(ASCII)
        x += 'A';
        orig_text.push_back(x);
      }
      return orig_text;
    };
    // VIGENERE CIPHER

};

#endif
