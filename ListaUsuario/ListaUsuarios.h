#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef LISTAUSUARIOS_H_INCLUDED
#define LISTAUSUARIOS_H_INCLUDED

typedef struct login
{
    char Usuario[50];
    char Senha[50];
    struct login *PROXIMO;
    struct login *ANTERIOR;
} Login;


struct login *PRIMEIRO;
struct login *ULTIMO;struct login *ValidarUsuario(char *vusuario);
int ValidarEntrada(char *USUARIO,char *SENHA,char *VUSUARIO,char *VSENHA);
void CadastrarUsuarios();void imprimir();
void SalvarUsuarioEmBinario();CarregarUsuariosdoArquivo();
struct login *BuscaParaValidar(char *Usuario);
void ListaUsuario(struct login *NOVO,struct login **PRIMEIRO, struct login **ULTIMO);

#endif // LISTAUSUARIOS_H_INCLUDED
