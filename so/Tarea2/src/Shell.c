/*
Nombre: Andres Luisos Barbosa Carranza
n.cuenta: 313055407
*/

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include "grep.c"

void ejecuta_accion(char * argv1, char *argv2, char * accion){
	int estado;
	pid_t pid;
	pid = fork();

	if(pid == 0){
		if(strcmp(accion, "pwd") == 0){
			execl("/bin/pwd", "/bin/pwd", NULL);
		} else if(strcmp(accion, "ls") == 0){	
			execl("/bin/ls", "/bin/ls", NULL);
		} else if(strcmp(accion, "ls1") == 0){	
			execl("/bin/ls", "/bin/ls", argv1, NULL);	
		} else if(strcmp(accion, "ls2") == 0) {
			execl("/bin/ls", "/bin/ls", argv1, argv2, NULL);
		} else if(strcmp(accion, "cp") == 0){
			execl("/bin/cp", "/bin/cp", argv1, argv2, NULL);
		} else if(strcmp(accion, "grep") == 0){
			grep(argv1, argv2);
		} else if(strcmp(accion, "cat") == 0){
			execl("/bin/cat", "/bin/cat", argv1, NULL);
		} else if(strcmp(accion, "cat1") == 0){
			execl("/bin/cat", "/bin/cat", argv1, argv2, NULL);
		} 
	} else if(pid < 0){
		printf("*****Error no se pudo hacer hijo del proceso.\n*****");
		estado = -1;
	} else{
		if(waitpid(pid, &estado, 0) != pid){
			printf("Error\n");
			estado = -1;
		}
	}
}

int main(int argc, char *argv) {
	char comando[50];
	char argv1[50];
	char argv2[50];

	while(strcmp(comando, "exit") != 0){

	    printf("<Shell-de-andres>$ ");	
	    scanf("%s", comando);

	    if(strcmp(comando, "pwd") == 0 || strcmp(comando, "exit") == 0){
	    	ejecuta_accion(NULL, NULL, comando);

	    } else if(strcmp(comando, "ls") == 0){
	    	ejecuta_accion(NULL, NULL, comando);
	    } else if(strcmp(comando, "ls1") == 0){
	    	scanf("%s", argv1);
	    	ejecuta_accion(argv1, NULL, comando);
	    } else if(strcmp(comando, "ls2") == 0){
	    	scanf("%s", argv1);
	    	scanf("%s", argv2);
	    	ejecuta_accion(argv1, argv2, comando);
	    } else if(strcmp(comando, "cp") == 0){
	    	scanf("%s", argv1);
	    	scanf("%s", argv2);
	    	ejecuta_accion(argv1, argv2, comando);
	    } else if(strcmp(comando, "grep") == 0){
	    	scanf("%s", argv1);
	    	scanf("%s", argv2);
	    	ejecuta_accion(argv1, argv2, comando);
	    } else if(strcmp(comando, "cat") == 0){
	    	scanf("%s", argv1);
	    	ejecuta_accion(argv1, NULL, comando);
	    } else if(strcmp(comando, "cat1") == 0){
	    	scanf("%s", argv1);
	    	scanf("%s", argv2);
	    	ejecuta_accion(argv1, argv2, comando);
	    }
	    else {
	        printf("ERROR: Comando desconocido\n");	
	    }
    }

    return(0);
}
