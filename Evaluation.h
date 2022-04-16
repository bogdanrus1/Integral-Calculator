#ifndef EVALUATION_H_INCLUDED
#define EVALUATION_H_INCLUDED


/// Struct defintion
typedef struct Number Number;
typedef struct StackChar StackChar;
typedef struct StackNumber StackNumber;

/// Functions for evaluating an expression:
extern void inputExpression(char *);
extern void reversePolishNotation(char *, char *);
extern void readNumber(Number *, char *, int *);
extern void evaluation(char *, Number, Number*);
extern int precedence(char, char);


#endif // EVALUATION_H_INCLUDED
