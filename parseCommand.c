#include <stdio.h>
#include "wish.h"


/*
0. 상태 (cmd, arg)
1. 순회하며 하나씩 확인
2. cmd상태 : 단어가 있는지 확인
3. arg상태 : 
*/

CommandNode* parseCommand(char** array, size_t arraySize, size_t* outputLength) {
   CommandNode* firstNode = NULL;
   CommandNode* node = firstNode;
   
   int parellelWordCount = 0;
   int index = 0;

   for(int i = 0; i < arraySize; i++) {
      if (strcmp(array[i], "&") == 0) parellelWordCount++;
      else if (strcmp(array[i], ">") == 0) {

      }


   }
}