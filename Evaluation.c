#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Evaluation.h"
#include "NumberArrays.h"
#include "Stack.h"

//struct for remembering the big numbers
struct Number{
    char no[101];
    int length;
    int length_float;
    int isNegative;
};

//struct for the stack of chars
struct StackChar{
    int top;
    int capacity;
    char *array;
};

//struct for the stack of numbers
struct StackNumber{
    int top;
    int capacity;
    Number *array;
};


Number val;
Number val1, val2, rezult;

void evaluation(char *ptr, Number x, Number *rez)
{
    int length = strlen(ptr);
    StackChar *sc = createStack(100);
    StackChar *sn = createStackNumber(100);

    for(int i = 0; i < length; i++){
        /// Transfering the numbers from the expression to the struct:
        attributeValue(&rezult, 0.0);
        attributeValue(&val,0.0);
        attributeValue(&val1,0.0);
        attributeValue(&val2,0.0);

        if(ptr[i] >= '0' && ptr[i] <= '9'){
            readNumber(&val, ptr, &i);
            pushNumber(sn, val);
        }

        if(ptr[i] == 'x')
            pushNumber(sn,x);

        if(ptr[i] == '*' || ptr[i] == '/' || ptr[i] == '+' || ptr[i] == '-'){
            val1 = popNumber(sn);
            val2 = popNumber(sn);
            switch(ptr[i]){
                case '+':
                    addition(val2,val1,&rezult);
                    break;
                case '-':
                    substraction(val2,val1,&rezult);
                    break;
                case '*':
                    multiplication(val2,val1,&rezult);
                    break;
            }

            pushNumber(sn,rezult);
        }
    }

    *rez = popNumber(sn);
}

/// Function that calculates the postfix,
/// the RPN ( reverse polish notation ) of an expression
void reversePolishNotation(char *ptr, char *newPtr)
{
    /// Finding the capacity of the stack and creating it
    int capacity = strlen(ptr);
    StackChar *stack = createStack(capacity);

    char top;
    int ok, i = 0, poz = 0;
    while(i < capacity){
        ok = 0;
        if(ptr[i] == 'x'){
            newPtr[poz] = ptr[i];
            i++;
            poz++;
            ok =1;
        }
        while((ptr[i] >= '0' && ptr[i] <= '9') || ptr[i] == '.'){
            newPtr[poz] = ptr[i];
            i++;
            poz++;
            ok = 1;
        }

        /// After we print a number in the RPN we leave a space so we can
        /// differentiate from them
        if(ok){
            newPtr[poz] = ' ';
            poz++;
        }

        /// If the character we are currently at is an operator other than '(' or ')'
        /// we start checking if we can put it in the stack
        if( ptr[i] == '*' || ptr[i] == '/' || ptr[i] == '+' || ptr[i] == '-'){

            /// If it's empty of course we can
            if(isEmpty(stack) == 1 || peek(stack) == '('){
                push(stack, ptr[i]);
                i++;
            }
            else{
                top = peek(stack);
                /// If it's higher precedence than the top of the stack
                /// of course we can
                if(precedence(ptr[i], top)){
                    push(stack, ptr[i]);
                    i++;
                }
                else{

                    /// If not, we place the top of the stack in our new expression:
                    while(precedence(ptr[i], top) == 0 && top != 'y' && top != '('){

                        top = pop(stack);
                        newPtr[poz] = top;
                        poz++;
                        top = peek(stack);
                    }
                    
                    push(stack, ptr[i]);
                    i++;
                }
            }
        }

        /// If the character we are currently at is '(' we push it in the stack
        if(ptr[i] == '('){
            push(stack,ptr[i]);
            i++;
        }

        /// If the character we are currently at is ')' we pop everything until we
        /// reach '('
        if(ptr[i] == ')'){
            top = peek(stack);
            while(top != '(' && isEmpty(stack) == 0){
                top = pop(stack);
                newPtr[poz] = top;
                poz++;
                top = peek(stack);
            }
            top = pop(stack);
            i++;

        }
    }
    
    while(isEmpty(stack) == 0){
        top = pop(stack);
        newPtr[poz] = top;
        poz++;
    }
}

/// Function that reads a number from an array of characters:
void readNumber(Number *x, char *array, int *i)
{
    int precision = 10;
    int length = 0;
    x->length_float = precision;

    /// Finding the lenght of the number:
    while(array[*i] >= '0' && array[*i] <= '9'){
        length++;
        (*i)++;
    }
    (*i) -= length;


    x->length = length + precision + 1;
    length = x->length;

    /// We set the integer part of the number:
    while(array[*i] >= '0' && array[*i] <= '9'){
        x->no[length] = array[*i];
        length--;
        (*i)++;
    }

    /// We place the dot:
    x->no[precision+1] = '.';
    length--;

    if(array[*i] == '.'){
        (*i)++;

        /// We set the float part of the number:
        while(array[*i] >= '0' && array[*i] <= '9'){
            x->no[length] = array[*i];
            length--;
            (*i)++;
        }
    }

    /// Filling the remaining float part of the number with 0:
    while(length){
        x->no[length] = '0';
        length--;
    }

}

/// Function for reading expression from file:
void inputExpression(char *expression)
{
    FILE *f = fopen("eval.txt", "r+");
    int c = getc(f);
    int i = 0;
    while (c != EOF) {
        expression[i] = c;
        i++;
        c = getc(f);
    }
    fclose(f);
}

/// Function that returns TRUE if the precedence of x operator is higher than
/// the one of y operator or FALSE if otherwise
int precedence(char x, char y)
{
    switch(x){
        case '+':
            return 0;
        case '-':
            return 0;
        case '*':
            if(y == '+' || y == '-')
                return 1;
            return 0;
        case '/':
            if(y == '+' || y == '-')
                return 1;
            return 0;
    }
}
