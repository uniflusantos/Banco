//
// Created by uniflusantos on 19/09/2023.
//

#ifndef UNTITLED_BIBLIOTECA_H
#define UNTITLED_BIBLIOTECA_H

typedef struct extrato {
    long cpf_origem;
    long cpf_destino;
    double entrada;
    double saida;
    double juros;
    int tipo;


}extrato;

typedef struct contas{
    char nome[100];
    long cpf;
    int tipo_conta;
    double valor_inicial;
    char senha[100];
    struct extrato lista[100];
    int operacoes;


}Contas;






int buscar_cpf(long cpf, struct contas*t, int cont);


void limpa_buffer();

void le_informacoes(struct contas *armazena, int cont);

void listar_contas(int cont, struct contas *t);

int deletar(long cpf, int cont, struct contas *t);

void debitar(long cpf, int cont, struct contas *t);

void deposito(long cpf, int cont, struct contas *t);

int transferencia(long cpf, int cont, struct contas *t, struct contas *armazena);

void extrato_funcao(long cpf, int cont, struct contas *t);

int le_binario(struct contas *t);

void escreve_binario(struct contas *t, int cont);

#endif //UNTITLED_BIBLIOTECA_H