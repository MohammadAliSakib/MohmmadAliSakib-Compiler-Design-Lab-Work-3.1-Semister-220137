#include <stdio.h>
#include <string.h>

int main() {
    char com[100];
    int i = 0, isComment = 0;

    printf("Enter comment: ");
    fgets(com, sizeof(com), stdin);

    if (com[0] == '/') {
        if (com[1] == '/') {
            printf("It is a single-line comment.\n");
            isComment = 1;
        } else if (com[1] == '*') {
            for (i = 2; i < strlen(com) - 1; i++) {
                if (com[i] == '*' && com[i + 1] == '/') {
                    printf("It is a multi-line comment.\n");
                    isComment = 1;
                    break;
                }
            }
            if (!isComment)
                printf("It is not a properly closed multi-line comment.\n");
        } else {
            printf("It is not a comment.\n");
        }
    } else {
        printf("It is not a comment.\n");
    }

    return 0;
}

