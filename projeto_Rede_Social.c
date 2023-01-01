#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define Dim1 100
#define Dim2 50
#define NULL ((void *)0)

typedef struct //Estrutura-DATA
  {
    int dia;
    int mes;
    int ano;
  }DATA; //Sinónimo

typedef struct pessoa //Perfil do utilizador
  {
    char Nome[Dim1];
    int idade;
    float salario;
    DATA dt_nasc; //Estrutura
    char local_trb[Dim1];   //Local de trabalho
    char local_nasc[Dim1]; //Local de nascimento
    int formacao;  //Formação académica
    int escol; //Nível de escolaridade
    char id[Dim1]; //Identificador
  }PESSOA;

void Ler(PESSOA vetor[],int i) //Registar utilizador
{
    printf("Insira o nome: "); fgets(vetor[i].Nome,Dim1,stdin);
    printf("Crie um identificador pessoal: "); fgets(vetor[i].id,Dim1,stdin);
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

void Mostrar(PESSOA vetor[],int i) //Mostrar perfil do utilizador
{
    printf("Nome: %s",vetor[i].Nome);
    printf("Idade: %d anos\n",vetor[i].idade);
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
    vetor[i].id[0]= '\0';

    vetor[i].idade= 0;
    vetor[i].salario= 0;
    vetor[i].dt_nasc.dia= 0;
    vetor[i].dt_nasc.mes= 0;
    vetor[i].dt_nasc.ano= 0;
    vetor[i].formacao= 0;
    vetor[i].escol= 0;
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

int main(int argc,char **argv) //MENU PRINCIPAL
{
    PESSOA vetor[Dim1];  //Vetor de perfis
    int i;  //Contador
    int n=0; //Nº de utilizadores
    char resp1; //1ª resposta
    char Perfil[Dim2]; //String auxiliar
    char Perfil2[Dim2]; //String auxiliar
    char Password[Dim1]; //Palavra passe
    int chg; //Alterar(CHanGe) dados do utilizador
    char opcao;
    FILE *fp; //File pointer

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
        printf("Total de utilizadores: %d\n",n);
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
              printf("Identificador: "); fgets(Password,Dim1,stdin);
              putchar('\n'); //Mudança de linha
              for(i=0; i<n; i++)
                {
                  if(strcmp(Perfil2,vetor[i].Nome)==0 && strcmp(Password,vetor[i].id)==0)
                    {
                      Mostrar(vetor,i);
                      Perfil2[0]= '\0'; //Limpeza das strings
                      Password[0]= '\0';
                    }
                  else
                    continue;
                }
            printf("\nPrima 2x \"Enter\" para retornar ao menu principal!\n");
            while(getchar()!='\n'); //Limpar buffer do teclado
            system("cls");
            break;

            case 'r':
            case 'R':
              puts("Opcao REGISTAR");
              putchar('\n'); //Mudança de linha
              Ler(vetor,n);
              n++; //Incrementação do contador
              system("cls"); //Clean screen
              break;

            case 'a':
            case 'A':
              puts("Opcao Alterar");
              printf("\nInsira o seu nome: "); fgets(Perfil2,Dim2,stdin);
              printf("Identificador: "); fgets(Password,Dim1,stdin);
              toupper(Perfil2[0]); //1ºcaractere é maiúsculo
              for(i=0; i<n; i++)
                {
                  if((strcmp(Perfil2,vetor[i].Nome)==0) && (strcmp(Password,vetor[i].id)==0))
                    {
                      Editar(); //Painel de Edição
                      printf("\nO que pretende alterar?\n");
                      printf("R: "); scanf("%d",&chg);
                      Alterar(vetor,i,chg); //Invocação da função "Alterar"
                      Perfil2[0]= '\0'; //Limpeza das strings
                      Password[0]= '\0';
                    }
                  else
                    continue;
                }
            printf("\nPrima 2x \"Enter\" para retornar ao menu principal!\n");
            while(getchar()!='\n'); //Limpar buffer do teclado
            system("cls");
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
                }
              printf("\nPrima 2x \"Enter\" para retornar ao menu principal!\n");
              while(getchar()!='\n'); //Limpar buffer do teclado
              system("cls"); //Clean screen
              break;

            case 'd':
            case 'D':
              puts("Opcao DEMITIR"); //REmover utilizador
              putchar('\n'); //Mudança de linha
              printf("ID do utilizador: "); fgets(Password,Dim2,stdin); //Obtenção do nome(do utilizador a remover)
              for(i=0; i<n; i++)
                {
                  if(strcmp(Password,vetor[i].id)==0)
                    {
                      Remover_Utilizador(vetor,i);
                      puts("Utilizador removido com sucesso!");
                      Password[0]='\0'; //Limpeza da string
                    }
                  else
                    continue;
                }
              printf("\nPrima 2x \"Enter\" para retornar ao menu principal!\n");
              while(getchar()!='\n'); //Limpar buffer do teclado
              system("cls"); //Clean screen
              break;

            case 's':
            case 'S':
              printf("Total de utilizadores: %d\n",n);
              fp= fopen("profiles.bd","w"); //Abertura do ficheiro para ESCRITA
              fwrite(&n,sizeof(int),1,fp);
              fwrite(vetor,sizeof(vetor),1,fp);
              fclose(fp); //Fechamento do arquivo
              printf("\nPrima 2x \"Enter\" para terminar!\n");
              break; //Não faz nada
            default: puts("Opcao INVALIDA!!"); break;
          }
        getchar(); //Parar a tela
         }
     while(opcao!= 's' && opcao !='S');
    return 0;
}
