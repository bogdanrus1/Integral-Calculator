#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "FunctionGraph.h"
#include "Menu.h"
#include "NumberArrays.h"
#include "Evaluation.h"

static FILE* gnuplotPipe; //file to pipe of gnuplot
FILE* txt;  ///Pointer to file containing the coordinates of the graph
FILE* txt2; ///Pointer to file containing the coordinates of the rectangles
FILE* txt3; ///Pointer to file containing the partial sum of the Riemann Sum

//struct that contains the big numbers
struct Number{
    char no[101];
    int length;
    int length_float;
    int isNegative;
};

//struct that contains the stack of chars
struct StackChar{
    int top;
    int capacity;
    char *array;
};

//struct that contains the stack of numbers
struct StackNumber{
    int top;
    int capacity;
    Number *array;
};

extern double xmin, xmax, division;

/// Function for showing the graph, if the user choose to
void function_graph_input(char *ptr)
{
    function_graph_instruction();
    int input;
    input = getchar();
    if(input == 'y') show_graph(ptr);
    return;
}

/// Function for plotting the graph
void show_graph(char *ptr)
{
    open_files();
    w_coordinates(xmin, xmax, division, ptr);
    costumization();
    fprintf(gnuplotPipe, "%s \n", "plot 'coordinates.txt' title 'function' lt rgb '#000000', 'rectangle.txt' u 1:2:($3-$1):($4-$2) with vectors nohead lc 1 title 'Riemann Divisions', \
                                                                                                        '' u 3:4:($5-$3):($6-$4) with vectors nohead lc 1 notitle, \
                                                                                                        '' u 5:6:($7-$5):($8-$6) with vectors nohead lc 1 notitle, \
                                                                                                        '' u 7:8:($1-$7):($2-$8) with vectors nohead lc 1 notitle");

    close_files();
}

/// Function for opening the files and the pipe to GnuPlot
void open_files()
{
    txt = fopen("coordinates.txt", "w");
    txt2 = fopen("rectangle.txt", "w");
    txt3 = fopen("integrala.txt","w");
    gnuplotPipe = popen("gnuplot -persistent", "w");
}

/// Function for calculating the integral and the coordinates of the graph and rectangle
void w_coordinates(double xmin, double xmax, double division, char *ptr)
{
    Number x, rezult, div;

    attributeValue(&div,division);

    ///Calculate the coordinates of the graph
    for(double i = xmin; i < xmax; i = i + 0.005)
    {
        attributeValue(&rezult,0.0);
        attributeValue(&x,i);

        evaluation(ptr,x,&rezult);

        fprintf(txt,"%lf ", i);
        printNumber(rezult, txt);
        fprintf(txt,"\n");
    }


    ///Calculate the coordinates of the rectangle and the Riemann Sum
    xmax -= division;

    Number current, previous, next, rezCurrent, rezPrevious, rezNext, zero, auxiliary;
    Number integralValue, sum;

    attributeValue(&sum,0.0);
    attributeValue(&zero,0.0);
    attributeValue(&previous,xmin);
    attributeValue(&rezPrevious,0.0);

    evaluation(ptr,previous,&rezPrevious);

    for(double i = xmin; i < xmax; i = i + division)
    {
        attributeValue(&auxiliary,0.0);
        attributeValue(&rezCurrent,0.0);
        attributeValue(&current,i);
        attributeValue(&integralValue,0.0);

        evaluation(ptr,current,&rezCurrent);

        /// Calculating the integral
        addition(rezCurrent,sum,&sum);

        /// Printing the Riemann rectangles
        substraction(rezPrevious,rezCurrent,&auxiliary);

        if((compareNumbers(rezCurrent,zero) == 1 && compareNumbers(auxiliary,zero) == 1) || (compareNumbers(rezCurrent,zero) == -1 && compareNumbers(auxiliary,zero) == -1))
        {
            attributeValue(&next,i+division);
            evaluation(ptr,next,&rezNext);

            fprintf(txt2, "%lf %lf %lf %lf %lf ", i, 0, i + division, 0, i + division);
            printNumber(rezNext, txt2);
            fprintf(txt2, " %lf ", i);
            printNumber(rezNext, txt2);
            fprintf(txt2,"\n");
        }
        else
        {
            fprintf(txt2, "%lf %lf %lf %lf %lf ", i, 0, i + division, 0, i + division);
            printNumber(rezCurrent, txt2);
            fprintf(txt2, " %lf ", i);
            printNumber(rezCurrent, txt2);
            fprintf(txt2,"\n");
        }

        attributeNumber(current,&previous);
        attributeNumber(rezCurrent,&rezPrevious);
    }
    ///Calculating the Riemann Integral
    multiplication(sum,div,&integralValue);
    printf("\n\n The integral value is: ");
    printNumberConsole(integralValue);
}

///Function for the customization of the graph
void costumization()
{
    fprintf(gnuplotPipe, "%s \n", "set xzeroaxis");
    fprintf(gnuplotPipe, "%s \n", "set yzeroaxis");
}

///Function for closing the files
void close_files()
{
    fclose(txt);
    fclose(txt2);
    fclose(txt3);
    close(gnuplotPipe);
}
