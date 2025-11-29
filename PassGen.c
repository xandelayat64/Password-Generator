#include "PassGen.h"

char * PasswordGen(int size, PassGen* passgen) {

    //create a letters tab ('a' to 'z')
    int let = 26;
    char* letTab = (char*) malloc(let * sizeof(char));
    for (int i = 0; i < let; i++) {
        letTab[i] = 'a' + i;
    }

    //create a digits tab ('0' to '9')
    int dig = 10;
    char* digTab = (int*) malloc(dig * sizeof(int));
    for (int i = 0; i < dig; i++) {
        digTab[i] = '0' + i;
    }

    char charac[] = "&{}[]()@%*_-/?!<>,;:+-'=";     //special characters

    //Initialisations
    srand(time(NULL));
    int randType;
    int letters;
    int digits;
    int character;
    int lu;
    int tempRand;

    //memory alloc for the password
    char* password = (char*) malloc((size + 1) * sizeof(char));
    if (password == NULL) {
        free(letTab);
        free(digTab);
        return NULL;
    }

    /*memory alloc for pass (will contain each characters informations
     *which means:
     *
     *LETTER or DIGIT or SPECIAL CHARACTER
     *its state: LOWERCASE, UPERCASE, NUMBER, OTHERQ
     *the character at a specific position
    */
    PassGen* pass = (PassGen*) malloc(size * sizeof(PassGen));
    if (pass == NULL) {
        free(password);
        free(letTab);
        free(digTab);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        randType = rand() % 3;
        //printf("%d", randType);

        //Avoid having 3 letters in a row
        if (pass[i-2].Type == LETTER
            && pass[i-1].Type == LETTER ) {
            randType = (rand() % 3) + 1;
        }
        //Avoid having 3 digits in a row
        else if (pass[i-2].Type == DIGIT
            && pass[i-1].Type == DIGIT) {
            tempRand = rand() % 2;
            if (tempRand == 0) randType = 0;
            else randType = 2;
        }
        //Avoid having 3 special characters in a row
        else if (pass[i-2].Type == OTHER
            && pass[i-1].Type == OTHER) {
            tempRand = rand() % 2;
            if (tempRand == 0) randType = 0;
            else randType = 1;
        }

        //Set a letter
        if (randType == 0) {
            letters = rand() % 26;
            char temp = letTab[letters];
            pass[i].Type = LETTER;

            //Random function: lowercase or uppercase letter
            lu = rand() % 2;

            //Avoid having 2 uppercase letters in a row
            if (pass[i-1].Type == LETTER && pass[i-1].State == UPPER) {
                lu = 0;
            }
            //Avoid having 2 lowercase letters in a row
            else if (pass[i-1].Type == LETTER && pass[i-1].State == LOWER) {
                lu = 1;
            }

            //set to UPPERCASE or NOT
            if (lu == 1) {
                temp = toupper(temp);
                pass[i].State = UPPER;
            }
            else {
                pass[i].State = LOWER;
            }

            password[i] = temp;
            pass[i].characters = temp;
            //printf("%c", password[i]);
        }
        //Set a digit
        else if (randType == 1) {
            digits = rand() % 10;

            if (digits == pass[i-1].characters) {
                digits += 3;
                //if digits > 9 (impossible), lower from 10 (ex: 12 -> 2)
                if (digits > 9) {
                    digits -= 10;
                }
            }

            char temp = digTab[digits];
            pass[i].Type = DIGIT;
            pass[i].State = NB;

            password[i] = temp;
            pass[i].characters = temp;
        }
        //Set a character
        else if (randType == 2) {
            character = rand() % strlen(charac);

            if (character == pass[i-1].characters) {
                character += 6;
                //if char > string length, reduce by string length
                if (character > strlen(charac)) {
                    character -= strlen(charac);
                }
            }

            char temp = charac[character];
            pass[i].Type = OTHER;
            pass[i].State = NA;

            password[i] = temp;
            pass[i].characters = temp;
        }
    }

    password[size] = '\0';

    //empty memory
    free(letTab);
    free(digTab);
    free(pass);

    return password;
}
