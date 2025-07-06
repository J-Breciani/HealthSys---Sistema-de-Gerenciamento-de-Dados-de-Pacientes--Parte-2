#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"

/* Estruturas internas */

/* Estrutura da lista encadeada */
struct bd_paciente { 
    PacienteNode* first;
    int proximo_id;
} BD_Paciente;

/* Estrutura do nó da lista encadeada */
struct paciente_node {
    Paciente info;
    PacienteNode* next;
}Paciente_Node; 

/* Funções internas */

/* Função de criar a lista encadeada */
BDPaciente* bd_create() {
    BDPaciente* bd = (BDPaciente*)malloc(sizeof(BDPaciente)); // Aloca memória para a estrutura do banco de dados
    if (bd == NULL) return NULL; // Verifica se a alocação foi bem-sucedida
    bd->first = NULL; // Inicializa o primeiro nó como nulo
    bd->proximo_id = 1; // Inicializa o próximo ID como 1
    return bd; // Retorna o ponteiro para a estrutura do banco de dados
}
/* Função de liberar a lista encadeada */
void bd_free(BDPaciente* bd) {
    if (bd == NULL) return; // Verifica se o ponteiro do banco de dados é nulo
    PacienteNode* p = bd->first; // Inicializa um ponteiro para o primeiro nó
    while (p != NULL) { // Percorre a lista encadeada
        PacienteNode* t = p->next;
        free(p); // Libera a memória do nó atual
        p = t; // Avança para o próximo nó
    }
    free(bd); // Libera a memória da estrutura do banco de dados
}

/* Função de adicionar um paciente na lista encadeada */
void bd_append(BDPaciente* bd, Paciente paciente) { // Recebe o ponteiro para o banco de dados e o paciente a ser adicionado
    PacienteNode* node = (PacienteNode*)malloc(sizeof(PacienteNode));
    if (node == NULL) return;
    node->info = paciente;
    node->next = NULL;

    if (paciente.id >= bd->proximo_id) { // Verifica se o ID do paciente é maior ou igual ao próximo ID disponível
        bd->proximo_id = paciente.id + 1; // Atualiza o próximo ID disponível
    }

    if (bd->first == NULL) { // Verifica se a lista está vazia
        bd->first = node;
    } else { // Se a lista não estiver vazia, adiciona o nó no final
        PacienteNode* p = bd->first;
        while (p->next != NULL) {
            p = p->next; // Avança para o próximo nó
        }
        p->next = node; // Adiciona o nó no final da lista
    }
}

/* Função de remover um paciente da lista encadeada */
int bd_remove(BDPaciente* bd, int id) { // Recebe o ponteiro para o banco de dados e o ID do paciente a ser removido
    PacienteNode* p = bd->first; // Inicializa um ponteiro para o primeiro nó
    PacienteNode* prev = NULL;// Inicializa um ponteiro para o nó anterior

    /* Percorre a lista encadeada até encontrar o nó com o ID desejado */
    while (p != NULL && p->info.id != id) {
        prev = p;
        p = p->next;
    }

    /* Verifica se o nó foi encontrado */
    if (p == NULL) return 0;

    /* Remove o nó da lista */
    if (prev == NULL) {
        bd->first = p->next; // Se o nó a ser removido é o primeiro, atualiza o primeiro nó
    } else {
        prev->next = p->next; // Se o nó a ser removido não é o primeiro, atualiza o próximo nó do nó anterior
    }
    free(p); // Libera a memória do nó removido
    return 1;
}
 /* Função de carregar os dados do arquivo CSV */
void bd_load_csv(BDPaciente* bd, const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        printf("AVISO: Arquivo '%s' nao encontrado. Um novo sera criado ao salvar.\n", filepath);
        pausarExecucao(); // Pausa para o usuário ler o aviso
        return;
    }
    
    char line[256]; 
    fgets(line, sizeof(line), file); // Ignora a primeira linha (cabeçalho)

    /* Leitura dos dados do arquivo */
    while (fgets(line, sizeof(line), file)) {
        Paciente p; // Cria uma variável para armazenar os dados do paciente
        sscanf(line, "%d,%[^,],%[^,],%d,%s", &p.id, p.cpf, p.nome, &p.idade, p.data_cadastro); // Leitura dos dados 
        bd_append(bd, p); // Adiciona o paciente ao bd
    }
    // Verifica se o fechamento do arquivo foi bem-sucedido
    if (fclose(file) != 0) {
        perror("Erro ao fechar o arquivo de leitura");
    }
}
/* Função de salvar os dados do csv */
void bd_save_csv(BDPaciente* bd, const char* filepath) {
    FILE* file = fopen(filepath, "w"); // Abre o arquivo para escrita
    if (file == NULL) { // Verifica se o arquivo foi aberto com sucesso
        perror("ERRO CRITICO AO SALVAR ARQUIVO");
        return;
    }

    /* Escreve o cabeçalho no arquivo */
    fprintf(file, "ID,CPF,Nome,Idade,Data_Cadastro\n");
    for (PacienteNode* p = bd->first; p != NULL; p = p->next) { // Percorre a lista encadeada
        fprintf(file, "%d,%s,%s,%d,%s\n",
                p->info.id, p->info.cpf, p->info.nome,
                p->info.idade, p->info.data_cadastro);
    }
    /* Verifica se o fechamento do arquivo foi bem-sucedido */
    if (fclose(file) != 0) {
        perror("Erro ao fechar o arquivo de escrita");
    }
}
/* Função para pegar o primeiro nó da lista BDPaciente */
PacienteNode* bd_get_first(BDPaciente* bd) {
    return bd->first;
}
/* Função para pegar as informações do paciente */
Paciente bd_get_paciente_info(PacienteNode* node) {
    return node->info;
}

/* Função para pegar o próximo nó da lista */
PacienteNode* bd_get_next_node(PacienteNode* node) {
    return node->next;
}

/* Função para encontrar um paciente pelo ID */
PacienteNode* bd_find_by_id(BDPaciente* bd, int id) {
    for (PacienteNode* p = bd->first; p != NULL; p = p->next) { // Percorre a lista
        if (p->info.id == id) { // Verifica se o ID do paciente é igual ao ID procurado
            return p; //Retorna o nó
        }
    }
    return NULL; 
}

/* Função para pegar o próximo ID */
int bd_get_proximo_id(BDPaciente* bd) {
    return bd->proximo_id;
}

/* Função para atualizar as informações do paciente no nó */
void bd_update_node_info(PacienteNode* node, Paciente new_info) {
    if (node != NULL) {
        node->info = new_info;
    }
}
/* Função para encontrar um paciente pelo CPF */
PacienteNode* bd_find_by_cpf(BDPaciente* bd, const char* cpf) {
    for (PacienteNode* p = bd->first; p != NULL; p = p->next) { // Percorre a lista
        if (strcmp(p->info.cpf, cpf) == 0) { // Verifica se o CPF do paciente é igual ao CPF procurado
            return p; // Retorna o nó encontrado
        }
    }
    return NULL;
}