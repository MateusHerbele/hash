#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include <stddef.h>
#include <stdlib.h>

struct nodoHash{
    int chave;
    struct nodoHash* proximo;
    struct nodoHash* anterior;
    //demais itens do nodo que você julgar necessários aqui
};

struct fila{
    struct nodoHash* cabeca;
    struct nodoHash* cauda;
};

struct aluno{
    char* nome;//nome completo
    char* nomeDinf;//nome de usuário nas servidoras do dinf
    unsigned int grr;
};

struct aluno* getAluno1();

//retorne NULL se o aluno2 não existir
struct aluno* getAluno2();

void imprimirDadosAlunos();

//aloca a tabela hash na memória
struct fila** gerarTabelaHash(size_t tamTabela);

//insere a chave na tabela hash. Duplicatas não são permitidas.
//Retorna o nodo inserido, ou NULL em caso de problemas (ex.: caso a chave seja uma duplicata)
struct nodoHash* inserir(struct fila* tabelaHash[], size_t tamTabela, int chave);

//deleta a tabela hash
void liberarTabelaHash(struct fila* tabelaHash[], size_t tamTabela);

//imprime na tela a tabela completa
void imprimirTabelaHash(struct fila* tabelaHash[], size_t tamTabela);

//busca o nodo com o chave, ou retorna NULL caso tal nodo não exista
struct nodoHash* buscar(struct fila*tabelaHash[], size_t tamTabela, int chave);

//exclui o nodo apontado
void excluir(struct fila* tabelaHash[], size_t tamTabela, struct nodoHash* nodo);

//retorna a posição do nodo na tabela hash
size_t hash(int chave, size_t tamTabela);

#endif // TABELA_HASH_H