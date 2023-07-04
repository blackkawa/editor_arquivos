#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <gtk/gtk.h>
#include "manipulador_texto.h"
#define NORMAL 0
#define ERRO 1

#define tamanho_busca 40
//Cria cadastros de acordo com a estrutura do cabeçalho, com o usuário inserindo os dados.
void criar_cadastro()
{
    buffer_texto *buffers_texto;
    buffers_texto = malloc(sizeof(buffer_texto));
    //Bloco de variaveis do construtor
    GtkBuilder *construtor = NULL;
    GtkWidget *janela_cadastro_novo = NULL;//
    GtkWidget *box1_cadastro_novo = NULL;//
    GtkWidget *grid1_cadatro_novo = NULL;//
    GtkWidget *box2_cadastro_novo = NULL;//
    GtkWidget *label1_cadastro_novo = NULL;//
    GtkWidget *nome_cadastro_novo = NULL;//
    GtkWidget *cpf_cadastro_novo = NULL;//
    GtkWidget *telefone_cadastro_novo = NULL;//
    GtkWidget *idade_cadastro_novo = NULL;//
    GtkEntry *nome_entry = NULL;//
    GtkEntry *idade_entry = NULL;//
    GtkEntry *telefone_entry = NULL;//
    GtkEntry *cpf_entry = NULL;//
    GtkButton *botao_criar_cadastro = NULL;//
    GtkButton *botao_limpar_criar_cadastro = NULL;//
    GtkEntryBuffer *buffer_nome = NULL;//
    GtkEntryBuffer *buffer_idade = NULL;//
    GtkEntryBuffer *buffer_telefone = NULL;//
    GtkEntryBuffer *buffer_cpf = NULL;

    construtor = gtk_builder_new_from_file("cadastro_novo.glade");

    buffer_nome = gtk_entry_buffer_new('\0', 0);

    buffer_idade = gtk_entry_buffer_new('\0', 0);

    buffer_cpf = gtk_entry_buffer_new('\0', 0);

    buffer_telefone = gtk_entry_buffer_new('\0', 0);

    if(construtor==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo cadastro_novo.glade\n");
        return;
    }

    janela_cadastro_novo = GTK_WIDGET(gtk_builder_get_object(construtor, "janela_cadastro_novo"));

    if(janela_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo janela_cadastro_novo\n");
        return;
    }

    box1_cadastro_novo = GTK_WIDGET(gtk_builder_get_object(construtor, "box1_cadastro_novo"));

    if(box1_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo box1_cadastro_novo\n");
        return;
    }
    grid1_cadatro_novo = GTK_WIDGET(gtk_builder_get_object(construtor, "grid1_cadatro_novo"));

    if(grid1_cadatro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo grid1_cadatro_novo\n");
        return;
    }
    box2_cadastro_novo = GTK_WIDGET(gtk_builder_get_object(construtor, "box2_cadastro_novo"));

    if(box2_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo box2_cadastro_novo\n");
        return;
    }
    label1_cadastro_novo = GTK_WIDGET(gtk_builder_get_object(construtor, "label1_cadastro_novo"));

    if(label1_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo label1_cadastro_novo\n");
        return;
    }
    nome_cadastro_novo = GTK_WIDGET(gtk_builder_get_object(construtor, "nome_cadastro_novo"));

    if(nome_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo nome_cadastro_novo\n");
        return;
    }
    cpf_cadastro_novo = GTK_WIDGET(gtk_builder_get_object(construtor, "cpf_cadastro_novo"));

    if(cpf_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo cpf_cadastro_novo\n");
        return;
    }
    telefone_cadastro_novo = GTK_WIDGET(gtk_builder_get_object(construtor, "telefone_cadastro_novo"));

    if(telefone_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo telefone_cadastro_novo\n");
        return;
    }
    idade_cadastro_novo = GTK_WIDGET(gtk_builder_get_object(construtor, "idade_cadastro_novo"));

    if(idade_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo idade_cadastro_novo\n");
        return;
    }
    nome_entry = GTK_ENTRY(gtk_builder_get_object(construtor, "nome_entry"));

    if(nome_entry==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo nome_entry\n");
        return;
    }
    idade_entry = GTK_ENTRY(gtk_builder_get_object(construtor, "idade_entry"));

    if(idade_entry==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo idade_entry\n");
        return;
    }
    telefone_entry = GTK_ENTRY(gtk_builder_get_object(construtor, "telefone_entry"));

    if(telefone_entry==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo telefone_entry\n");
        return;
    }
    cpf_entry = GTK_ENTRY(gtk_builder_get_object(construtor, "cpf_entry"));

    if(cpf_entry==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo cpf_entry\n");
        return;
    }
    botao_criar_cadastro = GTK_BUTTON(gtk_builder_get_object(construtor, "botao_criar_cadastro"));

    if(botao_criar_cadastro==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo botao_criar_cadastro\n");
        return;
    }
    botao_limpar_criar_cadastro = GTK_BUTTON(gtk_builder_get_object(construtor, "botao_limpar_criar_cadastro"));

    if(botao_limpar_criar_cadastro==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo botao_limpar_criar_cadastro\n");
        return;
    }

    buffer_nome = GTK_ENTRY_BUFFER(gtk_builder_get_object(construtor, "buffer_nome"));

    if(buffer_nome==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo buffer_nome\n");
        return;
    }
    buffer_idade = GTK_ENTRY_BUFFER(gtk_builder_get_object(construtor, "buffer_idade"));

    if(buffer_idade==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo buffer_idade\n");
        return;
    }
    buffer_telefone = GTK_ENTRY_BUFFER(gtk_builder_get_object(construtor, "buffer_telefone"));

    if(buffer_telefone==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo buffer_telefone\n");
        return;
    }
    buffer_cpf = GTK_ENTRY_BUFFER(gtk_builder_get_object(construtor, "buffer_cpf"));

    if(buffer_cpf==NULL)
    {
        printf("ERRO! Nao foi possivel carregar o arquivo buffer_cpf\n");
        return;
    }

    buffers_texto->buffer1 = buffer_cpf;
    buffers_texto->buffer2 = buffer_idade;
    buffers_texto->buffer3 = buffer_nome;
    buffers_texto->buffer4 = buffer_telefone;

    g_signal_connect_swapped(botao_limpar_criar_cadastro, "clicked", G_CALLBACK(limpar_buffer_novo_cadastro), buffers_texto);

    g_signal_connect_swapped(botao_criar_cadastro, "clicked", G_CALLBACK(confirmar_cadastro_novo), buffers_texto);

    g_signal_connect_swapped(janela_cadastro_novo, "destroy", G_CALLBACK(gtk_window_close),janela_cadastro_novo);

    gtk_widget_show_all(janela_cadastro_novo);

    g_object_unref(construtor);

    return;
}

//analisa qual sera a numeracao do cadastro, para manter um indice
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

//cria o arquivo .cadastro
void funcao_criar_cadastro(buffer_texto *buffers_texto)
{
    printf("Iniciando criacao de cadastro...\n");
    //Bloco de variaveis do cadastro
    const gchar *buffer_nome = "\0";
    const gchar *buffer_cpf = "\0";
    const gchar *buffer_telefone = "\0";
    const gchar *buffer_idade = "\0";

    int idade = 0;
    int telefone = 0;
    int cpf = 0;

    printf("Adquirindo texto dos buffers...\n");
    printf("Adquirindo texto buffer 3\n");
    buffer_nome = gtk_entry_buffer_get_text(buffers_texto->buffer3);
    printf("Adquirindo texto buffer 1\n");
    buffer_cpf = gtk_entry_buffer_get_text(buffers_texto->buffer1);
    printf("Adquirindo texto buffer 4\n");
    buffer_telefone = gtk_entry_buffer_get_text(buffers_texto->buffer4);
    printf("Adquirindo texto buffer 2\n");
    buffer_idade = gtk_entry_buffer_get_text(buffers_texto->buffer2);

    printf("Convertendo valores dos buffers...\n");
    cpf = atoi(buffer_cpf);
    telefone = atoi(buffer_telefone);
    idade = atoi(buffer_idade);

    dados *cadastro = NULL;
    cadastro = malloc(sizeof(dados));
    strcpy(cadastro->nome, "\0");

    printf("Repassando valores dos buffers ao cadastro novo...\n");
    cadastro->cpf = cpf;
    cadastro->idade = idade;
    strncpy(cadastro->nome, buffer_nome, 40);
    cadastro->telefone = telefone;

    DIR *diretorio;
    FILE *arquivo = NULL;

    char identificador[40] = "raiz";
    char caminho[40] = "./Cadastros/";
    char caminho2[40] = "./Cadastros/";
    strcat(caminho, identificador);

    int status = NORMAL;
    int c = 0;


    //abre o diretorio aonde ficarao alocados os registros
    if((diretorio = opendir("./Cadastros"))==NULL)
    {
        printf("Erro! Nao foi possivel abrir a pasta dos cadastros!\n");
        return;
    }
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
        fprintf(arquivo, "%s", "//Cadastro:");
        fprintf(arquivo, "%i\n", cadastro->codigo);
        fprintf(arquivo, "%s", "//Nome:");
        fprintf(arquivo, "%s\n", cadastro->nome);
        fprintf(arquivo, "%s", "//Idade:");
        fprintf(arquivo, "%i\n", cadastro->idade);
        fprintf(arquivo, "%s", "//Telefone:");
        fprintf(arquivo, "%i\n", cadastro->telefone);
        fprintf(arquivo, "%s", "//CPF:");
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

    limpar_buffer_novo_cadastro(buffers_texto);

    fclose(arquivo);
    free(cadastro);

    buffer_nome = "\0";
    buffer_cpf = "\0";
    buffer_telefone = "\0";
    buffer_idade = "\0";

    return;
}

//janela de confirmacao do novo cadastro, puxa os buffers ja inseridos e repassa para um arquivo .cadastro
//A ordem dos dados na janela de confirmaçã esta errada
int confirmar_cadastro_novo(buffer_texto *buffers_texto)
{
    const gchar *buffer_nome = "\0";
    const gchar *buffer_cpf = "\0";
    const gchar *buffer_telefone = "\0";
    const gchar *buffer_idade = "\0";

    GtkBuilder *construtor = NULL;
    GtkWidget *janela_confirmar_cadastro_novo = NULL;
    GtkWidget *box1_confirmar_cadastro_novo = NULL;
    GtkWidget *box2_confirmar_cadastro_novo = NULL;
    GtkWidget *grid_confirmar_cadastro_novo = NULL;
    GtkLabel *label_confirmar_cadastro_novo = NULL;
    GtkLabel *nome_confirmar_cadastro_novo = NULL;
    GtkLabel *telefone_confirmar_cadastro_novo = NULL;
    GtkLabel *idade_confirmar_cadastro_novo = NULL;
    GtkLabel *cpf_confirmar_cadastro_novo = NULL;
    GtkLabel *nome_inserido_confirmar_cadastro_novo = NULL;
    GtkLabel *telefone_inserido_confirmar_cadastro_novo = NULL;
    GtkLabel *idade_inserido_confirmar_cadastro_novo = NULL;
    GtkLabel *cpf_inserido_confirmar_cadastro_novo = NULL;
    GtkLabel *label_confirmar_confirmar_cadastro_novo = NULL;
    GtkButton *botao_confirmar_confirmar_cadastro_novo = NULL;
    GtkButton *botao_corrigir_confirmar_cadastro_novo = NULL;

    construtor = gtk_builder_new_from_file("confirmar_cadastro_novo.glade");

    janela_confirmar_cadastro_novo = GTK_WIDGET(gtk_builder_get_object(construtor, "janela_confirmar_cadastro_novo"));

    if(janela_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a janela_confirmar_cadastro_novo\n");
        return FALSE;
    }

    box1_confirmar_cadastro_novo = GTK_WIDGET(gtk_builder_get_object(construtor, "box1_confirmar_cadastro_novo"));

    if(box1_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a box1_confirmar_cadastro_novo\n");
        return FALSE;
    }

    box2_confirmar_cadastro_novo = GTK_WIDGET(gtk_builder_get_object(construtor, "box2_confirmar_cadastro_novo"));

    if(box2_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a box2_confirmar_cadastro_novo\n");
        return FALSE;
    }

    grid_confirmar_cadastro_novo = GTK_WIDGET(gtk_builder_get_object(construtor, "grid_confirmar_cadastro_novo"));

    if(grid_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a grid_confirmar_cadastro_novo\n");
        return FALSE;
    }

    label_confirmar_cadastro_novo = GTK_LABEL(gtk_builder_get_object(construtor, "label_confirmar_cadastro_novo"));

    if(label_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a label_confirmar_cadastro_novo\n");
        return FALSE;
    }

    nome_confirmar_cadastro_novo = GTK_LABEL(gtk_builder_get_object(construtor, "nome_confirmar_cadastro_novo"));

    if(nome_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a nome_confirmar_cadastro_novo\n");
        return FALSE;
    }

    telefone_confirmar_cadastro_novo = GTK_LABEL(gtk_builder_get_object(construtor, "telefone_confirmar_cadastro_novo"));

    if(telefone_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a telefone_confirmar_cadastro_novo\n");
        return FALSE;
    }

    idade_confirmar_cadastro_novo = GTK_LABEL(gtk_builder_get_object(construtor, "idade_confirmar_cadastro_novo"));

    if(idade_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a idade_confirmar_cadastro_novo\n");
        return FALSE;
    }

    cpf_confirmar_cadastro_novo = GTK_LABEL(gtk_builder_get_object(construtor, "cpf_confirmar_cadastro_novo"));

    if(cpf_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a cpf_confirmar_cadastro_novo\n");
        return FALSE;
    }

    nome_inserido_confirmar_cadastro_novo = GTK_LABEL(gtk_builder_get_object(construtor, "nome_inserido_confirmar_cadastro_novo"));

    if(nome_inserido_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a nome_inserido_confirmar_cadastro_novo\n");
        return FALSE;
    }

    telefone_inserido_confirmar_cadastro_novo = GTK_LABEL(gtk_builder_get_object(construtor, "telefone_inserido_confirmar_cadastro_novo"));

    if(telefone_inserido_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a telefone_inserido_confirmar_cadastro_novo\n");
        return FALSE;
    }

    idade_inserido_confirmar_cadastro_novo = GTK_LABEL(gtk_builder_get_object(construtor, "idade_inserido_confirmar_cadastro_novo"));

    if(idade_inserido_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a idade_inserido_confirmar_cadastro_novo\n");
        return FALSE;
    }

    cpf_inserido_confirmar_cadastro_novo = GTK_LABEL(gtk_builder_get_object(construtor, "cpf_inserido_confirmar_cadastro_novo"));

    if(cpf_inserido_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a cpf_inserido_confirmar_cadastro_novo\n");
        return FALSE;
    }

    label_confirmar_confirmar_cadastro_novo = GTK_LABEL(gtk_builder_get_object(construtor, "label_confirmar_confirmar_cadastro_novo"));

    if(label_confirmar_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a label_confirmar_confirmar_cadastro_novo\n");
        return FALSE;
    }

    botao_confirmar_confirmar_cadastro_novo = GTK_BUTTON(gtk_builder_get_object(construtor, "botao_confirmar_confirmar_cadastro_novo"));

    if(botao_confirmar_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a botao_confirmar_confirmar_cadastro_novo\n");
        return FALSE;
    }

    botao_corrigir_confirmar_cadastro_novo = GTK_BUTTON(gtk_builder_get_object(construtor, "botao_corrigir_confirmar_cadastro_novo"));

    if(botao_corrigir_confirmar_cadastro_novo==NULL)
    {
        printf("ERRO! Nao foi possivel criar a botao_corrigir_confirmar_cadastro_novo\n");
        return FALSE;
    }

    printf("Adquirindo texto dos buffers...\n");
    buffer_nome = gtk_entry_buffer_get_text(buffers_texto->buffer3);
    buffer_cpf = gtk_entry_buffer_get_text(buffers_texto->buffer1);
    buffer_telefone = gtk_entry_buffer_get_text(buffers_texto->buffer4);
    buffer_idade = gtk_entry_buffer_get_text(buffers_texto->buffer2);

    gtk_label_set_text(nome_inserido_confirmar_cadastro_novo, buffer_nome);
    gtk_label_set_text(telefone_inserido_confirmar_cadastro_novo, buffer_telefone);
    gtk_label_set_text(idade_inserido_confirmar_cadastro_novo, buffer_idade);
    gtk_label_set_text(cpf_inserido_confirmar_cadastro_novo, buffer_cpf);

    g_signal_connect_swapped(botao_corrigir_confirmar_cadastro_novo, "clicked", G_CALLBACK(gtk_window_close), janela_confirmar_cadastro_novo);

    g_signal_connect_swapped(botao_confirmar_confirmar_cadastro_novo, "clicked", G_CALLBACK(funcao_criar_cadastro), buffers_texto);
    g_signal_connect_swapped(botao_confirmar_confirmar_cadastro_novo, "clicked", G_CALLBACK(gtk_window_close), janela_confirmar_cadastro_novo);

    g_signal_connect_swapped(janela_confirmar_cadastro_novo, "destroy", G_CALLBACK(gtk_window_close),janela_confirmar_cadastro_novo);

    gtk_widget_show_all(janela_confirmar_cadastro_novo);

    g_object_unref(construtor);

    buffer_nome = "\0";
    buffer_cpf = "\0";
    buffer_telefone = "\0";
    buffer_idade = "\0";

    return 0;
}

//limpa os buffers da janela criar cadastro
void limpar_buffer_novo_cadastro(buffer_texto *buffers_texto)
{
    printf("Campos Limpos!\n");
    gtk_entry_buffer_delete_text(buffers_texto->buffer1, 0,-1);
    gtk_entry_buffer_delete_text(buffers_texto->buffer2, 0,-1);
    gtk_entry_buffer_delete_text(buffers_texto->buffer3, 0,-1);
    gtk_entry_buffer_delete_text(buffers_texto->buffer4, 0,-1);
    return;
}
