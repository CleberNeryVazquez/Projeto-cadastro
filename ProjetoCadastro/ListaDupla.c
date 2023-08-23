#include "ListaDupla.h"

void menu()
{
    int op;int64_t mostrar;
    do
    {
        printf("\n%c MENU INICIAL %c\n",174,175);
        printf("\n[0] - Sair\n[1] - Inserir Novo Cadastro\n[2] - Mostrar Todo os Cadastros\n"
               "[3] - Salvar em arquivo\n[4] - Carregar Cadastros do Arquivo\n"
               "[5] - Remover um cadastro\n[6] - Mostrar um paciente\n\n"
               " Entre com a opcao escolhida %c ",175);
        scanf("%d",&op);
        getchar();
        printf("\n\n");
        switch(op)
        {
        case 1:
            Entradas();
            break;
        case 2:
            imprimir();
            break;
        case 3:
            SalvarEmBinario();
            break;
        case 4:
            CarregardoArquivo();
            break;
        case 5:
            remover(&primeiro,&ultimo);
            break;
        case 6:
            printf("\nEntre com o CPF\n");
            scanf("%"SCNu64,&mostrar);
            MostraUmPaciente(mostrar);
            break;
        case 0:
            system("cls");
            printf("\nObrigado por utilizar o sistema de cadastro !\n\n");
            printf("\n\t\t  %c / %c \n\n\n",174,175);
            exit(0);
        default:
            printf("\nOpcao invalida !\n");
            break;
        }
    }
    while(op != 0);
    system("pause");
    system("cls");
}


void imprimir()
{
    struct no *info;
    info = primeiro;
    if(info == NULL)
    {
        printf("\nSistema esta vazio !!\n"
               "\nCarregue do arquivo opcao [4]\nOu Cadastre novos pacientes opcao [1]\n\n");
        system("pause");
    }
    system("cls");
    while(info)
    {
        printf("=======================================\n");
        printf("\nCPF %c %"PRIu64"\n",175,info->CPF);
        printf("\nNome %c %s\n",175,info->nome);
        printf("\nEmail %c %s\n",175,info->email);
        printf("\nIdade %c %d\n",175,info->idade);
        printf("\nComorbidade %c %c\n",175,info->comorbidade);
        printf("\nData Nascimento %c %02d/%02d/%04d\n",175,info->nasc.dia,info->nasc.mes,info->nasc.ano);
        printf("\nData do diagnostico %c %02d/%02d/%04d\n",175,info->diag.dia,info->diag.mes,info->diag.ano);
        printf("\n_______________ ENDERECO ______________\n");
        printf("\nRua %c %s N%c%d",175,info->resid.rua,248,info->resid.num);
        printf("\nBairro %c %s\n",175,info->resid.bairro);
        printf("\nCidade %c %s\n",175,info->resid.cidade);
        printf("\nEstado [UF] %c %c%c\n",175,info->resid.U,info->resid.F);
        printf("\nCEP %c %"PRIu64"\n",175,info->resid.cep);
        info = info->proximo;
    }
    printf("\n\n");
}

CarregardoArquivo()
{
    char c;
    struct no *info;
    FILE *arquivo;
    arquivo = fopen("ListaPacientes","rb");
    if(!arquivo)
    {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    printf("Arquivo carregado com sucesso!\n");
    while(primeiro)
    {
        info = primeiro->proximo;
        free(info);
        primeiro = info;
    }
    primeiro = ultimo = NULL;
    info = (struct no*)malloc(sizeof(struct no));
    if(!info)
    {
        printf("Erro ao alocar memoria!\n");
        return;
    }
    while(fread(info,sizeof(struct no), 1,arquivo))
    {
        Lista(info,&primeiro,&ultimo);
        info = (struct no*)malloc(sizeof(struct no));
    }
    fclose(arquivo);
}


void Entradas()
{
    struct tm tempo;
    time_t tempoSeg;
    time(&tempoSeg);
    tempo = *localtime(&tempoSeg);
    struct data agora;
    agora.dia = tempo.tm_mday;
    agora.mes = tempo.tm_mon + 1;
    agora.ano = tempo.tm_year + 1900;
    FILE *arqv;
    char opc,c;
    int aux=0,aux1=0,aux2=0,aux3=0, retornonumero=0;
    int64_t retorno=0, retornocep=0;
    struct no *info;
    do
    {
        system("cls");
        info = (struct no *)malloc(sizeof(No));
        if(!info)
        {
            printf("\nsem memoria\n");
            return;
        }
        do
        {
            printf("\n Insira o CPF somento numeros %c ",175);
            retorno = scanf("%"SCNu64,&info->CPF);
            do
            {
                c = getchar();
            }
            while(c != '\n');
        }
        while(retorno == 0);

        aux2 = BuscaValidar(info->CPF);
        if(aux2)
        {
            printf("\nUsuario ja cadastrado\n");
            break;
        }
        printf("\n Insira o nome %c ",175);
        fgets(info->nome,49,stdin);
        fflush(stdin);
        printf("\n Insira o email %c ",175);
        fgets(info->email,49,stdin);
        fflush(stdin);
        printf("\n Possui alguma comorbidade ? [S]im [N]ao\n"
               "Ex. Diabetes,Obesidade,Hipertensao,tuberculose,outros %c ",175);
        scanf("%c",&info->comorbidade);
        fflush(stdin);

        do
        {
            printf("\n Insira a Data de Nascimento dd/mm/aaaa %c ",175);
            scanf("%02d /%02d/ %04d",&info->nasc.dia,&info->nasc.mes,&info->nasc.ano);
            fflush(stdin);
            if(agora.ano >=info->nasc.ano)
            {
                if (info->nasc.ano >= 1900 && info->nasc.ano <= 9999)
                {
                    if (info->nasc.mes >= 1 && info->nasc.mes <= 12)
                    {
                        if ((info->nasc.dia >= 1 && info->nasc.dia <= 31)&&
                                (info->nasc.mes == 1 || info->nasc.mes == 3 || info->nasc.mes == 5 ||
                                 info->nasc.mes == 7 || info->nasc.mes == 8 || info->nasc.mes == 10 || info->nasc.mes == 12))
                        {
                            aux++;
                        }

                        else if ((info->nasc.dia >= 1 && info->nasc.dia <= 30) && (info->nasc.mes == 4 || info->nasc.mes == 6 || info->nasc.mes == 9 || info->nasc.mes == 11))
                        {
                            aux++;
                        }

                        else if ((info->nasc.dia >= 1 && info->nasc.dia <= 28) && (info->nasc.mes == 2))
                        {
                            aux++;
                        }

                        else if (info->nasc.dia == 29 && info->nasc.mes == 2 && (info->nasc.ano % 400 == 0 || (info->nasc.ano % 4 == 0 && info->nasc.ano % 100 != 0)))
                        {
                            aux++;

                        }
                        else
                        {
                            printf("|===============|\n");
                            printf("| Data Invalida.|\n");
                            printf("|_______________|\n");
                        }
                    }
                    else
                    {
                        printf("|===============|\n");
                        printf("| Data Invalida.|\n");
                        printf("|_______________|\n");
                    }
                }
                else
                {
                    printf("|===============|\n");
                    printf("| Data Invalida.|\n");
                    printf("|_______________|\n");
                }
            }
            else
            {
                printf("|===============|\n");
                printf("| Data Invalida.|\n");
                printf("|_______________|\n");
            }
        }
        while(aux == 0);
        info->idade = CalcularIdade(info->nasc.dia,info->nasc.mes,info->nasc.ano);

    do{
      printf("\n Insira a Data de diagnostico dd/mm/aaaa %c ",175);
            scanf("%02d /%02d/ %04d",&info->diag.dia,&info->diag.mes,&info->diag.ano);
            fflush(stdin);
            if(agora.ano >=info->diag.ano)
            {
                if (info->diag.ano >= 1900 && info->diag.ano <= 9999)
                {
                    if (info->diag.mes >= 1 && info->diag.mes <= 12)
                    {
                        if ((info->diag.dia >= 1 && info->diag.dia <= 31)&&
                                (info->diag.mes == 1 || info->diag.mes == 3 || info->diag.mes == 5 ||
                                 info->diag.mes == 7 || info->diag.mes == 8 || info->diag.mes == 10 || info->diag.mes == 12))
                        {
                            aux3++;
                        }

                        else if ((info->diag.dia >= 1 && info->diag.dia <= 30) && (info->diag.mes == 4 || info->diag.mes == 6 || info->diag.mes == 9 || info->diag.mes == 11))
                        {
                            aux3++;
                        }

                        else if ((info->diag.dia >= 1 && info->diag.dia <= 28) && (info->diag.mes == 2))
                        {
                            aux3++;
                        }

                        else if (info->diag.dia == 29 && info->diag.mes == 2 && (info->diag.ano % 400 == 0 || (info->diag.ano % 4 == 0 && info->diag.ano % 100 != 0)))
                        {
                            aux3++;

                        }
                        else
                        {
                            printf("|===============|\n");
                            printf("| Data Invalida.|\n");
                            printf("|_______________|\n");
                        }
                    }
                    else
                    {
                        printf("|===============|\n");
                        printf("| Data Invalida.|\n");
                        printf("|_______________|\n");
                    }
                }
                else
                {
                    printf("|===============|\n");
                    printf("| Data Invalida.|\n");
                    printf("|_______________|\n");
                }
            }
            else
            {
                printf("|===============|\n");
                printf("| Data Invalida.|\n");
                printf("|_______________|\n");
            }
        }
        while(aux3 == 0);

        printf("\n Insira o Nome da Rua %c ",175);
        fgets(info->resid.rua,49,stdin);
        fflush(stdin);
        do
        {
            printf("\n Insira o Numero %c ",175);
            retornonumero = scanf("%d",&info->resid.num);
            do
            {
                c = getchar();
            }
            while(c != '\n');
        }
        while(retornonumero == 0);
        printf("\n Insira o Nome do Bairro %c ",175);
        fgets(info->resid.bairro,49,stdin);
        fflush(stdin);
        printf("\n Insira o Nome da Cidade %c ",175);
        fgets(info->resid.cidade,49,stdin);
        fflush(stdin);
        printf("\n Insira o Nome do Estado \n Somento o UF Exemplo [ SP, PR ,RJ ]. %c ",175);
        scanf("%c%c",&info->resid.U,&info->resid.F);
        fflush(stdin);
        do
        {
            printf("\n Insira o CEP somento numero sem tra%co %c ",135,175);
            retornocep = scanf("%"SCNu64,&info->resid.cep);
            do
            {
                c = getchar();
            }
            while(c != '\n');
        }
        while(retornocep == 0);
        arqv = fopen("GrupoDeRisco.txt","a");
        if(info->idade >=65 || info->comorbidade == 's')
        {
            fprintf(arqv,"\nCEP  %"PRIu64"\t",info->resid.cep);
            fprintf(arqv,"\tIdade %d \n",info->idade);
        }
        fclose(arqv);
        Lista(info, &primeiro,&ultimo);
        printf("\nContinuar ? [S]im [N]ao .%c\n",175);
        opc = getchar();
        fflush(stdin);
        system("cls");
    }
    while(opc != 'n');
}

void SalvarEmBinario()
{
    struct no *info;
    FILE *arquivo;
    arquivo = fopen("ListaPacientes","ab");
    if(!arquivo)
    {
        printf("\nErro ao abrir arquivo !\n");
        exit(1);
    }
    printf("\nSalvo com sucesso \n");
    info = primeiro;
    while(info)
    {
        fwrite(info,sizeof(struct no),1,arquivo);
        info = info->proximo;
    }
    fclose(arquivo);
}

void Lista(struct no *novo,struct no **primeiro, struct no **ultimo)
{
    struct no *aux, *aux2;
    if (*ultimo == NULL)
    {
        novo ->proximo =NULL;
        novo ->anterior =NULL;
        *ultimo = novo;
        *primeiro = novo;
        return;
    }
    aux2 = *primeiro;
    aux = NULL;
    while(aux2)
    {
        if(strcmp(aux2->nome,novo->nome)<0)
        {
            aux = aux2;
            aux2 = aux2->proximo;
        }
        else
        {
            if(aux2->anterior)
            {
                aux2->anterior->proximo = novo;
                novo->proximo = aux2;
                novo->anterior = aux2->anterior;
                aux2->anterior = novo;
                return;
            }
            novo->proximo = aux2;
            novo->anterior = NULL;
            aux2->anterior = novo;
            *primeiro = novo;
            return;
        }
    }
    aux->proximo = novo;
    novo->proximo = NULL;
    novo->anterior = aux;
    *ultimo = novo;
}

int CalcularIdade(int DIA,int MES,int ANO)
{
    int Idade;
    struct tm tempo;
    time_t tempoSeg;
    time(&tempoSeg);
    tempo = *localtime(&tempoSeg);
    struct data agora;
    agora.dia = tempo.tm_mday;
    agora.mes = tempo.tm_mon + 1;
    agora.ano = tempo.tm_year + 1900;
    Idade = agora.ano - ANO;
    if ((agora.mes < MES)||((agora.mes== MES)&&(agora.dia < DIA)))
        Idade = Idade - 1;
    return (Idade);
}

struct no *BuscaParaRemover(int64_t *cpf)
{
    struct no *info;
    info = primeiro;
    while(info)
    {
        if(cpf == info->CPF){
            return info;break;}
        info = info->proximo;
    }
    printf("\nNao encontrado !");
    return NULL;
}

struct no *BuscaValidar(int64_t *cpf)
{
    struct no *info;
    info = primeiro;
    while(info)
    {
        if(cpf == info->CPF)
            return 1;
        info = info->proximo;
    }
    return NULL;
}

int remover(struct no **primeiro,struct no **ultimo)
{
    FILE *arquivo;
    struct no *info, *BuscaParaRemover();
    int64_t cpf;
    printf("Entre com  o CPF : ");
    scanf("%"SCNu64,&cpf);
    fflush(stdin);
    info = BuscaParaRemover(cpf);
    if(info)
    {
        *primeiro = info->proximo;
        if(*primeiro) (*primeiro)->anterior =NULL;
        else *ultimo = NULL;
    }
    else
    {
        info->anterior->proximo = info->proximo;
        if(info != *ultimo)
            info->proximo->anterior = info->anterior;
        else
            *ultimo = info->anterior;
    }
    free(info);
    arquivo = fopen("ListaPacientes","wb");
    if(!arquivo)
    {
        printf("\nErro ao abrir arquivo !\n");
        exit(1);
    }

    fclose(arquivo);
    printf("\nRemovido com sucesso! \n");
}

struct no *MostraUmPaciente(int64_t *cpf)
{
    struct no *info;
    info = primeiro;
    while(info)
    {
        if(cpf == info->CPF){
            system("cls");
           printf("=======================================\n");
        printf("\nCPF %c %"PRIu64"\n",175,info->CPF);
        printf("\nNome %c %s\n",175,info->nome);
        printf("\nEmail %c %s\n",175,info->email);
        printf("\nIdade %c %d\n",175,info->idade);
        printf("\nComorbidade %c %c\n",175,info->comorbidade);
        printf("\nData Nascimento %c %02d/%02d/%04d\n",175,info->nasc.dia,info->nasc.mes,info->nasc.ano);
        printf("\nData do diagnostico %c %02d/%02d/%04d\n",175,info->diag.dia,info->diag.mes,info->diag.ano);
        printf("\n_______________ ENDERECO ______________\n");
        printf("\nRua %c %s N%c%d",175,info->resid.rua,248,info->resid.num);
        printf("\nBairro %c %s\n",175,info->resid.bairro);
        printf("\nCidade %c %s\n",175,info->resid.cidade);
        printf("\nEstado [UF] %c %c%c\n",175,info->resid.U,info->resid.F);
        printf("\nCEP %c %"PRIu64"\n",175,info->resid.cep);
        printf("=======================================\n");
            break;}
            info=info->proximo;
    }
    printf("\nNao encontrado\n");
    return NULL;
}
