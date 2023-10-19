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
        printf("Digite o tipo de conta que deseja criar(1 para conta comum e 2 para conta plus): \n");
        scanf("%d", &teste_conta);

        if(teste_conta != 1 && teste_conta != 2){
            printf("Tipo de conta invalido. Entre com 1 para conta comum ou 2 para conta plus.\n");
        }
    } while(teste_conta < 1 || teste_conta > 2);
    armazena[cont].tipo_conta = teste_conta;
    limpa_buffer();

    printf("Digite o saldo inicial da conta: \n");
    scanf("%lf", &armazena[cont].valor_inicial);
    limpa_buffer();

    printf("Digite a senha: \n");
    scanf(" %[^\n]", armazena[cont].senha);
    limpa_buffer();
    armazena[cont].operacoes = 0;

}



int deletar(int cont, struct contas *t) {
    //printf("Entre com o CPF que vpcê deseja deletar: "); (debug)
    //scanf("%ld", &cpf); (debug)
    //buscar_cpf(cpf_recebido, armazena,cont); (debug)

    long cpf;

    if(cont ==0){
        printf("Nao existem contas cadastradas ainda.");
        return 1;
    }
    else {
        int teste;
        printf("Entre com o CPF que voce deseja deletar:  \n");
        scanf("%ld", &cpf);
        teste = buscar_cpf(cpf, t, cont);
        //printf("posicao delete: %d\n",teste); (debug)
        if (teste == -1) {
            printf("CPF inexistente, tente novamente.\n");
            limpa_buffer();
            return 1;
        }

        for (int i = teste; i < cont; i++) {
            t[i] = t[i + 1];
        }
        printf("Conta deletada !\n");
        limpa_buffer();
        return 0;
    }
}

void listar_contas(int cont, struct contas *t){
    if(cont ==0){
        printf("Nao existem contas cadastradas ainda.");
    }
    else {
        printf("Lista de Contas: \n\n");
        for (int x = 0; x < cont; x++) {
            printf("Conta %d\n", x + 1);
            printf("Nome: %s\n", t[x].nome);
            printf("CPF: %ld\n", t[x].cpf);
            if (t[x].tipo_conta == 1) {
                printf("Tipo de conta: Comum\n");
            } else if (t[x].tipo_conta == 2) {
                printf("Tipo de conta: Plus\n");
            }
            printf("Valor inicial: %.2lf\n", t[x].valor_inicial);
            printf("Senha: %s\n\n", t[x].senha);
        }
    }
}


void debitar(int cont, struct contas *t) {
    long cpf;
    int aux;
    if (cont == 0) {
        printf("Nao existem contas cadastradas ainda.\n");
    }
    else {

        printf("Entre com o CPF que voce deseja debitar um saldo: ");
        scanf("%ld", &cpf);
        printf("\n");
        aux = buscar_cpf(cpf, t, cont);
        //printf(" posicao: %d\n",aux); (debug)
        if (aux == -1) {
            printf("CPF nao registrado.\n\n");
            limpa_buffer();
        } else {
            char senha_[200];
            printf("Digite a senha: ");
            scanf("%s", senha_);
            int r = strcmp(senha_, t[aux].senha);
            if (r == 0) {
                double valor;
                printf("Digite o valor que voce deseja debitar: ");
                scanf("%lf", &valor);
                //printf("posicao: %d\n", aux);
                if (t[aux].tipo_conta == 1 && t[aux].valor_inicial - valor - (0.05 * valor) < -1000) {
                    printf("Sua conta nao possui saldo suficiente para realizar esse debito.\n\n");
                    limpa_buffer();
                }
                else if (t[aux].tipo_conta == 1 && t[aux].valor_inicial - valor - (0.05 * valor) > -1000) {
                    t[aux].valor_inicial = t[aux].valor_inicial - valor - (0.05 * valor);
                    printf("Valor debitado com sucesso!\n\n");
                    t[aux].lista[t[aux].operacoes].tipo = 1;
                    t[aux].lista[t[aux].operacoes].cpf_origem = t[aux].cpf;
                    t[aux].lista[t[aux].operacoes].saida = valor + (0.05 * valor);
                    t[aux].lista[t[aux].operacoes].juros = 0.05 * valor;
                    t[aux].operacoes++;
                    limpa_buffer();

                } else if (t[aux].tipo_conta == 2 && t[aux].valor_inicial - valor - (0.03 * valor) < -5000) {
                    printf("Sua conta nao possui saldo suficiente para realizar esse debito.\n\n");
                    limpa_buffer();

                } else if (t[aux].tipo_conta == 2 && t[aux].valor_inicial - valor - (0.03 * valor) > -5000) {
                    t[aux].valor_inicial = t[aux].valor_inicial - valor - (0.03 * valor);
                    printf("Valor debitado com sucesso!\n\n");
                    t[aux].lista[t[aux].operacoes].tipo = 1;
                    t[aux].lista[t[aux].operacoes].cpf_origem = t[aux].cpf;
                    t[aux].lista[t[aux].operacoes].saida = valor + (0.03 * valor);
                    t[aux].lista[t[aux].operacoes].juros = 0.03 * valor;
                    t[aux].operacoes++;
                    limpa_buffer();
                }
            } else {
                printf("Senha invalida!\n\n");
                limpa_buffer();
            }
        }
    }
}
void deposito(int cont, struct contas *t ){
    long cpf;
    int aux;
    if(cont == 0){
        printf("Nao existem contas cadastradas ainda.");
    }
    else {

        printf("Entre com o CPF que voce deseja debitar um saldo: ");
        scanf("%ld", &cpf);
        printf("\n");
        aux = buscar_cpf(cpf, t, cont);
        //printf(" posicao: %d\n",aux); (debug)
        if (aux == -1) {
            printf("CPF nao registrado.\n\n");
            limpa_buffer();
        } else {
            double valor;
            printf("Digite o valor que voce deseja depositar: ");
            scanf("%lf", &valor);
            //printf("posicao: %d\n", aux); (debug)
            t[aux].valor_inicial = t[aux].valor_inicial + valor;
            t[aux].lista[t[aux].operacoes].tipo = 2;
            t[aux].lista[t[aux].operacoes].cpf_destino = t[aux].cpf;
            t[aux].lista[t[aux].operacoes].entrada = valor;
            t[aux].operacoes++;


            printf("Valor depositado com sucesso!\n\n");
            limpa_buffer();
        }
    }
}

int transferencia(int cont, struct contas *t) {
    long cpf;
    int valor;
    int aux;
    int aux2;
    if(cont < 1){
        printf("Nao existem contas o suficiente para transferir.");
        return 1;
    }
    else {


        printf("Entre o CPF de origem que fara a transferencia: ");

        scanf("%ld", &cpf);
        printf("\n");
        aux = buscar_cpf(cpf, t, cont);
        if (aux == -1) {
            printf("CPF nao registrado.\n\n");
            limpa_buffer();
            return 1;
        } else {
            char senha_[200];
            printf("Digite a senha: ");
            scanf("%s", senha_);
            int r = strcmp(senha_, t[aux].senha);
            if (r != 0) {
                printf("Senha Invalida.\n\n");
                limpa_buffer();
                return 1;
            }
            printf("Digite o CPF da conta de destino: ");
            scanf("%ld", &cpf);
            aux2 = buscar_cpf(cpf, t, cont);
            if (aux2 == -1) {
                printf("CPF nao registrado.\n\n");
                limpa_buffer();
                return 1;
            }
            printf("Digite o valor que deseja transferir: ");
            scanf("%d", &valor);
            if (t[aux].tipo_conta == 1 && t[aux].valor_inicial - valor - (0.05 * valor) < -1000) {
                printf("Sua conta nao possui saldo suficiente para realizar esse debito.\n\n");
                limpa_buffer();
                return 1;
            } else if (t[aux].tipo_conta == 1 && t[aux].valor_inicial - valor - (0.05 * valor) > -1000) {
                t[aux].valor_inicial = t[aux].valor_inicial - valor - (0.05 * valor);
                t[aux].lista[t[aux].operacoes].tipo = 3;
                t[aux].lista[t[aux].operacoes].cpf_origem = t[aux].cpf;
                t[aux].lista[t[aux].operacoes].cpf_destino = t[aux2].cpf;
                t[aux].lista[t[aux].operacoes].saida = valor + (0.05 * valor);
                t[aux].lista[t[aux].operacoes].juros = 0.05 * valor;
                t[aux].operacoes++;
            } else if (t[aux].tipo_conta == 2 && t[aux].valor_inicial - valor - (0.03 * valor) < -5000) {
                printf("Sua conta nao possui saldo suficiente para realizar esse debito.\n\n");
                limpa_buffer();
                return 1;
            } else if (t[aux].tipo_conta == 2 && t[aux].valor_inicial - valor - (0.03 * valor) > -5000) {
                t[aux].valor_inicial = t[aux].valor_inicial - valor - (0.03 * valor);
                t[aux].lista[t[aux].operacoes].tipo = 3;
                t[aux].lista[t[aux].operacoes].cpf_origem = t[aux].cpf;
                t[aux].lista[t[aux].operacoes].cpf_destino = t[aux2].cpf;
                t[aux].lista[t[aux].operacoes].saida = valor + (0.03 * valor);
                t[aux].lista[t[aux].operacoes].juros = 0.03 * valor;
                t[aux].operacoes++;
            }
            t[aux2].valor_inicial = t[aux2].valor_inicial + valor;
            t[aux2].lista[t[aux2].operacoes].tipo = 4;
            t[aux2].lista[t[aux2].operacoes].cpf_origem = t[aux].cpf;
            t[aux2].lista[t[aux2].operacoes].cpf_destino = t[aux2].cpf;
            t[aux2].lista[t[aux2].operacoes].entrada = valor;
            t[aux2].operacoes++;
            limpa_buffer();
            printf("Transferencia realizada com sucesso!\n\n");
            return 0;
        }
    }
}


void extrato_funcao(int cont, struct contas *t){

    long cpf;

    if(cont == 0){
        printf("Nao existem contas cadastradas ainda.");
        //limpa_buffer();
    }
    else {
        int verifica;
        printf("Entre com o CPF que voce deseja ver o extrato: \n");
        scanf("%ld", &cpf);
        printf("\n");
        verifica = buscar_cpf(cpf, t, cont);
        if (verifica == -1) {
            printf("CPF nao registrado. \n");
            //limpa_buffer();
        } else {
            char senha_[200];
            printf("Digite a senha: ");
            scanf("%s", senha_);
            int r = strcmp(senha_, t[verifica].senha);
            if (r == 0) {
                printf("\nExtrato aqui: \n\n");
                for(int i = 0 ; i < t[verifica].operacoes;i++){
                    if(t[verifica].lista[i].tipo ==  2){
                        printf("Valor depositado: %.2lf\n",t[verifica].lista[i].entrada);
                        printf("CPF de destino: %ld\n \n \n",t[verifica].lista[i].cpf_destino);


                    }
                    else if (t[verifica].lista[i].tipo ==  1){
                        printf("Valor debitado: %.2lf\n",t[verifica].lista[i].saida - t[verifica].lista[i].juros);
                        printf("CPF de origem: %ld\n",t[verifica].lista[i].cpf_origem);
                        printf("Juros: %.2lf\n \n \n", t[verifica].lista[i].juros);

                    }
                    else if(t[verifica].lista[i].tipo ==  3){

                        printf("Valor transferido: %.2lf\n",t[verifica].lista[i].saida-t[verifica].lista[i].juros);
                        printf("da conta do CPF : %ld\n",t[verifica].lista[i].cpf_origem);
                        printf("para a conta do  CPF : %ld\n",t[verifica].lista[i].cpf_destino);
                        printf("Juros: %.2lf\n \n \n", t[verifica].lista[i].juros);

                    }

                    else if(t[verifica].lista[i].tipo ==  4){

                        printf("Valor recebido: %.2lf\n",t[verifica].lista[i].entrada);
                        printf("da conta do CPF : %ld\n",t[verifica].lista[i].cpf_origem);
                        printf("para a conta do  CPF : %ld\n \n \n",t[verifica].lista[i].cpf_destino);


                    }
                }

            }
            else {
                printf("Senha invalida!\n");
                //limpa_buffer();
            }

        }
        limpa_buffer();
    }
}

int le_binario(struct contas *t) {
    FILE *arquivo_binario = fopen("binario.txt", "rb");
    int y = 0;
    if (arquivo_binario) {
        while (fread(&t[y], sizeof(struct contas), 1, arquivo_binario) == 1) {
            y++;
        }
        return y;

    }
    return 0;
}

void escreve_binario(struct contas *t, int cont) {
    FILE *arquivo_binario;
    arquivo_binario = fopen("binario.txt", "wb");
    //printf("%p\n", arquivo_binario);
    if (arquivo_binario) {
        //printf("entrou\n");

        //printf("%d\n", t->prioridade);
        fwrite(t, sizeof(struct contas), cont, arquivo_binario);

        fclose(arquivo_binario);
    }

}