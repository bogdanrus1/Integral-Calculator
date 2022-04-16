#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED


/// Struct definitions
typedef struct StackChar StackChar;
typedef struct StackNumber StackNumber;
typedef struct Number Number;

/// Functions for stack of char:
extern StackChar * createStack(int);
extern int isFull(StackChar *);
extern int isEmpty(StackChar *);
extern void push(StackChar *, char);
extern char pop(StackChar *);
extern char peek(StackChar *);

/// Functions for stack of struct:
extern StackNumber * createStackNumber(int);
extern int isFullNumber(StackNumber *);
extern int isEmptyNumber(StackNumber *);
extern void pushNumber(StackNumber *, Number);
extern Number popNumber(StackNumber *);
extern Number peekNumber(StackNumber *);

#endif // STACK_H_INCLUDED
