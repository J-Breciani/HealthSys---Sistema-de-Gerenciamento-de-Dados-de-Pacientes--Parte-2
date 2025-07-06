#ifndef INTERFACE_H
#define INTERFACE_H

#include "bd_paciente.h"

// Macros para cores ANSI no terminal
#define CLR_RESET   "\x1b[0m" 
#define CLR_RED     "\x1b[31m"
#define CLR_GREEN   "\x1b[32m"
#define CLR_YELLOW  "\x1b[33m"
#define CLR_BLUE    "\x1b[34m"
#define CLR_CYAN    "\x1b[36m"

/* Função para pausar a execução do programa */
void iniciarLoopPrincipal(BDPaciente* bd);

#endif // INTERFACE_H