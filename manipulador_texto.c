#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <gtk/gtk.h>
#include "manipulador_texto.h"
#define NORMAL 0
#define ERRO 1


//Criar solucao para quando nao houver a pasta cadastro e pasta raiz!

//Este bloco lista todos os cadastros

//lista todos os cadastros existentes
void listar_cadastro(GtkButton *botao, gpointer data)
{
	
    //Variaveis do construtor GTK
    GtkBuilder *construtor = NULL;
    GtkWidget *janela_lista_cadastro = NULL;
    GtkWidget *box1_lista_cadastro = NULL;
    GtkWidget *label_lista_cadastro = NULL;
    //Variaveis da montagem da lista
    char nome[tamanho_busca] = "\0";
    GtkTreeView *tree_view = NULL;
    GtkListStore *liststore1 = NULL;
    GtkTreeIter iter;
    GtkTreeViewColumn *coluna_arquivo = NULL;
    GtkTreeViewColumn *coluna_nome = NULL;
    GtkTreeViewColumn *coluna_idade = NULL;
    GtkTreeViewColumn *coluna_telefone = NULL;
    GtkTreeViewColumn *coluna_cpf = NULL;
    GtkCellRenderer *renderer = NULL;
    //Variaveis de busca de arquivos
    DIR *diretorio;
    struct dirent *lsdiretorio;

    int resultado = 0;
    int varredura = 0;

    FILE *arquivo = NULL;
	
	GError *error = NULL;

    char *busca = NULL;
    int analisador_busca = 0;

    const char ponto[tamanho_busca] = ".cadastro";
    char comparar_nome[8] = "//Nome:";
    char comparar_idade[9] = "//Idade:";
    char comparar_cpf[7] = "//CPF:";
    char comparar_telefone[12] = "//Telefone:";
    char caminho2[tamanho_busca] = "./Cadastros/";
	 
	printf("teste!\n");

    exibir_dados *dados_exibidos = NULL;

    dados_exibidos = malloc(sizeof(dados_exibidos)*4);

    dados_exibidos->exibir_nome = malloc(sizeof(char[tamanho_busca]));
    strcpy(dados_exibidos->exibir_nome, "\0");

    dados_exibidos->exibir_idade = malloc(sizeof(char[tamanho_busca]));
    strcpy(dados_exibidos->exibir_idade, "\0");

    dados_exibidos->exibir_telefone= malloc(sizeof(char[tamanho_busca]));
    strcpy(dados_exibidos->exibir_telefone, "\0");

    dados_exibidos->exibir_cpf = malloc(sizeof(char[tamanho_busca]));
    strcpy(dados_exibidos->exibir_cpf, "\0");

    busca = malloc(sizeof(char[tamanho_busca]));
    strcpy(busca, "\0");

    printf("Construindo a janela lista_cadastro...\n");

    printf("Erro tipo: %i, %s \n", errno, strerror(errno));

    //Bloco de construção do glade - todos os objetos sao carregados do arquivo
    
    construtor = gtk_builder_new_from_file("lista_cadastro.glade");
    if (!construtor) {
        g_printerr("Erro ao carregar Glade: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    printf("Erro tipo: %i, %s \n", errno, strerror(errno));

    printf("Carregando o construtor...\n");
    if(construtor==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo lista_cadastro.glade!!\n");
        printf("Erro tipo: %i, %s \n", errno, strerror(errno));
        return;
    }

    janela_lista_cadastro = GTK_WIDGET(gtk_builder_get_object(construtor, "janela_lista_cadastro"));
    liststore1 = GTK_LIST_STORE(gtk_builder_get_object(construtor, "liststore1"));
    
    if (!liststore1) {
        g_printerr("Erro: liststore1 não encontrada no Glade\n");
        return;
    }
    
    gtk_list_store_clear(liststore1); // Limpa a lista antes de popular

    if(liststore1==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo lista_cadastro.glade!!\n");
        printf("Erro tipo: %i, %s \n", errno, strerror(errno));
    }

    liststore1 = gtk_list_store_new(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    coluna_arquivo = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(construtor, "tree_view_column_arquivo"));

    if(coluna_arquivo==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo lista_cadastro.glade!!\n");
        printf("Erro tipo: %i, %s \n", errno, strerror(errno));
    }

    coluna_cpf = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(construtor, "tree_view_column_cpf"));

    if(coluna_cpf==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo lista_cadastro.glade!!\n");
        printf("Erro tipo: %i, %s \n", errno, strerror(errno));
    }

    coluna_nome = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(construtor, "tree_view_column_nome"));

    if(coluna_nome==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo lista_cadastro.glade!!\n");
        printf("Erro tipo: %i, %s \n", errno, strerror(errno));
    }

    coluna_idade = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(construtor, "tree_view_column_idade"));

    if(coluna_idade==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo lista_cadastro.glade!!\n");
        printf("Erro tipo: %i, %s \n", errno, strerror(errno));
    }

    coluna_telefone = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(construtor, "tree_view_column_telefone"));

    if(coluna_telefone==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo lista_cadastro.glade!!\n");
        printf("Erro tipo: %i, %s \n", errno, strerror(errno));
    }

    box1_lista_cadastro = GTK_WIDGET(gtk_builder_get_object(construtor, "box1_lista_cadastro"));

    if(box1_lista_cadastro==NULL)
    {
        printf("ERRO! Nao foi possivel criar o widget box1_lista_cadastro!\n");
        printf("Erro tipo: %i, %s \n", errno, strerror(errno));
        return;
    }

    label_lista_cadastro = GTK_WIDGET(gtk_builder_get_object(construtor, "label_lista_cadastro"));

    if(label_lista_cadastro==NULL)
    {
        printf("ERRO! Nao foi possivel criar o widget label_lista_cadastro!\n");
        printf("Erro tipo: %i, %s \n", errno, strerror(errno));
        return;
    }

    tree_view = GTK_TREE_VIEW(gtk_builder_get_object(construtor, "tree_view_lista_cadastro"));

    if(tree_view==NULL)
    {
        printf("ERRO! Nao foi possivel criar o widget tree_view!\n");
        printf("Erro tipo: %i, %s \n", errno, strerror(errno));
        return;
    }

    printf("Listando todos os cadastros...\n");

        //abre o diretório em que se encontra o executável
        if((diretorio = opendir("./Cadastros"))==NULL)
        {
            printf("Erro! Nao foi possivel abrir a pasta dos cadastros!\n");
            printf("Erro tipo: %i, %s \n", errno, strerror(errno));
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

            strcpy(busca, "\0");

            strcpy(caminho2, "./Cadastros/");

            if((strstr(lsdiretorio->d_name, ponto)!=NULL))
            {
                printf("----------------------------------------------------------\n");
                printf("%s\n", lsdiretorio->d_name);
                printf("----------------------------------------------------------\n");

                strcpy(busca, lsdiretorio->d_name);

                strcat(caminho2, busca);

                printf("O caminho do proximo arquivo sera: %s\n", caminho2);

                arquivo = fopen(caminho2, "r");

                if(arquivo==NULL)
                {
                    printf("O arquivo nao pode ser aberto!!! Erro tipo: %i, %s \n", errno, strerror(errno));
                    fclose(arquivo);
                    return;
                }else
                    {
                        printf("Leitura do cadastro...\n");

                        if(strcmp(caminho2, "./Cadastros/raiz.cadastro")==0)
                        {
                            printf("O arquivo raiz nao precisa ser lido! Pulando...\n");
                        }else
                            {
                                //le o arquivo até o final, mas guarda apenas quebra de linha por vez
                                while(resultado!=-1)
                                {
                                //escaneia a linha, caso nao atinja o final do documento, retorna 1, caso encontre o final do documento, retorna -1
                                printf("Aqui foi executado o scan do arquivo..........\n\n");

                                resultado = fscanf(arquivo, "%s", busca);

                                analisador_busca = strlen(busca);

                                printf("O tamanho de busca e: %i\n", analisador_busca);

                                if(strncmp(busca, comparar_nome, 7)==0)
                                {
                                    printf("\\--------------------------------------------------------------\n");
                                    printf("Foi encontrado o exibir_nome!\n");
                                    printf("Encontrada a linha %s, copiando...\n", busca);
                                    for(varredura = 0;varredura<analisador_busca;varredura++)
                                    {
                                        if(busca[varredura+7]=='\n')
                                        {
                                            printf("Final da varredura!\n");
                                            varredura = 50;
                                        }else
                                            {
                                                dados_exibidos->exibir_nome[varredura] = busca[varredura+7];
                                            }

                                    }
                                    printf("O nome a ser exibido sera: %s\n", dados_exibidos->exibir_nome);
                                    printf("\\--------------------------------------------------------------\n");
                                    strcpy(busca, "\0");
                                }else if(strncmp(busca, comparar_idade, 8)==0)
                                    {
                                        printf("\\--------------------------------------------------------------\n");
                                        printf("Foi encontrado o exibir_idade!\n");
                                        printf("Encontrada a linha %s, copiando...\n", busca);
                                        for(varredura = 0;varredura<=analisador_busca;varredura++)
                                        {
                                            if(varredura+8==11)
                                            {
                                                printf("Final da varredura!\n");
                                                varredura = 50;
                                            }else
                                                {
                                                    dados_exibidos->exibir_idade[varredura] = busca[varredura+8];
                                                }

                                        }
                                        printf("O nome a ser exibido sera: %s\n", dados_exibidos->exibir_idade);
                                        printf("\\--------------------------------------------------------------\n");
                                        strcpy(busca, "\0");
                                    }else if(strncmp(busca, comparar_telefone, 11)==0)
                                        {
                                            printf("\\--------------------------------------------------------------\n");
                                            printf("Foi encontrado o exibir_telefone!\n");
                                            printf("Encontrada a linha %s, copiando...\n", busca);
                                            for(varredura = 0;varredura<=analisador_busca;varredura++)
                                            {
                                                if(varredura+11==22)
                                                {
                                                    printf("Final da varredura!\n");
                                                    varredura = 50;
                                                }else
                                                    {
                                                        dados_exibidos->exibir_telefone[varredura] = busca[varredura+11];
                                                    }

                                            }
                                            printf("O nome a ser exibido sera: %s\n", dados_exibidos->exibir_telefone);
                                            printf("\\--------------------------------------------------------------\n");
                                            strcpy(busca, "\0");
                                        }else if(strncmp(busca, comparar_cpf, 6)==0)
                                            {
                                                printf("\\--------------------------------------------------------------\n");
                                                printf("Foi encontrado o exibir_cpf!\n");
                                                printf("Encontrada a linha %s, copiando...\n", busca);
                                                for(varredura = 0;varredura<=analisador_busca;varredura++)
                                                {
                                                    if(varredura+8==15)
                                                    {
                                                        printf("Final da varredura!\n");
                                                        varredura = 50;
                                                    }else
                                                        {
                                                            dados_exibidos->exibir_cpf[varredura] = busca[varredura+8];
                                                        }

                                                }
                                                printf("O nome a ser exibido sera: %s\n", dados_exibidos->exibir_cpf);
                                                printf("\\--------------------------------------------------------------\n");
                                                strcpy(busca, "\0");
                                            }else
                                    printf("Nao foram encontradas linhas...\n");
                                    printf("\\--------------------------------------------------------------\n");
                                    printf("A string nome e: %s \n", dados_exibidos->exibir_nome);
                                    printf("A string idade e: %s \n", dados_exibidos->exibir_idade);
                                    printf("A string telefone e: %s \n", dados_exibidos->exibir_telefone);
                                    printf("A string cpf e: %s \n", dados_exibidos->exibir_cpf);
                                    printf("\\--------------------------------------------------------------\n");
                                    strcpy(busca, "\0");
                                    }

                                fclose(arquivo);
                            }

                        }


                if(strcmp(caminho2, "./Cadastros/raiz.cadastro")!=0)
                {
                    printf("Copiando os dados para as colunas...\n");
                    //copia o nome do arquivo encontrada para ser repassado depois a lista de visualização
                    strncpy(nome,lsdiretorio->d_name,tamanho_busca);

                    //Adiciona os cadastros encontrados na lista de visualizacao
                    gtk_list_store_append(liststore1, &iter);
                    gtk_list_store_set(liststore1, &iter, 0, &nome, 1, dados_exibidos->exibir_nome, 2, dados_exibidos->exibir_idade, 3, dados_exibidos->exibir_telefone, 4, dados_exibidos->exibir_cpf, -1);

                    strcpy(dados_exibidos->exibir_nome, "\0");
                    strcpy(dados_exibidos->exibir_idade, "\0");
                    strcpy(dados_exibidos->exibir_telefone, "\0");
                    strcpy(dados_exibidos->exibir_cpf, "\0");
                    strcpy(nome, "\0");
                    strcpy(busca, "\0");
                    strcpy(caminho2, "\0");
                    resultado = 0;
                }else
                    {
                        printf("Escaneamento terminado! Montando a visualizacao...\n");
                    }
            }
        }

        printf("Montando visualizacao...\n");
        //bloco de construção da visualização em árvore
        //define o modelo da arvore de acordo com a lista ligada ja pronta
        gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view),GTK_TREE_MODEL(liststore1));

        printf("Iniciando renderizador de texto...\n");
        //render de texto
        renderer = gtk_cell_renderer_text_new();

        printf("Iniciando o render da coluna...\n");
        //associa o render de texto com a coluna da visualização
        gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(coluna_arquivo), renderer, TRUE);


        printf("Iniciando a coluna 0...\n");
        //define os atributos da coluna da visualização
        gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(coluna_arquivo), renderer, "text", 0, NULL);

        //associa o render de texto com a coluna da visualização
        gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(coluna_telefone), renderer, TRUE);


        printf("Iniciando a coluna 4...\n");
        //define os atributos da coluna da visualização
        gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(coluna_telefone), renderer, "text", 4, NULL);

        //associa o render de texto com a coluna da visualização
        gtk_tree_view_column_pack_end(GTK_TREE_VIEW_COLUMN(coluna_idade), renderer, TRUE);


        printf("Iniciando a coluna 3...\n");
        //define os atributos da coluna da visualização
        gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(coluna_idade), renderer, "text", 3, NULL);

        //associa o render de texto com a coluna da visualização
        gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(coluna_cpf), renderer, TRUE);


        printf("Iniciando a coluna 2...\n");
        //define os atributos da coluna da visualização
        gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(coluna_cpf), renderer, "text", 2, NULL);

        //associa o render de texto com a coluna da visualização
        gtk_tree_view_column_pack_end(GTK_TREE_VIEW_COLUMN(coluna_nome), renderer, TRUE);


        printf("Iniciando a coluna 1...\n");
        //define os atributos da coluna da visualização
        gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(coluna_nome), renderer, "text", 1, NULL);

        printf("Encerrando o diretorio...\n");
        closedir(diretorio);

        printf("Ligando sinais...\n");
        g_signal_connect_swapped(janela_lista_cadastro, "destroy", G_CALLBACK(gtk_window_close),janela_lista_cadastro);

        printf("Mostrando a janela final...\n");
        gtk_widget_show_all(janela_lista_cadastro);

        printf("Liberando o construtor...\n");
        g_object_unref(construtor);

        printf("Liberando os últimos dados...\n");

        strcpy(dados_exibidos->exibir_nome, "\0");
        strcpy(dados_exibidos->exibir_idade, "\0");
        strcpy(dados_exibidos->exibir_telefone, "\0");
        strcpy(dados_exibidos->exibir_cpf, "\0");

        printf("Liberando as ultimas variaveis...\n");
        free(dados_exibidos);
        free(busca);

        printf("Retornando...\n");

    return;
}

//Prepara o arquivo para ser registrado como .cadastro, adicionando o sufixo .cadastro.
char Encapsulador_Arquivo(char arquivo[tamanho_busca])
{
    char comparativo[tamanho_busca];
    strcpy(comparativo, ".cadastro");

    //analisa se o arquivo ja foi encapsulado antes, caso sim, remove o nome anterior
    if(strcmp(arquivo, comparativo)==0)
    {
        printf("Reencapsulando o arquivo...\n");
        strcpy(arquivo, "./Cadastros/");
    }else
        {
            //Esta função encapsula o nome do arquivo a ser criado e adiciona o sufixo .cadastro, para permitir que o arquivo criado tenha um tipo especifico
            printf("Aqui e a primeira encapsulacao...\n");
            strcat(arquivo, ".cadastro");
        }
    return arquivo[tamanho_busca];
}

//retorna o arquivo sem o sufixo . cadastro
char Desencapsulador_Arquivo(char arquivo[tamanho_busca])
{
    char *resultado = '\0';
    int tamanho=0;
    char cadastro[tamanho_busca];

    strcpy(cadastro, ".");

    tamanho = strlen(arquivo);
    tamanho = tamanho-11;

    resultado = strtok(arquivo, cadastro);

    for(tamanho = 0;tamanho==tamanho_busca; tamanho++)
    {
        if(strncmp(arquivo, ".cadastro", tamanho)==0)
        {
            strncpy(resultado, arquivo, tamanho);
            printf("A string desencapsulada e: %s\n\n", resultado);
            return resultado[tamanho_busca];
        }
    }

    return resultado[tamanho_busca];
}
