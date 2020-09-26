#include <stdio.h>
#include "newline.h"

int newline(char line[], int limit) {
    char c;
    int size = 0;

    while (size < (limit-1) && (c = getchar()) != EOF && c != '\n') {
        line[size] = c;
        ++size;
    }

    if (c == '\n') {
        line[size] = '\n';
        size++;
    } 
    
    line[size] = '\0';
    return size;
}