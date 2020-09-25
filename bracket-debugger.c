#include <stdio.h>

/* Typical Statics */
#define MAXCHARS 1000
#define MAXLINES 1000

/* Error Codes */
#define EMPTY_LINE -1
#define NO_ERROR -1001
#define LOST_BRACKET -1002

/* Return Codes */
#define NEW_OPEN_BRACKET 1
#define CLOSE_OLD_BRACKET -1
#define LOST_CLOSE_BRACKET 0
#define NOT_BRACKET -10

/* Define brackets */
#define NUMB_OF_BRACKETS 3
#define CURLY 0
#define PARA 1
#define SQUARE 2



int bracket_type(char open, char close, int cursor, char c);
int newline(char line[], int limit);

int main() {

    /* Variables to do with getting line data */
    int size;
    int line_number = 0;
    char line[MAXCHARS];

    /* Variables to do with debugging */
    int error_history[MAXCHARS];
    int error_cursor = 0;
    int return_bracket_code;
    int return_error_code;

    int bracket_history[NUMB_OF_BRACKETS][MAXCHARS];
    int bracket_cursor[NUMB_OF_BRACKETS];

    /* Init arrays */
    for (int i=0; i<MAXCHARS; i++) {
        error_history[i] = EMPTY_LINE;
    }

    for (int i=0; i<NUMB_OF_BRACKETS; i++) {
        bracket_cursor[NUMB_OF_BRACKETS] = 0;
        for (int x=0; x<MAXCHARS; x++) {
            bracket_history[i][x] = EMPTY_LINE;
        }
    }

    /* Record new line and debug them */
    while ((size = newline(line, MAXCHARS)) > 0 && line_number < (MAXLINES-1)) {
        
        line_number++;                                      /* Record Line Numbers */
        char c;                     

        for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++) {
            
            c = line[i];                                    /* Indivual Char when looking at a line */

            /* Parathesis Check */
            return_bracket_code = bracket_type('(', ')', bracket_cursor[PARA], c);
            return_error_code = record_bracket(bracket_history[PARA], &bracket_cursor[PARA], return_bracket_code, line_number);

            if (return_error_code == LOST_BRACKET) {
                error_history[error_cursor] = line_number;
                error_cursor++;
            }

            /* Square Check */
            return_bracket_code = bracket_type('[', ']', bracket_cursor[SQUARE], c);
            return_error_code = record_bracket(bracket_history[SQUARE], &bracket_cursor[SQUARE], return_bracket_code, line_number);
            
            if (return_error_code == LOST_BRACKET) {
                error_history[error_cursor] = line_number;
                error_cursor++;
            }

            /* Curly Check */
            return_bracket_code = bracket_type('{', '}', bracket_cursor[CURLY], c);
            return_error_code = record_bracket(bracket_history[CURLY], &bracket_cursor[CURLY], return_bracket_code, line_number);
            
            if (return_error_code == LOST_BRACKET) {
                error_history[error_cursor] = line_number;
                error_cursor++;
            }
        }
    }

    for (int i=0; i< NUMB_OF_BRACKETS; i++) {
        for (int x=0; x<MAXCHARS; x++) {
            if (bracket_history[i][x] != EMPTY_LINE) {
                printf("Bracket not closed for bracket on line %d\n", bracket_history[i][x]);
            }
        }
    }

    for (int i=0; i<MAXCHARS; i++) {
        if (error_history[i] != EMPTY_LINE) {
            printf("Bracket has no opening on line %d\n", error_history[i]);
        }
    }

    return 0;
}

int record_bracket(int bracket_history[], int *cursor, int bracket_type_code, int line_number) {
    if (bracket_type_code == NEW_OPEN_BRACKET) {
        bracket_history[*cursor] = line_number;
        *cursor = *cursor + 1;
        return NO_ERROR;
    } else if (bracket_type_code == CLOSE_OLD_BRACKET) {
        *cursor = *cursor - 1;
        bracket_history[*cursor] = EMPTY_LINE;  
        return NO_ERROR;
    } else if (bracket_type_code == LOST_CLOSE_BRACKET) {
        return LOST_BRACKET;
    }
}

int bracket_type(char open, char close, int cursor, char c) {
    if (c == open) {
        return NEW_OPEN_BRACKET;
    } else if (c == close && cursor == 0) {
        return LOST_CLOSE_BRACKET;
    } else if (c == close && cursor > 0) {
        return CLOSE_OLD_BRACKET;
    } else {
        return NOT_BRACKET;
    }
}

int newline(char line[], int limit) {
    char c;
    int size = 0;

    while (size < (limit-1) && (c = getchar()) != EOF && c != '\n' && c != '^') {
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