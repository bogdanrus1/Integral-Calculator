#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Stack.h"

struct Number{
    char no[101];
    int length;
    int length_float;
    int isNegative;
};

struct StackChar{
    int top;
    int capacity;
    char *array;
};

struct StackNumber{
    int top;
    int capacity;
    Number *array;
};


/// -----------------------------------------------------------------------
/// The following stack functions were taken from
/// https://www.geeksforgeeks.org/stack-data-structure-introduction-program/

/// Function for creating a stack:
StackChar * createStack(int capacity)
{
    StackChar * stack = (StackChar*)malloc(sizeof(StackChar));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

/// Function for checking if a stack is full:
int isFull(StackChar *stack)
{
    return stack->top == stack->capacity - 1;
}

/// Function for checking if a stack is empty:
int isEmpty(StackChar *stack)
{
    return stack->top == -1;
}

/// Function to add an item to the top of the stack:
void push(StackChar *stack, char item)
{
    if(isFull(stack)){
        printf("\nERROR! Stack is full\n");
        return;
    }
    stack->top++;
    stack->array[stack->top] = item;
}

/// Function to take an item from the top of the stack:
char pop(StackChar *stack)
{
    if(isEmpty(stack)){
        printf("\ERROR! Stack is empty\n");
        return 'y';
    }
    stack->top--;
    return stack->array[stack->top+1];
}

/// Function to see the item on the top of the stack:
char peek(StackChar *stack)
{
    if(isEmpty(stack))
        return 'y';
    return stack->array[stack->top];
}

StackNumber * createStackNumber(int capacity)
{
    StackNumber * stack = (StackNumber*)malloc(sizeof(StackNumber));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (Number*)malloc(stack->capacity * sizeof(Number));
    return stack;
}

/// Function for checking if a stack is full:
int isFullNumber(StackNumber *stack)
{
    return stack->top == stack->capacity - 1;
}

/// Function for checking if a stack is empty:
int isEmptyNumber(StackNumber *stack)
{
    return stack->top == -1;
}

/// Function to add an item to the top of the stack:
void pushNumber(StackNumber *stack, Number item)
{
    if(isFull(stack)){
        printf("\nERROR! Stack is full\n");
        return;
    }
    stack->top++;
    stack->array[stack->top] = item;
}

/// Function to take an item from the top of the stack:
Number popNumber(StackNumber *stack)
{
    if(isEmpty(stack)){
        printf("\ERROR! Stack is empty\n");
        return;
    }
    stack->top--;
    return stack->array[stack->top+1];
}

/// Function to see the item on the top of the stack:
Number peekNumber(StackNumber *stack)
{
    if(isEmpty(stack))
        return;
    return stack->array[stack->top];
}
