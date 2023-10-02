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

int deletar(long cpf, int cont, struct contas *t) {
    //printf("Entre com o CPF que vpcê deseja deletar: ");
    //scanf("%ld", &cpf);
    //buscar_cpf(cpf_recebido, armazena,cont);
    int teste;
    do {
        printf("Entre com o CPF que voce deseja deletar:  \n");
        scanf("%ld", &cpf);
        teste = buscar_cpf(cpf, t, cont);
        if (teste == -1) {
            printf("CPF inexistente, tente novamente.\n");
        }
    } while (teste == -1);

    for (int i = teste; i < cont; i++) {
        t[i] = t[i + 1];
    }
    printf("Conta deletada !\n");
    return 0;







    /**
    char *p_posicao, s_posicao[100];
    fgets(s_posicao, sizeof(s_posicao), stdin);

    posicao = strtol(s_posicao, &p_posicao, 10);
    if(p_posicao == s_posicao || *p_posicao != '\n') {
        printf("Input invalido. Entre somente com numeros inteiros.\n\n");
        return 1;
    }
    else if(posicao <= 0 && cont > 1 || posicao > cont && cont > 1){
        printf("Numero invalido! Entre um numero entre 1 e %d\n\n", cont);
        return 1;
    }
    else if(cont == 0){
        printf("Voce nao tem nenhuma tarefa registrada.\n\n");
        return 1;
    }
    else if(posicao <= 0 && cont == 1 || posicao > cont && cont == 1){
        printf("Numero invalido! Voce tem somente 1 tarefa registrada.\n\n");
        return 1;
    }
    else{
        //printf("erro\n");
        //printf("%d\n",posicao - 1);
        //printf("%d\n",cont);
        for(int i = posicao - 1; i < cont ; i++){
            //printf("%d\n", i);
            //printf("%d\n", posicao);
            //printf("%d\n", cont);
            t[i] = t[i + 1];
        }
        printf("Tarefa deletada\n\n");
        return 0;
    }
}
**/
}