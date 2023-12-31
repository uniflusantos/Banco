#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca.h"

// funcao limpa buffer vai ser chamada para não dar erro no scanf.
void limpa_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

//funcao de buscar cpf serve para verificar se já existe um cpf existente, caso ele não existe ira me retornar -1 e se ja houver alguem com esse cpf ira retornar a posição do usuario dentro do vetor.
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


//funcao le_informaçoes serve para pegar as informaçoes dos usuarios e armazenar dentro do nosso vetor de struct,tambem utilizamos um contador(cont) para saber quantos usuarios cadastrados,
// e armazenar as informacoes na posicao correta. Além disso, é usado o limpa buffer para não dar erro no scanf.
//Na função usamos tambem o while, para caso o cpf que voce digitou ja foi usado por outro usuario, peça de novo a informacao de cpf.
// E usamos um while parecido para pedir o tipo de conta.
void le_informacoes(struct contas *armazena, int cont){
    long cpf_recebido;
    int teste;
    int teste_conta;
        do{
            printf("Digite seu CPF: \n");
            scanf("%ld", &cpf_recebido);
            teste = buscar_cpf(cpf_recebido, armazena,cont);
            if(teste > -1){
                printf("CPF invalido, tente novamente.\n");
            }
        }while(teste > -1);

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


/* Na funcao deletar, a primeira verificação serve para ver se ja existem contas cadastradas, caso não exista irá aparecer uma mensagem notificando o usuário.
 E se já houver contas cadastradas, vamos pedir o CPF do usuário, e com a funcao buscar_cpf, irá nos retornar a posicao do cpf dentro do vetor de struct, dessa forma
 o laco for procura por esse numero no vetor de struct de clientes e a deleta, rearrumando a lista. E o nosso contador de usuarios vai diminuir 1.
 */


int deletar(int cont, struct contas *t) {
    //printf("Entre com o CPF que vpcê deseja deletar: "); (debug)
    //scanf("%ld", &cpf); (debug)
    //buscar_cpf(cpf_recebido, armazena,cont); (debug)

    long cpf;

    if(cont ==0){
        printf("Nao existem contas cadastradas ainda.\n");
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

/*Na função listar_contas, vai verificar se já existe contas cadastradas, caso não exista nenhuma conta irá aparecer uma mensagem notificando o usuário. E se houver contas cadastradas
 o laço for serve para passar por todos os clientes que estao dentro do nosso vetor e printar as informações deles.
 */

void listar_contas(int cont, struct contas *t){
    if(cont ==0){
        printf("Nao existem contas cadastradas ainda.\n");
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

/*funcao de debitar vai verificar se já existe contas cadastradas, caso não exista nenhuma conta irá aparecer uma mensagem notificando o usuário. E se houver contas cadastradas, iremos
 pedir o CPF do usuário e chamaremos a nossa funcao de buscar_cpf, que caso nao exista esse cpf registrado ira notificar o usuario, e se houver ira pedir a senha dele, e usamos a funcao strcmp
 para verificar se a senha está correta. Após isso, iremos verificar o tipo de conta comum ou plus, se for comum ao debitar um saldo sera cobrado uma taxa de 5% e conta pode ficar 1000 negativas.
 E se a conta for plus, será cobrado uma taxa de 3% ao debitar  do saldo e pode ficar 5000 negativas.
 tipo de conta recebe 1, que vai ser utilizado no extrato para verificar as operacoes.*/
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
                else if (t[aux].tipo_conta == 1 && t[aux].valor_inicial - valor - (0.05 * valor) >= -1000) {
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

                } else if (t[aux].tipo_conta == 2 && t[aux].valor_inicial - valor - (0.03 * valor) >= -5000) {
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

/*funcao de deposito vai verificar se já existe contas cadastradas, caso não exista nenhuma conta irá aparecer uma mensagem notificando o usuário. E se houver contas cadastradas, iremos
 pedir o CPF do usuário e chamaremos a nossa funcao de buscar_cpf, que caso nao exista esse cpf registrado ira notificar o usuario, se houver conta cadastradaa funcao retorna
 a posicao do cliente dentro do vetor, assim iremos acrescentar um saldo na conta do usuario,utilizando a  => t[aux].valor_inicial = t[aux].valor_inicial + valor;
 tipo de conta recebe 2, que vai ser utilizado no extrato para verificar as operacoes. */


void deposito(int cont, struct contas *t ){
    long cpf;
    int aux;
    if(cont == 0){
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


/*funcao de transferencia vai verificar se já existe contas cadastradas, caso não exista contas suficientes irá aparecer uma mensagem notificando o usuário. E se houver contas cadastradas o suficiente
  para fazer a transferencia, iremos pedir o CPF do usuário que vai dar o dinheiro, e usaremos funcao buscar_cpf que ira nos retornar a posicao do usuario e dps disso usamos a funcao strcmp
  para ver se a senha esta correta. Após isso, iremos verificar o tipo de conta comum ou plus, se for comum ao debitar um saldo sera cobrado uma taxa de 5% e conta pode ficar 1000 negativas.
 E se a conta for plus, será cobrado uma taxa de 3% ao debitar  do saldo e pode ficar 5000 negativas. Depois disso, iremos pedir o cpf da conta que vai receber o dinheiro e iremos acresecntar
 esse dinheiro na conta desse ususario. tipo de conta recebe 3, que vai ser utilizado no extrato para verificar as operacoes.*/
int transferencia(int cont, struct contas *t) {
    long cpf;
    int valor;
    int aux;
    int aux2;
    if(cont <= 1){
        printf("Nao existem contas o suficiente para transferir.\n");
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
            } else if (t[aux].tipo_conta == 1 && t[aux].valor_inicial - valor - (0.05 * valor) >= -1000) {
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
            } else if (t[aux].tipo_conta == 2 && t[aux].valor_inicial - valor - (0.03 * valor) >= -5000) {
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

/*Na funcao extrato de funcao vamos verificar se ja existem contas cadastradas para verificar o extrato, depois disso vamos usar nossa funcao busca_cpf, que vai retornar a posicao do cliente
 cadastrado e tambem iremos pedir a senha e vrificar se esta correta utilizando o strcmp.E dependendo do tipo de conta ira aparecer deposito,debito ou transferencia. E usamos
 FILE *f = fopen("extrato.txt", "wb") no comeco da funcao para guardar as informacoes em arquivo txt, e no final de tudo usamos o  fclose(f) para fecahr arquivo.
 */
void extrato_funcao(int cont, struct contas *t){

    long cpf;

    if(cont == 0){
        printf("Nao existem contas cadastradas ainda.\n");
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
                FILE *f = fopen("extrato.txt", "wb");
                fprintf(f, "\nExtrato aqui: \n\n");
                for(int i = 0 ; i < t[verifica].operacoes;i++){
                    if(t[verifica].lista[i].tipo ==  2){
                        fprintf(f, "Valor depositado: %.2lf\n",t[verifica].lista[i].entrada);
                        fprintf(f, "CPF de destino: %ld\n \n \n",t[verifica].lista[i].cpf_destino);


                    }
                    else if (t[verifica].lista[i].tipo ==  1){
                        fprintf(f, "Valor debitado: %.2lf\n",t[verifica].lista[i].saida - t[verifica].lista[i].juros);
                        fprintf(f, "CPF de origem: %ld\n",t[verifica].lista[i].cpf_origem);
                        fprintf(f, "Juros: %.2lf\n \n \n", t[verifica].lista[i].juros);

                    }
                    else if(t[verifica].lista[i].tipo ==  3){

                        fprintf(f, "Valor transferido: %.2lf\n",t[verifica].lista[i].saida-t[verifica].lista[i].juros);
                        fprintf(f, "da conta do CPF : %ld\n",t[verifica].lista[i].cpf_origem);
                        fprintf(f, "para a conta do  CPF : %ld\n",t[verifica].lista[i].cpf_destino);
                        fprintf(f, "Juros: %.2lf\n \n \n", t[verifica].lista[i].juros);

                    }

                    else if(t[verifica].lista[i].tipo ==  4){

                        fprintf(f,"Valor recebido: %.2lf\n",t[verifica].lista[i].entrada);
                        fprintf(f,"da conta do CPF : %ld\n",t[verifica].lista[i].cpf_origem);
                        fprintf(f,"para a conta do  CPF : %ld\n \n \n",t[verifica].lista[i].cpf_destino);


                    }
                }
                fclose(f);

            }
            else {
                printf("Senha invalida!\n");
                //limpa_buffer();
            }

        }
        limpa_buffer();
    }
}
/* funcao le_binario le todas as informacoes dos clientes como arquivo binario */
int le_binario(struct contas *t, int *cont) {
    FILE *arquivo_binario;
    arquivo_binario = fopen("binario", "rb");
    if (arquivo_binario) {

        fread(cont, sizeof(int), 1, arquivo_binario);
        //printf("%d\n", *cont);



        fread(t, sizeof(struct contas), 1000, arquivo_binario);

        return 0;
    }
    else{
        return 1;
    }
}

/* funcao le_binario escreve todas as informacoes dos clientes para arquivo binario */
void escreve_binario(struct contas *t, int cont) {
    FILE *arquivo_binario;
    arquivo_binario = fopen("binario", "wb");
    //printf("%p\n", arquivo_binario);
    if (arquivo_binario) {
        //printf("entrou\n");

        //printf("%d\n", t->prioridade);
        fwrite(&cont, sizeof(int), 1, arquivo_binario);

        fwrite(t, sizeof(struct contas), 1000, arquivo_binario);

        fclose(arquivo_binario);
    }
    else{
        printf("Erro ao abrir o arquivo\n");
    }

}
