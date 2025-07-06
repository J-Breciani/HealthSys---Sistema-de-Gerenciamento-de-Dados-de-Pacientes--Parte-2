#ifndef BD_PACIENTE_H
#define BD_PACIENTE_H

/* Incluir 'paciente.h' PRIMEIRO para que o compilador saiba o que é 'Paciente'. */
#include "paciente.h" 


/* Define as estruturas BDPaciente e PacienteNode no estilo do professor */

typedef struct bd_paciente BDPaciente;   // Representa o banco de dados (a lista)

typedef struct paciente_node PacienteNode; // Representa um nó da lista


/* --- Operações sobre o Banco de Dados (Interface do TAD) --- */

BDPaciente* bd_create(); // Cria um banco de dados vazio

void bd_free(BDPaciente* bd); // Libera a memória alocada para o banco de dados

void bd_append(BDPaciente* bd, Paciente paciente); // Adiciona um paciente ao banco de dados

int bd_remove(BDPaciente* bd, int id); // Remove um paciente do banco de dados

void bd_load_csv(BDPaciente* bd, const char* filepath); // Carrega os dados do arquivo CSV para o banco de dados

void bd_save_csv(BDPaciente* bd, const char* filepath); // Salva os dados do banco de dados no arquivo CSV

PacienteNode* bd_get_first(BDPaciente* bd); // Retorna o primeiro nó da lista

Paciente bd_get_paciente_info(PacienteNode* node); // Retorna as informações do paciente armazenadas no nó

PacienteNode* bd_get_next_node(PacienteNode* node);  // Retorna o próximo nó da lista

PacienteNode* bd_find_by_id(BDPaciente* bd, int id); // Função para encontrar um paciente pelo ID

PacienteNode* bd_find_by_cpf(BDPaciente* bd, const char* cpf); // Função para encontrar um paciente pelo CPF

int bd_get_proximo_id(BDPaciente* bd); // Retorna o próximo ID 

void bd_update_node_info(PacienteNode* node, Paciente new_info); // Atualiza as informações do paciente no nó

#endif 