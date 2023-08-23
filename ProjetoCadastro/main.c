#include <stdio.h>
#include <stdlib.h>
#include "ListaDupla.h"

int main()
{


    char Usuario[50],Senha[50],UsuarioE[50],SenhaE[50];
    int a=0,b=1,d=3;
    char c;

    printf("\n\t\t\tCADASTRO\n\n");
    printf("\nDigite o login-> ");
    gets(Usuario);
    fflush(stdin);

    printf("\nDigite a senha: ");
    do
    {
        c=getch();
        if(isprint(c))
        {
            Senha[a]=c;
            a++;
            printf("*");
        }
        else if(c==8&&a)
        {
            Senha[a]='\0';
            a--;
            printf("\b \b");
        }
    }
    while(c!=13);
    Senha[a]='\0';
    system("cls");
    printf("\n\nCadastro efetuado com sucesso...\n\n");
    do
    {
        printf("\nEntre com o login: ");
        fflush(stdin);
        gets(UsuarioE);
        printf("\nEntre com a senha: ");
        a=0;
        do
        {
            c=getch();
            if(isprint(c))
            {
                SenhaE[a]=c;
                a++;
                printf("*");
            }
            else if(c==8&&a)
            {
                SenhaE[a]='\0';
                a--;
                printf("\b \b");
            }
        }
        while(c!=13);
        SenhaE[a]='\0';

        if(!strcmp(Usuario,UsuarioE)&&!strcmp(Senha,SenhaE))
        {

            printf("\n\n\t\t\tLogado com Sucesso\n\n");
            b=0;
            menu();
        }
        else
        {
            system("cls");
            d--;
            if (d)printf("\n\n\t\tLogin ou Senha Invalidos\n\n");
        }
    }
    while(b&&d);
    if(!d)printf("\n\n\t\tLimite de tentativas ultrapassado.\n\n");
        printf("\n\n\t\tTente Novamente mais Tarde.\n\n");

    system("pause");
}
