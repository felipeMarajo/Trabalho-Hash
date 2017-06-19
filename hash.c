#include<stdio.h>
#include<stdlib.h>
#include"hash.h"

Hash* criaHash(){
	Hash* hash = (Hash*)malloc(sizeof(Hash));
	hash->profundidade = 1;
	hash->lista = (Buckets**)malloc(2 * sizeof(Buckets*));
	hash->lista[0] = NULL;
	hash->lista[1] = NULL;
	hash->NBuckets = 0;
	return hash;
}

int criaBin(int nBits, int valorInt){
	int result = 0;
	int i, rest, div;
	int dec = 1;
	for(i = 0; i < nBits; i++){
		rest = valorInt % 2;
		result = result + (rest * dec);
		dec = dec * 10;
		valorInt = valorInt / 2;
		if(valorInt == 0)
			break;
	}
	return result;
}

int criaInt(int valor){

	int result = 0, exp = 1;
	int i,cont = -1, dec = 1;

	while(dec <= valor){
		dec *= 10;
		cont++;
	}

	dec /= 10;

	while(cont >= 0){
		for(i = 0; i < cont; i++)
			exp *= 2;
		result += ((valor/dec) * exp);
		valor = valor % dec;
		dec /= 10;
		cont--;
		exp = 1;
	}

	return result;

}

int funcaoHash1(int valor){
	return (valor & 0x7FFFFFFF);
}
int funcaoHash2(int valor, int profundidade){
	return criaInt(criaBin(profundidade,valor));
}

int insereHash(Hash *ha, int valor){
	if(ha == NULL)
		return 0;

	int pos = funcaoHash2(valor,ha->profundidade);

	if(ha->lista[pos] == NULL){
		Buckets *newBu = criaBucket(ha->profundidade-1, ha);
		ha->lista[0] = newBu;
		ha->lista[1] = newBu;
		insereBucket(ha->lista[pos], valor);
		return 1;
	}

	if(ha->lista[pos]->qtd == 4){

		if(ha->lista[pos]->profundidadeLocal < ha->profundidade){
			int NConexoes = exponencial(2,(ha->profundidade - ha->lista[pos]->profundidadeLocal));
			// guardar em um vetor os valores do bucket atual
			// limpar bucket atual
			// criar novo bucket nas novas posições
			// armazenar valores do vetor
			// armazenar o novo valor

			int temporario[4],i;
			for(i = 0; i < 4; i++)
				temporario[i] = ha->lista[pos]->valor[i];

			limparbucket(ha->lista[pos]);
			int primeiro = criaInt(criaBin(ha->lista[pos]->profundidadeLocal, pos));
			Buckets *newBu = criaBucket(ha->lista[pos]->profundidadeLocal, ha);
			
			for(i = 0; i < NConexoes/2; i++){
				ha->lista[primeiro] = newBu;
				primeiro += NConexoes;
			}
			for(i = 0; i < 4; i++)
				insereHash(ha, temporario[i]);

			insereHash(ha, valor);
			return 1;
		}

		if(ha->lista[pos]->profundidadeLocal == ha->profundidade){

			int NConexoes;
			Buckets* endBuckets[exponencial(2,ha->profundidade)];
			int i,j,salto;
			for(i = 0; i < exponencial(2,ha->profundidade); i++)
				endBuckets[i] = ha->lista[i];

			//expandirHah(ha);

			for(i = 0; i < exponencial(2,ha->profundidade)/2; i++)
				ha->lista[i] = endBuckets[i];

			int count = 0, limitador = exponencial(2,ha->profundidade);
			for(i = 0; i < limitador; i++){
				NConexoes = exponencial(2,((ha->profundidade - 1) - ha->lista[i]->profundidadeLocal));
				Buckets *buTemp = ha->lista[i];
				salto = i;
				for(j = 0; j < NConexoes*2; j++){
					ha->lista[salto] = buTemp;
					salto += exponencial(2,ha->profundidade) / (NConexoes*2);
					count++;
				}
				if(count == exponencial(2,ha->profundidade))
					break;
			}

			int temporario[4];
			for(i = 0; i < 4; i++)
				temporario[i] = ha->lista[pos]->valor[i];
			
			limparbucket(ha->lista[pos]);
			int primeiro = criaInt(criaBin(ha->lista[pos]->profundidadeLocal, pos));
			Buckets *newBu = criaBucket(ha->lista[pos]->profundidadeLocal, ha);
			ha->lista[primeiro] = newBu;
			for(i = 0; i < 4; i++)
				insereHash(ha, temporario[i]);

			insereHash(ha, valor);
			return 1;
		}


	}

	insereBucket(ha->lista[pos], valor);
	return 1;

}

Buckets* criaBucket(int profundidadeLocal, Hash *ha){
	Buckets *bu = (Buckets*)malloc(sizeof(Buckets));
	if(bu != NULL){
		ha->NBuckets++;
		bu->NBucket = ha->NBuckets;
		bu->profundidadeLocal = profundidadeLocal;
		bu->qtd = 0;
		return bu;
	}
}

int insereBucket(Buckets *bu, int valor){
	if(bu == NULL)
		return 0;
	bu->valor[bu->qtd] = valor;
	bu->qtd++;
	return 1;
}

int exponencial(int varivel, int expoente){
	int i, resultado = 1;
	for (i = 0; i < expoente; ++i){
		resultado *= varivel;
	}
	return resultado;
}

int limparbucket(Buckets *bu){
	if(bu == NULL)
		return 0;

	bu->qtd = 0;
	bu->profundidadeLocal++;

	return 1;
}

int bitsPedidos(int valorBi, int nBits){

	int i,resultado = 0, cont = 0, dec = 1;
	while(dec <= valorBi){
		dec *= 10;
		cont++;
	}

	dec /= 10;

	while(cont != 0){
		if(cont <= nBits){
			resultado += dec;
		}
		valorBi = valorBi % dec;
		dec /= 10;
		cont--;
	}

	return resultado;

}

int imprimiValores(Hash *ha){
	if(ha == NULL)
		return 0;

	int i,j, count = exponencial(2,ha->profundidade);
	int Nbu = ha->NBuckets;
	int vetorTeste[Nbu];

	for(i = 0; (i < count) && (Nbu != 0); i++){
		if(vetorTeste[ha->lista[i]->NBucket-1] != ha->lista[i]->NBucket){
			for(j = 0; j < ha->lista[i]->qtd; j++){
				printf("%d valor do Bucket %d: %d.\n",j+1,ha->lista[i]->NBucket,ha->lista[i]->valor[j]);
			}
			vetorTeste[ha->lista[i]->NBucket-1] = ha->lista[i]->NBucket;
			Nbu--;
		}
	}

	return 1;
}

int buscaValores(Hash *ha, int valor){
	if(ha == NULL)
		return 0;

	int i, count = exponencial(2,ha->profundidade);
	int Nbu = ha->NBuckets;
	int vetorTeste[Nbu];

	int pos = criaInt(criaBin(ha->profundidade,valor));

	for(i = 0; i < ha->lista[pos]->qtd; i++){
		if(ha->lista[pos]->valor[i] == valor)
			return ha->lista[pos]->NBucket;
	}

	return -1;

}

int remocaoElemento(Hash *ha, int valor){
	if(ha == NULL)
		return 0;

	int i,j, count = exponencial(2,ha->profundidade);
	int Nbu = ha->NBuckets;
	int vetorTeste[Nbu];

	int pos = criaInt(criaBin(ha->profundidade,valor));

	if(ha->lista[pos]->qtd == 0)
		return 0;

	printf("pos: %d.\n",pos);

	for(i = 0; i < ha->lista[pos]->qtd; i++){
		if(ha->lista[pos]->valor[i] == valor){
			for(j = i; j < ha->lista[pos]->qtd-1; j++){
				ha->lista[pos]->valor[j] = ha->lista[pos]->valor[j+1];
			}
			ha->lista[pos]->qtd--;
			return 1; // tem elemento
		}
	}
	return 0; //n tem elemento
}
