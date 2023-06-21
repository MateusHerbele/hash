#include "tabelaHash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void matarProgramaFaltaMemoria() {
    fputs("Falha ao alocar memoria.\n", stderr);
    exit(1);
}

struct aluno* getAluno1() {
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if (!retorno) matarProgramaFaltaMemoria();
    retorno->nome = malloc(sizeof("Mateus dos Santos Herbele"));  // sizeof conta o \0
    if (!retorno->nome)
        matarProgramaFaltaMemoria();
    retorno->nomeDinf = malloc(sizeof("msh22"));
    if (!(retorno->nomeDinf))
        matarProgramaFaltaMemoria();

    strcpy(retorno->nome, "Mateus dos Santos Herbele");
    strcpy(retorno->nomeDinf, "msh22");
    retorno->grr = 20221254;

    return retorno;
}

struct aluno* getAluno2() {
    return NULL;
}

void imprimirDadosAlunos() {
    struct aluno* aluno = getAluno1();

    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    aluno = getAluno2();
    if (!aluno) return;

    printf("...E... \n\n");
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);
}

struct fila** gerarTabelaHash(size_t tamTabela){
    struct fila** tabelaHash = malloc(tamTabela * sizeof(struct fila*)); // aloca a tabela hash, que é um vetor de ponteiros para filas
    if(!tabelaHash) // se não conseguir alocar, termina o programa com erro
        matarProgramaFaltaMemoria();
    for(size_t i = 0; i < tamTabela; i++){ // para cada posição da tabela hash
        tabelaHash[i] = calloc(1, sizeof(struct fila)); // aloca espaço para a posição, que é uma fila
        if(!tabelaHash[i]) // se não conseguir alocar, termina o programa com erro
            matarProgramaFaltaMemoria();
    }
    return tabelaHash;
}

struct nodoHash* inserir(struct fila* tabelaHash[], size_t tamTabela, int chave){
    unsigned int posicao = hash(chave, tamTabela); // determinará a posição na tabela hash
    struct nodoHash* nodo; // nodo que será inserido
    if(!tabelaHash[posicao]->cabeca){ // se a posição estiver vazia
        nodo = malloc(sizeof(struct nodoHash)); // aloca o nodo
        if(!nodo) // se não conseguir alocar, termina o programa com erro
            matarProgramaFaltaMemoria();
        nodo->chave = chave; // atribui a chave ao nodo
        tabelaHash[posicao]->cabeca = nodo; // atribui o nodo como cabeça da lista
        tabelaHash[posicao]->cauda = nodo; // atribui o nodo como cauda da lista
        nodo->anterior = NULL; // como só tem ele, o anterior é nulo 
        nodo->proximo = NULL; // e o próximo também
    }else{
        if(buscar(tabelaHash, tamTabela, chave)) // busca apenas se a posição não estiver vazia
            return NULL; // se a chave já existir, retorna nulo
        nodo = malloc(sizeof(struct nodoHash)); // aloca o nodo, caso a chave não exista
        if(!nodo) // se não conseguir alocar, termina o programa com erro
            matarProgramaFaltaMemoria();
        nodo->chave = chave; // atribui a chave ao nodo
        tabelaHash[posicao]->cauda->proximo = nodo; // atribui o nodo como próximo da cauda
        nodo->anterior = tabelaHash[posicao]->cauda; // atribui a cauda como anterior do nodo
        nodo->proximo = NULL; // como é o último, o próximo é nulo
        tabelaHash[posicao]->cauda = nodo; // atribui o nodo como cauda da lista
    }
    return nodo;
}

void liberarTabelaHash(struct fila* tabelaHash[], size_t tamTabela){
    for(size_t i = 0; i < tamTabela; i++){ // percorre a tabela
        while(tabelaHash[i]->cabeca != NULL){
            struct nodoHash* aux = tabelaHash[i]->cabeca->proximo; // auxiliar para percorrer a lista
            free(tabelaHash[i]->cabeca); // libera o nodo
            tabelaHash[i]->cabeca = aux; // atribui o próximo nodo
        }
        free(tabelaHash[i]); // libera a posição da tabela
    }
    free(tabelaHash); // libera a tabela
}

void imprimirTabelaHash(struct fila* tabelaHash[], size_t tamTabela){
    struct nodoHash* aux; // auxiliar para percorrer a posição da tabela
    for(size_t i = 0; i < tamTabela; i++){ // percorre a tabela
        aux = tabelaHash[i]->cabeca;
        printf("%lu ", i);
        while(aux != NULL){ // percorre a lista
            printf("[%d] -> ", aux->chave); // imprime a chave
            aux = aux->proximo; // atribui o próximo nodo
        }
        printf("NULL\n");
    }
}

struct nodoHash* buscar(struct fila* tabelaHash[], size_t tamTabela, int chave){
    unsigned int posicao = hash(chave, tamTabela); // acha a possível posição da chave
    if(!tabelaHash[posicao]) return NULL; // se a posição estiver vazia, retorna null
    struct nodoHash* aux = tabelaHash[posicao]->cabeca; // auxiliar para percorrer a lista
    while(aux != NULL && aux->chave != chave) // percorre a lista até encontrar a chave ou chegar ao final
        aux = aux->proximo;
    return aux; // retorna o nodo encontrado ou null
}


void excluir(struct fila* tabelaHash[], size_t tamTabela, struct nodoHash* nodo){
    if(nodo->anterior == NULL) // se o nodo for o primeiro da lista
        if(nodo->proximo == NULL){ // se o nodo for o único da lista
            tabelaHash[hash(nodo->chave, tamTabela)]->cabeca = NULL; // atribui nulo à posição da chave na tabela
            tabelaHash[hash(nodo->chave, tamTabela)]->cauda = NULL; // como é a única chave, zera a cauda também
        }else{ // se o nodo não for o único da lista
            tabelaHash[hash(nodo->chave, tamTabela)]->cabeca = nodo->proximo; // atribui o próximo nodo à posição da chave na tabela
            nodo->proximo->anterior = NULL;
        }         
    else // se o nodo não for o primeiro da lista
        if(nodo->proximo == NULL){// se o nodo for o último da lista
            nodo->anterior->proximo = NULL;
            tabelaHash[hash(nodo->chave, tamTabela)]->cauda = nodo->anterior; // atribui o anterior do nodo à cauda da lista
        }    
        else{ // se o nodo não for o último da lista
            nodo->anterior->proximo = nodo->proximo; // atribui o próximo nodo ao anterior do nodo
            nodo->proximo->anterior = nodo->anterior; // atribui o anterior do nodo ao próximo do nodo
        }
    free(nodo);
}

size_t hash(int chave, size_t tamTabela){
    if(chave > 0) // para chaves positivas
        return chave % tamTabela; // calcula a posição na tabela hash
    else // para chaves negativas
        return (chave * -1) % tamTabela; // calcula a posição na tabela hash
}