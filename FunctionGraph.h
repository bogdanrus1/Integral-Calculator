#ifndef FUNCTIONGRAPH_H_INCLUDED
#define FUNCTIONGRAPH_H_INCLUDED

#include <stdlib.h>

/// Struct defintion
typedef struct Number Number;
typedef struct StackChar StackChar;
typedef struct StackNumber StackNumber;

//function defintions

extern void function_graph_input(char *);

extern void show_graph(char *);

extern void open_files();

extern void w_coordinates(double, double, double, char*);

extern void costumization();

extern void riemann_divisions();

extern void close_files();

//file definitions
extern FILE* txt;
extern FILE* txt2;

#endif // FUNCTIONGRAPH_H_INCLUDED
