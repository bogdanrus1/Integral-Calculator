#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Menu.h"

FILE* f_ptr;

double xmin, xmax, division;

///Function to print the menu
void menu()
{
    printf("*************************************************\n");
    printf("*\tWelcome to Integral Calculator!\t\t*\n");
    printf("*************************************************\n\n\n");

    printf("To calculate the integral, firstly introduce your function:\n");
    read_f();

    printf("\n\nNow, introduce the values between the integral is calculated and the Riemann division( best for the value 0.1 ):\n");
    read_values();

    getchar();
}

///Function to ask the user for the input
void function_graph_instruction()
{
    printf("Do you want to show the graph of the function? [y/n]\n");
}

///Function for reading the function
void read_f()
{
    char f[100];
    f_ptr = fopen("eval.txt", "w");
    gets(f);
    fprintf(f_ptr, "%s", f);
    fclose(f_ptr);
}

///Function for reading the values for which the integral will be calculated over
void read_values()
{
    scanf("%lf %lf %lf", &xmin, &xmax, &division);
}
