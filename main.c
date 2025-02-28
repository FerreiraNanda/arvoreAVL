#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int main(){
    int opcao, chave, escolha;
    char arquivo [1024];
    No* raiz = NULL;

    printf("Escolha a forma de leitura de dados\n");
    printf("0 - Manualmente \n1 - Arquivo\n");
    scanf("%d", &escolha);

    if(escolha == 0){
        printf("Digite a chave para insercao: \n");
        scanf("%d", &chave);
        raiz = insereNo(raiz, chave);
    }else if (escolha == 1){
        printf("Digite o nome do arquivo:\n");
        scanf("%s", arquivo); 
        raiz = inserirArquivo(arquivo, raiz);
    }else{
        printf("Opção inválida!\n");
        return 0;
    }

    while(1){
        printf("1 - Inserir Elemento Manualmente\n");
        printf("2 - Remover Elemento\n");
        printf("3 - Buscar Elemento\n");
        printf("4 - Imprimir ArvoreAVL\n");
        printf("5 - Sair\n");
        printf("\nEscolha uma das opcoes acima: \n");
        scanf("%d", &opcao);

        switch (opcao){
            case 1: 
                if(escolha != 0){
                    printf("Operacao invalida!\n");
                    break;
                }
                printf("Digite a chave para insercao: \n");
                scanf("%d", &chave);
                raiz = insereNo(raiz, chave);
                break;
            case 2: 
                printf("Digite a chave para remocao: \n");
                scanf("%d", &chave);
                raiz = remover(raiz, chave);
                break;
            case 3: 
                printf("Digite a chave para busca: \n");
                scanf("%d", &chave);
                int encontrado = procuraNo(raiz, chave, NULL);

                break;
            case 4: 
                printf("Impressao da arvore AVL: \n");
                imprime(raiz, 0, NULL);
                break;
            case 5: 
                printf("Programa encerrado!\n");
                return 0;
                break;
            default: 
                printf("Opcao invalida!\n");
        }
    }   
}