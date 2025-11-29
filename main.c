#include <stdio.h>
#include <stdlib.h>
#include "PassGen.h"
#include "path.h"

int main(void) {

    PassGen passGen;

    int length;
    printf("Password length ? \n");
    scanf("%d", &length);

    //Where are you going to use this password (which website / account ) ?
    char reason[100];
    printf("What is the password going to be used for ?");
    getchar();
    fgets(reason, 100, stdin);

    char* password = (char*) malloc(length * sizeof(char));     //memory alloc for password

    //PasswordGen(length, &passGen);
    password = PasswordGen(length, &passGen);

    if (password != NULL) {
        printf("Password: %s\n", password);
    }
    else if (password == NULL) {
        printf("Password generation error\n");
        return EXIT_FAILURE;
    }

    //Create a file containing your password
    //path included from path.h
    FILE* file;

    if (!path) {
        file = fopen(path, "w");
    }
    else {
        file = fopen(path, "a");
    }

    //Display an error if the file doesn't exist
    if (file == NULL) {
        perror("/!\\ OPENING FILE ERROR /!\\");
        return EXIT_FAILURE;
    }

    //sprintf("Password: %s\n", password);

    fprintf(file, "%s : %s\n\n", reason, password);
    fclose(file);

    free(password);

    return EXIT_SUCCESS;
}
