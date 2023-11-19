#ifndef APLICACOES_H
#define APLICACOES_H

/*Função que insere um texto em uma 
base de dados em formato de trie.*/
void insereTextoNaTrie(FILE *base, FILE *texto, char *nomeArqTexto, nodo *raiz);

/*Função auxiliar para escrever trie no 
arquivo base de maneira recursiva.*/
void escreveTrieNaBase(FILE *base, nodo *atual, char palavra[], int cont);

/*Procura a palavra fornecida em uma base de dados que 
contém uma ou mais estruturas de dados trie.*/
void procuraPalavrasPorPrefixo(FILE *base, char *prefixo);

#endif