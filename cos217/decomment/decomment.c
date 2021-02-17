#include <stdio.h>
#include <stdlib.h>

enum Statetype {NORMAL, STARTCOMMENT, INCOMMENT, ENDCOMMENT, INSTRING, BACKSLASH_INSTRING, INCHAR, BACKSLASH_INCHAR};
int lineNumber = 1;
int commentStartLineNumber = 0;

enum Statetype handleNormal(int c){
    enum Statetype state;
    if (c=='/'){
        state = STARTCOMMENT;
    }
    else if (c=='\"'){
        putchar(c);
        state = INSTRING;
    }
    else if (c=='\''){
        putchar(c);
        state = INCHAR;
    }
    else if (c=='\n'){
        putchar(c);
        state = NORMAL;
        lineNumber++;
    }
    else{
        putchar(c);
        state = NORMAL;
    }
    return state;
}

enum Statetype handleStartComment(int c){
    enum Statetype state;
    if (c=='*'){
        putchar(' ');
        state = INCOMMENT;
        commentStartLineNumber = lineNumber;
    }
    else if (c=='\n'){
        putchar('/');
        putchar(c);
        state = NORMAL;
        lineNumber++;
    }
    else{
        putchar('/');
        putchar(c);
        state = NORMAL;
    }
    return state;
}

enum Statetype handleInComment(int c){
    enum Statetype state;
    if (c=='\n'){
        putchar(c);
        state = INCOMMENT;
        lineNumber++;
    }
    else if (c=='*'){
        state = ENDCOMMENT;
    }
    else{
        state = INCOMMENT;
    }
    return state;
}

enum Statetype handleEndComment(int c){
    enum Statetype state;
    if (c=='\n'){
        putchar(c);
        state = INCOMMENT;
        lineNumber++;
    }
    else if (c=='/'){
        commentStartLineNumber = 0;
        state = NORMAL;
    }
    else{
        state = INCOMMENT;
    }
    return state;
}

enum Statetype handleInString(int c){
    enum Statetype state;
    if (c=='\"'){
        putchar(c);
        state = NORMAL;
    }
    else if (c=='\\'){
        putchar(c);
        state = BACKSLASH_INSTRING;
    }
    else{
        putchar(c);
        state = INSTRING;
    }
    return state;
}

enum Statetype handleBackslashInString(int c){
    enum Statetype state;
    putchar(c);
    state = INSTRING;
    return state;
}

enum Statetype handleInChar(int c){
    enum Statetype state;
    if (c=='\''){
        putchar(c);
        state = NORMAL;
    }
    else if (c=='\\'){
        putchar(c);
        state = BACKSLASH_INCHAR;
    }
    else{
        putchar(c);
        state = INCHAR;
    }
    return state;
}

enum Statetype handleBackslashInChar(int c){
    enum Statetype state;
    putchar(c);
    state = INCHAR;
    return state;
}


int main()
{
    int c;
    enum Statetype state = NORMAL;
    while ((c = getchar()) != EOF){
        switch (state){
            case NORMAL:
                state = handleNormal(c);
                break;
            case STARTCOMMENT:
                state = handleStartComment(c);
                break;
            case INCOMMENT:
                state = handleInComment(c);
                break;
            case ENDCOMMENT:
                state = handleEndComment(c);
                break;
            case INSTRING:
                state = handleInString(c);
                break;
            case BACKSLASH_INSTRING:
                state = handleBackslashInString(c);
                break;
            case INCHAR:
                state = handleInChar(c);
                break;
            case BACKSLASH_INCHAR:
                state = handleBackslashInChar(c);
                break;
        }
    }
    if (commentStartLineNumber!=0){
        fprintf(stderr, "Error: line %d: unterminated comment\n", commentStartLineNumber);
        exit(EXIT_FAILURE);
    }

    return 0;
}
