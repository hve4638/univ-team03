#include "wish.h"

static int getBlankCount(CMD input) {
    int count = 0;
    for(int i = 0; input[i] != '\0'; i++) {
      if(input[i] == ' ') {
         count++;
      }
   }
   return count;
}

size_t splitCommand(CMD input, CMDArray *output) {
   int count = getBlankCount(input) + 1;
   CMDArray cmd = malloc(sizeof(CMD) * count);

   int index = 0;
   cmd[index++] = &(input[0]);
   for(int i = 0; input[i] != '\0'; i++) {
      if (input[i] == ' ') {
         if (input[i+1] != '\0') {
            cmd[index++] = &(input[i+1]);
         }
         input[i] = 0;
      }
   }
   
   *output = cmd;
   return count;
}

