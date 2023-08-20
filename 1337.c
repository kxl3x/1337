
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <signal.h>

#include <string.h>
#include <getopt.h>

#define MAX_BUFFER 10000000 // 10mb 
#define BUFFER_LEN BUFSIZ

#define PROGRAM_VERSION "1.0.4"

// 1337.c
// converts text to 1337 speak

static void sig_handler(int signo __attribute__ ((__unused__))) {

	_Exit(EXIT_SUCCESS);

}


void print_usage() {

    puts("\nUsage: 1337 [ OPTIONS... ] [ FILE... ]\n");
    puts("Options:");
    puts(" -V  --version\tdisplays version information.\n");
    puts(" -h, --help\tdisplay this help\n");
    
    exit(EXIT_SUCCESS);
}



char* encode(char* s) {    
    size_t len = strlen(s);

    for (size_t i = 0; i < len; i++) {

        switch (s[i]) {
            case 'A':
                s[i] = '4';
                break;
            case 'B':
                s[i] = '8';
                break;
            case 't':
                s[i] = '7';
                break;
            case 'i':
                s[i] = '!';
                break;
            case 'l':
                s[i] = '1';
                break;
            case 'e':
                s[i] = '3';
                break;
            case 'o':
                s[i] = '0';
                break;
            case 'S':
                s[i] = '5';
                break;
            case 'H':
                s[i] = '#';
                break;
            case 'z':
                s[i] = '2';
                break;
            default:
                //if (i % 2 == 0)	

				if ((i & 1) == 1)
                    s[i] = tolower(s[i]);
                else
                    s[i] = toupper(s[i]);
        }   
    }    

    return s;
}




char *read_file(FILE *fp) {
    
    size_t bufsize = BUFFER_LEN;
    char *buffer = NULL;

    if ((buffer = (char *)malloc(sizeof(char) * bufsize)) == NULL) {
        fprintf(stderr, "Failure to allocate sufficient memory.\n");
        exit(EXIT_FAILURE); 
    }

    size_t len = 0;
    int c;

    while ((c = fgetc(fp)) != EOF) {
        buffer[len] = c;

        //putchar(c);

        // SA [0.0.1]
        // Abusing the dynamic file size, could result in a DOS attack
        //  on the systemwide resources. Default MAX_BUFFER 10mb    

        if (++len == bufsize) {

            bufsize *= 2;   /* estimated new buffer size */
            if (bufsize >= MAX_BUFFER)
                break;

            buffer = (char *)realloc(buffer, (sizeof(char) * bufsize));
        }
    }

    // shave off excess unused memory
    buffer = (char *)realloc(buffer, (sizeof(char) * (len + 1)));
    buffer[len] = '\0';

    return buffer;
}



int main(int argc, char **argv) { 

    int c;

    static struct option long_options[] = {
        { "version",    no_argument,    0,      'V' },
        { "help",       no_argument,    0,      'h' },
        { 0,            0,              0,       0  }
    };

	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);

    int option_index = 0;

    while ((c = getopt_long(argc, argv, "Vh", long_options, &option_index)) != -1) {
        switch (c) {

            case 'h':
                print_usage();
                break;

            case 'V':
                printf("1337 from version: %s\n", PROGRAM_VERSION);
				exit(EXIT_SUCCESS);
                break;   

            case '?':
                print_usage();
                break;
        
            default: print_usage();
                abort();
        }
    }


    /* remove opt flags from argv */
    argc -= optind;     
    argv += optind;


    FILE *fp = stdin;
    char *buffer = NULL;
 
    if (argc > 0) {
        if ((fp = fopen(argv[0], "r")) == NULL) {
            fprintf(stderr, "Failure to read file.\n");
            exit(EXIT_FAILURE);
        }
    }   
        
    buffer = read_file(fp);

    /* encode read buffer */
    char *treated = encode(buffer);
    fprintf(stdout, "%s", treated);

    if (fp != stdin)
        fclose(fp);        

    free(buffer);

    return 0;
}

