#include <stdio.h>
#include <stdlib.h>

int frobcmp (char *a, char *b) {
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
  //pointer to an array of (10 to begin with) pointers
  char **strArr = (char **)malloc(10*sizeof(char *));

  //pointer to the continuous stream of characters to be read in
  char *inputStrm = (char *)malloc(200*sizeof(char));

  //current max size of the inputStrm array
  int currMaxChars = 200;

  //current max size of the strArr array
  int currMaxWords = 10;
  
  //catch memory allocation error for strArr
  if(strArr == NULL){
    fprintf(stderr, "Error allocating memory");
    exit(1);
  }

  //catch memory allocation error for inputStrm
  if(inputStrm == NULL){
    fprintf(stderr, "Error allocating memory");
    exit(1);
  }

  //read all input characters into inputStrm
  int numCharsRead = 0;
  while(!feof(stdin)){
    if(numCharsRead >= currMaxChars){
      //no more allocated space, free more
      inputStrm = (char *)realloc(inputStrm, (currMaxChars + 200)*sizeof(char));
      currMaxChars += 200;
      
      //catch memory allocation error
      if(inputStrm == NULL){
	fprintf(stderr, "Error allocating memory");
	exit(1);
      }
    }

    //read next character into inputStrm
    char temp = getc(stdin);
    inputStrm[numCharsRead] = temp;

    //increment counter (which also functions as size of array)
    numCharsRead++;
  }

  //connect the pointers in strArr to each word in inputStrm
  //allocate more space if need be
  int numWords = 0;
  int boolWordDone = 1;
  for(int iter = 0; iter < numCharsRead; iter++){
    if(numWords >= currMaxWords){
      //no more allocated space, free more
      strArr = (char **)realloc(inputStrm, (currMaxWords + 10)*sizeof(char *));

      currMaxWords += 10;
      //catch memory allocation error
      if(strArr == NULL){
	fprintf(stderr, "Error allocating memory");
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
	fprintf(stderr, "Error allocating memory");
	exit(1);
      }
    }
    inputStrm[numCharsRead] = ' ';
    //count the last word as complete, add to word count
    numWords++;
  }

  qsort(strArr, numWords, sizeof(char *), compare);

  for(int i = 0; i < numWords; i++){
    char *currArray = strArr[i];

    //print all consequtive characters until encounter space character
    //print space character, then finish
    int j = 0;
    while(currArray[j] != ' '){
      putchar(currArray[j]);
      j++;
    }
    putchar(currArray[j]);
  }

  //free all used memory!
  free(inputStrm);
  free(strArr);

  return;
}


int main(){
  sfrob();
  return 0;
}
