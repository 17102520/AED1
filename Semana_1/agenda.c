#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50 // tamanho máximo dos nomes
#define TAM 15 // tamanho de cada número de celular

// estrutura de um contato na agenda
struct agenda{
    char nome[MAX];
    char celular[TAM];
}typedef contato;

// estrutura auxiliar contendo as variáveis de controle necessárias
struct variables{
    int controleMenu;
    int contadorContatos;
    int tamanhoBuffer;
    int flag;
    char sort;
    int i;
    int j;
    int k;
}typedef variavel;

// estrutura contendo uma string auxiliar para as funcoes de buscar() e apagar()
struct searchBar{
    char busca[MAX];
    int flag;
}typedef busca;

// declaração dos ponteiros
void *buffer;
struct agenda *pContatos;
struct variables *pVar;
struct searchBar *pBusca;

// declaração das funções
void insereContato();
void apagaContato();
void buscaContato();
void imprimeContatos();
void imprimeMenu();


int main(){
    // no melhor caso, o usuário sai direto do programa (controleMenu == 5)
    buffer = malloc(sizeof(variavel));
    if (buffer == NULL){
        exit(1); 
    }
    pVar = buffer;
    pVar->controleMenu = 0;
    pVar->contadorContatos = 0;
    while(pVar->controleMenu != 5){
        imprimeMenu();
        scanf("%d", &pVar->controleMenu);
        getchar();
        switch (pVar->controleMenu){
            case 1:
                insereContato();
                break;
            case 2:
                apagaContato();
                break;
            case 3:
                buscaContato();
                break;
            case 4:
                imprimeContatos();
                break;
            default: 
                if (pVar->controleMenu != 5){
                    printf("Opcao invalida.\n");
                }
        }
    }
    free(buffer);
}

void insereContato(){
    (pVar->contadorContatos)++;
    pVar->tamanhoBuffer = sizeof(variavel) + sizeof(busca)+ (pVar->contadorContatos)*sizeof(contato);
    buffer = realloc(buffer, (pVar->tamanhoBuffer));
    pVar = buffer;
    pContatos = buffer + (pVar->tamanhoBuffer) - sizeof(contato);
    printf("\nNovo contato:\nNome: ");
    fgets(pContatos->nome, MAX, stdin);
    printf("Celular: ");
    fgets(pContatos->celular, TAM, stdin);
    printf("Contato inserido com sucesso.\n");
}

void apagaContato(){
    pBusca = buffer + sizeof(variavel);
    printf("\nContato a ser excluido: ");
    fgets(pBusca->busca, MAX, stdin);
    pBusca->flag = 0;
    contato *comparadorContato;
    comparadorContato = buffer + sizeof(variavel) + sizeof(busca);
    for (pVar->i = 0; pVar->i < pVar->contadorContatos; (pVar->i)++){
        if (strcmp(pBusca->busca,comparadorContato->nome) == 0){
            pBusca->flag++;
            pVar->j = pVar->i;
        }
        comparadorContato++;
    }
    if (pBusca->flag != 0){
        contato *contatoExcluido, *proximoContato;
        contatoExcluido = buffer + sizeof(variavel) + sizeof(busca) + (pVar->j * sizeof(contato));
        for (pVar->i = 0; pVar->i < ((pVar->contadorContatos) - (pVar->j)); (pVar->i)++){
            proximoContato = buffer + sizeof(variavel) + sizeof(busca) + (pVar->j+pVar->i+1) * sizeof(contato);
            strcpy(contatoExcluido->nome,proximoContato->nome);
            strcpy(contatoExcluido->celular,proximoContato->celular);
            contatoExcluido = buffer + sizeof(variavel) + sizeof(busca) + (pVar->j+pVar->i+1) * sizeof(contato);
        }
        pVar->contadorContatos--;
        pVar->tamanhoBuffer = pVar->tamanhoBuffer - sizeof(contato);
        buffer = realloc(buffer, pVar->tamanhoBuffer);
        printf("Contato excluido.\n");
    } else {
        printf("Esse contato nao existe.\n");
    }        
}

void buscaContato(){
    pBusca = buffer + sizeof(variavel);
    printf("\nPesquisar: ");
    fgets(pBusca->busca, MAX, stdin);
    pBusca->flag = 0;
    pVar->k = 0;
    contato *comparadorContato;
    comparadorContato = buffer + sizeof(variavel) + sizeof(busca);
    for (pVar->i = 0; pVar->i < pVar->contadorContatos; (pVar->i)++){
        for (pVar->j = 0; pVar->j < strlen(pBusca->busca)-1; (pVar->j)++){
            if (pBusca->busca[pVar->j] != comparadorContato->nome[pVar->j]){
                pBusca->flag++;
            }
        }
        if (pBusca->flag == 0){
            (pVar->k)++;
            if(pVar->k == 1){
                printf("\n");
            }
            printf("Contato %d:\n Nome: %s", (pVar->i)+1, comparadorContato->nome);
            printf(" Celular: %s", comparadorContato->celular);
        }
        comparadorContato++;
        pBusca->flag = 0;
    }
    if (pVar->k == 0){
        printf("Nenhum contato corresponde a sua busca.\n");
    }
    printf("\n");
}

void imprimeContatos(){
    contato *imprimeContatos;
    imprimeContatos = buffer + sizeof(variavel) + sizeof(busca);
    if (pVar->contadorContatos == 0){
        printf("\nAinda nao existem contatos.");
    }
    printf("\n");
    for (pVar->i = 0; pVar->i < pVar->contadorContatos; (pVar->i)++){
        printf("Contato %d:\n Nome: %s", (pVar->i)+1, imprimeContatos->nome);
        printf(" Celular: %s", imprimeContatos->celular);
        (imprimeContatos)++;
    } 
    printf("\n");  
}

void imprimeMenu(){
    printf("\n1. Incluir Contato\n2. Apagar Contato\n3. Buscar Contato\n4. Imprimir Contatos\n5. Sair\nSelecione sua opção: ");
}