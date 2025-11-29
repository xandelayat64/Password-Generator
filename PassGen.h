#ifndef PASSGEN_PASSGEN_H
#define PASSGEN_PASSGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

typedef struct PassGen {

    enum State {UPPER, LOWER, NB, NA} State;
    enum Type {DIGIT, LETTER, OTHER} Type;
    char characters;

} PassGen;

char* PasswordGen(int size, PassGen*);

#endif //PASSGEN_PASSGEN_H