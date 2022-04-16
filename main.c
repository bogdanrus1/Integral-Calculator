#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FunctionGraph.h";
#include "Menu.h"
#include "Stack.h"
#include "NumberArrays.h"
#include "Evaluation.h"

char expression[100], newExpression[100];

int main()
{
    menu();
    inputExpression(expression);
    reversePolishNotation(expression,newExpression);
    function_graph_input(newExpression);
    return 0;
}
