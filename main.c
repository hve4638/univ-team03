#include "wish.h"

int main(int argc, char** argv) {
    FILE* file;

    if (argc == 1) {
        file = stdin;
    }
    else if (argc == 2) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            Error();
            exit(1);
        }
    } else {
        Error();
        exit(1);
    }

    wish(file);
    exit(0);
}