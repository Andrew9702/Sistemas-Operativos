/*
		Andres Luisos Barbosa Carranza 313055407
		Tarea 6
*/
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{	
	/*
		En caso de recibir menos parametros de los pedidos
	*/
	if (argc == 1)
	{
		printf("Tienes que proporcionar una bandera\n");
		printf("Puedes escoger -b para buscar un archivo y -h para el histograma");
	}

	/*
		Caso de recibir la bandera -b
	*/
	else if (strcmp(argv[1], "-b") == 0)
	{
		if (argc < 3)
		{
			printf("Error: Ingresa el nombre del archivo que quieres buscar.\n");
		}
		else
		{
			/*Se crea una variable donde se va a almacenar el argumento 2*/
			char *buffer;
			buffer = malloc(strlen(argv[2]) + 5);
		    strcpy(buffer, argv[2]);

			/*Se crea un archivo donde se va almacenar el stdout*/
			FILE *p;
		    char ch;


			/*Se guarda la instruccion en el apuntador "a" */		    
		    char a[500] = "find -iname ";
		    strcat(a, buffer);
		    int tamanio = 0;

		    /*Luego con popen se ejecuta la instruccion "find -iname "nombre del archivo a buscar"*/
			p = popen(a,"r"); 
		    if( p == NULL)
		    {
		        puts("Unable to open process");
		        return(1);
		    }
		    /*Si se encuentra el archivo, se imprime su direccion y se checa su tamaño*/
		    while( (ch=fgetc(p)) != EOF){
		    	putchar(ch);
		    	tamanio = tamanio +1;
		    }
		    //printf("%d\n", tamanio);
		    /*En funcion de su tamaño se sabe si fue encontrado o no*/
		    if(tamanio == 0){
		    	printf("No encontrado! \n");
		    } else {
		    	printf("Encontrado! \n");
		    }
		    free(buffer);	
		    pclose(p);
		}
	}

	
	/*
		Caso de recibir la bandera -h
	*/
	else if (strcmp(argv[1], "-h") == 0)
	{
		int estado;
		pid_t pid;
		pid = fork();

		if(pid == 0){
			execl("/usr/bin/du","du", "-ba", NULL);
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
	else
	{
		printf("No existe esa bandera.\n");
		printf("Puedes escoger -b para buscar un archivo y -h para el histograma");
	}

	return 0;
}