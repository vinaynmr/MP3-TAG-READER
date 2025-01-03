#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef unsigned int uint;

typedef enum{
    failure,
    success
}status;

typedef enum{
    view,
    edit,
    help,
    unsupported
}OperationType;


#endif
