#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Para strlen, strncmp, strcpy, etc.
#include <ctype.h>   // Para tolower (para busca case-insensitive)
#include "bd_paciente.h" // Nossa definição de BDPaciente e Paciente
#include "paciente.h"    // Para a função imprimir_paciente

/* --- Funções Auxiliares (estáticas) --- */

/* Converte uma string para minúsculas (modifica a string original) */
static void string_para_minusculas(char* str) {
    if (str == NULL) return;
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

/* --- Implementações das Funções do TAD BDPaciente --- */

/* Inicializa a estrutura BDPaciente */
void inicializar_bd(BDPaciente* bd) {
    if (bd != NULL) {
        bd->quantidade_atual = 0; // Define a quantidade de pacientes como zero.
    }
}

/* Carrega dados do CSV. Retorna 1 em sucesso, 0 em erro. */
int carregar_dados_csv(BDPaciente* bd, const char* nome_arquivo_csv) {
    FILE* arquivo;
    char linha_cabecalho[200]; // Buffer para descartar a linha de cabeçalho.

    if (bd == NULL) {
        fprintf(stderr, "Erro: BDPaciente eh nulo em carregar_dados_csv.\n");
        return 0;
    }
    /* Abre o arquivo para leitura */
    arquivo = fopen(nome_arquivo_csv, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo CSV");
        return 0;
    }

    /* Descarta a primeira linha (cabeçalho) do CSV. */
    if (fgets(linha_cabecalho, sizeof(linha_cabecalho), arquivo) == NULL) {
        perror("Erro ao ler cabecalho do CSV");
        fclose(arquivo);
        return 0;
    }

    bd->quantidade_atual = 0; // Garante que a contagem comece do zero.

    /* Lê cada paciente do arquivo até o limite ou fim do arquivo.
     Formato esperado: ID,CPF,Nome,Idade,DataCadastro */
    while (bd->quantidade_atual < MAX_PACIENTES &&
           fscanf(arquivo, "%d,%14[^,],%99[^,],%d,%10s\n",
                  &bd->pacientes[bd->quantidade_atual].id,
                  bd->pacientes[bd->quantidade_atual].cpf,
                  bd->pacientes[bd->quantidade_atual].nome,
                  &bd->pacientes[bd->quantidade_atual].idade,
                  bd->pacientes[bd->quantidade_atual].data_cadastro) == 5) {
        bd->quantidade_atual++;
    }

    if (feof(arquivo)) {
        // Leitura concluída com sucesso.
    } else if (bd->quantidade_atual == MAX_PACIENTES) { // Verifica se foi atingido o limite de pacientes cadastrados
        printf("Aviso: Limite maximo de %d pacientes atingido.\n", MAX_PACIENTES);
    } else if (ferror(arquivo)) {
        perror("Erro ao ler dados do paciente do CSV");
        fclose(arquivo);
        return 0;
    }

    fclose(arquivo);
    return 1; // Sucesso
}

/* Consulta pacientes por nome (prefixo, case-insensitive). */
void consultar_pacientes_por_nome(const BDPaciente* bd, const char* prefixo_nome_original) {
    int encontrados = 0; // Contador de pacientes encontrados
    char nome_paciente_minusculo[MAX_NOME]; // Importante para captar o nome mesmo se for digitado minúsculo.
    char prefixo_nome_minusculo[MAX_NOME]; // Importante para captar o nome mesmo se for digitado em Caps Lock

    /* Verifica se a lista ou o nome pesquisado são nulos*/
    if (bd == NULL || prefixo_nome_original == NULL) {
        fprintf(stderr, "Erro: Dados invalidos para consulta por nome.\n");
        return;
    }

    /* Copia o prefixo original para uma variável local, com segurança */
    strncpy(prefixo_nome_minusculo, prefixo_nome_original, MAX_NOME - 1);
    prefixo_nome_minusculo[MAX_NOME - 1] = '\0'; // Garante a terminação da string 
    string_para_minusculas(prefixo_nome_minusculo); // Converte o prefixo para letras minúsculas
    size_t len_prefixo = strlen(prefixo_nome_minusculo); // Define o tamanho do prefixo para comparação

    /* Detecta se o prefixo foi digitado*/
    if (len_prefixo == 0) {
        printf("Prefixo de nome vazio. Nenhuma busca realizada.\n");
        return;
    }

    /* Imprime o cabeçalho */
    printf("\nPacientes encontrados com nome iniciando por \"%s\":\n", prefixo_nome_original);
    printf("-------------------------------------------------------------------------------\n");
    printf("%-4s %-15s %-30s %-6s %-10s\n", "ID", "CPF", "Nome", "Idade", "Data");

    /* Percorre todos os pacientes da nossa base de dados */
    for (int i = 0; i < bd->quantidade_atual; i++) {
        strncpy(nome_paciente_minusculo, bd->pacientes[i].nome, MAX_NOME - 1); // Copia o nome do paciente para uma variável local
        nome_paciente_minusculo[MAX_NOME - 1] = '\0'; // Garante a terminação 
        string_para_minusculas(nome_paciente_minusculo); // Converte o nome do paciente para letras minúsculas

        /* Compara o prefixo com o início do nome do paciente (ignora maiúsculas/minúsculas) */
        if (strncmp(nome_paciente_minusculo, prefixo_nome_minusculo, len_prefixo) == 0) {
            imprimir_paciente(&bd->pacientes[i]);
            encontrados++;
        }
    }
    /* Linha de encerramento */
    printf("-------------------------------------------------------------------------------\n");

    /* Mostra o resultado de registros compatíveis encontrados */
    if (encontrados == 0) { // Caso não houver nenhuma compatibilidade
        printf("Nenhum paciente encontrado com o nome iniciando por \"%s\".\n", prefixo_nome_original);
    } else { // Número de compatibilidades encontradas
        printf("%d paciente(s) encontrado(s).\n", encontrados);
    }
}

// Consulta pacientes por CPF (prefixo, case-insensitive).
void consultar_pacientes_por_cpf(const BDPaciente* bd, const char* prefixo_cpf_original) {
    int encontrados = 0;
    char cpf_paciente_processado[MAX_CPF];
    char prefixo_cpf_processado[MAX_CPF];

    /* Verifica se os ponteiros estão válidos*/
    if (bd == NULL || prefixo_cpf_original == NULL) {
        fprintf(stderr, "Erro: Dados invalidos para consulta por CPF.\n");
        return; // Encerra a função
    }

    /* Usa uma string para copiar o prefixo com segurança*/
    strncpy(prefixo_cpf_processado, prefixo_cpf_original, MAX_CPF - 1);
    prefixo_cpf_processado[MAX_CPF - 1] = '\0'; // Terminação da string
    string_para_minusculas(prefixo_cpf_processado); // Converte o prefixo para letras minúsculas
    size_t len_prefixo = strlen(prefixo_cpf_processado); // Calcula o tamanho do prefixo para as comparações

    /* Verifica se o prefixo está vazio*/
    if (len_prefixo == 0) {
        printf("Prefixo de CPF vazio. Nenhuma busca realizada.\n");
        return;
    }
    /* Indica a quantidade de cpfs existem compatíveis com o prefixo buscado*/
    printf("\nPacientes encontrados com CPF iniciando por \"%s\":\n", prefixo_cpf_original);
    printf("-------------------------------------------------------------------------------\n");
    printf("%-4s %-15s %-30s %-6s %-10s\n", "ID", "CPF", "Nome", "Idade", "Data");

    /* Loop que percorre todos os pacientes cadastrados */
    for (int i = 0; i < bd->quantidade_atual; i++) {  
        strncpy(cpf_paciente_processado, bd->pacientes[i].cpf, MAX_CPF - 1); // Copia o CPF atual do paciente para um buffer local
        cpf_paciente_processado[MAX_CPF - 1] = '\0'; // Garante a terminação da string
        string_para_minusculas(cpf_paciente_processado); // Converte o CPF do paciente para minúsculas para comparação

        /* Compara os primeiros caracteres (prefixo) dos CPFs, ignorando maiúsculas/minúsculas*/
        if (strncmp(cpf_paciente_processado, prefixo_cpf_processado, len_prefixo) == 0) {
            imprimir_paciente(&bd->pacientes[i]);
            encontrados++;
        }
    }
    printf("-------------------------------------------------------------------------------\n");

    /* Exibe a mensagem final com a quantidade de pacientes encontrados de acordo com o prefixo buscado*/
    if (encontrados == 0) { // Se não tiver compatibilidade com nenhym registro existente
        printf("Nenhum paciente encontrado com o CPF iniciando por \"%s\".\n", prefixo_cpf_original);
    } else { // Exibe a quantidade de resultados compatíveis encontrados
        printf("%d paciente(s) encontrado(s).\n", encontrados);
    }
}

/* Imprime lista de pacientes paginada.*/
void imprimir_lista_pacientes_paginada(const BDPaciente* bd, int itens_por_pagina) {
    if (bd == NULL) { // Verifica se bd é nula, o que não deveria ocorrer.
        fprintf(stderr, "Erro: BDPaciente eh nulo em imprimir_lista_pacientes_paginada.\n");
        return;
    }
    /* Verifica se a lista de pacientes estã vazia e avisa o usuário*/
    if (bd->quantidade_atual == 0) {
        printf("\nNenhum paciente cadastrado no sistema.\n");
        return;
    }
    /* Caso hajam pacientes previamente cadastrados, monta o cabeçario para melhor organização*/
    printf("\nLista de Todos os Pacientes:\n");
    printf("===============================================================================\n");
    printf("%-4s %-15s %-30s %-6s %-10s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro"); // [cite: 34]
    printf("-------------------------------------------------------------------------------\n");

    /* Percorre a lista de pacientes*/
    for (int i = 0; i < bd->quantidade_atual; i++) {
        imprimir_paciente(&bd->pacientes[i]);

        /* Verifica se é hora de pausar para paginação
         i+1 porque 'i' é baseado em zero.
         (i + 1) % itens_por_pagina == 0 : significa que imprimimos um bloco completo.
         i < bd->quantidade_atual - 1 : garante que não pausamos após o último item. */
        if ((i + 1) % itens_por_pagina == 0 && i < bd->quantidade_atual - 1) {
            printf("-------------------------------------------------------------------------------\n");
            printf("Mostrando %d de %d pacientes. Pressione ENTER para continuar, Q para sair: ", i + 1, bd->quantidade_atual);
            char ch = getchar(); // Pega o Enter pressionado
            /* Se o usuário digitar 'q' e depois Enter, getchar() pegará 'q' na primeira vez.
             Se só der Enter, getchar() pegará o '\n'.
             Para uma pausa mais robusta, pode-se ler a linha toda ou usar funções da interface.
            Vamos consumir um possível '\n' extra do buffer, caso o usuário só pressione Enter */
            if (ch != '\n' && ch != EOF) { //  Se não foi só Enter, pega o próximo char (que seria o \n) */
                 char next_ch = getchar();
                 if (next_ch != '\n' && next_ch != EOF && (ch == 'q' || ch == 'Q')) {
                    // Garante que se o usuário digitou 'q' ou 'Q' e um enter, o enter extra é consumido
                 }
            }

            /* Verifica se o comando de encerramento foi digitado */
            if (ch == 'q' || ch == 'Q') {
                printf("Retornando ao menu...\n");
                break; // Sai do loop for, interrompendo a listagem
            }

            /* Se não for 'q' ou 'Q', continua para a próxima página, reimprimindo o cabeçalho para clareza */
            printf("-------------------------------------------------------------------------------\n");
            printf("%-4s %-15s %-30s %-6s %-10s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro"); 
            printf("-------------------------------------------------------------------------------\n");
        }
    }
    /* Sinaliza o fim da lista e informa a quantidade de pacientes atualmente cadastrados */
    printf("===============================================================================\n");
    printf("Fim da lista. Total de %d paciente(s).\n", bd->quantidade_atual);
}