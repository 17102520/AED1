#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 5

//declaração da struct Pessoa
typedef struct pessoa{
    char nome[30];
    char idade[MAX];
    char altura[MAX];
    int contadorPessoa;
}Pessoa;

//declaração dos ponteiros
Pessoa *pPessoa;
void *buffer;
//declaração das funções
void imprimeMenu();
void insereContato();
void imprime();


int main(){
    int controle = 0;

    buffer = malloc(sizeof(Pessoa));
    if (buffer == NULL){
        exit(1); 
    }
    
    pPessoa = buffer;
    pPessoa->contadorPessoa = 0;

    while(controle!=2){
        imprimeMenu();
        scanf("%d", &controle);
        getchar();

        if(controle == 1){
            insereContato();
        }
        else if(controle != 2)
            printf("Opcao invalida! Tente novamente\n");
    }
    imprime();
    free(buffer);

}

void imprimeMenu(){
    printf("\n1. Incluir Contato\n2. Sair\nSelecione sua opcao: ");
}

void insereContato(){
    int tamanhoBuffer = 0;
    pPessoa->contadorPessoa++;  //incrementando a quantidade de pessoas
    tamanhoBuffer = (pPessoa->contadorPessoa)*sizeof(Pessoa);   //quanto de espaço será reservado para a quantidade de structs que teremos

    buffer = realloc(buffer, tamanhoBuffer);    //realocando o tamanho do buffer
    pPessoa = buffer + tamanhoBuffer - sizeof(Pessoa);  //indo até o ultimo contato da lista para acessarmos os dados somente dele

    printf("\nNovo contato:\nNome: ");
    fgets(pPessoa->nome, 30, stdin);
    printf("Idade: ");
    fgets(pPessoa->idade, MAX, stdin);
    printf("Altura: ");
    fgets(pPessoa->altura, MAX, stdin);
    printf("Contato inserido com sucesso.\n");
}

void imprime(){
    int i=0;
    Pessoa *imprime;
    imprime = buffer;

    if(pPessoa->contadorPessoa == 0)
        printf("Nao foi salva nennhuma pessoa!\n");

    for(i=0; i<pPessoa->contadorPessoa; i++){
        printf("Contato %d:\n Nome: %s", i+1, imprime->nome);
        printf(" Idade: %s", imprime->idade);
        printf(" Altura: %s", imprime->altura);
        (imprime)++;
    }
}