#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char letterArray[100];
int letterArrLength;
int numWords;
/*I decided to make an array that stores all of the chars, spaces and newlines
  included. letterArrLength stores the number of all chars in the array*/

void makeWordList (char *fileName){
  /*makeWordList does two things: initializes the array with all 0's, and
  copies all of the characters from the file, to the letterArray*/
  int j;
  for (j=0; j< sizeof(letterArray)/sizeof(int); j++){
    letterArray[j] = 0;
    //Here, all the elements in letterArray are set to zero.
  }
  FILE *inputFile = fopen(fileName, "r");
  char ch;
  int i = 0;
  do {
    ch = fgetc (inputFile);
    if(ch != EOF){
      letterArray[i] = ch;
      i++;
    }
  } while (ch != EOF);
  /*In the above loop, all chars, including spaces and newlines, are places in
   the array*/
  letterArrLength = i;
//letterArrLength is set to the last value of i which is the size of the array
  fclose (inputFile);
}

/*
void printWordList(char** wordList){
//printWordList was used as a tool to print out the wordLists for testing
  int i=0;
  int j=0;

  while(wordList[i][j] != '\0'){
    while(wordList[i][j] != '\0'){
      printf("%c", wordList[i][j]);
      j++;
    }
    printf(" %c", wordList[i][j+1] );
    j = 0;
    i++;
    printf("\n");
  }
}*/


char **getWordList (){
  /*getWordList uses malloc to allocate memory for the 2D array known as the
    words. It also places every char from letterArray into the 2D array*/
  char** words = (char**)malloc(sizeof(char*) * 10);
  int j, i;
  for(j=0; j<10; j++){
    words[j] = (char*)malloc(sizeof(char*) * 10);
  }
  //The memory is allocated. I decided to have a 10x10 buffer.

  for(i=0; i<10; i++){
    for(j=0; j<10; j++){
      words[i][j] = '\0';
    }
  }
  /*All of the elements are set to \0 to make it easy for later functions to
    know when the string ends on each word*/

  i = 0;
  j = 0;
  int n = 0;
  int lineNumber = '1';
  while(n<letterArrLength){
    if(letterArray[n] == ' '){
      words[i][j+1] = lineNumber;
      /*The lineNumber is stored on the same row as the word itsself. However,
        there is a \0 separating the word from the lineNumber. In the array it
        looks like this: 'n', 'a', 'h', '1', '\0', '3', '\0', '\0', ...*/
      i++;
      j=0;
    } else if (letterArray[n] == '\n') {
      words[i][j+1] = (char)( (int)lineNumber++ );
      //The lineNumber increments every time the array has a newline.
      i++;
      j=0;
    } else {
      words[i][j] = letterArray[n];
      j++;
    }
    n++;
  }
  numWords = i;
  /*i equals to the number of rows in the 2D array. Therefore it is also
    equivalent to the number of words. It is stored in the global variable.*/
  return words;
}

int getNumWords (){
  return numWords;
  //returns from the global variable.
}

void freeWordList(char** wordList){
  //Must free every time getWordList is called.
  int i;
  for(i=0; i<10; i++){
    free(wordList[i]);
  }
  free(wordList);
}

void compareFiles (char *fileName1, char* fileName2)
{
  char** wordList1;
  char** wordList2;

  makeWordList(fileName1);
  wordList1 = getWordList();
  int wordList1len = getNumWords();

  makeWordList(fileName2);
  wordList2 = getWordList();
  int wordList2len = getNumWords();

  int size;
  if(wordList1len > wordList2len){
    size = wordList1len;
  } else {
    size = wordList2len;
  }
  //The size is the number of words in the largest list.

  int i;
  char* word1;
  char* word2;
  char lineNumber1;
  char lineNumber2;
  for(i=0; i<size; i++){
  /*This for loop compares every word in the lists, determines if they are
    the same, different, or if a list is exhuasted*/
    printf("Word #%d: ", i);
    word1 = wordList1[i];
    lineNumber1 = wordList1[i][strlen(word1)+1];
    word2 = wordList2[i];
    lineNumber2 = wordList2[i][strlen(word2)+1];
    /*Since every lineNumber is stored with the word, I can collect it at the
      start of the loop for use in the output.*/
    if( strcmp(word1, word2) == 0){
      printf("same in each file");
      printf("\nOn Line %c In File %s: %s\n",
                lineNumber1, fileName1, wordList1[i]);
      printf("On Line %c In File %s: %s\n",
              lineNumber2, fileName2, wordList2[i]);
      /*This if statement shows if the words are the same.*/
    } else if (i>wordList1len-1 || i>wordList2len-1) {
      if(i>wordList1len-1){
        printf("\nFile %s Exhuasted", fileName1);
        printf("\nOn Line %c In File %s: %s\n",
                  lineNumber2, fileName2, wordList2[i]);
      } else {
        printf("\nOn Line %c In File %s: %s\n",
                  lineNumber1, fileName1, wordList1[i]);
        printf("File %s Exhuasted\n", fileName2);
      }
      /*If either of the lists are past their lengths, then the output will
        say so.*/
    } else {
      printf("\nOn Line %c In File %s: %s\n",
                lineNumber1, fileName1, wordList1[i]);
      printf("On Line %c In File %s: %s\n",
              lineNumber2, fileName2, wordList2[i]);
    }
    /*The lineNumber is shown for each word in the list.*/
  }
  freeWordList(wordList1);
  freeWordList(wordList2);
}
