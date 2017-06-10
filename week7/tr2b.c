#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){
  //argc = number of arguments
  if(argc != 3){
    printf("%s\n", "Wrong number of arguments");
    exit(1);
  }

  //argv = array of arguments (c strings)
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

  //arguments are valid, start transliteration
  int c;
  while((c = getchar()) != EOF){
    int translated = 0; //0 for false, 1 for true
    for(int i = 0; i < fromLen; i++){
      if(c == from[i]){
	putchar(to[i]);
	translated = 1;
	break;
      }
    }
    if(translated){
      continue;
    }
    else{
      putchar(c);
    }
  }
  printf("\n");

  return 0;
  
}
