#include <stdio.h>

#include "tabelaHash.h"

int main(){
    char* op = NULL; // operação a ser realizada
    char* erro = NULL; // controla se houve valores não desejados na entrada
	struct fila** tabelaHash = NULL; // tabela hash
    struct nodoHash* nodo = NULL; // retorno das funções    
    size_t tamanho = 0; // para informar o tamanho do buffer
    size_t tamTabela = 0; // tamanho da tabela hash
    int chave = 0; // chave a ser inserida, removida ou buscada
    long long int conversor = 0; // para converter a string lida para o tamanho da tabela hash
    imprimirDadosAlunos();

    // lê o tamanho da tabela hash
    while(getline(&op, &tamanho, stdin)){
        chave = strtol(op, &erro, 10); // converte o valor lido para inteiro
        if(*erro == '\n'){ // verifica se o valor é apenas um número
            if(conversor > 0){ // verifica se o valor é válido
                tamTabela = chave; // define o tamanho da tabela hash
                break; // sai do loop
            }
            printf("Valor de tamanho inválido. Digite novamente.\n");
        }
        else
            printf("Valor de tamanho inválido. Digite novamente.\n");
    }
    tabelaHash = gerarTabelaHash(tamTabela);

    while(getline(&op, &tamanho, stdin)){
        // verifica se usuário digitou um valor de comando válido
        // INSERIR
        if(op[0] == 'i' && op[1] == ' '){
            chave = strtol(op + 2, &erro, 10);
            if(*erro == '\n'){
                nodo = inserir(tabelaHash, tamTabela, chave);
                if(!nodo)
                    printf("Falha ao inserir %d.\n", chave);   
            }
            else
                printf("Valor de inserção inválido.\n");
        }// REMOVER
        else if(op[0] == 'r' && op[1] == ' '){
            chave = strtol(op + 2, &erro, 10);
            if(*erro == '\n'){
                nodo = buscar(tabelaHash, tamTabela, chave);
                if(!nodo){
                    printf("Falha ao excluir %d.\n", chave);
                }
                excluir(tabelaHash, tamTabela, nodo);
            }
            else
                printf("Valor de remoção inválido.\n");
        }// BUSCAR
        else if(op[0] == 'b' && op[1] == ' '){
            chave = strtol(op + 2, &erro, 10);
            if(*erro == '\n'){
                nodo = buscar(tabelaHash, tamTabela, chave);
                if(nodo)
                    printf("Encotrado %d.\n", chave);
                else
                    printf("Não encontrado %d.\n", chave);
            }
            else
                printf("Valor de busca inválido.\n");
        }// IMPRIMIR
        else if(op[0] == 'l' && op[1] == '\n'){
            imprimirTabelaHash(tabelaHash, tamTabela);
        }// SAIR
        else if(op[0] == 'f' && op[1] == '\n'){
            liberarTabelaHash(tabelaHash, tamTabela);
            free(op);
            exit(0);
        }else{
            printf("Operação inválida.\n");
        }
    }        
    return 0;
}