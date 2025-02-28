#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avl.h"

struct no{
    int chave;
    struct no *esquerdo, *direito;
    int altura;
};

No* cria(int chave){
    No *novo = (No*) malloc(sizeof(No));

    if(novo == NULL){
        printf("Erro ao alocar um novo no\n");
        exit(1);
    }
    novo -> chave = chave; 
    novo -> esquerdo = NULL;
    novo -> direito = NULL;
    novo -> altura = 1;

    return novo;
}

int maior (int a, int b){
    return(a > b) ? a: b;
}

No* minimo(No* no){
    if(no == NULL){
        return NULL;
    }
    No* noatual = no;

    while(noatual && noatual -> esquerdo != NULL){
        noatual = noatual -> esquerdo;
    }
    return noatual;
}

int altura(No* no) {
    if (no == NULL) {
        return 0;
    }
    return no->altura;
}

int fatorBalanceador(No* no){
    if(no == NULL){
        return 0;
    }
    return altura(no -> esquerdo) - altura(no -> direito);
}

No* balanceamento(No* no){
    int fb = fatorBalanceador(no);

    if(fb > 1 && fatorBalanceador(no->esquerdo) >= 0){
        return rotacaoDireita(no);
    }

    if(fb < -1 && fatorBalanceador(no->direito) <= 0){
        return rotacaoEsquerda(no);
    }

    if(fb > 1 && fatorBalanceador(no->esquerdo) < 0){
        no->esquerdo = rotacaoEsquerda(no->esquerdo);
        return rotacaoDireita(no);
    }

    if(fb < -1 && fatorBalanceador(no->direito) > 0){
        no->direito = rotacaoDireita(no->direito);
        return rotacaoEsquerda(no);
    }

    return no;
}

No* rotacaoDireita(No* r){
    No* y = r -> esquerdo;
    No* x = y -> direito;

    y -> direito = r;
    r -> esquerdo = x;

    r -> altura = maior(altura(r -> esquerdo), altura(r -> direito)) + 1;
    y -> altura = maior(altura(y -> esquerdo), altura(y -> direito)) + 1;

    return y;
}

No* rotacaoEsquerda(No* r){
    No* y = r -> direito;
    No* x = y -> esquerdo;

    y -> esquerdo = r;
    r -> direito = x;

    r -> altura = maior(altura(r -> esquerdo), altura(r -> direito)) + 1;
    y -> altura = maior(altura(y -> esquerdo), altura(y -> direito)) + 1;

    return y;
}

No* insereNo(No* no, int chave){
    if(no == NULL){
        return cria(chave);
    }

    if(chave < no -> chave){
        no -> esquerdo = insereNo(no -> esquerdo, chave);
    }else if(chave > no -> chave){
        no -> direito = insereNo(no -> direito, chave);
    }else{
        printf("Erro ao inserir elemento\n");
        return no;
    }

    no -> altura = maior(altura(no -> esquerdo), altura(no -> direito)) + 1;

    return balanceamento(no);
}

No* inserirArquivo(const char* nArquivo, No* raiz) {
    FILE* arquivo = fopen(nArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return raiz;
    }

    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char* token = strtok(linha, ";");
        while (token != NULL) {
            if (token != NULL && token[0] != '\0' && strspn(token, "0123456789") == strlen(token)) {
                int chave = atoi(token);
                raiz = insereNo(raiz, chave);
            }
            token = strtok(NULL, ";");
        }
    }

    fclose(arquivo);
    return raiz;
}

No* remover(No* no, int chave){
    if(no == NULL){
        printf("\nElemento nao encontrado!\n");
        return no;
    }

    if(chave < no -> chave){
        no -> esquerdo = remover(no -> esquerdo, chave);
    }else if(chave > no -> chave) {
        no -> direito = remover(no -> direito, chave);
    }else{
        if(no -> esquerdo == NULL){
            No* aux = no -> direito;
            free(no);
            printf("Elemento removido com sucesso!\n");
            return aux;
        }else if(no -> direito == NULL){
            No* aux = no -> esquerdo;
            free(no);
            printf("Elemento removido com sucesso!\n");
            return aux;
        }

        No* aux = minimo(no -> direito);
        no -> chave = aux -> chave;
        no -> direito = remover(no -> direito, aux -> chave);
    }

    no -> altura = maior(altura(no -> esquerdo), altura(no -> direito)) + 1;
    return balanceamento(no);
}
void imprime(No* no, int nivel, No* pai) {
    if (no != NULL) {
 
        for (int i = 0; i < nivel; i++) {
            printf("    ");
        }
        if (pai == NULL) {
            printf("%d (raiz – FB: %d)\n", no->chave, fatorBalanceador(no));
        } else {
            printf("%d (pai: %d – FB: %d)\n", no->chave, pai->chave, fatorBalanceador(no));
        }
        imprime(no->esquerdo, nivel + 1, no);
        imprime(no->direito, nivel + 1, no);
    }
}


int procuraNo(No* no, int chave, No* pai){
    if(no == NULL){
        printf ("No nao encontrado!\n");
        return 0;
    }

    if(no -> chave == chave){
        printf("No encontrado! Valor: %d (FB: %d)\n", no -> chave, fatorBalanceador(no));

        if(pai != NULL){
            printf("No pai: %d (fb: %d)\n", pai -> chave, fatorBalanceador(pai));
        }else{
            printf("No raiz\n");
        }

        if(no -> esquerdo != NULL){
            printf("Filho esquerdo: %d (FB: %d)\n", no ->esquerdo -> chave, fatorBalanceador(no -> esquerdo));
        }else{
            printf("Filho esquerdo nao existe\n");
        }

        if(no -> direito != NULL){
            printf("Filho direito: %d (FB: %d)\n", no -> direito -> chave, fatorBalanceador(no -> direito));
        }else{
            printf("Filho direito nao existe\n");
        }
        return 1;
    }

    if(chave < no -> chave){
        return procuraNo(no -> esquerdo, chave, no);
    }else{
        return procuraNo(no -> direito, chave, no);
    }
}

