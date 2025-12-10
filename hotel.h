#ifndef HOTEL_H
#define HOTEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char status[15];
} Quarto;

typedef struct {
    int codigo;
    char dataEntrada[11];
    char dataSaida[11];
    int quantidadeDiarias;
    int codigoCliente;
    int numeroQuarto;
} Estadia;

void cadastrarCliente();
void cadastrarFuncionario();
void cadastrarQuarto();
void cadastrarEstadia();
void darBaixaEstadia();
void pesquisarCliente();
void pesquisarFuncionario();
void mostrarEstadiasCliente();

#endif
