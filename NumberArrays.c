#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "NumberArrays.h"

struct Number{
    char no[101];
    int length;
    int length_float;
    int isNegative;
};

/// -----------------------------------------------------------------------
void printNumberConsole(Number x)
{
    if(x.isNegative == -1)
        printf("-");
    while(x.length){
        printf("%c",x.no[x.length]);
        x.length--;
    }
    printf("\n");
}
void printNumber(Number x, FILE *ptr)
{
    if(x.isNegative == -1)
        fprintf(ptr,"-");
    while(x.length){
        fprintf(ptr,"%c",x.no[x.length]);
        x.length--;
    }
}

/// Function for comparing 2 numbers written as arrays:
/// Returns 1 if true or -1 if false
int compareNumbers(Number x, Number y)
{
    /// If the numbers have different signs, the bigger one is the positive one
    if(x.isNegative == -1 && y.isNegative == 1)
        return -1;
    if(x.isNegative == 1 && y.isNegative == -1)
        return 1;

    /// If they have the same parity the one with more numbers is grater / lower
    if(x.length > y.length)
        return 1 * x.isNegative;
    if(x.length < y.length)
        return -1 * x.isNegative;

    /// If they have the same parity and length we compare them digit by digit
    int digit1, digit2;
    if(x.length == y.length){
        for(int i = x.length; i >= 1; i--){
            if(x.no[i] == '.') continue;
            digit1 = x.no[i] - '0';
            digit2 = y.no[i] - '0';
            if(digit1 > digit2)
                return 1 * x.isNegative;
            if(digit1 < digit2)
                return -1 * x.isNegative;
        }
    }
    return 0;
}

/// Function for substracting 2 numbers written as arrays:
void substraction(Number x, Number y, Number *sub)
{
    /// If the numbers are of opposite sign we add them
    if(x.isNegative != y.isNegative){
        /// We will change their signs temporary
        y.isNegative *= -1;
        addition(x,y,sub);
        return;
    }

    /// We substract the lower one from the greater one
    if(compareNumbers(x,y) == -1){
        sub->isNegative = -1;
        substraction(y,x,sub);
        return;
    }

    /// We take the greater length of the 2
    int total_length = 0;
    total_length = (x.length > y.length)? x.length : y.length;

    /// We complete the number that is lower with 0
    for(int i = y.length + 1; i <= total_length; i++){
        y.no[i] = '0';
        y.length++;
    }

    /// Here the transpose can be only -1 or 0 because at most we will 'borrow'
    /// 10 from the higher order
    int transpose = 0;
    int digit1, digit2;

    for(int i = 1; i <= total_length; i++){
        if(i == x.length_float + 1){
            sub->no[i] = '.';
            continue;
        }

        digit1 = x.no[i] - '0';
        digit2 = y.no[i] - '0';

        if(digit1 - digit2 - transpose < 0){
            /// The 10 in the equation represent the 10 that we 'borrow'
            sub->no[i] = (char)(10 + digit1 - digit2 - transpose + '0');
            transpose = 1;
        }
        else{
            sub->no[i] = (char)(digit1 - digit2 - transpose + '0');
            transpose = 0;
        }

    }

    /// We delete the extra zeros
    while(sub->no[total_length] == '0')
        total_length--;

    /// If we get to '.' we add 1 zero
    if(total_length == 11){
        total_length++;
        sub->no[total_length] = '0';
    }

    sub->length = total_length;
}

/// Function for adding 2 numbers written as arrays:
void addition(Number x, Number y, Number *sum)
{
    /// If one of them is negative and the other is positive we will substract them instead.
    if(x.isNegative == -1 && y.isNegative == 1){
        x.isNegative *= -1;
        substraction(y,x,sum);
        return;
    }
    if(x.isNegative == 1 && y.isNegative == -1){
        y.isNegative *= -1;
        substraction(x,y,sum);
        return;
    }

    /// We take the greater length of the 2 numbers so we can add them
    int total_length = 0;
    total_length = (x.length > y.length)? x.length : y.length;

    /// We complete the number that is lower with 0
    if(x.length < total_length)
        for(int i = x.length + 1; i <= total_length; i++) x.no[i] = '0';
    if(y.length < total_length)
        for(int i = y.length + 1; i <= total_length; i++) y.no[i] = '0';

    int transpose = 0;
    int digit1, digit2;

    for(int i = 1; i <= total_length; i++){
        /// We jump over the '.'
        if(i == x.length_float + 1){
            sum->no[i] = '.';
            continue;
        }

        /// We add the 2 digits
        digit1 = x.no[i] - '0';
        digit2 = y.no[i] - '0';
        sum->no[i] = (char)((digit1 + digit2 + transpose) % 10 + '0');
        transpose = (digit1 + digit2 + transpose) / 10;
    }
    if(transpose != 0){
        total_length++;
        sum->no[total_length] = (char)(transpose + '0');
    }

    /// We place the '.' and assign the sign of the sum
    sum->length = total_length;
    sum->isNegative = x.isNegative;
}

/// Function for multiplying 2 numbers written as arrays:
void multiplication(Number x, Number y, Number *product)
{
    /// The sing of the product
    product->isNegative = x.isNegative * y.isNegative;

    /// The product of the 2 numbers will have the same precision
    int l = x.length_float;

    /// For the product we won't need the '.'
    for(int i = l + 1; i <= x.length; i++){
        x.no[i] = x.no[i+1];
    }
    x.length--;
    for(int i = l + 1; i <= y.length; i++){
        y.no[i] = y.no[i+1];
    }
    y.length--;

    /// The total length of the product will either be M + N or M + N - 1
    /// It will be M + N if the transpose will not be equal to 0 after the multiplying
    int total_length = x.length + y.length - 1;

    /// We will initialize the product array with 0 on X.length + Y.length positions
    for(int i = 1; i <= x.length + y.length; i++)
        product->no[i] = '0';

    /// Unlike ADDITION and SUBSTRACTION we don't need the total length of the 2 numbers
    /// for the multiplication
    int digitX, digitY;
    int transpose = 0, rezult = 0, reminder = 0, poz;
    for(int i = 1; i <= y.length; i++)
    {
        transpose = 0;
        digitY = y.no[i] - '0';

        if(digitY == 0) continue;

        for(int j = 1; j <= x.length; j++){
            digitX = x.no[j] - '0';
            reminder = product->no[i+j-1] - '0';
            rezult = digitX * digitY + reminder + transpose;
            /// The transpose will be what we will add to the digits of the higher order
            transpose = rezult / 10;
            /// The digit we will place in *PRODUCT will be the last digit of REZULT
            rezult = rezult % 10;

            product->no[i+j-1] = (char)(rezult + '0');
        }

        if(transpose != 0){
            poz = x.length + i;
            product->no[poz] = (char)(transpose + '0');
        }
    }

    /// If the transpose is not equal to 0 we set it as the first digit of the product
    if(transpose != 0)
    {
        total_length++;
        product->no[total_length] = (char)(transpose + '0');
    }

    /// We will set the precision of the product to the one we want
    for(int i = 1; i <= total_length; i++)
    {
        product->no[i] = product->no[i+l];
    }
    total_length -= l;

    /// We move the array in such way so we can place the '.' character
    total_length++;
    for(int i = total_length; i > l + 1; i--)
    {
        product->no[i] = product->no[i-1];
    }

    product->no[l+1] = '.';
    product->length = total_length;

    while(product->no[product->length]=='0')
        product->length--;

    if(product->no[product->length] == '.')
    {
        product->length++;
        product->no[product->length] = '0';
    }
}

/// Functions for writing a number as an array:
void attributeValue(Number *x, double val)
{
    int precision = 10;
    /// Intialize the total lenght and the lenght behind '.' with 0
    x->length = 0;
    x->length_float = 0;
    x->isNegative = 1;

    /// if the number is NEGATIVE we need a variable to remember it
    if(val < 0){
        val *= -1;
        x->isNegative = -1;
    }

    /// Dividing the number in INT and FLOAT
    long long integer = (long long)val;
    double point = val - integer;

    /// Writing the FLOAT part as an array
    long long digit;
    x->length_float = precision;

    /// In order to find the digit of the number we will multiply it by 10
    /// convert it to INT so we can find the last digit before the '.'
    while(x->length_float){
        point *= 10;
        digit = (long long)point % 10;
        if(digit != 0)
            /// The equation will give us the digit in CHAR -- in ASCII
            /// the numbers from 0 - 9 are in ascending order so we just add the digit
            /// to the ASCII code of '0' if the digit is not equal to 0.
            x->no[x->length_float] = (char)(digit + (int)'0');
        else
            x->no[x->length_float] = '0';
         x->length_float--;
    }
    x->length_float = precision;

    /// Setting the '.'
    x->length = precision;
    x->length++;
    x->no[x->length] = '.';

    /// if the INT part of the number is equal to 0 we put a 0 before the '.'
    if(integer == 0){
        x->length++;
        x->no[x->length] = '0';
    }

    /// Writing the INT part as an array
    while(integer){
        x->length++;
        x->no[x->length] = (char)(integer % 10 + (int)'0');
        integer /= 10;
    }
}
/// Function for transferring a number written as array to another number written as array:
void attributeNumber(Number x, Number *y)
{
    y->isNegative = x.isNegative;
    y->length = x.length;
    y->length_float = x.length_float;

    for(int i = 0; i < x.length; i++){
        y->no[i] = x.no[i];
    }
}
