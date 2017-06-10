#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
  //argc = number of arguments
  if(argc != 3){
    printf("%s\n", "Wrong number of arguments");
    exit(1);
  }

  //argc = array of arguments (c strings)
  char *from = argv[1];
  char *to = argv[2];

  //check that arguments are of the same length
  if(strlen(from) != strlen(to)){
    printf("%s\n", "Arguments must be of the same length!");
    exit(1);
  }

  //check that first argument has no repeats
  int fromLen = strlen(from);
  for(int i = 0; i < fromLen; i++){
    for(int j = 0; j < fromLen; j++){
      if(i == j){
	continue;
      }
      if(from[i] == from[j]){
	printf("%s\n", "First argument cannot have duplicates!");
	exit(1);
      }
    }
  }

  //arguments are valid, start translitration
  //use read and write instead of getchar and putchar
  char c[1]; //only need to read one character at a time
  while(read(0, c, 1) > 0){
    //if read returned -1 or 0,it would indicate an error reading file or EOF
    int translated = 0; //0 for false, 1 for true
    for(int i = 0; i < fromLen; i++){
      if(c[0] == from[i]){
	write(1, &to[i], 1);
	translated = 1;
	break;
      }
    }
    if(translated){
      continue;
    }
    else{
      write(1, &c, 1);
    }
  }
  printf("\n");

  return 0;
  
}
