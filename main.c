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
        int x;
        do{
            printf("Digite a chave para insercao: \n");

           if (scanf("%d", &chave) != 1) {
                printf("Erro: Entrada invalida.\n");

                while (getchar() != '\n');
                continue; 
            }
            raiz = insereNo(raiz, chave);

            printf("\nDeseja continuar a insercao?\n");
            printf("0 - Continuar insercao \n1 - Parar insercao\n");

            if (scanf("%d", &x) != 1) {
                printf("Erro: Entrada invalida.\n");

                while (getchar() != '\n');
                continue; 
            }

        }while(x != 1);

    }else if (escolha == 1){

        printf("Digite o nome do arquivo:\n");
        scanf("%s", arquivo); 
        raiz = inserirArquivo(arquivo, raiz);

        if (raiz == NULL) {
            return 0; 
        }

    }else{
        printf("\nOpcao invalida!\n");
        return 0;
    }

    while(1){
        printf("\n ----------MENU----------\n\n");
        printf("1 - Remover Elemento\n");
        printf("2 - Buscar Elemento\n");
        printf("3 - Imprimir ArvoreAVL\n");
        printf("4 - Sair\n");
        printf("\nEscolha uma das opcoes acima: \n");
        scanf("%d", &opcao);

        switch (opcao){
            case 1: 
                printf("Digite a chave para remocao: \n");
                scanf("%d", &chave);
                raiz = remover(raiz, chave);

                if (scanf("%d", &chave) != 1) {
                    printf("Erro: Entrada invalida.\n");
    
                    while (getchar() != '\n');
                    continue; 
                }
                break;
            case 2: 
                printf("Digite a chave para busca: \n");
                scanf("%d", &chave);

                if (scanf("%d", &chave) != 1) {
                    printf("Erro: Entrada invalida.\n");
    
                    while (getchar() != '\n');
                    continue; 
                }
                
                int encontrado = procuraNo(raiz, chave, NULL);

                break;
            case 3: 
                printf("\nImpressao da arvore AVL: \n\n");
                imprime(raiz, 0, NULL);
                break;
            case 4: 
                printf("\nPrograma encerrado!\n");
                libera(raiz);
                return 0;
                break;
            default: 
                printf("\nOpcao invalida!\n");
        }
    }   
}