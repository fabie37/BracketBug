#include <stdio.h>
#include "brackets.h"

#define MAXCHARS 1000
#define numb_brackets 3

const char bracket_string[] = "()[]{}";
char history[numb_brackets][MAXCHARS];
int  history_pointer[numb_brackets];
int  not_opened_history[MAXCHARS];
int  not_opened_pointer = 0;


void putbracket(int ln, int type) {
    history[type][history_pointer[type]++] = ln;
}

void removebracket(int ln, int type) {
    if (history_pointer[type] == 0) {
        not_opened_history[not_opened_pointer++] = ln;
    } else {
        history[type][--history_pointer[type]] = 0;
    }   
}

int isopenbracket(char c) {
    char b;
    for (int i=0; ((b=bracket_string[i]) != '\0'); i++) {
        if (c==b) {
            /* Return history position for bracket type if bracket is a open bracket */
            return ((i%2) != 0) ? -1 : i/2;  
        }
    }
    return -1;
}

int isclosebracket(char c) {
    char b;
    for (int i=0; ((b=bracket_string[i]) != '\0'); i++) {
        if (c==b) {
            /* Return history position for bracket type if bracket is a close bracket */
            return ((i%2) == 0) ? -1 : (i-1)/2;  
        }
    }
    return -1;
}

int str_len(char s[]) {
    for (int i=0; s[i] != '\0'; i++)
    return i+1;
}

void printerrors() {
     for (int i=0; i<numb_brackets; i++) {
        for (int x=0; x<MAXCHARS; x++) {
                if (history[i][x] != 0) {
                    printf("Bracket not closed for bracket on line %d\n", history[i][x]);
                }
        }
    }

    for (int i=0; i<MAXCHARS; i++) {
        if (not_opened_history[i] != 0) {
            printf("Bracket has no opening on line %d\n", not_opened_history[i]);
        }
    }
}