/*
 * Defs.h
 *
 *  Created on: Dec 8, 2021
 *      Author: ise
 */

#ifndef DEFS_H_
#define DEFS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef enum e_bool { false,true } bool;
typedef enum e_status { success, failure} status;

char** slice_str1(char* str, char* del);

typedef void * element;
typedef element(*copyFunction) (element);
typedef status(*freeFunction) (element);
typedef status(*printFunction) (element);
typedef int(*equalFunction) (element, element);//1 first bigger, 0 - same, -1 second bigger
typedef char*(*getCategoryFunction)(element);
// return the first attack - second attack . also produce the attack of each element, The function transmits the information through the pointers received in the function.
typedef int(*getAttackFunction)(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond);
typedef void*(*getKey)(element);


#endif /* DEFS_H_ */
