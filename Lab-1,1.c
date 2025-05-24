#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to check if a string is a keyword
void keyword(char str[10]) {
    if (strcmp("for", str) == 0 || strcmp("while", str) == 0 || strcmp("do", str) == 0 ||
        strcmp("int", str) == 0 || strcmp("float", str) == 0 || strcmp("char", str) == 0 ||
        strcmp("double", str) == 0 || strcmp("static", str) == 0 ||
        strcmp("switch", str) == 0 || strcmp("case", str) == 0)
        printf("\n%s is a keyword", str);
    else
        printf("\n%s is an identifier", str);
}

int main() {
    FILE *f1, *f2, *f3;
    char c, str[10], st1[10];
    int num[100], lineno = 1, tokenvalue = 0, i = 0, j = 0, k = 0;

    printf("Enter the C program (Press Ctrl+D to end input on Linux/Mac or Ctrl+Z on Windows):\n");
    f1 = fopen("input", "w");
    while ((c = getchar()) != EOF)
        putc(c, f1);
    fclose(f1);

    f1 = fopen("input", "r");
    f2 = fopen("identifier", "w");
    f3 = fopen("specialchar", "w");

    while ((c = getc(f1)) != EOF) {
        if (isdigit(c)) {
            tokenvalue = c - '0';
            c = getc(f1);
            while (isdigit(c)) {
                tokenvalue = tokenvalue * 10 + c - '0';
                c = getc(f1);
            }
            num[i++] = tokenvalue;
            ungetc(c, f1);
        } else if (isalpha(c)) {
            putc(c, f2);
            c = getc(f1);
            while (isalnum(c) || c == '_' || c == '$') {
                putc(c, f2);
                c = getc(f1);
            }
            putc(' ', f2);
            ungetc(c, f1);
        } else if (c == ' ' || c == '\t') {
            // Skip whitespace
        } else if (c == '\n') {
            lineno++;
        } else {
            putc(c, f3);
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);

    // Print numbers
    printf("\nThe numbers in the program are: ");
    for (j = 0; j < i; j++)
        printf("%d ", num[j]);

    // Print keywords and identifiers
    printf("\nThe keywords and identifiers are:");
    f2 = fopen("identifier", "r");
    k = 0;
    while ((c = getc(f2)) != EOF) {
        if (c != ' ')
            str[k++] = c;
        else {
            str[k] = '\0';
            keyword(str);
            k = 0;
        }
    }
    fclose(f2);

    // Print special characters
    printf("\nSpecial characters are: ");
    f3 = fopen("specialchar", "r");
    while ((c = getc(f3)) != EOF)
        printf("%c ", c);
    fclose(f3);

    printf("\nTotal number of lines: %d\n", lineno);

    return 0;
}
