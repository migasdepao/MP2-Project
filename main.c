#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define Dim1 100
#define Dim2 50
#define MAX 500
#define SMAX 50
#define NULL ((void *)0)
char *interesses[MAX];  //Array de strings
char *interesse[SMAX]; //Array de pointers para caracteres(strings)
int tot_areas;  //Nº total de áreas de interesse

typedef struct //Estrutura-DATA
  {
    int dia;
    int mes;
    int ano;
  }DATA; //Sinónimo

typedef struct Amigo
{
    int id; //Identificador do amigo
    int data;
    struct Amigo *seguinte; //Apontador para o amigo seguinte
}amigo;

typedef struct pessoa //Perfil do utilizador
  {
    char Nome[Dim1];
    int idade;
    int friends; //Nº total de amigos do utilizador
    float salario;
    DATA dt_nasc; //Estrutura
    char local_trb[Dim1];   //Local de trabalho
    char local_nasc[Dim1]; //Local de nascimento
    int formacao;  //Formação académica
    int escol; //Nível de escolaridade
    int identificador; //Identificador
    char area_interesse[Dim1]; //Área de interesse
    amigo *queue; //Apontador para lista de amigos
  }PESSOA;

void EscreverFicheiro(amigo *cabeca)
{
    amigo *atual= NULL;
    FILE *fp= fopen("friends.txt","w"); //Abertura do ficheiro "friends" para ESCRITA
    if(fp==NULL)
      {
        printf("ERRO na abertura do ficheiro!\n"); //Menssagem de erro
      }
    else
      {
        atual= cabeca; //Passagem de endereços
        while(atual != NULL)
          {
            fwrite(&atual->id,sizeof(int),1,fp);
            fwrite(&atual->data,sizeof(int),1,fp);
            atual= atual->seguinte; //Passagem para o amigo seguinte
          }
      }
    fclose(fp); //Fechamento do ficheiro
}

amigo *novoElemento(int id, int data)
{
    amigo *temporario= malloc(sizeof(amigo)); //Reservar um bloco de memória para o apontador
    temporario->id= id;
    temporario->data= data;
    temporario->seguinte= NULL;
    return temporario; //Retorna o apontador para struct "amigo"
}

amigo *inserirElemento(amigo *cabeca, int id, int data) //Inserção do novo amigo, na lista de amigos do utilizador
{
    amigo *novo= novoElemento(id,data);
    amigo *atual= NULL;
    if(cabeca==NULL) //Lista VAZIA
      cabeca= novo;
    else
      {
        atual= cabeca;
        while(atual->seguinte !=NULL) //Enquanto existirem amigos na lista do utilizador
          {
            atual= atual->seguinte;
          }
        atual->seguinte= novo; //Inserção do utilizador
      }
    return cabeca; //Retorna a cabeça da lista
}

amigo *LerFicheiro(amigo *cabeca)
{
    int id= 0; int data= 0;
    FILE *fp= fopen("friends.txt","r"); //Abertura do ficheiro "friends" para LEITURA
    if(fp==NULL) //Não foi possível adquirir o endereço de memória do ficheiro
      {
        printf("ERRO na abertura do ficheiro!\n"); //Menssagem de erro
      }
    else
      {
        while(fread(&id,sizeof(int),1,fp)==1) //Enquanto o nº de identificadores lidos for igual a 1
          {
            fread(&data,sizeof(int),1,fp);
            cabeca= inserirElemento(cabeca,id,data);
          }
      }
    return cabeca; //Retorno da cabeça da lista de amigos
}

amigo *removerAmigo(amigo *cabeca, int id) //Remover amigos do utilizador
{
    amigo *atual= NULL;
    amigo *anterior= NULL;
    if(cabeca==NULL) //Caso a lista esteja vazia
      printf("ERRO: Lista sem conteudo.\n");
    else
      {
        atual= cabeca;
        while(atual->id != id)
          {
            if(atual->id== NULL)
              {
                printf("ERRO: Elemento inexistente\n");
                return cabeca; //Retorno da cabeca da lista
              }
            else
              {
                anterior= atual;
                atual= atual->seguinte;
              }
          }
        if(atual==cabeca)
          cabeca= cabeca->seguinte; //1 2 3 4 5 6 7
        else
          anterior->seguinte = atual->seguinte;
      }
    return cabeca; //Retorna a cabeça da lista
}

void alterarElemento(amigo *cabeca, int id)
{
    amigo *atual= NULL;
    if(cabeca==NULL)
      {
        printf("ERRO: Lista sem conteudo.\n");
      }
    else
      {
        atual= cabeca;
        while(atual->id != id)
          {
            if(atual->seguinte == NULL)
              printf("ERRO: Elemento inexistente\n");
            else
              {
                atual= atual->seguinte;
              }
          }
        atual->data= atual->data*10;
      }
}

void visualizarAmigos(amigo *cabeca)
{
    amigo *atual= NULL;

    if(cabeca==NULL) //Lista vazia
      printf("ERRO: Lista sem conteudo.\n");
    else
      {
        atual= cabeca;
        while(atual != NULL) //Até a lista chegar ao fim
          {
            printf("ID: %d\n",atual->id); //Impressão do ID
            printf("No de amigos: %d\n",atual->data); //Impressão da data
            atual= atual->seguinte; //Avança para o próximo amigo
          }
      }
}

void Editar()
{
    puts("\t\t\t*-----------*---------*");
    puts("\t\t\t|  1.NOME   | 2.IDADE |");
    puts("\t\t\t*-----------*---------*------------*");
    puts("\t\t\t| 3.SALARIO | 4.DATA DE NASCIMENTO |");
    puts("\t\t\t*-----------*----------*-----------*-------------*");
    puts("\t\t\t| 5.LOCAL DE TRABALHO  |  6.LOCAL DE NASCIMENTO  |");
    puts("\t\t\t*----------------------*-------------------------*");
    puts("\t\t\t| 7.FORMACAO ACADEMICA | 8.NIVEL DE ESCOLARIDADE |");
    puts("\t\t\t*----------------------*-------------------------*");
}

void Painel_Menu_Principal()
{
    puts("\t*------------------------------------*");
    puts("\t|**** M E N U  P R I N C I P A L ****|");
    puts("\t*------------------------------------*");

    puts("\t\t*--------------*");
    puts("\t\t| (E) ENTRAR   |");
    puts("\t\t*--------------*");
    puts("\t\t| (R) REGISTAR |");
    puts("\t\t*--------------*");
    puts("\t\t| (A) ALTERAR  |");
    puts("\t\t*--------------*");
    puts("\t\t| (L) LISTAR   |");
    puts("\t\t*--------------*");
    puts("\t\t| (D) DEMITIR  |"); //Demitir = ELiminar utilizador
    puts("\t\t*--------------*");
    puts("\t\t| (F) AMIZADES |");
    puts("\t\t*--------------*");
    puts("\t\t| (S) SAIR     |");
    puts("\t\t*--------------*");
}

void Painel_Graduacao()
{
    puts("\t\t*---------------*-----------------*");
	puts("\t\t|  1.MESTRADO   | 2.POS-GRADUACAO |");
	puts("\t\t*---------------*-----------------*");
	puts("\t\t|  3.GRADUACAO  |  4.LICENCIATURA |");
	puts("\t\t*---------------*-----------------*");
	puts("\t\t| 5.BACHARELADO |   6.DOUTURADO   |");
	puts("\t\t*---------------*-----------------*");
	puts("\t\t|  7.NAO POSSUI FORMACAO SUPERIOR |");
	puts("\t\t*---------------------------------*");
	putchar('\n'); //Mudança de linha
}

void Painel_escolaridade()
{
    puts("\t\t\t\t*---------*---------*---------*--------------*");
	puts("\t\t\t\t| 1.CICLO | 2.CICLO | 3.CICLO | 4.SECUNDARIO |");
	puts("\t\t\t\t*---------*---------*---------*--------------*");
	puts("\t\t\t\t          | 5.ENSINO SUPERIOR |");
	puts("\t\t\t\t          *----------*--------*");
}
void Painel_amizades()
{
    puts("\t\t\t\t*--------------*-----------------*---------------------*");
	puts("\t\t\t\t| 1.NOVO AMIGO | 2.REMOVER AMIGO | 3.VIZUALIZAR AMIGOS |");
	puts("\t\t\t\t*--------------*-----------------*---------------------*");
}

void Ler(PESSOA vetor[],int i) //Registar utilizador
{
    printf("Insira o nome: "); fgets(vetor[i].Nome,Dim1,stdin);
    printf("Crie um identificador pessoal: "); scanf("%d",&vetor[i].identificador);
    printf("Insira a idade: "); scanf("%d",&(vetor[i]).idade);
    printf("Insira o salario: "); scanf("%f",&(vetor[i]).salario);
    printf("Data de nascimento (dd mm aaaa): "); scanf("%d %d %d",&(vetor[i]).dt_nasc.dia,&(vetor[i]).dt_nasc.mes,&(vetor[i]).dt_nasc.ano);
    while(getchar()!='\n'); //Limpar buffer do teclado
    printf("Local de trabalho: "); fgets(vetor[i].local_trb,Dim1,stdin);
    printf("Local de nascimento: "); fgets(vetor[i].local_nasc,Dim1,stdin);
    putchar('\n'); //Mudança de linha

    putchar('\n'); //Mudança de linha
    Painel_Graduacao(); //Invocação da função
    printf("Qual a sua formacao academica?: "); scanf("%d",&(vetor[i]).formacao);

    putchar('\n'); //Mudança de linha
    Painel_escolaridade(); //Invocação da função
    printf("Nivel de escolaridade?: "); scanf("%d",&(vetor[i]).escol);
}

char *areas(PESSOA vetor[],int k) //Áreas de interesse do utilizador
{
    int teste=1;
    int i; //Contador (do ciclo FOR)
    int length; //Comprimento da string
    char resp; //Resposta do utilizador
    FILE *fp; //File pointer

    fp= fopen("areas.txt","r"); //Abertura de o ficheiro para LEITURA
    if(fp==NULL) //Verificar a abertura do ficheiro de texto
      {
        printf("Impossivel abrir o ficheiro \"areas.txt\"!\n");
        exit(1); //Termina o programa
      }
    else
      {
        fscanf(fp,"%d\n",&tot_areas); //Obtenção do nº de áreas de interesse
      }
    for(i=0; i<tot_areas; i++)
      {
        fgets(interesse,SMAX,fp); //Obtenção das strings presentes no ficheiro
        interesses[i]= strdup(interesse); //Passagem das strings do array "interesse" para "interesses"
      }
    printf("%d Areas de interesse:\n",tot_areas); //Casting do nº de áreas de interesse
    for(i=0; interesses[i]!=NULL; i++)
      {
        printf("%s",interesses[i]); //Impressão das strings
      }
    printf("\nInsira a sua area de interesse:\n");
    while(getchar()!='\n'); //Limpeza do buffer do teclado
    fgets(vetor[k].area_interesse,Dim1,stdin);  //Obtenção da área de interesse do utilizador
    length= strlen(vetor[k].area_interesse)-1; //-1 devido ao "\0" (caractere delimitador da string)
    for(i=0 ; interesses[i]!=NULL; i++)
      {
        if(strncmp(vetor[k].area_interesse,interesses[i],length)==0)
          {
            printf("Area de interesse registada com sucesso!");
            fclose(fp); //Fechamento do ficheiro
            return (vetor[k].area_interesse); //Retorno da string
          }
        else
          teste++;
      }
    if(teste>tot_areas)
      {
        printf("A area registada nao se identifica com as areas impressas!\nPretende adiciona-la ao conjunto? S/N\n");
        scanf(" %c",&resp); //Leitura da resposta do utilizador
        switch(resp)
          {
            case 's':
            case 'S':
              interesses[i]= strdup(vetor[k].area_interesse); //Copia a área do utilizado para o vetor(global) de áreas de interesse
              tot_areas++;
              fp= fopen("areas.txt","w"); //Abertura de o ficheiro para ESCRITA
              fprintf(fp,"%d\n",tot_areas);
              for(i=0; interesses[i]!=NULL; i++)
                {
                  fprintf(fp,"%s",interesses[i]); //Impressão das strings
                }
              fclose(fp); //Fechamento do ficheiro
              return (vetor[k].area_interesse); //Retorno da string
            case 'n':
            case 'N':
              fclose(fp); //Fechamento do ficheiro;
              return (vetor[k].area_interesse); //Retorno da string
            default:
              printf("Caractere inserido INVALIDO!\n");
              fclose(fp); //Fechamento do ficheiro
          }
      }
}

void Alterar(PESSOA vetor[],int i,int chg) //Alterar dados relativos ao perfil
{
    switch(chg)
      {
        case 1:
          printf("Insira o seu nome: ");
          while(getchar()!='\n');
          fgets((vetor[i]).Nome,Dim1,stdin);
          break;
        case 2:
          printf("Insira a idade: ");
          scanf("%d",&(vetor[i]).idade);
          break;
        case 3:
          printf("Insira o salario: ");
          scanf("%f",&(vetor[i]).salario);
          break;
        case 4:
          printf("Data de nascimento: ");
          scanf("%d %d %d",&(vetor[i]).dt_nasc.dia,&(vetor[i]).dt_nasc.mes,&(vetor[i]).dt_nasc.ano);
          break;
        case 5:
          printf("Local de trabalho: ");
          while(getchar()!='\n');
          fgets((vetor[i]).local_trb,Dim1,stdin);
          break;
        case 6:
          printf("Local de nascimento: ");
          while(getchar()!='\n');
          fgets((vetor[i]).local_nasc,Dim1,stdin);
          break;
        case 7:
          Painel_Graduacao();
          printf("R: ");
          scanf("%d",&(vetor[i]).formacao);
          break;
       case 8:
          Painel_escolaridade();
          printf("R: ");
          scanf("%d",&(vetor[i]).escol);
          break;
    default: printf("Numero inserido invalido!");
    }
}

void Remover_Utilizador(PESSOA vetor[],int i) //Remover utilizador
{
    vetor[i].Nome[0]= '\0'; //LIMPEZA das strings
    vetor[i].local_nasc[0]='\0';
    vetor[i].local_trb[0]= '\0';
    vetor[i].identificador= 0;

    vetor[i].idade= 0;
    vetor[i].salario= 0;
    vetor[i].dt_nasc.dia= 0;
    vetor[i].dt_nasc.mes= 0;
    vetor[i].dt_nasc.ano= 0;
    vetor[i].formacao= 0;
    vetor[i].escol= 0;
}

void Mostrar(PESSOA vetor[],int i) //Mostrar perfil do utilizador
{
    printf("Nome: %s",vetor[i].Nome);
    printf("Idade: %d anos\n",vetor[i].idade);
    printf("No de amigos: %d\n",vetor[i].friends);
    printf("Area de interesse: %s",vetor[i].area_interesse);
    printf("Salario: %.2f\n",vetor[i].salario);
    printf("Data de nascimento: %d/%d/%d\n",vetor[i].dt_nasc.dia,vetor[i].dt_nasc.mes,vetor[i].dt_nasc.ano);
    printf("Local de trabalho: %s",vetor[i].local_trb);
    printf("Local de nascimento: %s",vetor[i].local_nasc);
    switch(vetor[i].formacao)
      {
        case 1: printf("Formacao Academica: Mestrado\n"); break;
        case 2: printf("Formacao Academica: Pos-Graduacao\n"); break;
        case 3: printf("Formacao Academica: Graduacao\n"); break;
        case 4: printf("Formacao Academica: Licenciatura\n"); break;
        case 5: printf("Formacao Academica: Bacharelado\n"); break;
        case 6: printf("Formacao Academica: Douturado\n"); break;
        case 7: printf("Formacao Academica: NAO\n"); break;
        default: printf("Numero inserido invalido"); break;
      }
    switch(vetor[i].escol)
      {
        case 1: printf("Nivel de Escolaridade: 1oCiclo\n"); break;
        case 2: printf("Nivel de Escolaridade: 2oCiclo\n"); break;
        case 3: printf("Nivel de Escolaridade: 3oCiclo\n"); break;
        case 4: printf("Nivel de Escolaridade: 4.Secundario\n"); break;
        case 5: printf("Nivel de Escolaridade: Ensino Superior\n"); break;
        default: printf("Numero inserido invalido\n"); break;
      }
}

int main(int argc,char **argv) //MENU PRINCIPAL
{
    PESSOA vetor[Dim1];  //Vetor de perfis
    int i; //Contador do ciclo "for"
    int n=0; //Nº de utilizadores
    char resp; //Resposta do utilizador
    char Perfil2[Dim2]; //String auxiliar
    int ID_aux; //Identificador auxiliar
    int chg; //Alterar(CHanGe) dados do utilizador
    int frop; //Opcao do painel das amizades (friend option)
    int frid; //Id dos dos amigos (friend ID)
    char opcao; //Opção do utilizador
    FILE *fp= NULL; //File pointer
    amigo *cabeca= NULL;

    cabeca= LerFicheiro(cabeca); //Ler lista das amizades(presente num ficheiro)
    fp= fopen("profiles.bd","r"); //Abertura do ficheiro para LEITURA
    if(fp==NULL)
      {
        printf("Impossivel abrir o arquivo \"profiles.bd\"\n");
        exit(1); //Termina o programa
      }
    else
      {
        fread(&n,sizeof(int),1,fp);
        fread(vetor,sizeof(vetor),1,fp);
        printf("*Total de utilizadores: %d\n\n",n);
      }
    fclose(fp); //Fechamento do ficheiro

    do
      {
        Painel_Menu_Principal(); //Invocação da função
        printf("\n\nOpcao: ");
        scanf(" %c",&opcao);
        fflush(stdin); //Limpar buffer do teclado
        switch(opcao)
          {
            case 'e':
            case 'E':
              puts("Opcao ENTRAR");
              putchar('\n');
              printf("Nome: "); fgets(Perfil2,Dim2,stdin); toupper(Perfil2[0]);
              printf("Identificador: "); scanf("%d",&ID_aux);
              putchar('\n');
              for(i=0; i<n; i++)
                {
                  if(strcmp(Perfil2,vetor[i].Nome)==0 && vetor[i].identificador== ID_aux)
                    {
                      Mostrar(vetor,i);
                      Perfil2[0]= '\0'; //Limpeza da string
                      ID_aux= 0; //Limpeza do inteiro
                    }
                }
              fflush(stdin); //Limpeza do buffer
              printf("\nPrima \"R\" para retornar ao menu principal\nR: ");
              scanf("%c",&resp);
              switch(resp)
                {
                  case 'r':
                  case 'R': system("cls"); break;
                  default:  printf("ERRO: Caractere inserido INVALIDO!");
                }
              break;

            case 'r':
            case 'R':
              puts("Opcao REGISTAR");
              putchar('\n');  //Mudança de linha
              Ler(vetor,n);  //Ler utilizador
              putchar('\n');//Mudança de linha
              areas(vetor,n); //Ler área de interesse do utilizador
              n++; //Incrementação do contador
              fflush(stdin); //Limpeza do buffer
              printf("\nPrima \"R\" para retornar ao menu principal\nR: ");
              scanf("%c",&resp);
              switch(resp)
                {
                  case 'r':
                  case 'R': system("cls"); break;
                  default:  printf("ERRO: Caractere inserido INVALIDO!");
                }
              break;

            case 'a':
            case 'A':
              puts("Opcao Alterar");
              printf("\nInsira o seu nome: "); fgets(Perfil2,Dim2,stdin);
              printf("Identificador: "); scanf("%d",&ID_aux);
              toupper(Perfil2[0]); //1ºcaractere é maiúsculo
              for(i=0; i<n; i++)
                {
                  if((strcmp(Perfil2,vetor[i].Nome)==0) && (vetor[i].identificador)== ID_aux)
                    {
                      Editar(); //Painel de Edição
                      printf("\nO que pretende alterar?\nR: ");
                      scanf("%d",&chg);
                      Alterar(vetor,i,chg); //Invocação da função "Alterar"
                      Perfil2[0]= '\0'; //Limpeza das strings
                      ID_aux= 0; //Limpeza do identificador auxiliar
                    }
                  else
                    continue;
                }
              fflush(stdin); //Limpeza do buffer
              printf("\nPrima \"R\" para retornar ao menu principal\nR: ");
              scanf("%c",&resp);
              switch(resp)
                {
                  case 'r':
                  case 'R': system("cls"); break;
                  default:  printf("ERRO: Caractere inserido INVALIDO!");
                }
              break;

            case 'l':
            case 'L':
              puts("Opcao LISTAR");
              putchar('\n'); //Mudança de linha
              for(i=0; i<n; i++)
                {
                  if((vetor[i].Nome[0])!='\0')
                    {
                      Mostrar(vetor,i);
                      putchar('\n'); //Mudança de linha
                    }
                  else
                    continue;
                }
               fflush(stdin); //Limpeza do buffer
               printf("Prima \"R\" para retornar ao menu principal\nR: ");
               scanf("%c",&resp);
               switch(resp)
                {
                  case 'r':
                  case 'R': system("cls"); break;
                  default:  printf("ERRO: Caractere inserido INVALIDO!");
                }
              break;

            case 'd':
            case 'D':
              puts("Opcao DEMITIR"); //REmover utilizador
              putchar('\n'); //Mudança de linha
              printf("ID do utilizador: "); scanf("%d",&ID_aux); //Obtenção do identificador(do utilizador a remover)
              for(i=0; i<n; i++)
                {
                  if((vetor[i].identificador)== ID_aux)
                    {
                      Remover_Utilizador(vetor,i);
                      puts("Utilizador removido com sucesso!");
                      ID_aux=0; //Limpeza do ID auxiliar
                    }
                  else
                    continue;
                }
              fflush(stdin); //Limpeza o buffer
              printf("\nPrima \"R\" para retornar ao menu principal\nR: ");
              scanf("%c",&resp);
              switch(resp)
                {
                  case 'r':
                  case 'R': system("cls"); break;
                  default:  printf("ERRO: Caractere inserido INVALIDO!");
                }
              break;

            case 'f':
            case 'F':
              puts("Opcao AMIZADES");
              printf("\nNome: "); fgets(Perfil2,Dim2,stdin);
              printf("ID :"); scanf("%d",&ID_aux);
              for(i=0; i<n; i++)
                {
                  if(strcmp(vetor[i].Nome,Perfil2)==0 && vetor[i].identificador== ID_aux)
                    {
                      Painel_amizades();
                      printf("Insira a opcao:\nR: ");
                      scanf("%d",&frop);
                      switch(frop)
                        {
                          case 1: //Adicionar Amigo
                            Perfil2[0]= '\0'; //Limpeza da string
                            fflush(stdin); //Limpeza do buffer
                            printf("Quem pretende adicionar como amigo?\nR: "); fgets(Perfil2,Dim2,stdin);
                            for(i=0; i<n; i++)
                              {
                                if(strcmp(vetor[i].Nome,Perfil2)==0)
                                  {
                                    vetor[i].friends++; //Incrementação do nº de amigos
                                    cabeca= inserirElemento(cabeca,vetor[i].identificador,vetor[i].friends);
                                    puts("Amigo adicionado com sucesso!");
                                  }
                              }
                            Perfil2[0]= '\0'; //Limpeza da string
                            break;
                          case 2: //Remover amigo
                            printf("ID: ");
                            scanf("%d",&frid); //Obtenção do ID do amigo a remover
                            cabeca= removerAmigo(cabeca,frid); //Remoção do amigo
                            break;
                          case 3: //Visualizar lista de amigos
                            visualizarAmigos(cabeca);
                            break;
                          default:
                            printf("ERRO: Numero inserido INVALIDO");
                            break;
                        }
                    }
                }
              fflush(stdin); //Limpar buffer
              printf("\nPrima \"R\" para retornar ao menu principal\nR: ");
              scanf("%c",&resp);
              switch(resp)
                {
                  case 'r':
                  case 'R': system("cls"); break;
                  default:  printf("ERRO: Caractere inserido INVALIDO!");
                }
              break;

            case 's':
            case 'S':
              printf("Total de utilizadores: %d\n",n);
              fp= fopen("profiles.bd","w"); //Abertura do ficheiro para ESCRITA
              fwrite(&n,sizeof(int),1,fp);
              fwrite(vetor,sizeof(vetor),1,fp);
              fclose(fp); //Fechamento do arquivo
              EscreverFicheiro(cabeca); //Escrever lista de amigos do utilizador no ficheiro "friends.txt"

              printf("\nAte amanha, obrigado!\n");
              break; //Não faz nada
            default: puts("Opcao INVALIDA!!"); break;
          }
        getchar(); //Parar a tela
         }
     while(opcao!= 's' && opcao !='S');
    return 0;
}


