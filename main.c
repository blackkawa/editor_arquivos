#include <stdio.h>
#include <stdlib.h>
#include "manipulador_texto.h"
#include <gtk/gtk.h>

/*
ESTE PROGRAMA CRIA CADASTROS SIMPLES E OS ARMAZENA EM FORMATO DE ARQUIVOS BINARIOS

Os arquivos sao em formato .cadastro, e podem ser alterados facilmente com um bloco de notas

Estrutura basica do cadastro:
    int codigo; - c�digo identificador do cadastro, gerado automaticamente
    int idade;
    int telefone;
    char nome[20];
    int cpf;

    Progresso: modelo definido, falta a cria��o do arquivo em si
    Fun��o de cadastro novo:
    Fun��o de listar cadastros: pronto!
    Fun��o de alterar cadastros: nada feito

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
Dados da estrutura raiz, que � um registro de �ndice de todos os cadastros ja criados

//----------------------------------------------------------
Numero de Cadastros registrados: 00
//----------------------------------------------------------

*/

void fechar_janela();
void teste();

int main(int argc, char **argv)
{
    GtkBuilder *construtor = NULL;
    GtkWidget *Janela = NULL;
    GtkWidget *box1 = NULL;
    GtkWidget *botao_criar_cadastro = NULL;
    GtkWidget *botao_listar_cadastro = NULL;

    gtk_init(&argc, &argv);

    construtor = gtk_builder_new_from_file("glade.glade");
    if(construtor == NULL)
        {
            printf("ERRO! o arquivo glade.glade nao foi encontrado!\n");
            return 1;
        }

    Janela = GTK_WIDGET(gtk_builder_get_object(construtor, "Janela"));

    box1 = GTK_WIDGET(gtk_builder_get_object(construtor, "box1"));

    if(box1 == NULL)
    {
        printf("ERRO! nao foi possivel carregar o Widget box1\n");
        return 1;
    }

    botao_criar_cadastro = GTK_WIDGET(gtk_builder_get_object(construtor, "botao_criar_cadastro"));

    if(botao_criar_cadastro == NULL)
    {
        printf("ERRO! nao foi possivel carregar o Widget botao_criar_cadastro\n");
        return 1;
    }

    botao_listar_cadastro = GTK_WIDGET(gtk_builder_get_object(construtor, "botao_listar_cadastro"));

    if(botao_listar_cadastro == NULL)
    {
        printf("ERRO! nao foi possivel carregar o Widget botao_listar_cadastro\n");
        return 1;
    }

    g_signal_connect(Janela, "destroy", G_CALLBACK(fechar_janela), NULL);

    g_signal_connect(botao_criar_cadastro, "clicked", G_CALLBACK(criar_cadastro), NULL);

    g_signal_connect(botao_listar_cadastro, "clicked", G_CALLBACK(listar_cadastro), NULL);

    g_object_unref(construtor);

    gtk_widget_show(Janela);

    gtk_main();

    system("pause");
    return 0;
}

void fechar_janela()
{
    gtk_main_quit();
}

void teste()
{
    GtkWidget *novaJanela = NULL;

    printf("TESTE!\n");

    novaJanela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(novaJanela), 400,400);
    gtk_window_set_title(GTK_WINDOW(novaJanela), "TESTE!");

    gtk_widget_show_all(novaJanela);

    return;

}
