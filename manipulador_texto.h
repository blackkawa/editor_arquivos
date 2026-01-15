#ifndef MANIPULADOR_TEXTO_H_INCLUDED
#define MANIPULADOR_TEXTO_H_INCLUDED

#include <gtk/gtk.h>

#define tamanho_busca 40


typedef struct
{
    int codigo;
    char idade[40];
    char telefone[40];
    char nome[40];
    char cpf[40];
}dados;

typedef struct
{
    GtkEntryBuffer *buffer1;
    GtkEntryBuffer *buffer2;
    GtkEntryBuffer *buffer3;
    GtkEntryBuffer *buffer4;
}buffer_texto;

typedef struct
{
    char *exibir_nome;
    char *exibir_idade;
    char *exibir_cpf;
    char *exibir_telefone;
}exibir_dados;

int criar_numero_cadastro(FILE *arquivo, char *identificador);
void criar_cadastro(GtkButton *botao, gpointer data);
void listar_cadastro(GtkButton *botao, gpointer data);
char Desencapsulador_Arquivo(char arquivo[tamanho_busca]);
char Encapsulador_Arquivo(char arquivo[tamanho_busca]);
void limpar_buffer_novo_cadastro(buffer_texto *buffers_texto);
void funcao_criar_cadastro(buffer_texto *buffers_texto);
int confirmar_cadastro_novo(buffer_texto *buffers_texto);


#endif // MANIPULADOR_TEXTO_H_INCLUDED
