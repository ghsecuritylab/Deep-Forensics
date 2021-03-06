#include <ctype.h>

typedef struct {
	unsigned int starting_address;
	unsigned int length;
} mem_dump_request;

void print_mem(mem_dump_request request, unsigned char* data) {
    unsigned int i = 0;            
    unsigned int j = 0;
                
    for (i = 0; i < request.length;) {     
        printf("0x%08x\t", request.starting_address + i);
        
        for(j = 0; j < 8; j++) {
            if(i + j < request.length)
                printf("%02x ",data[i+j]);
            else
                printf(".. ");
        }
        
        printf("\t");
        
        for(j = 0; j < 8; j++) {
            if(i+j < request.length) {
                if(isprint(data[i+j]))
                    printf("%c",data[i+j]);
                else
                    printf(".");
            }
            
            else
                printf(".");
        }
        
        printf("\n");
        i += 8;
    }
}

// Splits a given string with a given delimiter and fills the parts to the given (by address) 
// string array, The function also returns the size of the array.
// The array and all of its strings are dynamically allocated and should be freed after use.
int split(char*** parts, const char* str, const char* delimiter) {
    int i = 0;
    int counter = 0;
    char* token = NULL;
    char* buffer = NULL;
    char* ptr = NULL;

    buffer = strdup(str);
    ptr = buffer;
    size_t nlen = strlen(delimiter);

    while (ptr != NULL) {
	ptr = strstr (ptr, delimiter);

	if (ptr != NULL) {
	    counter++;
	    ptr += nlen;
	}
    }

    (*parts) = (char**)calloc(counter + 1, sizeof(char*));

    token = strtok(buffer, delimiter);

    i = 0;
    while(token != NULL) {
	(*parts)[i++] = strdup(token);
	token = strtok(NULL, delimiter);
    }

    free(buffer);

    return counter + 1;
}