#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

union no
{
	char operador;
	float valor;
	char func[20];
};

struct listagen
{
	char terminal;
	union no No;
	struct listagen *head, *tail;
}; typedef struct listagen ListaGen;


ListaGen *Criat( char terminal, union no nodo)
{
	ListaGen *K = (ListaGen*)malloc(sizeof(ListaGen));
	if(terminal == 'V')
	{
		K->terminal = terminal;
		K->No.valor = nodo.valor;
	}
	else if(terminal == 'O')
	{
		K->terminal = terminal;
		K->No.operador = nodo.operador;
	}
	else if(terminal == 'F')
	{
		K->terminal = terminal;
        strcpy(K->No.func, nodo.func);
	}
	K->head = NULL;
	K->tail = NULL;
	return K;
}

char Nula(ListaGen *L)
{
	return L == NULL;
}


ListaGen *CalculaFuncao(ListaGen *L)
{
	char aux[20];
	float a,b;
	int  i =0,j =0;

	if(L->No.func[2] == 'w') // é um pow pois a terceira letra é o w
	{
		i = 4; // caractere depois do '('
		while(L->No.func[i] != ',')//primeiro numero, para quando achar virgula
			aux[j++] = L->No.func[i++];
		aux[j] = 0; // fechando a string
		a = atof(aux); //a recebe a string em forma de float

		j = 0;
		i++; // i++ pois i estava no ','
		while(L->No.func[i] != ')') // segundo numero, irá parar quando achar o ')'
			aux[j++] = L->No.func[i++];

		aux[j]= 0; //fechando a string

		b = atof(aux);

		L->terminal = 'V'; //transformando em valor;
		L->No.valor = pow(a,b);	// faz a conta
	}
	else if(L->No.func[2] == 'r') //é um sqrt pois a terceira letra é 'r'
	{
		 i = 5;

		 while(L->No.func[i] != ')' )
		 	aux[j++] = L->No.func[i++];
		aux[j]= 0;

		a = atof(aux);
		L->terminal = 'V';
		L->No.valor = sqrt(a);
	}
	else if(L->No.func[2] == 'n')// é um sin pois a terceira letra é 'n'
	{
		i = 4;
		while(L->No.func[i]!=')')
			aux[j++] = L->No.func[i++];
		aux[j] = 0;
		a = atof(aux);

		L->terminal = 'V';
		L->No.valor = sin(a);

	}
	else if(L->No.func[2] == 's')//é cos porque a terceira letra é 's'
	{
		i = 4;
		while(L->No.func[i])
			aux[j++] = L->No.func[i++];
		aux[j]=0;
		a = atof(aux);

		L->terminal = 'V';
		L->No.valor = cos(a);
	}
	return L;
}

ListaGen *ConstroiLista(char lista[50] ,  int *i)
{
    int j = 0;

    char aux[20];
    union no nodo;  // Nome da variavel 'nodo' que é uma varíavel do tipo 'no' (precisa declarar que é union tambem)
    char auxTerminal;
    ListaGen *L = NULL;

	if( (*i)>= strlen(lista)  || lista[*i]  == ')') // se o i for maior que a string da lista ou se aquela parte da lista conter ')', irá retornar NULL
	{
        return NULL;
	}


    else if((lista[*i] >= 48 && lista[*i]<=57)) // Checagem dos números
    {

        while((lista[*i] >= 49 && lista[*i]<=58)|| lista[*i]  == '.')
        {

            aux[j++] = lista[(*i)++];

        }

        (*i)--;
        aux[j] = 0;

        nodo.valor = atof(aux);
        auxTerminal = 'V';

        L = Criat(auxTerminal, nodo);


    }

    else if(lista[*i] == '+' || lista[*i] == '-' || lista[*i] == '*' || lista[*i] == '/') // Checagem dos operandos
    {
        auxTerminal = 'O';
        nodo.operador = lista[*i];
        L = Criat(auxTerminal, nodo);
    }
    else if(lista[*i] == '(')// Se abrir parenteses, cria uma struct com terminal 'V' com valor de 0, e continua a construção da lista na head dessa struct
    {
    	nodo.valor = 0;
        L = Criat('V',nodo);
        (*i)++;
        L->head = ConstroiLista(lista, i);


    }

   else
    {
   		while(lista[*i]!=')')//Checagem das Funcoes
        {
            aux[j++] = lista[(*i)++];
        }
        aux[j++] = lista[(*i)]; // tirar o ++
        aux[j]= 0;
        strcpy(nodo.func,aux);
        L = Criat('F',nodo);

	}


		(*i)++;

    	L->tail = ConstroiLista(lista, i) ;



    return L;

    }


void ExibeLista(ListaGen *L)
{

	if(!Nula(L))
	{
		if(!Nula(L->head))
		{
			printf("(");
			ExibeLista(L->head);
			printf(")");
		}
		else if(L -> terminal == 'F')
		{

			printf("%s",L->No.func);

		}

		else if(L->terminal == 'V')
		{
			printf("%g",L->No.valor);
		}
		else if(L->terminal == 'O')
		{
			printf("%c",L->No.operador);
		}


		if(!Nula(L->tail))
			ExibeLista(L->tail);

	}



}


ListaGen *Resolve(ListaGen *L, int modo, ListaGen *print)
{
	ListaGen *aux,*esq,*dir,*meio;
	aux = L;

	if(modo == 0)//Anda a lista
	{
		while(!Nula(aux))
		{
			if(!Nula(aux->head))
			{
				aux->No.valor = Resolve(aux->head,0,print)->No.valor;

				free(aux->head);
				aux->head = NULL;
			}
			aux = aux->tail;
		}

		return Resolve(L,1,print);
	}
	if(modo == 1)//Calculo de função
	{

		while(!Nula(aux))
		{
			if(aux->terminal == 'F')
			{
				ExibeLista(print);
				printf("\n");
				aux = CalculaFuncao(aux);

			}
			aux = aux->tail;
		}
		return Resolve(L,2,print);

	}
	if(modo ==2)//Multiplicação e Divisão
	{
		esq = aux;
		if(!Nula(esq->tail))
		{
			dir = (aux -> tail)->tail;
			meio = aux -> tail;
		}
		else
			return Resolve(L,4,print);
		while(!Nula(dir))
		{
			if(meio->terminal == 'O' && (meio->No.operador == '*' || meio->No.operador == '/'))
			{
				ExibeLista(print);
				printf("\n");
				if(meio->No.operador == '*')
				{
					esq -> No.valor *=  dir->No.valor;
					esq->tail = dir->tail;
					free(meio);
					free(dir);

				 	return Resolve(L,2,print);
				}
				esq -> No.valor /=  dir->No.valor;
				esq->tail = dir->tail;
				free(meio);
				free(dir);

				return Resolve(L,2,print);
			}
			esq = meio;
			meio = dir;
			dir = dir->tail;
		}
		return Resolve(L,3,print);



	}
	if(modo == 3)//Adição e Subtração
	{

		esq = aux;
		if(!Nula(esq->tail))
		{
			dir = (aux -> tail)->tail;
			meio = aux -> tail;
		}
		else
			return Resolve(L,4,print);
		while(!Nula(dir))
		{

			if(meio->terminal == 'O' && (meio->No.operador == '+' || meio->No.operador == '-'))
			{
				ExibeLista(print);
				printf("\n");
				if(meio -> No.operador == '+')
				{
					esq->No.valor += dir->No.valor;
					esq->tail = dir->tail;
					free(meio);
					free(dir);

					return Resolve(L,3,print);
				}

				esq->No.valor -= dir->No.valor;
				esq->tail = dir->tail;
				free(meio);
				free(dir);

				return Resolve(L,3,print);
			}
			esq = meio;
			meio = dir;
			dir = dir->tail;
		}


	return Resolve(L,4,print);

	}
	if(modo == 4)//Operação da linha feita, só falta retornar o valor
	{
		aux = L;
		return L;
	}

}








/*ListaGen *Cons(ListaGen *H, ListaGen *T)
{

    ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
    L->head = H;
    L->tail = T;
    L->terminal = H->terminal;
    if(H->terminal == 'V')
    {
        L->no.valor = H->no.valor;
    }
    else if(H->no.terminal == 'O')
    {
        L->no.terminal = H->no.terminal;
    }
    else if(H->no.terminal == 'F')
    {

        L->no.func = H->no.terminal;
    }

}*/

