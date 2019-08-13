#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

extern void makeWordList (char*);
extern char **getWordList ();
extern void compareFiles (char*, char*);
extern void freeWordList(char**);
/*I added a freeWordList function to make sure I free the malloc'ed arrays.
  Every time I call getWordList, I must call freeWordList*/


void printWordList (char *fileName){
  char **words;
  int i, numWords;

  makeWordList (fileName);

  words = (char**) getWordList ();
  numWords = getNumWords ();
  printf ("Words in file %s\n", fileName);
  for (i=0; i<numWords; i++) {
    printf ("  %s\n", words[i]);
  }
  freeWordList(words);
  //I called this because of the getWordList call in line 21.
}


int main (int argc, char **argv)
{
  printWordList ("ex2test1.txt");
  printWordList ("ex2test2.txt");
  printWordList ("ex2test3.txt");
  compareFiles ("ex2test2.txt", "ex2test3.txt");
}
