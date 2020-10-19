#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char *aux;
    char *nome = (char *)malloc(sizeof(char));

    //teste para verificar se tem espaço na memória.
    if (!nome) {
        printf("Erro, falta de memória");
        return -1;
    }

    //inserindo a string dentro do ponteiro
    printf("Entre com um nome : ");
    fgets(aux,20,stdin);

    //realocando a memória necessária para receber o ponteiro e copiando a string para o ponteiro principal
    nome = (char *) realloc(nome, strlen(aux));
    memcpy( nome, aux, strlen(aux));

    printf("%s", nome);
    printf("%d ( o tamanho do buffer vai ser sempre um numeor maior do que a string por conta do /0 no final. )\n", strlen(nome));

    //liberando a memoria dos dois ponteiros
    free(nome);
    free(aux);

    return(0);
}