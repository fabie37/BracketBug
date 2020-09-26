#include <stdio.h>
#include "newline.h"
#include "brackets.h"

/* Typical Statics */
#define MAXLINES 1000
#define MAXCHARS 1000

int main() {

    /* Place to store each line */
    char line[MAXCHARS];

    /* Character Size of line */
    int ls;

    /* Record what line number you are on */
    int ln = 1;

    /* indivual char */
    char c;  
    int type;
 
    /* Keep taking in new lines until EOF (0 Characters) or you've ran out of lines to anaylse */
    while ((ls = newline(line, MAXCHARS)) > 0 && ln < (MAXLINES-1)) {

        /* Get the character case of each character on line until you reach the end of the string */
        for (int i = 0; (c = line[i]) != '\0'; i++) {
            /* if it is a bracket, put it in history */
            if ((type = isopenbracket(c)) != -1) {
                putbracket(ln, type);
            } else if ((type = isclosebracket(c)) != -1) {
                removebracket(ln, type);
            }
        }

        /* On a new line */
        ++ln;
    }

    printerrors();
}

