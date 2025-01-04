#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 50

// Keywords
char *keywords[] = {
    "int", "float", "char", "if", "else", "for", "while", "do", "break", "continue", "return", "void", NULL
};

// Operator symbols
char *operators[] = {
    "+", "-", "*", "/", "%", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "&", "|", "^", "<<", ">>", NULL
};

// Function to check if a character is an operator
int isOperator(char ch) {
    for (int i = 0; operators[i] != NULL; i++) {
        if (ch == *operators[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is a delimiter
int isDelimiter(char ch) {
    if (ch == ' ' || ch == '\t' || ch == '\n' || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ',') {
        return 1;
    }
    return 0;
}

// Function to check if a character is an alphabet
int isAlphabet(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// Function to check if a character is a digit
int isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

// Function to check if a lexeme is a keyword
int isKeyword(char* lexeme) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(lexeme, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char ch, lexeme[MAX_TOKEN_LEN];
    int i, j = 0;
    FILE *fp;

    fp = fopen("input.txt", "r"); // Open the input file

    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Lexemes:\n");

    // Handle the first character separately
    ch = fgetc(fp);
    if (isOperator(ch)) {
        printf("%c: Operator\n", ch);
    } else if (isDelimiter(ch)) {
        if (ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ',') { 
            printf("%c: Delimiter\n", ch); 
        }
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (isDelimiter(ch)) {
            if (j > 0) { // Only process if lexeme has characters
                lexeme[j] = '\0'; // Null-terminate the string
                if (isKeyword(lexeme)) {
                    printf("%s: Keyword\n", lexeme);
                } else if (isDigit(lexeme[0])) {
                    printf("%s: Integer\n", lexeme);
                } else {
                    printf("%s: Identifier\n", lexeme);
                }
                j = 0; // Reset lexeme index
            }
            if (ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ',') { 
                printf("%c: Delimiter\n", ch); 
            }
        } else if (isOperator(ch)) {
            printf("%c: Operator\n", ch);
        } else if (isAlphabet(ch) || isDigit(ch)) {
            lexeme[j++] = ch;
        }
    }

    // Check for any remaining lexeme at the end of the file
    if (j > 0) {
        lexeme[j] = '\0';
        if (isKeyword(lexeme)) {
            printf("%s: Keyword\n", lexeme);
        } else if (isDigit(lexeme[0])) {
            printf("%s: Integer\n", lexeme);
        } else {
            printf("%s: Identifier\n", lexeme);
        }
    }

    fclose(fp);

    return 0;
}
