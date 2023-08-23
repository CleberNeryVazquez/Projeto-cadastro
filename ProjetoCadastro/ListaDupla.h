#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#ifndef LISTADUPLA_H_INCLUDED
#define LISTADUPLA_H_INCLUDED



typedef struct data
{
    int dia,mes,ano;
} Data;

typedef struct endereco
{
    char rua[50];
    char bairro[50];
    char cidade[50];
    char U,F;
    int num;
    int64_t cep;
} Endereco;

typedef struct no
{
    char nome[50];
    char email[50];
    char comorbidade;
    int64_t CPF;
    int idade;
    struct data nasc;
    struct data diag;
    struct endereco resid;
    struct no *proximo;
    struct no *anterior;
} No;

struct no *primeiro;
struct no *ultimo;

void menu();
void imprimir();
void Entradas();
void SalvarEmBinario();
void CarregardoArquivo();
int CalcularIdade(int DIA,int MES,int ANO);
struct no *BuscaParaRemover(int64_t *cpf);
struct no *MostraUmPaciente(int64_t *cpf);
struct no *BuscaValidar(int64_t *cpf);
int remover(struct no **primeiro,struct no **ultimo);
void Lista(struct no *novo,struct no **primeiro, struct no **ultimo);


#endif // LISTADUPLA_H_INCLUDED
