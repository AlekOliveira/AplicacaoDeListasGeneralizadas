#include <stdio.h>
#include <string.h>
#include "TAD.h"
//ALEXANDRE CARDOZO DE OLIVEIRA  101730527
//HEITOR PAYÃO                   101810164





int main()
{
    /*
    Casos de teste:
        2+(3-5(pow(2,3)-3)-8)
        pow(3,2)1/3+1/4-1/3
        (2+(sqrt(16)+pow(2,3))-4)3
        5+cos(3.1415)3
        (cos(3.1415)*sin(3.1415))/sin(3.1415)
        84-pow(8,2)+4/7
    */

	ListaGen *L,*K;
	char expressao[30];
	strcpy(expressao,"(cos(3.1415)*sin(3.1415))/sin(3.1415)");
	int i = 0;

	L = ConstroiLista(expressao,&i);
	Resolve(L,0,L);
	ExibeLista(L);


	//Resolve(L);
	return 1;
}
