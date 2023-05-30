#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <gtk/gtk.h>
#include "manipulador_texto.h"
#define NORMAL 0
#define ERRO 1

//Criar solucao para quando nao houver a pasta cadastro e pasta raiz!

/*
Dados da estrutura do cadasto

int codigo; - código identificador do cadastro, gerado automaticamente
    int idade;
    int telefone;
    char nome[20];
    int cpf;
*/

/*
Modelo de um cadastro:
//----------------------------------------------------------
Codigo:
Idade:
Telefone:
Nome:
CPF:
//----------------------------------------------------------
*/

/*
Dados da estrutura raiz:

//----------------------------------------------------------
Numero de Cadastros registrados: 00
//----------------------------------------------------------

*/

char Encapsulador_Arquivo();
char Desencapsulador_Arquivo();
int criar_numero_cadastro();

//Cria cadastros de acordo com a estrutura do cabeçalho, com o usuário inserindo os dados.
void criar_cadastro()
{
    dados *cadastro = NULL;
    cadastro = malloc(sizeof(dados));


    strcpy(cadastro->nome, "\0");

    DIR *diretorio;

    FILE *arquivo = NULL;

    char identificador[30] = "raiz";

    char caminho[30] = "./Cadastros/";

    char caminho2[30] = "./Cadastros/";

    int status = NORMAL;

    int c = 0;

    strcat(caminho, identificador);

    printf("%s\n", caminho);

    //abre o diretorio aonde ficarao alocados os registros
    if((diretorio = opendir("./Cadastros"))==NULL)
    {
        printf("Erro! Nao foi possivel abrir a pasta dos cadastros!\n");
        return;
    }

    printf("Insira os dados do novo cadastro!\n");
    printf("Nome: ");
    fgets(cadastro->nome, 30, stdin);
    fflush(stdin);

    printf("Idade: ");
    scanf("%i", &cadastro->idade);
    fflush(stdin);

    printf("Telefone: ");
    scanf("%i", &cadastro->telefone);
    fflush(stdin);

    printf("CPF: ");
    scanf("%i", &cadastro->cpf);
    fflush(stdin);

    //------------------------------------------------------------
    //Checa se os valores inseridos sao validos e os imprime
    printf("----------------------------------------------------------\n");
    printf("Cadastro Inserido: \n");

    //Verifica se o nome possui apenas numeros
    if((strcmp(cadastro->nome, "\0")!=0)&&(strcmp(cadastro->nome, "@")>0))
    {
        printf("\nNome: %s", cadastro->nome);
    }else
        {
            printf("\nErro! Nome Invalido!\n");
            status = ERRO;
        }

    //Verifica se foi inserido um numero valido
    if(cadastro->idade!=0)
    {
        printf("Idade: %i\n", cadastro->idade);
    }else
        {
            printf("Erro! Idade Invalida!\n");
            status = ERRO;
        }

    //Verifica se foi inserido um numero valido
    if(cadastro->telefone!=0)
    {
        printf("Telefone: %i\n", cadastro->telefone);
    }else
        {
            printf("Erro! Telefone Invalido!\n");
            status = ERRO;
        }

    //Verifica se foi inserido um numero valido
    if(cadastro->cpf!=0)
    {
        printf("CPF: %i\n", cadastro->cpf);
    }else
        {
            printf("Erro! CPF Invalido!\n");
            status = ERRO;
        }

    printf("----------------------------------------------------------\n");
    //------------------------------------------------------------

    if(status==0)
    {
        printf("inserindo...\n");

        //Aqui fica a função que vai definir a numeração do cadastro.
        //O arquivo raiz contem todas as informações sobre os cadastros gerados,
        //permitindo a sua organização.
        //------------------------------------------------------------
        //Cncapsula o arquivo como .cadastro
        Encapsulador_Arquivo(caminho);
        arquivo = fopen(caminho, "r");

        cadastro->codigo = criar_numero_cadastro(arquivo, caminho);

        printf("O numero do novo cadastro sera: %i\n", cadastro->codigo);

        Desencapsulador_Arquivo(caminho);
        fclose(arquivo);
        //------------------------------------------------------------

        //aqui inserir os novos dados do cadastro novo.

        //converte o numero do codigo em string para ser escrito no nome do arquivo.
        sprintf(caminho, "%i", cadastro->codigo);

        Encapsulador_Arquivo(caminho);

        strcat(caminho2, caminho);

        printf("O caminho do novo arquivo sera: %s\n", caminho2);

        arquivo = fopen(caminho2, "w+");

        if(arquivo == NULL)
        {
            printf("Erro! Nao foi possivel abrir o arquivo...\n");
            return;
        }

        fprintf(arquivo, "%s", "//----------------------------------------------------------\n");
        fprintf(arquivo, "%s", "//Cadastro: ");
        fprintf(arquivo, "%i\n", cadastro->codigo);
        fprintf(arquivo, "%s", "//Nome: ");
        fprintf(arquivo, "%s", cadastro->nome);
        fprintf(arquivo, "%s", "//Idade: ");
        fprintf(arquivo, "%i\n", cadastro->idade);
        fprintf(arquivo, "%s", "//Telefone: ");
        fprintf(arquivo, "%i\n", cadastro->telefone);
        fprintf(arquivo, "%s", "//CPF: ");
        fprintf(arquivo, "%i\n", cadastro->cpf);
        fprintf(arquivo, "%s", "//----------------------------------------------------------\n");

        fclose(arquivo);
        arquivo = fopen(caminho2, "r");

        //Loop de leitura do cadastro criado
        while(1)
        {
            c = fgetc(arquivo);
            if(feof(arquivo))
                {
                    break;
                }

            printf("%c", c);
        }

        Desencapsulador_Arquivo(caminho);
        fclose(arquivo);

    }else
        {
            printf("Nao e possivel criar o cadastro, encerrando...\n");
            status = ERRO;
        }


    fclose(arquivo);
    free(cadastro);

    return;
}

//lista todos os cadastros existentes
void listar_cadastro()
{
    //Variaveis do construtor GTK
    GtkBuilder *construtor = NULL;
    GtkWidget *janela_lista_cadastro = NULL;
    GtkWidget *box1_lista_cadastro = NULL;
    GtkWidget *label_lista_cadastro = NULL;
    //Variaveis da montagem da lista
    char nome[30] = "\0";
    GtkTreeView *tree_view;
    GtkListStore *liststore1;
    GtkTreeIter iter;
    GtkTreeViewColumn *coluna;
    GtkCellRenderer *renderer;
    //Variaveis de busca de arquivos
    DIR *diretorio;
    struct dirent *lsdiretorio;
    const char ponto[10] = ".cadastro";


    //Bloco de construção do glade - todos os objetos sao carregados do arquivo
    {
    construtor = gtk_builder_new_from_file("lista_cadastro.glade");

    if(construtor==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo lista_cadastro.glade!!\n");
        return;
    }

    liststore1 = GTK_LIST_STORE(gtk_builder_get_object(construtor, "liststore1"));

    if(liststore1==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo lista_cadastro.glade!!\n");
    }

    liststore1 = gtk_list_store_new(1, G_TYPE_STRING);

    coluna = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(construtor, "tree_view_column"));

    if(coluna==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo lista_cadastro.glade!!\n");
    }

    janela_lista_cadastro = GTK_WIDGET(gtk_builder_get_object(construtor, "janela_lista_cadastro"));

    if(janela_lista_cadastro==NULL)
    {
        printf("ERRO! Nao foi possivel criar o widget janela_lista_cadastro!\n");
        return;
    }

    box1_lista_cadastro = GTK_WIDGET(gtk_builder_get_object(construtor, "box1_lista_cadastro"));

    if(box1_lista_cadastro==NULL)
    {
        printf("ERRO! Nao foi possivel criar o widget box1_lista_cadastro!\n");
        return;
    }

    label_lista_cadastro = GTK_WIDGET(gtk_builder_get_object(construtor, "label_lista_cadastro"));

    if(label_lista_cadastro==NULL)
    {
        printf("ERRO! Nao foi possivel criar o widget label_lista_cadastro!\n");
        return;
    }

    tree_view = GTK_TREE_VIEW(gtk_builder_get_object(construtor, "tree_view_lista_cadastro"));

    if(tree_view==NULL)
    {
        printf("ERRO! Nao foi possivel criar o widget tree_view!\n");
        return;
    }
    }

    printf("Listando todos os cadastros...\n");

        //abre o diretório em que se encontra o executável
        if((diretorio = opendir("./Cadastros"))==NULL)
        {
            printf("Erro! Nao foi possivel abrir a pasta dos cadastros!\n");
        }
        //lê todos os nomes de arquivos que se encontram na pasta aberta no diretório
        //este loop passa por todos os arquivos, até encontrar o final
        //o loop funciona da seguinte maneira: o sistema tenta ler o nome do arquivo, caso não consiga, corta o loop
        while ((lsdiretorio = readdir(diretorio)) != NULL)
        {
            //esta função imprime o nome do arquivo escolhido
            //a função strstr compara duas strings, e caso o texto de uma string esteja em outra, retorna um valor
            //neste caso, caso a o if encontre a string .cadastro em algum dos nomes dos arquivos, ele passa o comando para
            //imprimir o nome do arquivo
            if((strstr(lsdiretorio->d_name, ponto)!=NULL))
            {
                printf("----------------------------------------------------------\n");
                printf("%s\n", lsdiretorio->d_name);
                printf("----------------------------------------------------------\n");

                //copia o nome do arquivo encontrada para ser repassado depois a lista de visualização
                strncpy(nome,lsdiretorio->d_name,30);

                //Adiciona os cadastros encontrados na lista de visualizacao
                gtk_list_store_append(liststore1, &iter);
                gtk_list_store_set(liststore1, &iter, 0, &nome, -1);
            }
        }

        //bloco de construção da visualização em árvore
        //define o modelo da arvore de acordo com a lista ligada ja pronta
        gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view),GTK_TREE_MODEL(liststore1));

        //render de texto
        renderer = gtk_cell_renderer_text_new();

        //associa o render de texto com a coluna da visualização
        gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(coluna), renderer, TRUE);

        //define os atributos da coluna da visualização
        gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(coluna), renderer, "text", 0, NULL);

        g_object_unref(liststore1);

        closedir(diretorio);

        gtk_widget_show_all(janela_lista_cadastro);

        g_object_unref(janela_lista_cadastro);

    return;
}

//altera um cadastro especifico
int alterar_cadastro()
{
    printf("faca o alterar cadastro!\n");
    return 0;
}

//Prepara o arquivo para ser registrado como .cadastro, adicionando o sufixo .cadastro.
//pronto
char Encapsulador_Arquivo(char arquivo[30])
{
    //Esta função encapsula o nome do arquivo a ser criado e adiciona o sufixo .cadastro, para permitir que o arquivo criado tenha um tipo especifico
    strcat(arquivo, ".cadastro");
    return arquivo[40];
}

//retorna o arquivo sem o sufixo . cadastro
//pronto
char Desencapsulador_Arquivo(char arquivo[40])
{
    char *resultado;
    int tamanho=0;
    char cadastro[10];

    strcpy(cadastro, ".");

    tamanho = strlen(arquivo);
    tamanho = tamanho-9;

    resultado = strtok(arquivo, cadastro);

    return resultado[30];
}

int criar_numero_cadastro(FILE *arquivo, char *identificador)
{
    int varredura = 0; //Identifica qual o numero do cadastro
    char varredura2[60] = "\0";
    int c = 0;
    int codigo = 0;

    if(arquivo==NULL)
        {
            printf("Erro! Nao foi possivel abrir o cadastro raiz dos arquivos.\n");
            return 1;
        }else
            {

                //Checa se existe texto escrito no arquivo raiz
                if(fgets(varredura2, 10, arquivo)==NULL)
                {
                    printf("Arquivo vazio!Criando os dados do arquivo raiz...\n");

                    fclose(arquivo);
                    arquivo = fopen(identificador, "w+");

                    fprintf(arquivo, "%s", "//----------------------------------------------------------\n");
                    fprintf(arquivo, "%s", "Numero de Cadastros registrados: 00\n");
                    fprintf(arquivo, "%s", "//----------------------------------------------------------\n");

                    //Este passo e necessario dado que, quando voce abre um arquivo para alteracao, voce remove todos os dados do
                    //arquivo e re-escreve todos os dados do arquivo. Então, para que se possa ler o arquivo, ele e aberto em modo
                    //somente leitura
                    fclose(arquivo);
                    arquivo = fopen(identificador, "r");


                    while(1)
                    {
                        c = fgetc(arquivo);
                        if(feof(arquivo))
                        {
                            break;
                        }

                        printf("%c", c);
                    }
                }else
                    {
                        //Caso encontre o arquivo raiz, adquirir o valor registrado no arquivo e usar como base para a numeracao
                        //do cadastro
                        printf("\n");
                        printf("Arquivo raiz encontrado! Imprimindo...\n");

                        fclose(arquivo);
                        arquivo = fopen(identificador, "r");


                        while(1)
                        {
                            c = fgetc(arquivo);
                            if(feof(arquivo))
                            {
                                break;
                            }

                            printf("%c", c);
                        }

                        //funcao que vai identificar o valor registrado no arquivo raiz

                        //Esta parte escanea o arquivo ate chegar no valor
                        rewind(arquivo);
                        printf("\n");
                        for(varredura=0;varredura<6;varredura++)
                        {
                        fscanf(arquivo, "%s", varredura2);
                        }

                        //aqui converte o valor encontrado em int e o imprime
                        varredura = atoi(varredura2);
                        varredura++;

                        //Aqui vai a funcao que vai inserir o valor novo
                        fclose(arquivo);
                        fopen(identificador, "w+");

                        fprintf(arquivo, "%s", "//----------------------------------------------------------\n");
                        fprintf(arquivo, "%s", "Numero de Cadastros registrados: ");
                        fprintf(arquivo, "%i", varredura);
                        fprintf(arquivo, "%s", "\n//----------------------------------------------------------\n");

                        fclose(arquivo);
                        fopen(identificador, "r");

                        printf("Novo arquivo raiz: \n");

                        while(1)
                        {
                            c = fgetc(arquivo);
                            if(feof(arquivo))
                            {
                                break;
                            }

                            printf("%c", c);
                        }

                        codigo = varredura;

                        return codigo;
                    }

            }

    return 0;
}
