/*
 * Zachary Smith & Sam Whalen
 * Operating Systems
 * Project 1 Data munger and listifier
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h> //added for timing at the end
#include <sys/resource.h> 

#include "list.h"

void process_data(FILE *input_file) {
    // !! your code should start here.  the input_file parameter
    // is an already-open file.  you can read data from it using
    // the fgets() C library function.  close it with the fclose()
    // built-in function
    char buff[256];
    struct node *head = NULL;
    struct node **phead = &head;
 
    // read each line
    while (fgets(buff, 256, input_file) != NULL) {
	const char s[2]= " ";
	char *token;
	token = strtok(buff, s);
 

	while (token != NULL) { //tokenize and check for ints
		if (strncmp(token, "#", 1)==0 || strcmp(token, "\n")==0) { // ignore comments and newlines
			break;
		}
 
			
		if (( token[0]>=(int)'0' && token[0]<=(int)'9' ) || token[0]==(int)'-') { // check 1st char for a digit or negative sign
 
 
			// check the rest of the chars for digits
			int i=1;
			int num=1;
			int token_len=strlen(token);
 
			for (; i < token_len ; i++) {
				if (token[i]<(int)'0' || token[i]>(int)'9') {
					num=0;
					break;
				}
			}

			if (num==1) { // if the num == 1 we have an integer
				const int t = atoi(token);
				//printf("%i \n", t);
				list_insert(t,phead); //add to linked list
			}
		}
 
		token = strtok(NULL,s);
    	}
    }
 
    printf("*** List Contents Begin ***\n");
    list_print(head);
    printf("*** List Contents End ***\n");
 
    list_clear(head);


    return;


}


void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    struct rusage usg;
    struct timeval user, system;

    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    process_data(datafile);
//*************************************************************** 
//print CPU resource stats
	int rv = getrusage(RUSAGE_SELF, &usg);
	system = usg.ru_stime;
	user = usg.ru_utime;
 
	if (rv == 0) {
		printf("The user time is: %ld.%06ld\n", user.tv_sec, user.tv_usec);
		printf("The system time is: %ld.%06ld\n", system.tv_sec, system.tv_usec);
	} else {
		printf("Time error\n");
	}
//**************************************************************** 
    fclose(datafile); //wasn't sure if we needed to close the data file here, or in process_data

    return 0;
}
#endif


