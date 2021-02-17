/*---------------------------------------------------------------------*/
/* decomment.c                                                         */
/* Author: Sean Wang                                                   */
/*---------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

enum Statetype {NORMAL, STARTCOMMENT, INCOMMENT, ENDCOMMENT, 
    INSTRING, BACKSLASH_INSTRING, INCHAR, BACKSLASH_INCHAR};

int lineNumber = 1;
int commentStartLineNumber = 0;

/* Implement the NORMAL state of the DFA. c is the current DFA character.
Write c to stdout (or not), as specified by the DFA. 
Update global variable lineNumber. Return the next state. */

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

/* Implement the StartComment state of the DFA. c is the current DFA character.
Write a character to stdout, as specified by the DFA. 
Update global variables lineNumber and commentStartLineNumber.
Return the next state. */

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

/* Implement the InComment state of the DFA. c is the current DFA character.
Write a character (or not) to stdout, as specified by the DFA. 
Update global variable lineNumber. Return the next state. */

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

/* Implement the EndComment state of the DFA. c is the current DFA character.
Write a character (or not) to stdout, as specified by the DFA. 
Update global variable lineNumber. Return the next state. */

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

/* Implement the InString state of the DFA. c is the current DFA character.
Write c to stdout, as specified by the DFA. 
Update global variable lineNumber. Return the next state. */

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
    else if (c=='\n'){
        putchar(c);
        state = INSTRING;
        lineNumber++;
    }
    else{
        putchar(c);
        state = INSTRING;
    }
    return state;
}

/* Implement the BackslashInString state of the DFA. 
c is the current DFA character.
Write c to stdout, as specified by the DFA. 
Update global variable lineNumber. Return the next state. */

enum Statetype handleBackslashInString(int c){
    enum Statetype state;
    if (c=='\n'){
        lineNumber++;
    }
    putchar(c);
    state = INSTRING;
    return state;
}

/* Implement the InChar state of the DFA. c is the current DFA character.
Write c to stdout, as specified by the DFA. 
Update global variable lineNumber. Return the next state. */

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
    else if (c=='\n'){
        putchar(c);
        state = INCHAR;
        lineNumber++;
    }
    else{
        putchar(c);
        state = INCHAR;
    }
    return state;
}

/* Implement the BackslashInChar state of the DFA. 
c is the current DFA character.
Write c to stdout, as specified by the DFA. 
Update global variable lineNumber. Return the next state. */

enum Statetype handleBackslashInChar(int c){
    enum Statetype state;
    if (c=='\n'){
        lineNumber++;
    }
    putchar(c);
    state = INCHAR;
    return state;
}

/* Read text from stdin. Replace the comments with a space, 
while leaving everything else unchanged. Write the result to stdout.
Throw an error if there is an unterminated comment and print the 
line number where the unterminated comment begins. Otherwise return 0.
*/

int main(void)
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
