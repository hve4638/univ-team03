#include <stdio.h>
#include "wish.h"

static inline int strIsEquals(const char* x, const char* y) {
   return (strcmp(x, y) == 0);
}

static Command* parseOneCommand(char*** pCmd, char** pCmdEnd) {
   Command* cmd = (Command*)malloc(sizeof(Command));
   cmd->cmd = **pCmd;
   cmd->args = (const char**)(*pCmd + 1);

   size_t count = 0;
   for(;++(*pCmd) < pCmdEnd; count++) {
      char* ch = **pCmd;
      if (strIsEquals(ch, "&") || strIsEquals(ch, ">")) {
         (*pCmd)--;
         break;
      }
   }

   cmd->argc = count;
   if (count == 0) cmd->args = NULL;

   return cmd;
}

CommandNode* parseCommand(char** array, size_t arraySize, size_t* outputLength) {
   CommandNode initNode;
   CommandNode* lastNode = &initNode;
   CommandNode* node = NULL;
   
   initNode.next = NULL;

   char** pCmdBegin = array;
   char** pCmdEnd = array+arraySize;
   for(char** pCmd = pCmdBegin; pCmd < pCmdEnd; pCmd++) {
      if (strIsEquals(*pCmd, "&")) {
         if (node == NULL) {
            return NULL;
         } else {
            node = NULL;
         }
      } else if (strIsEquals(*pCmd, ">")) {
         if (node == NULL) return NULL;
         else if (node->command->redirectTo != NULL) return NULL;
         else if ((pCmd+1) >= pCmdEnd) return NULL;
         else {
            node->command->redirectTo = *(++pCmd);
         }
      } else {
         node = malloc(sizeof(CommandNode));
         lastNode->next = node;
         lastNode = node;

         Command* cmd = parseOneCommand(&pCmd, pCmdEnd);
         node->command = cmd;
         
         printf("cmd: '%s' ", cmd->cmd);
         printf("argc: %ld\n", cmd->argc);
         printf("argv: ");
         for (size_t i = 0; i<cmd->argc; i++) {
            printf("%s, ", cmd->args[i]);
         }
         printf("\n");

      }
   }

   return initNode.next;
}