#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CLIENTES 100
#define TAM_NOME 50
#define TAM_CPF 12
#define TAM_TELEFONE 15
#define TAM_EMAIL 30

#define TAM_MENSAGEM 100

typedef struct {
    int teto;
    float valor;
    float valor_bonificar;
} bonus;

typedef struct {
    float valor_compra_sem_bonus;
    float valor_total_da_compra;
    int compra_cancelada;
    bonus bonus_da_compra;
} compra;

typedef struct {
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char telefone[TAM_TELEFONE];
    char email[TAM_EMAIL];
    int bonus;
    float total_em_compras;
    compra ultima_compra;
} cliente;

// Funcoes do menu principal
void mostrar_opcoes_do_menu_principal();
void abrir_menu_principal();
void processar_operacao_do_menu_principal(cliente clientes[NUM_CLIENTES], bonus *bonus_atual,int *indice_atual, int operacao);

// Funcoes do menu cliente
void mostrar_opcoes_do_menu_cliente();
void mostrar_quantidade_de_clientes_cadastrados(int *indice_atual);
void abrir_menu_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual);
void processar_operacao_do_menu_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual, int operacao);
int identificar_cliente_pelo_cpf(cliente clientes[NUM_CLIENTES], char cpf[TAM_CPF], int quantidade);
void cadastrar_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual);
void imprimir_cliente(cliente cliente);
void consultar_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual);
void alterar_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual);
void alterar_cpf_do_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual, int indice_cliente);
void alterar_nome_do_cliente(cliente clientes[NUM_CLIENTES], int indice_cliente);
void alterar_telefone_do_cliente(cliente clientes[NUM_CLIENTES], int indice_cliente);
void alterar_email_do_cliente(cliente clientes[NUM_CLIENTES], int indice_cliente);
void mostrar_opcoes_do_menu_alterar_cliente();
void abrir_menu_alterar_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual, int indice_cliente);
void processar_operacao_do_menu_alterar_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual, int indice_cliente, int operacao);
void remover_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual);

// Funcoes do menu compra
void mostrar_opcoes_do_menu_compra();
void abrir_menu_compra(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual);
void processar_operacao_do_menu_compra(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual, int operacao);
void efetuar_compra(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual);
void cancelar_compra(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual);

// Funcoes do menu bonus
void mostrar_opcoes_do_menu_bonus();
void abrir_menu_bonus(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual);
void processar_operacao_do_menu_bonus(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual, int operacao);
void mostrar_configuracao_do_bonus_atual(bonus *bonus_atual);
void mostrar_opcoes_do_menu_alterar_bonus();
void abrir_menu_alterar_bonus(bonus *bonus_atual);
void processar_operacao_do_menu_alterar_bonus(bonus *bonus_atual, int operacao);
void exibir_bonus(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual);
void imprimir_bonus(cliente cliente, bonus *bonus_atual);

// Funcoes do menu relatorios
void mostrar_opcoes_do_menu_relatorios();
void abrir_menu_relatorios(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual);
void processar_operacao_do_menu_relatorios(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual, int operacao);
void listar_clientes(cliente clientes[NUM_CLIENTES], int *indice_atual);
void listar_bonus(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual);
void listar_clientes_por_total_em_compra(cliente clientes[NUM_CLIENTES], int *indice_atual);

// Funcoes auxiliares
void requisitar_operacao(int *operacao);
void requisitar_cpf(char *cpf);
void requisitar_nome(char *nome);
void requisitar_telefone(char *telefone);
void requisitar_email(char *email);
void inicializar_bonus(bonus *bonus_atual);
void validar_valor_inteiro(int *valor);
void validar_valor_float(float *valor);
void requisitar_novo_valor_de_teto(int *novo_teto);
void requisitar_novo_valor_de_bonus(float *novo_valor_de_bonus);
void requisitar_novo_valor_para_receber_bonus(float *novo_valor_bonificar);
void requisitar_valor_total_em_compra(float *valor_total_em_compra);
void limpar_tela();
void imprimir_mensagem(char mensagem[TAM_MENSAGEM]);
void requisitar_valor_compra(float *valor_compra);
void requisitar_pagamento_cliente(float *valor_pagamento);
void imprimir_encerramento();

int main() {
    abrir_menu_principal();
    imprimir_encerramento();
    return 0;
}

/* Funcoes do menu principal */

/*
Imprime as opcoes do menu principal. Apenas informa o usuario das operacoes do programa.
Nao recebe parametros.
Nao retorna nada.
*/

void mostrar_opcoes_do_menu_principal() {
    printf("\n----- MENU PRINCIPAL -----\n");
    printf("0 - Encerrar programa.\n");
    printf("1 - Acessar menu do cliente.\n");
    printf("2 - Acessar menu de compra.\n");
    printf("3 - Acessar menu de bonus.\n");
    printf("4 - Acessar menu de relatorios.\n");
    printf("5 - Limpar tela.\n");
    printf("\n");
}

/*
Abre o menu principal. Apresenta as opcoes e le/processa a opcao escolhida. Também mantem o menu aberto(loop).
Nao recebe parametros.
Nao retorna nada.
*/

void abrir_menu_principal() {
    int indice_atual = 0;
    int operacao;
    cliente clientes[NUM_CLIENTES];
    bonus bonus_atual;

    inicializar_bonus(&bonus_atual);

    do {
        mostrar_opcoes_do_menu_principal();
        requisitar_operacao(&operacao);
        processar_operacao_do_menu_principal(clientes, &bonus_atual, &indice_atual, operacao);
    } while (operacao);
}

/* 
Processa a operacao escolhida no menu principal. Executa a funcao adequada conforme a escolha.
Recebe um vetor com os clientes cadastrados, a configuracao do bonus atual, o indice atual que identifica o proximo indice "vago" e a operacao escolhida pelo usuario
Nao retorna nada
*/

void processar_operacao_do_menu_principal(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual, int operacao) {
    if (operacao == 0) {}

    else if (operacao == 1) {
        abrir_menu_cliente(clientes, indice_atual);
    }

    else if (operacao == 2) {
        abrir_menu_compra(clientes, bonus_atual, indice_atual);
    }
    
    else if (operacao == 3) {
        abrir_menu_bonus(clientes, bonus_atual, indice_atual);
    }

    else if (operacao == 4) {
        abrir_menu_relatorios(clientes, bonus_atual, indice_atual);
    }

    else if (operacao == 5) {
        limpar_tela();
    }

    else {
        imprimir_mensagem("ERRO: Operacao invalida!");
    }
}

/* Funcoes do menu cliente */

/*
Imprime as opcoes do menu cliente. Apenas informa o usuario das operacoes do programa.
Nao recebe parametros.
Nao retorna nada.
*/

void mostrar_opcoes_do_menu_cliente() {
    printf("\n----- MENU CLIENTE -----\n");
    printf("0 - Retornar para o menu principal.\n");
    printf("1 - Cadastrar cliente.\n");
    printf("2 - Alterar cliente.\n");
    printf("3 - Consultar cliente.\n");
    printf("4 - Remover cliente.\n");
    printf("5 - Limpar tela.\n");
    printf("\n");
}

/*
Abre o menu cliente. Apresenta as opcoes e le/processa a opcao escolhida. Também mantem o menu aberto(loop).
Recebe um vetor contendo todos os clientes cadastrados e um indice atual que serve para identificar o proximo indice "vago".
Nao retorna nada.
*/

void abrir_menu_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual) {
    int operacao;

    do {
        mostrar_quantidade_de_clientes_cadastrados(indice_atual);
        mostrar_opcoes_do_menu_cliente();
        requisitar_operacao(&operacao);
        processar_operacao_do_menu_cliente(clientes, indice_atual, operacao);
    } while (operacao);
}

/*
Mostra a quantidade de clientes cadastrados. Informa ao usuario a quantidade de clientes salvos no sistema.
Recebe o indice atual, a fim de identificar a quantidade.
Nao retorna nada.
*/

void mostrar_quantidade_de_clientes_cadastrados(int *indice_atual) {
    printf("\n%d cliente(s) cadastrado(s).\n", *indice_atual);
}

/* 
Processa a operacao escolhida no menu cliente. Executa a funcao adequada conforme a escolha.
Recebe um vetor com os clientes cadastrados, a configuracao do bonus atual, o indice atual que identifica o proximo indice "vago" e a operacao escolhida pelo usuario
Nao retorna nada
*/

void processar_operacao_do_menu_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual, int operacao) {
    if (operacao == 0) {}

    else if (operacao == 1) {
        cadastrar_cliente(clientes, indice_atual);
    }

    else if (operacao == 2) {
        alterar_cliente(clientes, indice_atual);
    }
    
    else if (operacao == 3) {
        consultar_cliente(clientes, indice_atual);
    }

    else if (operacao == 4) {
        remover_cliente(clientes, indice_atual);
    }

    else if (operacao == 5) {
        limpar_tela();
    }

    else {
        imprimir_mensagem("ERRO: Operacao invalida!");
    }
}

/*
Identifica o cliente pelo cpf. Busca o cliente no vetor ate o ultimo cadastrado atraves do cpf.
Recebe um vetor com os clientes cadastrados, uma variavel com o cpf a ser buscado e a quantidade de clientes cadastrados ate entao.
Retorna o indice do cliente no vetor, se encontrado. Caso contrario, retorna -1.
*/

int identificar_cliente_pelo_cpf(cliente clientes[NUM_CLIENTES], char cpf[TAM_CPF], int quantidade) {
	int i;

	for(i = 0; i < quantidade; i++){
		if (strcmp(clientes[i].cpf, cpf) == 0){
			return i;
		}
	}

	return -1;
}

/*
Cadastra o cliente. Insere uma variavel do tipo cliente no vetor clientes.
Recebe um vetor do tipo cliente e uma variavel que identifica o proximo indice "vago"
Nao retorna nada.
*/

void cadastrar_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual) {
    if (*indice_atual == NUM_CLIENTES) {
        imprimir_mensagem("ERRO: O numero de clientes ja chegou ao limite!");
    }

    else {
        char cpf[TAM_CPF];
        requisitar_cpf(cpf);

        int indice_cliente = identificar_cliente_pelo_cpf(clientes, cpf, *indice_atual);

        if (indice_cliente != -1) { 
            imprimir_mensagem("ERRO: Esse CPF ja foi cadastrado!");
        }

        else {
            char nome[TAM_NOME];
            char telefone[TAM_TELEFONE];
            char email[TAM_EMAIL];

            requisitar_nome(nome);
            requisitar_telefone(telefone);
            requisitar_email(email);

            cliente *cliente = &clientes[*indice_atual];

            strcpy(cliente->cpf, cpf);
            strcpy(cliente->nome, nome);
            strcpy(cliente->telefone, telefone);
            strcpy(cliente->email, email);
            cliente->bonus = 0;
            cliente->total_em_compras = 0;

            (*indice_atual)++;

            imprimir_mensagem("CLIENTE CADASTRADO COM SUCESSO!");
        }
    }
}

/*
Consulta os dados de um cliente atraves do cpf.
Recebe o vetor de clientes e o indice atual a fim de identificar o ultimo cadastrado e fazer a busca. O cliente ja precisa ter realizado alguma compra, pois sao impressas informacoes da ultima compra.
Nao retorna nada.
*/

void consultar_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual) {
    char cpf[TAM_CPF];
    requisitar_cpf(cpf);
    int indice_cliente = identificar_cliente_pelo_cpf(clientes, cpf, *indice_atual);

    if (indice_cliente == -1) {
        imprimir_mensagem("ERRO: Esse CPF nao foi cadastrado!");
    }

    else {
        imprimir_cliente(clientes[indice_cliente]);
        printf("Ultima compra:\n");
        printf("Valor da compra realmente pago: %.2f\n", clientes[NUM_CLIENTES].ultima_compra.valor_compra_sem_bonus);
        printf("Valor total da compra: %.2f\n", printf("Valor da ultima compra: %.2f\n", clientes[NUM_CLIENTES].ultima_compra.valor_total_da_compra));
        printf("Compra cancelada: %d\n", clientes[NUM_CLIENTES].ultima_compra.compra_cancelada);
    }
}

/*
Imprime os dados dos clientes.
Recebe uma variavel do tipo cliente, contendo as informacoes.
Nao retorna nada.
*/

void imprimir_cliente(cliente cliente) {
    printf("Nome: %s\n", cliente.nome);
    printf("CPF: %s\n", cliente.cpf);
    printf("Telefone: %s\n", cliente.telefone);
    printf("Email: %s\n", cliente.email);
    printf("Bonus atual: %d\n", cliente.bonus);
    printf("Valor total em compras: %.2f\n", cliente.total_em_compras);
    printf("Valor da ultima compra: %.2f\n", cliente.ultima_compra.valor_total_da_compra);
    printf("----------\n");
}

/*
Imprime as opcoes do menu alterar cliente. Apenas informa o usuario das operacoes do programa.
Nao recebe parametros.
Nao retorna nada.
*/

void mostrar_opcoes_do_menu_alterar_cliente() {
    printf("\n----- MENU ALTERAR CLIENTE -----\n");
    printf("0 - Retornar para o menu cliente.\n");
    printf("1 - Alterar CPF.\n");
    printf("2 - Alterar nome.\n");
    printf("3 - Alterar telefone.\n");
    printf("4 - Alterar email.\n");
    printf("5 - Limpar tela.\n");
    printf("\n");
}

/*
Executa o menu de alteracao de dados do cliente, caso o cpf seja encontrado.
Recebe o vetor de clientes e o indice atual para identificar o ultimo indice inserido.
Nao retorna nada.
*/

void alterar_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual) {
    char cpf[TAM_CPF];
    requisitar_cpf(cpf);

    int indice_cliente = identificar_cliente_pelo_cpf(clientes, cpf, *indice_atual);

    if (indice_cliente == -1) {
        imprimir_mensagem("ERRO: Esse CPF nao foi cadastrado!");
    }

    else {
        abrir_menu_alterar_cliente(clientes, indice_atual, indice_cliente);
    }
}

/*
Abre o menu alterar cliente. Apresenta as opcoes e le/processa a opcao escolhida. Também mantem o menu aberto(loop).
Recebe um vetor contendo todos os clientes cadastrados, um indice atual que eh usado na funcao de identificao do cliente e um indice que identifica o cliente pesquisado na funcao alterar cliente.
Nao retorna nada.
*/

void abrir_menu_alterar_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual, int indice_cliente) {
    int operacao;
    
    do {
        mostrar_opcoes_do_menu_alterar_cliente();
        requisitar_operacao(&operacao);
        processar_operacao_do_menu_alterar_cliente(clientes, indice_atual, indice_cliente, operacao);
    } while (operacao);
}

/* 
Processa a operacao escolhida no menu alterar cliente. Executa a funcao adequada conforme a escolha.
Recebe um vetor com os clientes cadastrados, o indice atual que identifica o proximo indice "vago", o indice do cliente que identifica um cliente e a operacao escolhida pelo usuario
Nao retorna nada
*/

void processar_operacao_do_menu_alterar_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual, int indice_cliente, int operacao) {
    if (operacao == 0) {}

    else if (operacao == 1) {
        alterar_cpf_do_cliente(clientes, indice_atual, indice_cliente);
    }

    else if (operacao == 2) {
        alterar_nome_do_cliente(clientes, indice_cliente);
    }
    
    else if (operacao == 3) {
        alterar_telefone_do_cliente(clientes, indice_cliente);
    }

    else if (operacao == 4) {
        alterar_email_do_cliente(clientes, indice_cliente);
    }

    else if (operacao == 5) {
        limpar_tela();
    }

    else {
        imprimir_mensagem("ERRO: Operacao invalida!");
    }
}

/*
Altera o cpf de um cliente.
Recebe um vetor com os clientes cadastrados, o indice atual para ser usado na função de busca do cpf e o indice cliente identificando o cliente alterado
Nao retorna nada.
*/

void alterar_cpf_do_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual, int indice_cliente) {
    char cpf[TAM_CPF];
    requisitar_cpf(cpf);
    int indice = identificar_cliente_pelo_cpf(clientes, cpf, *indice_atual);

    if (indice != -1) {
        imprimir_mensagem("ERRO: Esse CPF ja foi cadastrado!");
    }

    else {
        strcpy(clientes[indice_cliente].cpf, cpf);
        imprimir_mensagem("CPF ALTERADO COM SUCESSO!");
    }
}

/*
Altera o nome de um cliente.
Recebe um vetor de clientes cadastrados e um indice do cliente para identifica-lo
Nao retorna nada.
*/

void alterar_nome_do_cliente(cliente clientes[NUM_CLIENTES], int indice_cliente) {
    char nome[TAM_NOME];
    requisitar_nome(nome);
    strcpy(clientes[indice_cliente].nome, nome);

    imprimir_mensagem("NOME ALTERADO COM SUCESSO!");
}

/*
Altera o telefone de um cliente.
Recebe um vetor de clientes cadastrados e um indice do cliente para identifica-lo
Nao retorna nada.
*/

void alterar_telefone_do_cliente(cliente clientes[NUM_CLIENTES], int indice_cliente) {
    char telefone[TAM_TELEFONE];
    requisitar_telefone(telefone);
    strcpy(clientes[indice_cliente].telefone, telefone);

    imprimir_mensagem("TELEFONE ALTERADO COM SUCESSO!");
}

/*
Altera o email de um cliente.
Recebe um vetor de clientes cadastrados e um indice do cliente para identifica-lo
Nao retorna nada.
*/

void alterar_email_do_cliente(cliente clientes[NUM_CLIENTES], int indice_cliente) {
    char email[TAM_EMAIL];
    requisitar_email(email);
    strcpy(clientes[indice_cliente].email, email);
    imprimir_mensagem("EMAIL ALTERADO COM SUCESSO!");
}


/* 
Remove o cliente buscado pelo cpf.
Recebe o vetor de clientes e o indice atual que eh usado na funcao de identificao do cliente.
Nao retorna nada.
*/

void remover_cliente(cliente clientes[NUM_CLIENTES], int *indice_atual) {
    char cpf[TAM_CPF];
    requisitar_cpf(cpf);

    int indice_cliente = identificar_cliente_pelo_cpf(clientes, cpf, *indice_atual);
    if (indice_cliente == -1) {
        imprimir_mensagem("ERRO: Esse CPF nao foi cadastrado!");
    }

    else {
        imprimir_cliente(clientes[indice_cliente]);
        printf("Tem certeza que deseja remover esse cliente? [1 - sim, <outro valor> - nao]: ");
        
        int confirmar_remocao;

        scanf("%d", &confirmar_remocao);

        if (confirmar_remocao == 1) {
            int i;

            for (i = indice_cliente; i < *indice_atual - 1; i++) {
                clientes[i] = clientes[i + 1];
            }

            cliente *ultimo_cliente = &clientes[*indice_atual - 1];

            // "Apaga" os dados do ultimo cliente no vetor
            strcpy(ultimo_cliente->nome, "");
            strcpy(ultimo_cliente->cpf, "");
            strcpy(ultimo_cliente->email, "");
            strcpy(ultimo_cliente->telefone, "");
            ultimo_cliente->bonus = 0;
            ultimo_cliente->total_em_compras = 0;

            (*indice_atual)--;

            imprimir_mensagem("CADASTRO EXCLUIDO COM SUCESSO!");
        }

        else {
            imprimir_mensagem("CADASTRO DO CLIENTE NAO EXCLUIDO!");
        }
    }
}

/* Funcoes do menu compra */

/*
Imprime as opcoes do menu compra. Apenas informa o usuario das operacoes do programa.
Nao recebe parametros.
Nao retorna nada.
*/

void mostrar_opcoes_do_menu_compra() {
    printf("\n----- MENU COMPRA -----\n");
    printf("0 - Retornar para o menu principal.\n");
    printf("1 - Efetivar compra.\n");
    printf("2 - Cancelar compra.\n");
    printf("3 - Limpar a tela.\n");
    printf("\n");
}

/*
Abre o menu compra. Apresenta as opcoes e le/processa a opcao escolhida. Também mantem o menu aberto(loop).
Recebe um vetor contendo todos os clientes cadastrados, a configuracao do bonus atual para ser utilizada nas operacoes de compra e um indice atual usada na funcao de identificao de cliente.
Nao retorna nada.
*/

void abrir_menu_compra(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual) {
    int operacao;

    do {
        mostrar_opcoes_do_menu_compra();
        requisitar_operacao(&operacao);
        processar_operacao_do_menu_compra(clientes, bonus_atual, indice_atual, operacao);
    } while (operacao);
}

/* 
Processa a operacao escolhida no menu compra. Executa a funcao adequada conforme a escolha.
Recebe um vetor com os clientes cadastrados, a configuracao do bonus atual, o indice atual que identifica o proximo indice "vago" e a operacao escolhida pelo usuario
Nao retorna nada
*/

void processar_operacao_do_menu_compra(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual, int operacao) {
    if (operacao == 0) {}

    else if (operacao == 1) {
        efetuar_compra(clientes, bonus_atual, indice_atual);
    }

    else if (operacao == 2) {
        cancelar_compra(clientes, bonus_atual, indice_atual);
    }

    else if (operacao == 3) {
        limpar_tela();
    }

    else {
        imprimir_mensagem("ERRO: Operacao invalida!");
    }
}

/*
Efetua uma compra.
Recebe o vetor de clientes, a configuracao do bonus e o indice atual usado na identificao do cliente.
Nao retorna nada.
*/

void efetuar_compra(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual) {
    char cpf[TAM_CPF];
    requisitar_cpf(cpf);
    int indice_cliente = identificar_cliente_pelo_cpf(clientes, cpf, *indice_atual);

    if (indice_cliente == -1) {
        imprimir_mensagem("ERRO: Esse CPF nao foi cadastrado!");
    }

    else {
        imprimir_bonus(clientes[indice_cliente], bonus_atual);

        float valor_compra_total, valor_compra_sem_bonus;
        requisitar_valor_compra(&valor_compra_total);
        valor_compra_sem_bonus = valor_compra_total;
        int bonus_restante = 0;

        if (clientes[indice_cliente].bonus > 0) {
            int usar_bonus;
            printf("Deseja utilizar o bonus? [1 - Sim <outro valor> - Nao]:");
            scanf("%d", &usar_bonus);

            if (usar_bonus == 1)  {
                float valor_correspondente = clientes[indice_cliente].bonus * bonus_atual->valor;

                if (valor_correspondente <= valor_compra_total) {
                    valor_compra_total -= valor_correspondente;
                    // Nessa circunstancia o bonus_restante vai ser 0
                }
                
                else {
                    int bonus_que_falta = (valor_compra_total / bonus_atual->valor);
                    valor_correspondente = bonus_que_falta * bonus_atual->valor;
                    valor_compra_total -= valor_correspondente;
                    bonus_restante = clientes[indice_cliente].bonus - bonus_que_falta;
                }

                printf("BONUS ATUAL: %d. VALOR DA COMPRA ATUALIZADO = R$ %.2f\n", bonus_restante, valor_compra_total);
            }
        }

        float valor_total_de_pagamento = 0;

        if (valor_compra_total != 0) {
            requisitar_pagamento_cliente(&valor_total_de_pagamento);

            while (valor_total_de_pagamento < valor_compra_total) {
                imprimir_mensagem("ERRO: Valor de pagamento inferior ao valor da compra!");
                
                printf("Pagamento fornecido ate entao: R$ %.2f\n", valor_total_de_pagamento);

                int fornecer_mais_dinheiro;
                printf("Deseja fornecer mais dinheiro? [1 - Sim <outro valor> - Nao]: ");
                scanf("%d", &fornecer_mais_dinheiro);

                if (fornecer_mais_dinheiro != 1) {
                    break;
                }

                float pagamento_cliente;
                requisitar_pagamento_cliente(&pagamento_cliente);
                valor_total_de_pagamento += pagamento_cliente;
            }
        }

        if (valor_total_de_pagamento < valor_compra_total) {
            printf("COMPRA NAO EFETIVADA. Valor devolvido ao cliente: R$ %.2f\n", valor_total_de_pagamento + bonus_restante * bonus_atual->valor);
        }

        else {
            printf("TROCO = R$ %.2f\n", valor_total_de_pagamento - valor_compra_total);

            clientes[indice_cliente].total_em_compras += valor_compra_sem_bonus;

            if (valor_compra_total >= bonus_atual->valor_bonificar) {
                int bonus_ganho = valor_compra_total / bonus_atual->valor_bonificar;
                int bonus_que_falta = bonus_atual->teto - clientes[indice_cliente].bonus;

                if (bonus_ganho <= bonus_que_falta) {
                    clientes[indice_cliente].bonus += bonus_ganho;
                }

                else if (bonus_que_falta > 0) {
                    clientes[indice_cliente].bonus += bonus_que_falta;
                }
            }

            clientes[indice_cliente].ultima_compra.valor_total_da_compra = valor_compra_total;
            clientes[indice_cliente].ultima_compra.valor_compra_sem_bonus = valor_compra_sem_bonus;
            clientes[indice_cliente].ultima_compra.compra_cancelada = 0;
            clientes[indice_cliente].ultima_compra.bonus_da_compra = *bonus_atual;

            imprimir_mensagem("COMPRA EFETIVADA!");
        }
    }
}

/*
Cancela uma compra.
Recebe o vetor de clientes, a configuracao do bonus no momento e o indice atual usado para identificar o cliente.
Nao retorna nada.
*/

void cancelar_compra(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual){
    int pergunta1,pergunta2,pergunta_vendedor, novo_bonus_vendedor, pergunta3;
    float valor_outra_compra;
    char cpf[TAM_CPF];
    requisitar_cpf(cpf);
   
    int indice_cliente = identificar_cliente_pelo_cpf(clientes, cpf, *indice_atual);
    if (indice_cliente == -1) {
        printf("ERRO: Esse CPF nao foi cadastrado!\n");
    }
    
    else{
        printf("Qual compra voce deseja cancelar? [1 - ultima compra, 2 - outra compra]");
        scanf("%d", &pergunta1);

        while(pergunta1 != 1 && pergunta1 != 2){
            printf("ERRO: escolha uma opçao:");
            printf("Qual compra voce deseja cancelar? [1 - ultima compra, 2 - outra compra]");
            scanf("%d", &pergunta1);
        }
        
        if(pergunta1 == 1){
            if(clientes[indice_cliente].ultima_compra.compra_cancelada == 1){
                printf("ERRO: ultima compra ja cancelada");
            }
            
            else{
                printf("Valor da compra: %.2f\n", clientes[indice_cliente].ultima_compra.valor_compra_sem_bonus);
                printf("Valor pago: %.2f\n", clientes[indice_cliente].ultima_compra.valor_total_da_compra);
                printf("Bonus usados: %.2f\n", (clientes[indice_cliente].ultima_compra.valor_compra_sem_bonus - clientes[indice_cliente].ultima_compra.valor_total_da_compra) / clientes[indice_cliente].ultima_compra.bonus_da_compra.valor);
                printf("Bonus ganhos: %.2f\n", clientes[indice_cliente].ultima_compra.valor_total_da_compra / clientes[indice_cliente].ultima_compra.bonus_da_compra.valor_bonificar);

                printf("Tem certeza que deseja cancelar essa compra [1-sim <outro valor>-nao]?");
                scanf("%d", &pergunta2);
                if(pergunta2 != 1){
                    printf("Compra NAO cancelada!!");
                } 
                
                else{
                    // Adiciona o bonus que foi removido
                    clientes[indice_cliente].bonus += (clientes[indice_cliente].ultima_compra.valor_compra_sem_bonus - clientes[indice_cliente].ultima_compra.valor_total_da_compra) / bonus_atual->valor;

                    if (clientes[indice_cliente].bonus < 0) {
                        clientes[indice_cliente].bonus = 0;
                    }

                    // Remove o bonus que foi adicionado
                    clientes[indice_cliente].bonus -= clientes[indice_cliente].ultima_compra.valor_total_da_compra / bonus_atual->valor_bonificar;

                    clientes[indice_cliente].total_em_compras -= clientes[indice_cliente].ultima_compra.valor_total_da_compra + bonus_atual->valor * (clientes[indice_cliente].ultima_compra.valor_compra_sem_bonus - clientes[indice_cliente].ultima_compra.valor_total_da_compra) / bonus_atual->valor;
                    clientes[indice_cliente].ultima_compra.compra_cancelada = 1;
                    printf("Compra cancelada!");
                    printf("Valores atualizados:\n"); 
                    printf("Bonus total do cliente apos o cancelamento: %d", clientes[indice_cliente].bonus);
                    printf("Total em compras do cliente apos o cancelamento: %.2f", clientes[indice_cliente].total_em_compras);
                }
            }   
        }
        
        else if( pergunta1 == 2){
            printf("Qual o valor pago da compra a ser cancelada?");
            scanf("%f", &valor_outra_compra);
            
            if(valor_outra_compra > clientes[indice_cliente].total_em_compras){
                printf("Compra inexistente!\n");
            }
            
            else{
                printf("Valor da compra: R$ %.2f\n", valor_outra_compra);
                int bonus_ganho = (int) (valor_outra_compra / bonus_atual->valor_bonificar);
                int bonus_que_falta = bonus_atual->teto - bonus_ganho;


                if (bonus_ganho <= bonus_que_falta) {
                    clientes[indice_cliente].bonus += bonus_ganho;
                }

                else if (bonus_que_falta > 0) {
                    clientes[indice_cliente].bonus += bonus_que_falta;
                }

                printf("Bonus a ser retirado do cliente: %d\n", bonus_ganho);
                printf("Vendedor, deseja informar um valor menor do bonus? [1 - sim <outro valor>- nao]");
                scanf("%d", &pergunta_vendedor);

                if(pergunta_vendedor == 1){
                    printf("Digite o valor do bonus a ser retirado do cliente (menor ou igual a %d): ", bonus_ganho);
                    scanf("%d", &novo_bonus_vendedor);
                    
                    while(novo_bonus_vendedor > bonus_ganho) {
                        printf("valor invalido, digite novamente o bonus a ser retirado do cliente (menor ou igual a %d): ", bonus_ganho);
                        scanf("%d", &novo_bonus_vendedor);
                    }
                    
                    printf("Tem certeza que deseja cancelar essa compra [1-sim <outro valor>-nao]?");
                    scanf("%d", &pergunta3);
                    
                    if(pergunta3 == 1){
                        clientes[indice_cliente].bonus -= novo_bonus_vendedor;
                        clientes[indice_cliente].total_em_compras -= valor_outra_compra;
                        printf("Compra CANCELADA!");
                    } 
                    
                    else{
                        printf("Compra NAO cancelada!");
                    }
                 } 
                 
                 else{
                    printf("Tem certeza que deseja cancelar essa compra [1-sim <outro valor>-nao]?");
                    scanf("%d", &pergunta3);
                    if(pergunta3 == 1){
                        clientes[indice_cliente].bonus -= bonus_ganho;
                        clientes[indice_cliente].total_em_compras -= valor_outra_compra;
                        printf("Compra CANCELADA!");
                    } 
                    
                    else{
                        printf("Compra NAO cancelada!");
                    }
                 }               
             }
        }
    }
}

/* Funcoes do menu bonus */

/*
Imprime as opcoes do menu bonus. Apenas informa o usuario das operacoes do programa.
Nao recebe parametros.
Nao retorna nada.
*/

void mostrar_opcoes_do_menu_bonus() {
    printf("\n----- MENU BONUS -----\n");
    printf("0 - Retornar para o menu principal.\n");
    printf("1 - Configurar bonus.\n");
    printf("2 - Exibir bonus.\n");
    printf("3 - Limpar a tela.\n");
    printf("\n");
}

/*
Abre o menu bonus. Apresenta as opcoes e le/processa a opcao escolhida. Também mantem o menu aberto(loop).
Recebe um vetor contendo todos os clientes cadastrados, a configuracao do bonus atual para ser utilizada e um indice atual usada na funcao de identificao de cliente.
Nao retorna nada.
*/

void abrir_menu_bonus(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual) {
    int operacao;

    do {
        mostrar_opcoes_do_menu_bonus();
        requisitar_operacao(&operacao);
        processar_operacao_do_menu_bonus(clientes, bonus_atual, indice_atual, operacao);
    } while (operacao);
}

/* 
Processa a operacao escolhida no menu bonus. Executa a funcao adequada conforme a escolha.
Recebe um vetor com os clientes cadastrados, a configuracao do bonus atual, o indice atual que identifica o proximo indice "vago" e a operacao escolhida pelo usuario
Nao retorna nada
*/

void processar_operacao_do_menu_bonus(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual, int operacao) {
    if (operacao == 0) {}

    else if (operacao == 1) {
        abrir_menu_alterar_bonus(bonus_atual);
    }

    else if (operacao == 2) {
        exibir_bonus(clientes, bonus_atual, indice_atual);
    }

    else if (operacao == 3) {
        limpar_tela();
    }

    else {
        imprimir_mensagem("Erro: Operacao invalida!");
    }
}

/* 
Apenas imprime os dados da configuracao do bonus
Recebe a configuracao do bonus.
Nao retorna nada.
*/

void mostrar_configuracao_do_bonus_atual(bonus *bonus_atual) {
    printf("Valor atual do teto: %d\n", bonus_atual->teto);
    printf("Valor atual do bonus: %.2f\n", bonus_atual->valor);
    printf("Valor bonificar atual: %.2f\n", bonus_atual->valor_bonificar);
    printf("\n");
}

/*
Imprime as opcoes do menu alterar bonus. Apenas informa o usuario das operacoes do programa.
Nao recebe parametros.
Nao retorna nada.
*/

void mostrar_opcoes_do_menu_alterar_bonus() {
    printf("\n--- MENU ALTERAR BONUS ---\n");
    printf("0 - Retornar para o menu bonus.\n");
    printf("1 - Alterar teto.\n");
    printf("2 - Alterar valor do bonus.\n");
    printf("3 - Alterar valor para receber bonus.\n");
    printf("4 - Limpar a tela.\n");
    printf("\n");
}

/*
Abre o menu alterar bonus. Apresenta as opcoes e le/processa a opcao escolhida. Também mantem o menu aberto(loop).
Recebe a configuracao do bonus atual
Nao retorna nada.
*/

void abrir_menu_alterar_bonus(bonus *bonus_atual) {
    int operacao;

    do {
        mostrar_opcoes_do_menu_alterar_bonus();
        mostrar_configuracao_do_bonus_atual(bonus_atual);
        requisitar_operacao(&operacao);
        processar_operacao_do_menu_alterar_bonus(bonus_atual, operacao);
    } while (operacao);
}

/* 
Processa a operacao escolhida no menu alterar bonus. Executa a funcao adequada conforme a escolha.
Recebe a configuracao do bonus atual e a operacao escolhida pelo usuario.
Nao retorna nada
*/

void processar_operacao_do_menu_alterar_bonus(bonus *bonus_atual, int operacao) {
    if (operacao == 0) {}

    else if (operacao == 1) {
        requisitar_novo_valor_de_teto(&(bonus_atual->teto));
    }

    else if (operacao == 2) {
        requisitar_novo_valor_de_bonus(&(bonus_atual->valor));
    }

    else if (operacao == 3) {
        requisitar_novo_valor_para_receber_bonus(&(bonus_atual->valor_bonificar));
    }

    else if (operacao == 4) {
        limpar_tela();
    }

    else {
        imprimir_mensagem("Erro: Operacao invalida!");
    }
}

/*
Exibe o bonus e o valor correspondente do cliente procurado atraves do cpf.
Recebe o vetor de clientes, a configuracao do bonus atual e o indice atual.
Nao retorna nada.
*/

void exibir_bonus(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual) {
    char cpf[TAM_CPF];
    requisitar_cpf(cpf);

    int indice_pesquisado = identificar_cliente_pelo_cpf(clientes, cpf, *indice_atual);

    if (indice_pesquisado == -1) {
        imprimir_mensagem("Erro: esse CPF nao foi cadastrado!");
    }

    else {
        cliente cliente_pesquisado = clientes[indice_pesquisado];
        imprimir_bonus(cliente_pesquisado, bonus_atual);
    }

}

/*
Imprime o bonus de um cliente.
Recebe um cliente e a configuracao do bonus.
Nao retorna nada.
*/

void imprimir_bonus(cliente cliente, bonus *bonus_atual) {
    float valor_correspondente_ao_bonus = cliente.bonus * bonus_atual->valor;
    
    printf("BONUS = %d\n", cliente.bonus);
    printf("VALOR CORRESPONDETE = R$ %.2f\n", valor_correspondente_ao_bonus);
}

/* Funcoes do menu relatorios */

/*
Imprime as opcoes do menu relatorios. Apenas informa o usuario das operacoes do programa.
Nao recebe parametros.
Nao retorna nada.
*/

void mostrar_opcoes_do_menu_relatorios() {
    printf("\n----- MENU RELATORIOS -----\n");
    printf("0 - Retornar para o menu principal.\n");
    printf("1 - Listar clientes.\n");
    printf("2 - Listar bonus.\n");
    printf("3 - Listar cliente por compras.\n");
    printf("4 - Limpar a tela.\n");
    printf("\n");
}

/*
Abre o menu relatorios. Apresenta as opcoes e le/processa a opcao escolhida. Também mantem o menu aberto(loop).
Recebe um vetor de clientes, a configuracao do bonus atual e o indice atual para identiificar o indice do ultimo cliente adicionado
Nao retorna nada.
*/

void abrir_menu_relatorios(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual) {
    int operacao;

    do {
        mostrar_opcoes_do_menu_relatorios();
        requisitar_operacao(&operacao);
        processar_operacao_do_menu_relatorios(clientes, bonus_atual, indice_atual, operacao);
    } while (operacao);
}

/* 
Processa a operacao escolhida no menu relatorios. Executa a funcao adequada conforme a escolha.
Recebe um vetor com os clientes cadastrados, a configuracao do bonus atual, o indice atual que identifica o proximo indice "vago" e a operacao escolhida pelo usuario
Nao retorna nada
*/

void processar_operacao_do_menu_relatorios(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual, int operacao) {
    if (operacao == 0) {}

    else if (operacao == 1) {
        listar_clientes(clientes, indice_atual);
    }

    else if (operacao == 2) {
        listar_bonus(clientes, bonus_atual, indice_atual);
    }
    
    else if (operacao == 3) {
        listar_clientes_por_total_em_compra(clientes, indice_atual);
    }

    else if (operacao == 4) {
        limpar_tela();
    }

    else {
        imprimir_mensagem("Erro: Operacao invalida!");
    }
}

/*
Lista as informacoes de todos os clientes
Recebe o vetor de clientes e o indice atual
Nao retorna nada
*/

void listar_clientes(cliente clientes[NUM_CLIENTES], int *indice_atual) {
    int i;

    for (i = 0; i < *indice_atual; i++) {
        imprimir_cliente(clientes[i]);
    }
}

/*
Lista as informacoes de bonus de todos os clientes.
Recebe o vetor de clientes, a configuracao do bonus e o indice atual.
Nao retorna nada.
*/

void listar_bonus(cliente clientes[NUM_CLIENTES], bonus *bonus_atual, int *indice_atual) {
    int i;

    for (i = 0; i < *indice_atual; i++) {
        printf("----------\n");
        printf("CPF : %s\n", clientes[i].cpf);
        imprimir_bonus(clientes[i], bonus_atual);
    }
}

/*
Lista as informacoes do cliente com base no valor total em compras.
Recebe o vetor com os clientes cadastrados e o indice atual que eh usado para marcar o ultimo cliente cadastrado.
Nao retorna nada.
*/

void listar_clientes_por_total_em_compra(cliente clientes[NUM_CLIENTES], int *indice_atual) {
    float valor_total;
    int criterio_pesquisa;
    requisitar_valor_total_em_compra(&valor_total);

    printf("Deseja as informacoes do usuario com valor total maior, menor ou igual a esse valor?(1 - maior, 0 - igual, -1 - menor): ");
    scanf("%d", &criterio_pesquisa);

    int i;
    if (criterio_pesquisa == 1) {
        for (i = 0; i < *indice_atual; i++) {
            if (clientes[i].total_em_compras > valor_total) {
                imprimir_cliente(clientes[i]);
                printf("----------\n");
            }
        }
    }

    else if (criterio_pesquisa == 0) {
        for (i = 0; i < *indice_atual; i++) {
            if (clientes[i].total_em_compras == valor_total) {
                imprimir_cliente(clientes[i]);
                printf("----------\n");
            }
        }
    }

    else if (criterio_pesquisa == -1) {
        for (i = 0; i < *indice_atual; i++) {
            if (clientes[i].total_em_compras < valor_total) {
                imprimir_cliente(clientes[i]);
                printf("----------\n");
            }
        }
    }

    else {
        imprimir_mensagem("ERRO: Operacao invalida!");
    }
}

/* Funcoes auxiliares */

/* 
Pede e le uma operacao.
Recebe um ponteiro representando a operacao.
Nao retornada nada.
*/

void requisitar_operacao(int *operacao) {
    printf("Insira uma operacao: ");
    scanf("%d", operacao);
}

/* 
Pede e le um cpf.
Recebe um ponteiro representando o cpf.
Nao retornada nada.
*/

void requisitar_cpf(char *cpf) {
    printf("Qual o CPF do cliente?: ");
    scanf("%s", cpf);
}

/* 
Pede e le um nome.
Recebe um ponteiro representando nome.
Nao retornada nada.
*/

void requisitar_nome(char *nome) {
    printf("Qual o nome do cliente?: ");
    scanf("%*c");
    fgets(nome, TAM_NOME, stdin);
    nome[strlen(nome) - 1] = '\0'; // Elimina o \n
}

/* 
Pede e le um telefone.
Recebe um ponteiro representando o telefone.
Nao retornada nada.
*/

void requisitar_telefone(char *telefone) {
    printf("Qual o telefone do cliente?: ");
    scanf("%s", telefone);
    scanf("%*c");
}

/* 
Pede e le um email.
Recebe um ponteiro representando um email.
Nao retornada nada.
*/

void requisitar_email(char *email) {
    printf("Qual o email do cliente?: ");
    scanf("%s", email);
    scanf("%*c");
}

/* 
Pede e le um novo valor de teto para o bonus.
Recebe um ponteiro representando o novo valor.
Nao retornada nada.
*/

void requisitar_novo_valor_de_teto(int *novo_teto) {
    printf("Qual o novo valor de teto?: ");
    scanf("%d", novo_teto);
    validar_valor_inteiro(novo_teto);
    printf("\nVALOR DO TETO ALTERADO PARA %d\n", *novo_teto);
}

/* 
Pede e le o novo valor do bonus.
Recebe um ponteiro representando o novo valor do bonus.
Nao retornada nada.
*/

void requisitar_novo_valor_de_bonus(float *novo_valor_de_bonus) {
    printf("Qual o novo valor de bonus?: ");
    scanf("%f", novo_valor_de_bonus);
    validar_valor_float(novo_valor_de_bonus);
    printf("\nVALOR DO BONUS ALTERADO PARA %.2f\n", *novo_valor_de_bonus);
}

/* 
Pede e le o novo valor bonificar do bonus.
Recebe um ponteiro representando o novo valor bonificar.
Nao retornada nada.
*/

void requisitar_novo_valor_para_receber_bonus(float *novo_valor_bonificar) {
    printf("Qual o novo valor para receber o bonus?: ");
    scanf("%f", novo_valor_bonificar);
    validar_valor_float(novo_valor_bonificar);
    printf("\nVALOR BONIFICAR ALTERADO PARA %.2f\n", *novo_valor_bonificar);
}

/*
Incializa os campos do bonus.
Recebe a configuracao do bonus.
Nao retorna nada.
*/

void inicializar_bonus(bonus *bonus_atual) {
    bonus_atual->teto = 100;
    bonus_atual->valor = 0.5;
    bonus_atual->valor_bonificar = 100;
}

/*
Valida uma variavel do tipo float. Nao permite que ela seja negativa.
Recebe um ponteiro representando um float.
Nao retorna nada.
*/

void validar_valor_float(float *valor) {
    while (*valor < 0) {
        if (*valor < 0) {
            imprimir_mensagem("ERRO: valor negativo.");
        }

        printf("Digite um valor maior ou igual a zero:");
        scanf("%f", valor);
    }
}

/*
Valida uma variavel do tipo inteiro. Nao permite que ela seja negativa.
Recebe um ponteiro representando um inteiro.
Nao retorna nada.
*/

void validar_valor_inteiro(int *valor) {
    while (*valor < 0) {
        if (*valor < 0) {
            imprimir_mensagem("ERRO: valor negativo.");
        }

        printf("Digite um valor maior ou igual a zero:");
        scanf("%d", valor);
    }
}

/*
Limpa a tela. Chama o comando cls do prompt de comando.
Nao recebe nada.
Nao retorna nada.
*/

void limpar_tela() {
    system("cls");
}

/* 
Imprime uma mensagem no formato definido.
Recebe um char representando a mensagem.
Nao retorna nada.
*/

void imprimir_mensagem(char mensagem[TAM_MENSAGEM]) {
    printf("\n%s\n", mensagem);
}

/*
Pede e le um valor de compra.
Recebe um ponteiro representando o valor de compra.
Nao retornada nada.
*/

void requisitar_valor_compra(float *valor_compra) {
    printf("Qual eh o valor da compra?: ");
    scanf("%f", valor_compra);
    validar_valor_float(valor_compra);
}

/*
Pede e le um valor do pagamento do cliente.
Recebe um ponteiro representando o pagamento do cliente.
Nao retornada nada.
*/

void requisitar_pagamento_cliente(float *valor_pagamento) {
    printf("Qual eh o valor de pagamento do cliente?: ");
    scanf("%f", valor_pagamento);
    validar_valor_float(valor_pagamento);
}

/*
Imprime uma mensagem de encerramento.
Nao recebe nada.
Nao retorna nada.
*/

void imprimir_encerramento() {
    printf("\nObrigado por usar nosso programa!\n");
    printf("\nAlunos:\n");
    printf("    - Gabriel Alves da Silva\n");
    printf("    - Rayanne Lopes Ellen Ferreira\n");
}

/*
Pede e le um valor total em compras para a listagem de clientes por compra.
Recebe um ponteiro representando o valor total em compras.
Nao retorna nada.
*/

void requisitar_valor_total_em_compra(float *valor_total_em_compra) {
    printf("Qual eh o valor total?: ");
    scanf("%f", valor_total_em_compra);
    validar_valor_float(valor_total_em_compra);
}