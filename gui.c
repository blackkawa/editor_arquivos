#include <gtk/gtk.h>

#include "gui.h"
#include "manipulador_texto.h"

void iniciar(GtkApplication *programa, gpointer data)
{
    GError *error = NULL; // Inicializado como NULL
    GtkBuilder *construtor = NULL;
    GtkWidget *Janela = NULL;

    construtor = gtk_builder_new();
    
    // 1. PASSE &error AQUI para capturar a mensagem de erro real
    if (!gtk_builder_add_from_file(construtor, "glade.glade", &error)) {
        // Se error não for NULL, podemos acessar ->message
        g_printerr("Erro ao carregar arquivo: %s\n", error->message);
        g_clear_error(&error); // Forma segura de limpar
        g_object_unref(construtor);
        return;
    }

    // 2. BUSQUE A JANELA DO GLADE
    Janela = GTK_WIDGET(gtk_builder_get_object(construtor, "Janela"));

    if (!Janela) {
        g_printerr("Objeto 'Janela' nao encontrado no arquivo .glade\n");
        g_object_unref(construtor);
        return;
    }

    // 3. VINCULE A JANELA À APLICAÇÃO (Essencial para GtkApplication)
    gtk_application_add_window(programa, GTK_WINDOW(Janela));

    // Verifique os outros objetos de forma simples
    if (!gtk_builder_get_object(construtor, "box1")) {
        g_printerr("Aviso: 'box1' nao encontrado.\n");
    }

    // 4. CONECTE OS SINAIS
    // Isso liga os nomes das funções no Glade às funções no seu C
	// Registrar manualmente cada função definida em outros arquivos
	gtk_builder_add_callback_symbol(construtor, "criar_cadastro", G_CALLBACK(criar_cadastro));
	gtk_builder_add_callback_symbol(construtor, "listar_cadastro", G_CALLBACK(listar_cadastro));
	
    gtk_builder_connect_signals(construtor, data);

    // 5. EXIBIR E LIMPAR O CONSTRUTOR
    gtk_widget_show_all(Janela);
    
    // O construtor não é mais necessário após carregar os objetos
    g_object_unref(construtor);
}

