/*
Nombre: Andres Luisos Barbosa Carranza
n.cuenta: 313055407
*/
#include <stdio.h>
#include <string.h>

void grep(const char * argv1, const char * argv2){

    FILE *f;
    f = fopen(argv2, "r");

	char buffer[2048];
	char *substr;
    
    while(fgets(buffer, 2048, f)) {
    	substr = strstr(buffer, argv1);
    	if (substr != NULL){
    		printf("%s\n", buffer);
    	}
    }
    
    fclose(f);
}