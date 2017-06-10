#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int comparisons = 0;

int frobcmp (char *a, char *b) {

  //count number of comparisons made
  comparisons++;
  
  //accepts two pointers to the beginning of char arrays
  //end of the char array indictaed by a space character
  char *arrA = a;
  char *arrB = b;

  int i= 0;
  int result = 0;
  while(arrA[i] != ' ' && arrB[i] != ' ') {

    int itemA = arrA[i] ^ 42;
    int itemB = arrB[i] ^ 42;

    if(itemA < itemB){
      result = itemA - itemB;
      return result;
    }
    else if(itemA > itemB){
      result = itemA - itemB;
      return result;
    }
    i++;
  }

  if(arrA[i] != ' ' && arrB[i] == ' '){
    return 1;
  }
  else if(arrA[i] == ' ' && arrB[i] != ' '){
    return -1;
  }
  else{
    return result;
  }
}

int compare(void const *x, void const *y){
  return frobcmp(*((char **)x), *((char **)y));
}

void sfrob() {

  //pointer for array of pointers
  char **strArr = (char **)malloc(10*sizeof(char *));

  //pointer to the buffer
  char *inputStrm;

  //current max size of the strArr array
  int currMaxWords = 10;
  
  //current max size of the inputstrm array
  int currMaxChars;

  int numCharsRead = 0;
  
  struct stat fileStats;
  stat(0, &fileStats);
  if(fileStats.st_size){
    //unknown size, dynamically allocate memory
    int successRead;
    currMaxChars = 4096;

    inputStrm = (char *)malloc(currMaxChars*sizeof(char));
    if(inputStrm == NULL){
      fprintf(stderr, "Error allocating memory 1");
      exit(1);
    }
    
    successRead = read(0, inputStrm, 4096);
    while(successRead != 0){
      //this means EOF, when 0 characters are successfully read
      numCharsRead += successRead;
      if(successRead < 4096 && successRead > 0){
	//done reading
	break;
      }
      else{
	//more to read, make buffer bigger
	//printf("current size: %d\n", currMaxChars);
	inputStrm = (char *)realloc(inputStrm, (currMaxChars + 4096)*sizeof(char));
	currMaxChars += 4096;
	if(inputStrm == NULL){
	  fprintf(stderr, "Error allocating memory 2");
	  exit(1);
	}
	successRead = read(0, inputStrm + numCharsRead, 4096);
      }
    }
  }
  else{
    //exact size known
    currMaxChars = fileStats.st_size;
    inputStrm = (char *)malloc(currMaxChars*sizeof(char));
    if(inputStrm == NULL){
      fprintf(stderr, "Error allocating memory 3");
      exit(1);
    }
    read(0, inputStrm, currMaxChars);
    numCharsRead = currMaxChars;
  }

  //connect the pointers in strArr to each word in inputStrm
  //allocate more space if need be
  int numWords = 0;
  int boolWordDone = 1;
  for(int iter = 0; iter < numCharsRead; iter++){
    if(numWords >= currMaxWords){
      //no more allocated space, free more
      strArr = (char **)realloc(strArr, (currMaxWords + 10)*sizeof(char *));

      currMaxWords += 10;
      //catch memory allocation error
      if(strArr == NULL){
	fprintf(stderr, "Error allocating memory 4");
	exit(1);
      }
    }
    if(boolWordDone){
      //previous word is done, current character is start of next word
      strArr[numWords] = &inputStrm[iter];
      //new word not "done" yet
      boolWordDone = 0;
    }
    if(inputStrm[iter] == ' '){
      //current word is done
      boolWordDone = 1;

      //word is completed, number of words increase
      numWords++;
    }
  }
  
  if(boolWordDone){
    //ended with a space!
  }
  else{
    //did not end with space, add trailing space
    if(numCharsRead >= currMaxChars){
      //no more allocated space, free just ONE more for the space char
      inputStrm = (char *)realloc(inputStrm, (currMaxChars + 1)*sizeof(char));
      currMaxChars += 1;
      
      //catch memory allocation error
      if(inputStrm == NULL){
	fprintf(stderr, "Error allocating memory 5");
	exit(1);
      }
    }
    inputStrm[numCharsRead] = ' ';
    //count the last word as complete, add to word count
    numWords++;
    // printf("number of words: %d", numWords);
  }

  qsort(strArr, numWords, sizeof(char *), compare);

  //printf("number of words: %d\n", numWords);
  //printf("number of characters : %d\n", numCharsRead);
  for(int i = 0; i < numWords; i++){
    //printf("i = %d\n", i);
    char *currArray = strArr[i];

    //print all consequtive characters until encounter space character
    //print space character, then finish
    int j = 0;
    while(currArray[j] != ' '){
      write(1, &currArray[j], 1);
      j++;
    }


    write(1, &currArray[j], 1);

  }


  
  //free all used memory!
  free(inputStrm);
  free(strArr);

  //printf("hello\n");  
  
  //print out number of comparisons made
  fprintf(stderr, "Comparisons: %d", comparisons);


  return;
}


int main(){
  sfrob();
  return 0;
}
