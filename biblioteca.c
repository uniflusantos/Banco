#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca.h"

void limpa_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}


int buscar_cpf(long cpf, struct contas*t, int cont){
    int saida = -1;
    for(int i = 0; i < cont; i++){
        if(t[i].cpf == cpf){
            saida = i;
        }
        printf("indice :%d \n", i);
        printf("cpf1: %ld \n", t[i].cpf);
        printf("cpf2: %ld \n", cpf);
        printf("saida %d \n", saida);
    }
    return saida;
}

/**int verifica_cpf(long cpf, struct contas *armazena,int cont){
  int saida =0;
  printf("cont: %d\n", cont);
  for(int i = 0;i <= cont;i++){
    printf("cpf passado: %ld\n", cpf);
    printf("cpf armazenado: %ld\n", armazena[i].cpf);
    if(armazena[i].cpf == cpf){
      saida = 1;  
    }
  }
  printf("saida: %d\n", saida);
  return saida;
}
**/



int le_informacoes(struct contas *armazena, int cont){
    long cpf_recebido;
    int teste;
    if(cont>=0){
        do{
            printf("Digite seu CPF: \n");
            scanf("%ld", &cpf_recebido);
            teste = buscar_cpf(cpf_recebido, armazena,cont);
            if(teste > -1){
                printf("CPF invalido, tente novamente.\n");
            }
        }while(teste > -1);
    };

    armazena[cont].cpf = cpf_recebido;

    limpa_buffer();

    printf("Digite seu nome: \n");
    scanf("%[^\n]", armazena[cont].nome);
    limpa_buffer();

    printf("Digite o tipo de conta que deseja criar: \n");
    scanf("%d", &armazena[cont].tipo_conta);
    limpa_buffer();


    printf("Digite o saldo inicial da conta: \n");
    scanf("%d", &armazena[cont].valor_inicial);
    limpa_buffer();

    printf("Digite a senha: \n");
    scanf(" %[^\n]", armazena[cont].senha);
    limpa_buffer();
}



void listar_contas(int cont, struct contas *t){
    for(int x = 0; x < cont; x++){
        printf("Conta %d\n", x + 1);
        printf("Nome: %s\n", t[x].nome);
        printf("CPF: %ld\n", t[x].cpf);
        printf("Tipo de conta: %d\n", t[x].tipo_conta);
        printf("Valor inicial: %d\n", t[x].valor_inicial);
        printf("Senha: %s\n\n", t[x].senha);
    }
}