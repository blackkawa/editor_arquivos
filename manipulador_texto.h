#ifndef MANIPULADOR_TEXTO_H_INCLUDED
#define MANIPULADOR_TEXTO_H_INCLUDED

#include <gtk/gtk.h>

typedef struct
{
    int codigo;
    int idade;
    int telefone;
    char nome[40];
    int cpf;
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

void criar_cadastro();
void listar_cadastro();
char Encapsulador_Arquivo();
char Desencapsulador_Arquivo();
void limpar_buffer_novo_cadastro();
int criar_numero_cadastro();
void funcao_criar_cadastro();
int confirmar_cadastro_novo();


#endif // MANIPULADOR_TEXTO_H_INCLUDED
