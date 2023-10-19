#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    Contas *t = malloc(sizeof(Contas)*1000);
    int cont = 0;
    cont = le_binario(t);
    int posicao = 0;

    while (1) {
        printf("\nMenu de opcoes\n\n");
        printf("1 - Criar conta\n");
        printf("2 - Deletar conta\n");
        printf("3 - Listar Clientes\n");
        printf("4 - Realizar debito\n");
        printf("5 - Realizar deposito\n");
        printf("6 - Mostrar extrato\n");
        printf("7 - Realizar transferencia\n");
        printf("8 - Sair\n\n");
        printf("Digite o numero da opcao que deseja usar: ");

        char *p, s_opcao[100];
        int opcao;
        fgets(s_opcao, 100, stdin);
        opcao = strtol(s_opcao, &p, 10);

        if (opcao == 1) {
            //printf("\nVoce entrou na funcao de criar contas.\n\n");

            le_informacoes(t, cont);
            //buscar_cpf(t[cont].cpf,t,cont);
            cont++;

            printf("Conta cadastrada com sucesso!\n");
        }

        else if (opcao == 2) {
            printf("\nVoce entrou na funcao de deletar contas.\n");
            int verifica = deletar(cont,t);
            if(verifica == 0){
                cont--;
            }
        }

        else if (opcao == 3) {
            printf("\nVoce entrou na funcao de listar clientes.\n\n");
            listar_contas(cont, t);
        }

        else if (opcao == 4) {
            printf("\nVoce entrou na funcao de realizar debitos.\n");
            debitar(cont,t);
        }

        else if (opcao == 5) {
            printf("\nVoce entrou na funcao de realizar depositos.\n");
            deposito(cont,t);
        }

        else if (opcao == 6) {
            printf("\nVoce entrou na funcao de mostrar extrato.\n");
            extrato_funcao(cont,t);
        }
        else if (opcao == 7) {
            printf("\nVoce entrou na funcao de realizar transferencias.\n");
            transferencia(cont, t);
        }

        else if (opcao == 8) {
            printf("\nSaindo do programa");
            escreve_binario(t, cont);
            break;
        }
    }

}
