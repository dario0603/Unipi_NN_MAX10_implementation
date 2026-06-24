#ifndef DEBUG_FUNCTIONS_H
#define DEBUG_FUNCTIONS_H

#include <stdio.h>

#define FUNCTIONS_LIB_DEBUG

#ifdef FUNCTIONS_LIB_DEBUG
#define DEBUG_FUNCTIONS_PRINTF(...)   printf(__VA_ARGS__)
#else 
#define DEBUG_FUNCTIONS_PRINTF(...)
#endif

#endif