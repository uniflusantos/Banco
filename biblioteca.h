//
// Created by uniflusantos on 19/09/2023.
//

#ifndef UNTITLED_BIBLIOTECA_H
#define UNTITLED_BIBLIOTECA_H

//criando struct para os registrar os extratos dos usuários.
typedef struct extrato {
    long cpf_origem;
    long cpf_destino;
    double entrada;
    double saida;
    double juros;
    int tipo;


}extrato;

//criando struct para registrar od dados cos usuários.
typedef struct contas{
    char nome[100];
    long cpf;
    int tipo_conta;
    double valor_inicial;
    char senha[100];
    struct extrato lista[100];
    int operacoes;


}Contas;





//funcao busca_cpf recebe o cpf, ponteiro da struct da nossas contas e contador como parametro.
int buscar_cpf(long cpf, struct contas*t, int cont);


void limpa_buffer();

//funcao le_informacoes recebe ponteiro da struct de clientes e cont como parametro
void le_informacoes(struct contas *armazena, int cont);

//funcao listar_contas recebe cont e ponteiro da struct de clientes
void listar_contas(int cont, struct contas *t);

//funcao deletar recebe cont e ponteiro da struct de clientes
int deletar(int cont, struct contas *t);

//funcao debitar recebe cont e ponteiro da struct de clientes
void debitar(int cont, struct contas *t);

//funcao deposito recebe cont e ponteiro da struct de clientes
void deposito(int cont, struct contas *t);

//funcao transferencia recebe cont e ponteiro da struct de clientes
int transferencia(int cont, struct contas *t);

//funcao extrato_funcao recebe cont e ponteiro da struct de clientes
void extrato_funcao(int cont, struct contas *t);

//funcao le_binario recebe ponteiro do cont e ponteiro da struct de clientes
int le_binario(struct contas *t, int *cont);

//funcao escrve_binario recebe cont e ponteiro da struct de clientes
void escreve_binario(struct contas *t, int cont);

#endif //UNTITLED_BIBLIOTECA_H