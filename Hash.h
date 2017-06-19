
typedef struct buckets{
	int profundidadeLocal;
	int valor[4];
	int qtd;
	int NBucket;
}Buckets;

typedef struct hash{
	int profundidade;
	Buckets **lista;
	int NBuckets;
}Hash;

Hash* criaHash();
int criaBin(int nBits, int valorInt);
int criaInt(int valor);
int funcaoHash1(int valor);
int funcaoHash2(int valor, int profundidade);
int insereHash(Hash *ha, int valor);
int dividiBuckets();
Buckets* criaBucket(int profundidadeLocal, Hash *ha);
int insereBucket(Buckets *bu, int valor);
int exponencial(int varivel, int expoente);
int limparbucket(Buckets *bu);
int bitsPedidos(int valorBi, int nBits);
int imprimiValores(Hash *ha);
int buscaValores(Hash *ha, int valor);
int remocaoElemento(Hash *ha, int valor);