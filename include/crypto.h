#ifndef ENCRYPTANDDECRYPT_H
#define ENCRYPTANDDECRYPT_H

void encryptAndDecrypt(char text[]) {
  char xorKey = 'P';
  int len = strlen(text);
  for (int i = 0; i < len; i++) {
    text[i] = text[i] ^ xorKey;
    printf("%c",text[i]);
  }
}

#endif
