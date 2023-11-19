#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

#define MAX_FILENAME_LENGTH 256

/*Inicializa uma nova trie alocando memória para 
o nodo raiz e definindo um filho para cada letra 
inicial possível das palavras.*/
nodo *inicializaTrie() { 
    nodo *raiz = (nodo *)malloc(sizeof(nodo)); 
    raiz->caractere = '\0';
    raiz->nomeArquivo = NULL;

    for (int i = 0; i < 52; i++) 
        raiz->filhos[i] = NULL; 
    
    return raiz;
}

int contemNomeArquivo(const char *nomesArquivos, const char *nomeArquivo) {
    /* Verifica se o nome do arquivo já está na lista*/
    const char *ptr = strstr(nomesArquivos, nomeArquivo);
    return (ptr != NULL);
}

void insereChave(nodo *raiz, char *chave, char *nomeArqTexto) {
    nodo *atual = raiz;
    int tam = strlen(chave);
    int índiceCaractere; // Índice do caractere a ser inserido no vetor filhos

    /* Faz a inserção de caracteres e (se 
    necessário) a criação de novos nodos */
    for (int i = 0; i < tam; i++) {
        
        /* Transforma um caractere ASCII da 
        palavra em índice de vetor filhos */
        if (chave[i] >= 'A' && chave[i] <= 'Z')
            índiceCaractere = chave[i] - 65;
        else if (chave[i] >= 'a' && chave[i] <= 'z')
            índiceCaractere = chave[i] - 71;
        else
            índiceCaractere = -1;

        /* Se o caractere recebido é uma letra válida, insere-a 
        no nodo correspondente de acordo com seu índice */
        if (índiceCaractere != -1 && atual) {
            if (!atual->filhos[índiceCaractere]) {
                atual->filhos[índiceCaractere] = inicializaTrie();
                atual->filhos[índiceCaractere]->caractere = chave[i];
            }
            atual = atual->filhos[índiceCaractere];

            /* Se for o último caractere da palavra, adiciona o nome do arquivo */
            if (i == tam - 1) {
                if (atual->nomeArquivo == NULL) {
                    size_t length = strlen(nomeArqTexto);

                    // Check if it fits in the buffer
                    if (length < MAX_FILENAME_LENGTH - 3) { 
                        atual->nomeArquivo = (char *)malloc(length + 3);  
                        if (atual->nomeArquivo != NULL) {
                            sprintf(atual->nomeArquivo, "[%s]", nomeArqTexto);
                        } else {
                            fprintf(stderr, "Falha na alocação de memória para nomeArquivo.\n");
                        }
                    } else {
                        fprintf(stderr, "O nome do arquivo é muito longo para ser armazenado.\n");
                    }
                } else {
                    /* Verifica se o nome do arquivo já está na lista */
                    if (!contemNomeArquivo(atual->nomeArquivo, nomeArqTexto)) {
                        size_t tamNomeArquivo = strlen(atual->nomeArquivo);
                        size_t novoTam = tamNomeArquivo + strlen(nomeArqTexto) + 3; // +3 para "[", "]" e "\0"
                        atual->nomeArquivo = (char *)realloc(atual->nomeArquivo, novoTam);
                        if (atual->nomeArquivo != NULL) {
                            strcat(atual->nomeArquivo, "[");
                            strcat(atual->nomeArquivo, nomeArqTexto);
                            strcat(atual->nomeArquivo, "]");
                        } else {
                            fprintf(stderr, "Falha na realocação de memória para nomeArquivo.\n");
                        }
                    }
                }
            }
        }
    }
}

/*Libera a memória alocada percorrendo recursivamente 
todos os nodos da trie e liberar a memória alocada 
para eles e para suas respectivas strings nomeArquivo*/
void destroiTrie(nodo *raiz) {
    if (raiz) {
        for (int i = 0; i < 52; i++) {
            if (raiz->filhos[i] != NULL)
                destroiTrie(raiz->filhos[i]);
        }
        free(raiz->nomeArquivo);
        free(raiz);
    }
}
