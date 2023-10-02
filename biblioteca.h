//
// Created by uniflusantos on 19/09/2023.
//

#ifndef UNTITLED_BIBLIOTECA_H
#define UNTITLED_BIBLIOTECA_H

struct contas{
    char nome[100];
    long cpf;
    int tipo_conta;
    int valor_inicial;
    char senha[100];
};



int buscar_cpf(long cpf, struct contas*t, int cont);


void limpa_buffer();

int le_informacoes(struct contas *armazena, int cont);

void listar_contas(int cont, struct contas *t);

int deletar(long cpf, int cont, struct contas *t);
#endif //UNTITLED_BIBLIOTECA_H