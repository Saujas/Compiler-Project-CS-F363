// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#ifndef _SEMANTICANALYZERDEF_
#define _SEMANTICANALYZERDEF_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table_def.h"

// Length of semantic error message
#define ERROR_STRING_SIZE 200

// Structure for storing line number and error message for all semantic errors
typedef struct error{
	int line_num;
	char* str;
	struct error* next;

}Error;

// Structure for storing a list of semantic errors
typedef struct errorList{
	Error* head;
	int total_errors;
}ErrorList;

#endif