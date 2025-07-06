#ifndef PACIENTE_H
#define PACIENTE_H

// Define a estrutura para armazenar os dados de um único paciente
typedef struct {
    int id; // Identificador único do paciente
    char cpf[15]; // CPF do paciente (string)
    char nome[100]; // Nome do paciente
    int idade; // Idade do paciente
    char data_cadastro[11]; // Data de cadastro do paciente (formato DD/MM/AAAA)
} Paciente; 

// Função para imprimir as informações do paciente.
void imprimir_paciente(const Paciente* p);

#endif // PACIENTE_H