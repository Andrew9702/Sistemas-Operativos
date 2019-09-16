/*
Nombre: Andres Luisos Barbosa Carranza
		Cesar Derian Estrada Gomez
n.cuenta: 313055407
n. cuenta: 31222446-4.
*/

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

char* inputs[40];
char* instrucciones[40];

//Permite tokenizar la entrada del programa
void tokens(char * parametro){
	int i = 0;
    char *token = strtok(parametro, " ");

    while(token != NULL){
    	inputs[i] = malloc(strlen(token) + 1);
		strcpy(inputs[i], token);
        token = strtok(NULL, " ");
        i++;
    }
}

//Realiza una llamada al sistema con el programa deseado con n parametros
//Permite introducir la direccion del programa para ejecutarlo
void ejecuta_accion(char * accion){
	int estado;
	int error;
	pid_t pid;

	//Se obtiene el ambiente PATH de la computadora
	char *path = getenv("PATH");
    char  pathenv[strlen(path) + sizeof("PATH=")];
    sprintf(pathenv, "PATH=%s", path);
    //Se crea el arreglo que tendra el ambiente PATH
    char *envp[] = {pathenv, NULL};
	pid = fork();
	if(pid == 0){
		tokens(accion);
		//Se ejecuta el comando que se pide con los parametros que se usen y con el ambiente bin
		error = execvpe(accion, inputs, envp); 
		if(error == -1 && strcmp(accion, "exit") != 0){	
			//Si la funcion no esta en bin se busca con su direccion entera		
			execvpe(accion, inputs, envp);
			printf("%s\n", "Error: Comando desconocido");
			exit(0);
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

int main() {
	char comando[65];

	while(strcmp(comando, "exit") != 0){
	    printf("\n<Shell-de-andres>$ ");	
	    fgets(comando, 81, stdin);
	    comando[strlen(comando)-1] = '\0';
	    ejecuta_accion(comando);
    }

    return(0);
}
