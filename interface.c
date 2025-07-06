#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "interface.h"
#include "bd_paciente.h"

// --- Funções Auxiliares da Interface ---
void limparBuffer() { int c; while ((c = getchar()) != '\n' && c != EOF); }
void pausarExecucao() { printf("\n" CLR_YELLOW "Pressione ENTER para continuar..." CLR_RESET); getchar(); }
void formatarCPF(const char* o, char* d) { sscanf(o, "%3s%3s%3s%2s", d, d+4, d+8, d+12); d[3]=d[7]='.'; d[11]='-'; d[14]='\0'; }
int validarCPF(const char* cpf_str) { if (strlen(cpf_str) != 11) { return 0; } for (int i = 0; i < 11; i++) { if (!isdigit(cpf_str[i])) { return 0; } } return 1; }
int validarIdade(const char* idade_str) {
    if (strlen(idade_str) == 0) {
        return 0;
    }
    size_t len = strlen(idade_str);
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)idade_str[i])) {
            return 0;
        }
    }
    return 1;
}

void limparTela() {
    // Comando para limpar a tela em sistemas baseados em Unix (Linux, macOS) e Windows
    system("clear || cls");
}

/* --- Funções de Interface para cada Funcionalidade --- */

void ui_consultarPaciente(BDPaciente* bd) {
    printf(CLR_CYAN "\nEscolha o modo de consulta:\n1 - Por nome\n2 - Por CPF\n" CLR_RESET);
    char modo; // Variável para armazenar o modo de consulta
    scanf(" %c", &modo);
    limparBuffer();

    char busca[100]; // Variável para armazenar a string de busca
    int encontrou = 0; // Variável para verificar se encontrou algum paciente
    PacienteNode* p = bd_get_first(bd); // Ponteiro para o primeiro nó da lista

    /* Verifica se o modo de consulta é por nome ou CPF */
    if (modo == '1') { // Verifica se o modo de consulta é por nome
        printf(CLR_YELLOW "Digite o nome (ou prefixo): " CLR_RESET);
        fgets(busca, sizeof(busca), stdin);// Leitura da string de busca
        busca[strcspn(busca, "\n")] = 0; // Remove o caractere de nova linha
        printf("\n--- Resultados da Busca por Nome ---\n");
        printf(CLR_BLUE "%-5s %-15s %-30s %-10s %-15s\n" CLR_RESET, "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
        printf("--------------------------------------------------------------------------\n");
        while (p != NULL) { // Percorre a lista encadeada
            Paciente info = bd_get_paciente_info(p); // Pega as informações do paciente
            if (strncasecmp(info.nome, busca, strlen(busca)) == 0) { // Verifica se o nome do paciente começa com a string de busca
                imprimir_paciente(&info); // Imprime as informações do paciente
                encontrou = 1;// Marca que encontrou algum paciente
            }
            p = bd_get_next_node(p); // Avança para o próximo nó
        }
    } else if (modo == '2') { // Consulta por CPF
        printf(CLR_YELLOW "Digite o CPF (ou prefixo): " CLR_RESET); // Solicita o CPF ao usuário
        fgets(busca, sizeof(busca), stdin);// Leitura da string de busca
        busca[strcspn(busca, "\n")] = 0; // Remove o caractere de nova linha
        printf("\n--- Resultados da Busca por CPF ---\n");
        printf(CLR_BLUE "%-5s %-15s %-30s %-10s %-15s\n" CLR_RESET, "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
        printf("--------------------------------------------------------------------------\n");
        while (p != NULL) { // Percorre a lista encadeada
            Paciente info = bd_get_paciente_info(p); // Pega as informações do paciente
            if (strncmp(info.cpf, busca, strlen(busca)) == 0) { // Verifica se o CPF do paciente começa com a string de busca
                imprimir_paciente(&info);
                encontrou = 1; // Marca que encontrou algum paciente
            }
            p = bd_get_next_node(p); // Avança para o próximo nó
        }
    } else { // Modo de consulta inválido
        printf(CLR_RED "Modo de busca inválido.\n" CLR_RESET);
    }
    if (!encontrou) { // Se não foi encontrado nenhum paciente
        printf(CLR_RED "\nNenhum paciente encontrado para a busca '%s'.\n" CLR_RESET, busca); // Imprime mensagem de erro
    }
    printf("--------------------------------------------------------------------------\n");
    pausarExecucao();
}

/* --- Função de Atualização de Paciente --- */
void ui_atualizarPaciente(BDPaciente* bd) { // Recebe o ponteiro para o banco de dados
    printf(CLR_YELLOW "Digite o ID do registro a ser atualizado: " CLR_RESET); // Solicita o ID ao usuário
    int id; // Variável para armazenar o ID
    scanf("%d", &id);
    limparBuffer();

    
    /* Verifica se o paciente foi encontrado */
    PacienteNode* node = bd_find_by_id(bd, id);
    if (node == NULL) { // Se não foi encontrado, imprime mensagem de erro
        printf(CLR_RED "Erro: Paciente com ID %d nao encontrado.\n" CLR_RESET, id);
    } else { // Se foi encontrado:
        Paciente temp_info = bd_get_paciente_info(node); // Pega as informações do paciente
        printf("Paciente encontrado: %s\n", temp_info.nome); // Imprime o nome do paciente
        printf("Digite os novos valores (para manter, digite '-'):\n"); // Solicita os novos valores ao usuário

        char n_cpf[50], n_nome[100], n_idade_str[50], cpf_formatado[15]; // Variáveis para armazenar os novos valores

        /* Leitura e validação dos novos valores */
        do {
            printf(CLR_YELLOW "CPF (11 digitos ou '-'): " CLR_RESET); // Solicita o CPF ao usuário
            fgets(n_cpf, sizeof(n_cpf), stdin); n_cpf[strcspn(n_cpf, "\n")] = 0; // Leitura do CPF e remoção do caractere de nova linha

            if (strcmp(n_cpf, "-") == 0) break; // Se for '-', sai do loop

            if (!validarCPF(n_cpf)) {// Verifica se o CPF é válido
                printf(CLR_RED "ERRO: Formato de CPF invalido! Tente novamente.\n" CLR_RESET);
                continue; // Volta ao início do loop
            }

            /* Verifica se o CPF já está cadastrado */
            formatarCPF(n_cpf, cpf_formatado);
            PacienteNode* existente = bd_find_by_cpf(bd, cpf_formatado); // Procura o CPF no banco de dados
            if (existente != NULL && bd_get_paciente_info(existente).id != id) { // Verifica se o CPF já está cadastrado em outro paciente
                 printf(CLR_RED "ERRO: CPF ja pertence a outro paciente! Tente novamente.\n" CLR_RESET);
                 strcpy(n_cpf, "invalido"); // Força o loop a continuar
            }
        } while (strcmp(n_cpf, "-") != 0 && !validarCPF(n_cpf)); // Continua o loop até que o CPF seja válido ou o usuário digite '-'

        printf(CLR_YELLOW "Nome (ou '-'): " CLR_RESET); // Solicita o nome ao usuário
        fgets(n_nome, sizeof(n_nome), stdin); n_nome[strcspn(n_nome, "\n")] = 0; // Leitura do nome e remoção do caractere de nova linha

        /* Leitura e validação da idade */
        do { 
            printf(CLR_YELLOW "Idade (ou '-'): " CLR_RESET); // Solicita a idade ao usuário
            fgets(n_idade_str, sizeof(n_idade_str), stdin); n_idade_str[strcspn(n_idade_str, "\n")] = 0; // Leitura da idade e remoção do caractere de nova linha
            if (strcmp(n_idade_str, "-") != 0 && !validarIdade(n_idade_str)) { // Verifica se a idade é válida
                printf(CLR_RED "ERRO: Idade invalida! Tente novamente.\n" CLR_RESET);
            }
        } while (strcmp(n_idade_str, "-") != 0 && !validarIdade(n_idade_str));// Continua o loop até que a idade seja válida ou o usuário digite '-'

        if(strcmp(n_cpf, "-") != 0) strcpy(temp_info.cpf, cpf_formatado); // Copia o CPF formatado para a estrutura do paciente
        if(strcmp(n_nome, "-") != 0) strcpy(temp_info.nome, n_nome); // Copia o nome para a estrutura do paciente
        if(strcmp(n_idade_str, "-") != 0) temp_info.idade = atoi(n_idade_str); // Copia a idade para a estrutura do paciente

        printf("\nConfirma os novos valores para o registro abaixo? (S/N)\n");
        imprimir_paciente(&temp_info); // Imprime as novas informações do paciente
        char conf; // Variável para armazenar a confirmação
        scanf(" %c", &conf); limparBuffer();

        /* Verifica a confirmação e atualiza o paciente no banco de dados */
        if (conf == 'S' || conf == 's') {
            bd_update_node_info(node, temp_info);  // Atualiza as informações do paciente no nó
            printf(CLR_GREEN "Registro atualizado com sucesso.\n" CLR_RESET);
            bd_save_csv(bd, "bd_paciente.csv");  // Salva o banco de dados no arquivo
        } else {
            printf(CLR_YELLOW "Atualizacao cancelada.\n" CLR_RESET);
        }
    }
    pausarExecucao();
}

/* --- Função de Remoção de Paciente --- */
void ui_removerPaciente(BDPaciente* bd) { // Recebe o ponteiro para o banco de dados
    printf(CLR_YELLOW "Digite o ID do registro a ser removido: " CLR_RESET); // Solicita o ID ao usuário
    int id; // Variável para armazenar o ID
    scanf("%d", &id);
    limparBuffer(); // Limpa o buffer

    PacienteNode* node = bd_find_by_id(bd, id); // Procura o paciente pelo ID
    if (node == NULL) {// Verifica se o paciente foi encontrado
        printf(CLR_RED "Erro: Paciente com ID %d nao encontrado.\n" CLR_RESET, id);
    } else {// Se o paciente foi encontrado, solicita a confirmação ao usuário
        printf(CLR_RED "\nTem certeza que deseja excluir o registro abaixo? (S/N)\n" CLR_RESET);
        Paciente info = bd_get_paciente_info(node); // Pega as informações do paciente
        imprimir_paciente(&info); // Imprime as informações do paciente

        char conf; // Variável para armazenar a confirmação
        scanf(" %c", &conf);
        limparBuffer();

        if (conf == 'S' || conf == 's') { // Verifica a confirmação
            if (bd_remove(bd, id)) { // Remove o paciente do banco de dados
                printf(CLR_GREEN "Registro removido com sucesso.\n" CLR_RESET);
                bd_save_csv(bd, "bd_paciente.csv"); // Salva o banco de dados no arquivo
            }
        } else {
            printf(CLR_YELLOW "Remocao cancelada.\n" CLR_RESET); // Cancela a remoção
        }
    }
    pausarExecucao(); // Pausa a execução
}
/* --- Função de Inserção de Paciente --- */
void ui_inserirPaciente(BDPaciente* bd) { // Recebe o ponteiro para o banco de dados
    Paciente p; // Cria uma variável para armazenar os dados do paciente
    char cpf_temp[50], idade_temp[50], cpf_formatado[15];

    printf(CLR_CYAN "\n--- Inserir Novo Paciente ---\n" CLR_RESET);

    /* Leitura e validação dos dados */
    do {  // Loop para ler e validar o CPF
        printf(CLR_YELLOW "CPF (apenas 11 digitos): " CLR_RESET);
        fgets(cpf_temp, sizeof(cpf_temp), stdin); // Leitura do CPF
        cpf_temp[strcspn(cpf_temp, "\n")] = 0; // Remove o caractere de nova linha

        /* Verifica se o CPF é válido */
        if (!validarCPF(cpf_temp)) { 
            printf(CLR_RED "ERRO: CPF invalido! Deve conter exatamente 11 digitos numericos. Tente novamente.\n" CLR_RESET);
            continue; // Volta ao início do loop
        }
    
        formatarCPF(cpf_temp, cpf_formatado); // Formata o CPF para o padrão XXX.XXX.XXX-XX

        /* Verifica se o CPF já está cadastrado */
        if (bd_find_by_cpf(bd, cpf_formatado) != NULL) {
            printf(CLR_RED "ERRO: CPF ja cadastrado no sistema! Tente novamente.\n" CLR_RESET);
            strcpy(cpf_temp, "invalido");
        }
    } while (!validarCPF(cpf_temp)); // Continua o loop até que o CPF seja válido

    /* Leitura e validação do nome */
    do {
        printf(CLR_YELLOW "Nome: " CLR_RESET); // Solicita o nome ao usuário
        fgets(p.nome, sizeof(p.nome), stdin); // Leitura do nome
        p.nome[strcspn(p.nome, "\n")] = 0; // Remove o caractere de nova linha
        if (strlen(p.nome) == 0) { // Verifica se o nome está vazio
            printf(CLR_RED "ERRO: O nome nao pode ser vazio. Tente novamente.\n" CLR_RESET);
        }
    } while (strlen(p.nome) == 0); // Continua o loop até que o nome seja válido

    /* Leitura e validação da idade */
    do {
        printf(CLR_YELLOW "Idade: " CLR_RESET); // Solicita a idade 
        fgets(idade_temp, sizeof(idade_temp), stdin); // Leitura da idade
        idade_temp[strcspn(idade_temp, "\n")] = 0; // Remove o caractere de nova linha
        if (!validarIdade(idade_temp)) { // Verifica se a idade é válida
            printf(CLR_RED "ERRO: Idade invalida! Use apenas numeros. Tente novamente.\n" CLR_RESET);
        }
    } while (!validarIdade(idade_temp)); // Continua o loop até que a idade seja válida
    p.idade = atoi(idade_temp); // Converte a idade para inteiro

    time_t tempo_atual; // Variável para armazenar o tempo atual
    struct tm *info_tempo; // Ponteiro para a estrutura de tempo
    time(&tempo_atual); // Obtém o tempo atual
    info_tempo = localtime(&tempo_atual); // Converte o tempo atual para a estrutura de tempo
    strftime(p.data_cadastro, sizeof(p.data_cadastro), "%Y-%m-%d", info_tempo); // Formata a data de cadastro para o padrão AAAA-MM-DD

    p.id = bd_get_proximo_id(bd); // Obtém o próximo ID disponível
    strcpy(p.cpf, cpf_formatado); // Copia o CPF formatado para a estrutura do paciente

    printf("\nConfirma a insercao do registro abaixo? (S/N)\n"); // Solicita a confirmação ao usuário
    imprimir_paciente(&p); // Imprime os dados do paciente

    char conf; // Variável para armazenar a confirmação
    scanf(" %c", &conf); limparBuffer();

    /* Verifica a confirmação e insere o paciente no banco de dados */
    if (conf == 'S' || conf == 's') {
        bd_append(bd, p);
        printf(CLR_GREEN "Registro inserido com sucesso.\n" CLR_RESET);
        bd_save_csv(bd, "bd_paciente.csv");
    } else {
        printf(CLR_YELLOW "Insercao cancelada.\n" CLR_RESET);
    }
    pausarExecucao();
}

/* --- Função de Impressão da Lista --- */
void ui_imprimirLista(BDPaciente* bd) { // Recebe o ponteiro para o banco de dados
    const int ITENS_POR_PAGINA = 10; // Número de itens a serem exibidos por página (fica mais fácil de visualizar)
    int contador = 0; 
    PacienteNode* p = bd_get_first(bd);  // Ponteiro para o primeiro nó da lista
    if (p == NULL) { // Verifica se a lista está vazia
        printf(CLR_YELLOW "\nNenhum paciente cadastrado.\n" CLR_RESET);
    } else { // Se a lista não estiver vazia, imprime os pacientes
        printf(CLR_CYAN "\n--- Lista de Pacientes ---\n" CLR_RESET); // Imprime o cabeçalho
        printf(CLR_BLUE "%-5s %-15s %-30s %-10s %-15s\n" CLR_RESET, "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
        printf("--------------------------------------------------------------------------\n");
        while (p != NULL) { // Percorre a lista
            Paciente info = bd_get_paciente_info(p); // Pega as informações do paciente
            imprimir_paciente(&info);
            contador++; // Incrementa o contador de pacientes
            if (contador % ITENS_POR_PAGINA == 0 && bd_get_next_node(p) != NULL) {
                printf("--------------------------------------------------------------------------\n");
                printf("Mostrando %d registros. Pressione ENTER para ver mais...", contador);
                getchar();
                printf("\n");
                printf(CLR_BLUE "%-5s %-15s %-30s %-10s %-15s\n" CLR_RESET, "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
                printf("--------------------------------------------------------------------------\n");
            }
            p = bd_get_next_node(p); // Avança para o próximo nó
        }
        printf("--------------------------------------------------------------------------\n");
        printf("Fim da lista. Total de %d paciente(s).\n", contador);
    }
    pausarExecucao();
}

/* --- Função Principal da Interface --- */
void iniciarLoopPrincipal(BDPaciente* bd) { // Recebe o ponteiro para o banco de dados
    char opcao;
    do {
        limparTela();
        printf(CLR_CYAN "\n===== HealthSys - Sistema de Pacientes =====\n" CLR_RESET); 
        printf("1 - Consultar paciente\n");
        printf("2 - Atualizar paciente\n");
        printf("3 - Remover paciente\n");
        printf("4 - Inserir paciente\n");
        printf("5 - Imprimir lista de pacientes\n");
        printf(CLR_RED "Q - Sair e Salvar\n" CLR_RESET); // Opção para sair do programa
        printf("==========================================\n");
        printf(CLR_YELLOW "Escolha uma opção: " CLR_RESET);// Solicita a opção ao usuário

        scanf(" %c", &opcao);
        limparBuffer(); // Limpa o buffer 

        switch (toupper(opcao)) { // Converte a opção para maiúscula antes de comparar
            case '1': ui_consultarPaciente(bd); break; // Chama a função de consulta
            case '2': ui_atualizarPaciente(bd); break; // Chama a função de atualização
            case '3': ui_removerPaciente(bd); break; // Chama a função de remoção
            case '4': ui_inserirPaciente(bd); break; // Chama a função de inserção
            case '5': ui_imprimirLista(bd); break;// Chama a função de impressão
            case 'Q': break; // Sai do loop
            default: printf(CLR_RED "Opcao invalida! Tente novamente.\n" CLR_RESET); pausarExecucao(); break; // Opção inválida
        }
    } while (toupper(opcao) != 'Q'); // Continua o loop até que o usuário escolha sair
}
