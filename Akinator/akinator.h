#ifndef AKINATOR_H_INCLUDED
#define AKINATOR_H_INCLUDED

#include <TXLib.h>
#include "tree.h"
#include "akinator_config.h"


void free_all(tree_element* root);

void print_all_elements(tree_element* tmp, FILE* dump);



#endif // AKINATOR_H_INCLUDED
