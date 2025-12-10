#ifndef HOTEL_H
#define HOTEL_H

#include <stdio.h>

// Definição das Estruturas
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
    int status; // 0 = Disponível, 1 = Ocupado
} Quarto;

typedef struct {
    int codigoEstadia;
    int codigoCliente;
    int numeroQuarto;
    char dataEntrada[11]; // Formato DD/MM/AAAA
    char dataSaida[11];
    int quantidadeDiarias;
    int ativa; // 1 = Ativa (check-in feito), 0 = Finalizada (checkout feito)
} Estadia;

// Protótipos das funções
void cadastrarCliente();
void cadastrarFuncionario();
void cadastrarQuarto();
void cadastrarEstadia();
void darBaixaEstadia();
void pesquisarCliente();
void pesquisarFuncionario();
void mostrarEstadiasCliente();

#endif