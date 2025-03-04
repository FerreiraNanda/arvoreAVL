#define AVL_H

typedef struct no No;

No* cria(int chave);

int maior (int a, int b);

No* minimo(No* no);

int altura(No* no);

int fatorBalanceador(No* no);

No* rotacaoDireita(No* r);

No* rotacaoEsquerda(No* x);

No* balanceamento(No* no);

No* insereNo(No* no, int chave);

No* inserirArquivo(const char* nArquivo, No* raiz);

No* remover(No* no, int chave);

void imprime(No* no, int nivel, No* pai);

int procuraNo(No* no, int chave, No* pai); 

void libera(No* no);
