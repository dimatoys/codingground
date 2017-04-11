/*
 * utils.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Dmitry ryashchentsev
 */
#include <stdio.h>

void dumpBin(void* ptr, int size) {
    for (int i = 0; i < size; ++i) {
    	if (i % 16 == 0) {
    		printf("\n%04X ", i);
    	}
    	printf(" %02X", (unsigned int)*(((unsigned char*)ptr) + i));
    }
    printf("\n");
}
