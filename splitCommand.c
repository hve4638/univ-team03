#include <string.h>
#include "wish.h"

static char** splitBuffer;
static size_t splitBufferSize;
static size_t splitIndex;

static void initBuffer(size_t size) {
   splitBufferSize = size;
   splitBuffer = (char**)malloc(sizeof(char*) * splitBufferSize);
   splitIndex = 0;
}

static void resizeBuffer(size_t size) {
   splitBufferSize = size;
   splitBuffer = (char**)realloc(splitBuffer, sizeof(char*) * size);
}

static void freeBuffer() {
   if (splitBuffer != NULL) {
      free(splitBuffer);
      splitBuffer = NULL;
   }
}

static void addToBuffer(char* str) {
   splitBuffer[splitIndex++] = str;
}

static int strrp(char** input, char* word) {
   size_t length = 0;
   while(word[length] != '\0') length++;

   if (strncmp(*input, word, length) == 0) {
      for(size_t i = 0; i < length; i++) {
         (*input)[i] = '\0';
      }
      *input += length - 1;
      return 1;
   } else {
      return 0;
   }
}

size_t splitCommand(char* input, char*** output) {
   initBuffer(128);

   int isWord = 0;
   int index = 0;
   for(char *p = input; *p != '\0'; p++) {
      if (strrp(&p, "2>")) { addToBuffer("2>"); isWord = 0; }
      else if (strrp(&p, ">"))  { addToBuffer(">"); isWord = 0; }
      else if (strrp(&p, "&"))  { addToBuffer("&"); isWord = 0; }
      else if (strrp(&p, " ")) { isWord = 0; }
      else if (strrp(&p, "\t") || strrp(&p, "\n")) { }
      else if (!isWord) { addToBuffer(p); isWord = 1; }
   }
   *output = splitBuffer;
   return splitIndex;
}
