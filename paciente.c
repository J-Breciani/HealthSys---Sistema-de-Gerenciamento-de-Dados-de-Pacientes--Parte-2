// Em paciente.c
#include <stdio.h>
#include "paciente.h"

void imprimir_paciente(const Paciente* p) {
    if (p != NULL) {
        /* ID   CPF              Nome                            Idade  Data Cadastro */
        printf("%-4d %-15s %-30s %-6d %-10s\n",
               p->id,
               p->cpf,
               p->nome,
               p->idade,
               p->data_cadastro);
    }
}

/* Estrutura para armazenar os dados de um paciente 
Estrura baseada no exemplo do documento: 
ID      CPF          Nome   Idade  Data_Cadastro
1 123.456.789-09 João Silva 45 2024-12-01 */
typedef struct {
  int id;
  char cpf[MAX_CPF]; 
  char nome[MAX_NOME];
  int idade;
  char data_cadastro[MAX_DATA];
} Paciente;