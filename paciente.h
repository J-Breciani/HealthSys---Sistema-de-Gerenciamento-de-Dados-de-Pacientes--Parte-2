#ifndef PACIENTE_H
#define PACIENTE_H

/* Define o tamanho máximo para os campos de texto */
#define MAX_NOME 100
#define MAX_CPF 15 // Precisa incluir . e -
#define MAX_DATA 11  // // Formato AAAA-MM-DD

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

void imprimir_paciente(const Paciente *p);

#endif // PACIENTE_H
/* ifndef verifica se o arquivo já foi incluído, se não foi, ele inclui. 
Assim, evita uma declaração dupla, porque se já foi incluido, retorna uma blank file.*/