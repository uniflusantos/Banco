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
        //printf("indice :%d \n", i); (debug)
        //printf("cpf1: %ld \n", t[i].cpf); (debug)
        //printf("cpf2: %ld \n", cpf);(debug)
        //printf("saida %d \n", saida); (debug)
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



void le_informacoes(struct contas *armazena, int cont){
    long cpf_recebido;
    int teste;
    int teste_conta;
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

    do{
        printf("Digite o tipo de conta que deseja criar: \n");
        scanf("%d", &teste_conta);

        if(teste_conta != 1 && teste_conta != 2){
            printf("Tipo de conta invalido. Entre com 1 para conta comum ou 2 para conta plus.\n");
        }
    } while(teste_conta < 1 || teste_conta > 2);
    armazena[cont].tipo_conta = teste_conta;
    limpa_buffer();

    printf("Digite o saldo inicial da conta: \n");
    scanf("%d", &armazena[cont].valor_inicial);
    limpa_buffer();

    printf("Digite a senha: \n");
    scanf(" %[^\n]", armazena[cont].senha);
    limpa_buffer();
}



int deletar(long cpf, int cont, struct contas *t) {
    //printf("Entre com o CPF que vpcê deseja deletar: "); (debug)
    //scanf("%ld", &cpf); (debug)
    //buscar_cpf(cpf_recebido, armazena,cont); (debug)
    int teste;
    do {
        printf("Entre com o CPF que voce deseja deletar:  \n");
        scanf("%ld", &cpf);
        teste = buscar_cpf(cpf, t, cont);
        //printf("posicao delete: %d\n",teste); (debug)
        if (teste == -1) {
            printf("CPF inexistente, tente novamente.\n");
        }
    } while (teste == -1);

    for (int i = teste; i < cont; i++) {
        t[i] = t[i + 1];
    }
    printf("Conta deletada !\n");
    return 0;

}

void listar_contas(int cont, struct contas *t){
    for(int x = 0; x < cont; x++){
        printf("Conta %d\n", x + 1);
        printf("Nome: %s\n", t[x].nome);
        printf("CPF: %ld\n", t[x].cpf);
        if(t[x].tipo_conta == 1){
            printf("Tipo de conta: Comum\n");
        }
        else if(t[x].tipo_conta == 2){
            printf("Tipo de conta: Plus\n");
        }
        printf("Valor inicial: %d\n", t[x].valor_inicial);
        printf("Senha: %s\n\n", t[x].senha);
    }
}


void debitar(long cpf, int cont, struct contas *t){
    int aux;

    printf("Entre com o CPF que você deseja debitar um saldo: ");
    scanf("%ld", &cpf);
    printf("\n");
    aux = buscar_cpf(cpf, t, cont);
    //printf(" posicao: %d\n",aux); (debug)
    if(aux == -1){
        printf("CPF inexistente.\n");
    }

    else{
        char senha_[200];
        printf("Digite a senha: ");
        scanf("%s",senha_);
        int r = strcmp (senha_,t[aux].senha);
        if(r == 0){
            int valor;
            printf("Digite o valor que você deseja debitar: ");
            scanf("%d", &valor);
            //printf("posicao: %d\n", aux);
            t[aux].valor_inicial =  t[aux].valor_inicial - valor;
            printf("valor debitado");

        }
        else{
            printf("Senha invalida !\n");
        }


    }

}

void deposito(long cpf, int cont, struct contas *t){
    int aux;

    printf("Entre com o CPF que você deseja debitar um saldo: ");
    scanf("%ld", &cpf);
    printf("\n");
    aux = buscar_cpf(cpf, t, cont);
    //printf(" posicao: %d\n",aux); (debug)
    if(aux == -1){
        printf("CPF inexistente.\n");
    }

    else{
        int valor;
        printf("Digite o valor que você deseja depositar: ");
        scanf("%d", &valor);
        //printf("posicao: %d\n", aux); (debug)
        t[aux].valor_inicial =  t[aux].valor_inicial + valor;
        printf("valor depositado");

    }
}



