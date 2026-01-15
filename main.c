#include <stdio.h>
#include <stdlib.h>
#include "gui.h"
#include <gtk/gtk.h>

/*
ESTE PROGRAMA CRIA CADASTROS SIMPLES E OS ARMAZENA EM FORMATO DE ARQUIVOS BINARIOS

Os arquivos sao em formato .cadastro, e podem ser alterados facilmente com um bloco de notas

Estrutura basica do cadastro:
    int codigo; - código identificador do cadastro, gerado automaticamente
    int idade;
    int telefone;
    char nome[20];
    int cpf;

    Progresso: modelo definido, falta a criação do arquivo em si
    Função de cadastro novo:
    Função de listar cadastros: pronto!
    Função de alterar cadastros: nada feito

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
Dados da estrutura raiz, que é um registro de índice de todos os cadastros ja criados

//----------------------------------------------------------
Numero de Cadastros registrados: 00
//----------------------------------------------------------

*/

int main(int argc, char **argv)
{		
	int status = 0;
		
	GtkApplication *app = NULL;
		
	app = gtk_application_new("org.exemplo.cadastros", G_APPLICATION_DEFAULT_FLAGS);
		
	g_signal_connect(app, "activate", G_CALLBACK(iniciar), NULL);
		
	status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
	