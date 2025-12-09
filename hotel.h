#ifndef HOTEL_H
#define HOTEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir as coisa para as funções, pro computador ler

typedef struct {
    int codigo;
    char nome[100];
    char endereco[150];
    char telefone[20];
} Cliente;

typedef struct {
    int codigo;
    char nome[100];
    char telefone[20];
    char cargo[50];
    float salario;
} Funcionario;

typedef struct {
    int numero;
    int quantidadeHospedes;
    float valorDiaria;
    char status[15]; // ocupado ou vazio
} Quarto;

typedef struct {
    int codigo;
    char dataEntrada[11]; // Dia/ Mes / Ano
    char dataSaida[11];   // Dia / Mes / Ano 
    int quantidadeDiarias;
    int codigoCliente;
    int numeroQuarto;
} Estadia;

// Todas as funções

void cadastrarCliente();
void cadastrarFuncionario();
void cadastrarQuarto();
void cadastrarEstadia();
void darBaixaEstadia();
void pesquisarCliente();
void pesquisarFuncionario();
void mostrarEstadiasCliente();


#endif