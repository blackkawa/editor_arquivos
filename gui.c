#include <gtk/gtk.h>
#include "manipulador_texto.h"
#include "gui.h"

typedef struct _Editor_Arquivos
{
    GtkWidget *Janela;

}Editor_Arquivos;

static void iniciar(GtkApplication *programa, gpointer dados_usuario)
{
    Editor_Arquivos *data;

    GtkWidget *Janela = NULL;
    GtkWidget *box1 = NULL;
    GtkWidget *botao_criar_cadastro = NULL;
    GtkWidget *botao_listar_cadastro = NULL;
    GtkWidget *botao_alterar_cadastro = NULL;
    GtkBuilder *construtor = NULL;

    Janela = gtk_application_window_new(programa);
    gtk_window_set_title(GTK_WINDOW(Janela), "Manipulador de cadastros em texto!");

    construtor = gtk_builder_new();
    gtk_builder_add_from_file(construtor, "glade.glade", NULL);

    Janela = GTK_WIDGET(gtk_builder_get_object(construtor, "Janela"));
    box1 = GTK_WIDGET(gtk_builder_get_object(construtor, "box1"));
    botao_criar_cadastro = GTK_WIDGET(gtk_builder_get_object(construtor, "botao_criar_cadastro"));
    botao_listar_cadastro = GTK_WIDGET(gtk_builder_get_object(construtor, "botao_listar_cadastro"));
    botao_alterar_cadastro = GTK_WIDGET(gtk_builder_get_object(construtor, "botao_alterar_cadastro"));

    gtk_widget_set_visible(Janela, TRUE);

    gtk_builder_connect_signals(construtor, data);

    g_object_unref(construtor);

    g_object_unref(Janela);

    return;
}
