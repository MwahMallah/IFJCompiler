#include "scanner.h"
#include <stdio.h>

void readInput() {
    int ch;

    while ((ch = getchar()) != EOF) {
        printf("You entered: %c\n", ch);
    }
    
}