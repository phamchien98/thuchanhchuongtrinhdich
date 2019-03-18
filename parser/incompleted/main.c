/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>

#include "reader.h"
#include "parser.h"
extern FILE * outputfileforprint;

/******************************************************************/

int main(int argc, char *argv[]) {
	printf("%s",argv[2]);
  if (argc <= 1) {
    printf("parser: no input file.\n");
    return -1;
  }

   outputfileforprint=fopen(argv[2],"w");

   
  if (compile(argv[1]) == IO_ERROR) {
    printf("Can\'t read input file!\n");
    return -1;
  }
  fclose(outputfileforprint);
  return 0;
}
