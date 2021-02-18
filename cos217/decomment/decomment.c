/*---------------------------------------------------------------------*/
/* decomment.c                                                         */
/* Author: Sean Wang                                                   */
/*---------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

enum Statetype {NORMAL, STARTCOMMENT, INCOMMENT, ENDCOMMENT, 
    INSTRING, BACKSLASH_INSTRING, INCHAR, BACKSLASH_INCHAR};



/* Implement the NORMAL state of the DFA. c is the current DFA character.
plineNumber is a pointer, pointing to the memory address of lineNumber.
Write c to stdout (or not), as specified by the DFA. 
Update the variable lineNumber. Return the next state. */

enum Statetype handleNormal(int c, int* plineNumber){
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
        *plineNumber+=1;
    }
    else{
        putchar(c);
        state = NORMAL;
    }
    return state;
}

/* Implement the StartComment state of the DFA. c is the current DFA character.
plineNumber is a pointer, pointing to the memory address of lineNumber.
pcommentStartLineNumber is a pointer, pointing to the memory address of 
commentStartLineNumber.
Write a character to stdout, as specified by the DFA. 
Update  variables lineNumber and commentStartLineNumber.
Return the next state. */

enum Statetype handleStartComment(int c, int* plineNumber, int* pcommentStartLineNumber){
    enum Statetype state;
    if (c=='*'){
        putchar(' ');
        state = INCOMMENT;
        *pcommentStartLineNumber = *plineNumber;
    }
    else if (c=='\n'){
        putchar('/');
        putchar(c);
        state = NORMAL;
        *plineNumber+=1;
    }
    else{
        putchar('/');
        putchar(c);
        state = NORMAL;
    }
    return state;
}

/* Implement the InComment state of the DFA. c is the current DFA character.
plineNumber is a pointer, pointing to the memory address of lineNumber.
Write a character (or not) to stdout, as specified by the DFA. 
Update variable lineNumber. Return the next state. */

enum Statetype handleInComment(int c, int* plineNumber){
    enum Statetype state;
    if (c=='\n'){
        putchar(c);
        state = INCOMMENT;
        *plineNumber+=1;
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
plineNumber is a pointer, pointing to the memory address of lineNumber.
pcommentStartLineNumber is a pointer, pointing to the memory address of 
commentStartLineNumber.
Write a character (or not) to stdout, as specified by the DFA. 
Update the variables lineNumber and commentStartLineNumber. 
Return the next state. */

enum Statetype handleEndComment(int c, int* plineNumber, int* pcommentStartLineNumber){
    enum Statetype state;
    if (c=='\n'){
        putchar(c);
        state = INCOMMENT;
        *plineNumber+=1;
    }
    else if (c=='/'){
        *pcommentStartLineNumber = 0;
        state = NORMAL;
    }
    else{
        state = INCOMMENT;
    }
    return state;
}

/* Implement the InString state of the DFA. c is the current DFA character.
plineNumber is a pointer, pointing to the memory address of lineNumber.
Write c to stdout, as specified by the DFA. 
Update variable lineNumber. Return the next state. */

enum Statetype handleInString(int c, int* plineNumber){
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
        *plineNumber+=1;
    }
    else{
        putchar(c);
        state = INSTRING;
    }
    return state;
}

/* Implement the BackslashInString state of the DFA. 
c is the current DFA character.
plineNumber is a pointer, pointing to the memory address of lineNumber.
Write c to stdout, as specified by the DFA. 
Update variable lineNumber. Return the next state. */

enum Statetype handleBackslashInString(int c, int* plineNumber){
    enum Statetype state;
    if (c=='\n'){
        *plineNumber+=1;
    }
    putchar(c);
    state = INSTRING;
    return state;
}

/* Implement the InChar state of the DFA. c is the current DFA character.
plineNumber is a pointer, pointing to the memory address of lineNumber.
Write c to stdout, as specified by the DFA. 
Update variable lineNumber. Return the next state. */

enum Statetype handleInChar(int c, int* plineNumber){
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
        *plineNumber+=1;
    }
    else{
        putchar(c);
        state = INCHAR;
    }
    return state;
}

/* Implement the BackslashInChar state of the DFA. 
c is the current DFA character.
plineNumber is a pointer, pointing to the memory address of lineNumber.
Write c to stdout, as specified by the DFA. 
Update variable lineNumber. Return the next state. */

enum Statetype handleBackslashInChar(int c, int* plineNumber){
    enum Statetype state;
    if (c=='\n'){
        *plineNumber+=1;
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
    
    
    int c; // each character read from stdin.
    int lineNumber = 1; // current line number
    //line number on which an unterminated comment begins
    int commentStartLineNumber = 0; 
    
    enum Statetype state = NORMAL;
    while ((c = getchar()) != EOF){
        switch (state){
            case NORMAL:
                state = handleNormal(c, &lineNumber);
                break;
            case STARTCOMMENT:
                state = handleStartComment(c, &lineNumber, &commentStartLineNumber);
                break;
            case INCOMMENT:
                state = handleInComment(c, &lineNumber);
                break;
            case ENDCOMMENT:
                state = handleEndComment(c, &lineNumber, &commentStartLineNumber);
                break;
            case INSTRING:
                state = handleInString(c, &lineNumber);
                break;
            case BACKSLASH_INSTRING:
                state = handleBackslashInString(c, &lineNumber);
                break;
            case INCHAR:
                state = handleInChar(c, &lineNumber);
                break;
            case BACKSLASH_INCHAR:
                state = handleBackslashInChar(c, &lineNumber);
                break;
        }
    }
    if (commentStartLineNumber!=0){
        fprintf(stderr, "Error: line %d: unterminated comment\n", commentStartLineNumber);
        exit(EXIT_FAILURE);
    }

    return 0;
}
