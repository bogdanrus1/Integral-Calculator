#ifndef NUMBERARRAYS_H_INCLUDED
#define NUMBERARRAYS_H_INCLUDED

/// Struct defintion

typedef struct Number Number;

/// Functions for evaluating numbers written as arrays:
extern void attributeValue(Number*, double);
extern void addition(Number, Number, Number*);
extern void substraction(Number, Number, Number*);
extern void multiplication(Number, Number, Number*);
extern void printNumber(Number, FILE *);
extern int compareNumbers(Number, Number);
extern void attributeNumber(Number , Number *);
extern void printNumberConsole(Number );
#endif // NUMBERARRAYS_H_INCLUDED
