#ifndef PACIENTE_H
#define PACIENTE_H

/* Define o tamanho máximo para os campos de texto */
#define MAX_NOME 100
#define MAX_CPF 15 // Precisa incluir . e -
#define MAX_DATA 11  // // Formato AAAA-MM-DD


void imprimir_paciente(const Paciente *p);

#endif // PACIENTE_H
/* ifndef verifica se o arquivo já foi incluído, se não foi, ele inclui. 
Assim, evita uma declaração dupla, porque se já foi incluido, retorna uma blank file.*/