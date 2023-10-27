#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    //aqui estamos declarando o tamanho do nosso vetor de struct dos clientes que ira receber 1000.
    Contas *t = malloc(sizeof(Contas)*1000);

    // declaracao do contador que vai armazenar os numeros de cadastros de clientes.
    int cont = 0;

    //chamamos a funcao le_binario no comeco do codigo para salvar tudo.
    le_binario(t, &cont);

    //menu de opcoes
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
        // vai pedir informaçao como se fosse um scanf.
        fgets(s_opcao, 100, stdin);
        opcao = strtol(s_opcao, &p, 10);

        // se vc escolher a opcao 1, voce ira criar conta, entao iremos chamar a funcao de le_informcaoes, e tbm adicionamos +1 ao nosso contador mostrando que esta aumentando o numero de cadastros.
        if (opcao == 1) {


            le_informacoes(t, cont);

            cont++;

            printf("Conta cadastrada com sucesso!\n");
        }

        // se vc escolher a opcao 2, voce ira deletar conta, entao iremos chamar a funcao de deletar, e tbm subtraimos -1 ao nosso contador mostrando que esta apagando os nossos cadastros.
        else if (opcao == 2) {
            printf("\nVoce entrou na funcao de deletar contas.\n");
            int verifica = deletar(cont,t);
            if(verifica == 0){
                cont--;
            }
        }

        // se vc escolher a opcao 3, voce ira listar as contas, entao iremos chamar a funcao de lista_contas, dessa forma mostrando os nossos usuarios cadastrados.
        else if (opcao == 3) {
            printf("\nVoce entrou na funcao de listar clientes.\n\n");
            listar_contas(cont, t);
        }

        // se vc escolher a opcao 4, voce ira debitar um saldo na conta, entao iremos chamar a funcao de debitar, dessa forma debitando o saldo do cliente.
        else if (opcao == 4) {
            printf("\nVoce entrou na funcao de realizar debitos.\n");
            debitar(cont,t);
        }

        // se vc escolher a opcao 5, voce ira depositar um saldo na conta, entao iremos chamar a funcao de deposito, dessa forma depositando o saldo do cliente.
        else if (opcao == 5) {
            printf("\nVoce entrou na funcao de realizar depositos.\n");
            deposito(cont,t);
        }

        // se vc escolher a opcao 6, voce ira visualizar o extrato da conta que voce deseja, entao iremos chamar a funcao de extrato_funcao, dessa forma mostrando o extrato.
        else if (opcao == 6) {
            printf("\nVoce entrou na funcao de mostrar extrato.\n");
            extrato_funcao(cont,t);
        }

        // se vc escolher a opcao 7, voce ira realizar transferencia de contas, entao iremos chamar a funcao de transferencia, dessa forma realizaremos as operacoes entre contas.
        else if (opcao == 7) {
            printf("\nVoce entrou na funcao de realizar transferencias.\n");
            transferencia(cont, t);
        }

        // se vc escolher opcao 8 ira sair do programa.
        else if (opcao == 8) {
            printf("\nSaindo do programa");
            escreve_binario(t, cont);
            break;
        }

        // se vc escolher uma opcao diferente das opcoes do menu ira aparecer uma mensagem de erro.
        else if (opcao > 8 || p == s_opcao || *p != '\n' || opcao < 1) {
            printf("Input invalido. Entre somente com valores inteiros entre 1 e 8.\n\n");
        }
    }

}
