//Equipe:	Felipe Gomes Marajó
	//	Gustavo dos Santos Soares	

#include<stdio.h>
#include<stdlib.h>
#include"hash.h"

int main(){
	Hash *ha = criaHash();
	int opcao, valor;

	for(;;){
		printf("\n\n==================================\n");
		printf("1 - Adicionar um novo elemento\n");
		printf("2 - Remover um elemento\n");
		printf("3 - Buscar um valor\n");
		printf("4 - Imprimir todos os valores\n");
		printf("5 - Sair\n");
		printf("==================================\n");
		printf("Opcao: ");
		scanf("%d",&opcao);

		switch(opcao){

			case 1:

				printf("\nAdicionar valor: ");
				scanf("%d",&valor);
				insereHash(ha, valor);
				printf("\n");

			break;

			case 2:

				printf("\nRemover valor: ");
				scanf("%d",&valor);
				remocaoElemento(ha, valor);
				printf("\n");

			break;

			case 3:

				printf("\nBuscar valor: ");
				scanf("%d",&valor);
				if(buscaValores(ha, valor) != -1)
					printf("valor no bucket %d\n",buscaValores(ha, valor));
				else
					printf("O valor nao existe\n");
				printf("\n");

			break;

			case 4:

				printf("\n");
				imprimiValores(ha);
				printf("\n");

			break;

			case 5:
				return 0;

			break;
		}

	}

	return 0;
}
