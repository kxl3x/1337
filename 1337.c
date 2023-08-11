#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1337.c 

char* encode(char* s) {
    size_t len = strlen(s);
    char* pstr = malloc(len + 1); // afnt

    // Lets not make this more complicated, and just read directly from s
    // strncpy(pstr, s, len);

    // Account for null terminator
    pstr[len] = '\0';

    for(int i = 0; i < len; i++) {

	switch(s[i]) {
	    case 'A':
		pstr[i] = '4';
		break;
	    case 'B':
		pstr[i] = '8';
		break;
	    case 't':
		pstr[i] = '7';
		break;	
	    case 'i':
		pstr[i] = '!';	
		break;
	    case 'l':
		pstr[i] = '1';
		break;
	    case 'e':
		pstr[i] = '3';
		break;	
	    case 'o':
		pstr[i] = '0';
		break;
	    case 'S':
		pstr[i] = '5';
		break;
	    default:
	        if(i % 2 == 0) {
		    pstr[i] = tolower(s[i]);
		} else {
		    pstr[i] = toupper(s[i]);
		}
	}	
    }    

    return pstr;    
}	

int main(int argc, char **argv) {

    if(argc == 2) {
	char* output = encode(argv[1]);
    	
	// echo out; 
	puts(output);

	free(output);
    } else {
	puts("Invalid arguments supplied.");
    }

    return 0;
}
