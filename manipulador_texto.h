#ifndef MANIPULADOR_TEXTO_H_INCLUDED
#define MANIPULADOR_TEXTO_H_INCLUDED

typedef struct
{
    int codigo;
    int idade;
    int telefone;
    char nome[30];
    int cpf;
}dados;

void criar_cadastro();
void listar_cadastro();
int alterar_cadastro();
char Encapsulador_Arquivo();
char Desencapsulador_Arquivo();
int criar_numero_cadastro();


#endif // MANIPULADOR_TEXTO_H_INCLUDED
