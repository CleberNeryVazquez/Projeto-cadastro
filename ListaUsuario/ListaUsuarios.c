#include "ListaUsuarios.h"

void imprimir()
{

    struct login *info;
    info = PRIMEIRO;

    while(info)
    {
        printf("\nNOme -> %s\n",info->Usuario);
        printf("\nSEnha -> %s\n",info->Senha);
        info = info ->PROXIMO;
    }
    printf("\n\n");
}



void CadastrarUsuarios()
{
    CarregarUsuariosdoArquivo();
    struct login *info;
    char opc;
    int aux2;
    do
    {
        system("cls");
        info = (struct login *)malloc(sizeof(Login));
        if(!info)
        {
            printf("\nsem memoria\n");
            return;
        }
        printf("\n Insira o nome de Usuario %c ",175);
        fgets(info->Usuario,49,stdin);
        aux2 = BuscaParaValidar(info->Usuario);
        if(aux2)
        {
            printf("\nUsuario ja cadastrado\n");
            system("pause");
            break;
        }

        printf("\n Insira a Senha %c ",175);
        fgets(info->Senha,49,stdin);
        fflush(stdin);

        ListaUsuario(info,&PRIMEIRO,&ULTIMO);
        SalvarUsuarioEmBinario();
        printf("\nContinuar ? [S]im [N]ao .%c\n",175);
        opc = getchar();
        fflush(stdin);
        system("cls");
    }
    while(opc != 'n');
}

void ListaUsuario(struct login *NOVO,struct login **PRIMEIRO, struct login **ULTIMO)
{
    struct login *aux, *aux2;
    if (*ULTIMO == NULL)
    {
        NOVO ->PROXIMO =NULL;
        NOVO ->ANTERIOR =NULL;
        *ULTIMO = NOVO;
        *PRIMEIRO = NOVO;
        return;
    }
    aux2 = *PRIMEIRO;
    aux = NULL;
    while(aux2)
    {
        if(strcmp(aux2->Usuario,NOVO->Usuario)<0)
        {
            aux = aux2;
            aux2 = aux2->PROXIMO;
        }
        else
        {
            if(aux2->ANTERIOR)
            {
                aux2->ANTERIOR->PROXIMO = NOVO;
                NOVO->PROXIMO = aux2;
                NOVO->ANTERIOR = aux2->ANTERIOR;
                aux2->ANTERIOR = NOVO;
                return;
            }
            NOVO->PROXIMO = aux2;
            NOVO->ANTERIOR = NULL;
            aux2->ANTERIOR = NOVO;
            *PRIMEIRO = NOVO;
            return;
        }
    }
    aux->PROXIMO = NOVO;
    NOVO->PROXIMO = NULL;
    NOVO->ANTERIOR = aux;
    *ULTIMO = NOVO;
}
void SalvarUsuarioEmBinario()
{
    struct login *info;
    FILE *arquivo;
    arquivo = fopen("ListaDeUsuariosCadastrados","ab");
    if(!arquivo)
    {
        printf("\nErro ao abrir arquivo !\n");
        exit(1);
    }
    printf("\nSalvo com sucesso \n");
    info = PRIMEIRO;
    while(info)
    {
        fwrite(info,sizeof(struct login),1,arquivo);
        info = info->PROXIMO;
    }
    fclose(arquivo);
}
struct login *BuscaParaValidar(char *Nome)
{
    struct login *info;
    info = PRIMEIRO;
    while(info)
    {
        if(!strcmp(Nome, info->Usuario))
            return 1;
        info = info->PROXIMO;
    }
    return NULL;
}
int MenuInicial()
{

    CarregarUsuariosdoArquivo();
    struct login *info;
    info = PRIMEIRO;
    int a=0,b=1,d=3,aux=0,aux1=0;
    char c, VUSUARIO[50], VSENHA[50];
    do
    {
        printf("\nEntre com o login: ");
        fflush(stdin);
        gets(VUSUARIO);
        printf("\nEntre com a senha: ");
        a=0;
        do
        {
            c=getch();
            if(isprint(c))
            {
                VSENHA[a]=c;
                a++;
                printf("*");
            }
            else if(c==8 && a)
            {
                VSENHA[a]='\0';
                a--;
                printf("\b \b");
            }
        }
        while(c!=13);
        VSENHA[a]='\0';

aux = ValidarUsuario(VUSUARIO);

        if(aux)
        {
            printf("\n\n\t\t\tLogado com sucesso...\n\n");
            b=0;
        }
        else
        {
            system("cls");
            d--;
            if (d)printf("\n\n\t\tSENHA INVALIDA - TENTE NOVAMENTE...\n\n");
        }
    }
    while(b && d);
    if(!d)printf("\n\n\t\tCONTA BLOQUEADA - VOCE ERROU 3 VEZES CONSECUTIVAS...\n\n");
    system("pause");
}

CarregarUsuariosdoArquivo()
{

    struct login *info;
    FILE *arquivo;
    arquivo = fopen("ListaDeUsuariosCadastrados","rb");
    if(!arquivo)
    {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    while(PRIMEIRO)
    {
        info = PRIMEIRO->PROXIMO;
        free(info);
        PRIMEIRO = info;
    }
    PRIMEIRO = ULTIMO = NULL;
    info = (struct login*)malloc(sizeof(struct login));
    if(!info)
    {
        printf("Erro ao alocar memoria!\n");
        return;
    }
    while(fread(info,sizeof(struct login), 1,arquivo))
    {
        ListaUsuario(info,&PRIMEIRO,&ULTIMO);
        info = (struct login*)malloc(sizeof(struct login));
    }
    fclose(arquivo);
}
//================================================================

struct login *ValidarUsuario(char *vusuario)
{
    struct login *info;
    info = PRIMEIRO;
    while(info)
    {
        if(!strcmp(vusuario, info->Usuario))
            return 1;
        info = info->PROXIMO;
    }
    return NULL;
}
struct login *ValidarSenha(char *vsenha)
{
    struct login *info;
    info = PRIMEIRO;
    while(info)
    {
        if(!strcmp(vsenha, info->Usuario))
            return 1;
        info = info->PROXIMO;
    }
    return NULL;
}
