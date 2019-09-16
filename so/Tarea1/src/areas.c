/*
Nombre: Andres Luisos Barbosa Carranza
n.cuenta: 313055407
*/

#include "areas.h"

float areas_figuras(char figura [], float parametro1, float parametro2){

	float resultado = 0;

	if(strcmp(figura, "-t") == 0){
		if(parametro2 == 0){
			printf("Error falta un dato");
			exit(0);
		}
		resultado = (parametro1 * parametro2)/2;
	}

	if(strcmp(figura, "-dc") == 0){
		if(parametro2 != 0 && parametro1 != parametro2){
			printf("Error eso no es un cuadrado");
			exit(0);
		}
		resultado = parametro1 * parametro1;
	}

	if(strcmp(figura, "-dr") == 0){
		if(parametro2 == 0){
			printf("Error falta un dato");
			exit(0);
		}
		resultado = (parametro1 * parametro2);
	}

	if(strcmp(figura, "-c") == 0){
		if(parametro2 != 0){
			printf("Error el circulo solo recibe radio");
			exit(0);
		}
		resultado = parametro1 * PI;
	}

	if(strcmp(figura, "-c") != 0 && strcmp(figura, "-dr") != 0 && strcmp(figura, "-dc") != 0 && strcmp(figura, "-t") != 0){
		printf("Bandera incorrecta, banderas disponibles: -c, -dc, -dr, -t");
		exit(0);
	}
	return resultado;
}


int main(int argc, char** argv)
{
	printf("%f", areas_figuras(argv[1], atof(argv[2]), atof(argv[3])));
    return 0; 
}