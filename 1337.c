#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1337.c 

char* encode(char* s) {
    size_t len = strlen(s);
    char* pstr = malloc(len + 1); // afnt
    strcpy(pstr, s);

    for(int i = 0; i < len; i++) {
	
	if(i % 2 == 0) {
	    pstr[i] = tolower(pstr[i]);
	} else {
	    pstr[i] = toupper(pstr[i]);
	}

	switch(pstr[i]) {
	    case 'A':
		pstr[i] = '@';
		break;
	    case 't':
		pstr[i] = '7';
		break;	
	    case 'i':
		pstr[i] = '1';	
		break;
	    case 'e':
		pstr[i] = '3';
		break;	
	    case 'o':
		pstr[i] = '0';
		break;
	    case 'F':
		pstr[i] = '7';
		break;
	    case 'S':
		pstr[i] = '$';
		break;
	}	
    }    

    return pstr;    
}	

int main(int argc, char **argv) {

    if(argc == 2) {
	char* output = encode(argv[1]);

    	printf("input: %s\n\n", argv[1]);
    	printf("output: %s\n", output);

	free(output);
    } else {
	printf("Invalid arguments supplied.\n");
    }	    

    return 0;
}
