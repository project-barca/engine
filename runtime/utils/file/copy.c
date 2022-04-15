#include<stdio.h>
#include<conio.h>

int main() {
  char ch;
  FILE *fs, *ft;

  fs = fopen("..\\..\\core\\win\\server.cpp", "r");
  if(fs == NULL)
  {
    printf("\nError in Opening the file, %s", "server.cpp");
    getch();
    return 0;
  }

  ft = fopen("C:\\Barca\\1.0\\installer\\server\\tcp_server.cpp", "w");
  if(ft == NULL)
  {
    printf("\nError in Opening the file, %s", "tcp_server.cpp");
    getch();
    return 0;
  }
  ch = fgetc(fs);
  while(ch != EOF)
  {
    fputc(ch, ft);
    ch = fgetc(fs);
  }
  fclose(fs);
  fclose(ft);
  getch();
  return 0;
}