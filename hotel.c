#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"

#include <stdio.h>

// --- STRUCTS ---
typedef struct {
    int codigo;
    char nome[100];
    char endereco[100];
    char telefone[20];
} Cliente;

typedef struct {
    int codigo;
    char nome[100];
    char cargo[50];
    float salario;
} Funcionario;

typedef struct {
    int numero;
    int quantidadeHospedes;
    float valorDiaria;
    int status; 
} Quarto;

typedef struct {
    int codigoEstadia;
    int codigoCliente;
    int numeroQuarto;
    char dataEntrada[11]; 
    char dataSaida[11];
    int quantidadeDiarias;
    int ativa; 
} Estadia;

// --- PROTOTIPOS ---
void cadastrarCliente();
void cadastrarFuncionario();
void cadastrarQuarto();
void cadastrarEstadia();
void darBaixaEstadia();
void pesquisarCliente();
void pesquisarFuncionario();
void mostrarEstadiasCliente();

#endif