#include <stdio.h>
#include <stdlib.h>
#include "wish.h"

static int getBlankCount(CMD input);
int splitCommand(CMD input, CMDArray output, size_t *capatity) {
    int count = getBlankCount(input);
    CMDArray cmdArray = malloc(sizeof(CMDArray) * count);

    CMD position = input;
    for(int i = 0; input[i] != '\0'; i++) {
      if (input[i] == ' ') {
         input[i] = 0;
      }
   }
   return count;
}

int getBlankCount(CMD input) {
    int count = 0;
    for(int i = 0; input[i] != '\0'; i++) {
      if(input[i] == ' ') {
         count++;
      }
   }
   return count;
}