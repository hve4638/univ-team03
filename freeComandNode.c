#include "wish.h"

void freeCommandNode(CommandNode* node) {
    CommandNode* next;

    while(node != NULL) {
        next = node->next;
        
        free(node->command);
        free(node);
        node = next;
    }
}