#include <string.h>
#include "wish.h"
#define CHECK(X) printf("%s\n", X); fflush(stdout);

static size_t getBlankCount(char* input) {
    int count = 0;
    for(int i = 0; input[i] != '\0'; i++) {
      if(input[i] == ' ') {
         count++;
      }
   }
   return count;
}

size_t splitCommand(char* input, char*** output) {
   size_t count = getBlankCount(input) + 1;
   char** splitted = malloc(sizeof(char*) * count);

   int index = 0;
   splitted[index++] = input;

   char* pInput = input;
   for(int i = 0; *pInput != '\0'; pInput++) {
      if (pInput[0] == ' ') {
         if (pInput[1] != '\0') {
            splitted[index++] = pInput+1;
         }
         *pInput = '\0';
      }
   }
   
   *output = splitted;
   return count;
}

