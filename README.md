# Algoritmos e Estrutura de Dados III

## Trabalho Prático 2: Indexação de Arquivos
Este trabalho prático foi desenvolvido para a disciplina CI1057 - Algoritmos e Estruturas de Dados 3 do Departamento de Informática da UFPR. <br>
O objetivo do trabalho é a implementação de uma base de dados para localização de palavras em um conjunto de arquivos.

Equipe: 
- Juliana Zambon (jz22), GRR20224168;
- Millena Suiani Costa (msc22), GRR20221243.

### Função Principal (main.c)
Contém as estruturas necessárias para a execução das aplicações -- tais como nomes de arquivos e prefixos -- informadas na stdin.<br>
Em caso de chamada de função incorreta ou se algum dos arquivos essenciais para a aplicação não for encontrado (como o arquivo de texto para operações de inserção ou o arquivo base para operações de busca), são impressas mensagens na stderr.<br>
O programa continua a execução até encontrar uma linha vazia na stdin ou quando a aplicação não se refere a operações de inserção ou busca.

### Base de Dados (trie.c e trie.h)
Arquivos texto contém palavras que são organizadas e inseridas em uma estrutura trie. Independente de quantas chamadas de inserção forem feitas (e quantos arquivos diferentes forem disponibilizados), todos serão inseridos em uma mesma estrutura trie, implementada através das funções contidas em trie.c e trie.h.<br>
Caso duas (ou mais) palavras iguais forem inseridas na trie, provenientes de arquivos diferentes, o nome de seus arquivos são concatenados na string nomeArquivo (preenchida sempre no nodo que representa o último caractere da palavra inserida), separados por vírgulas e sem espaços entre si.

#### Estrutura de dados da Trie

##### Struct Nodo da Trie

```c
typedef struct nodo {
    int caractere; //Valor do caractere armazenado no nó (ASCII)
    struct nodo *filhos[52]; //Ponteiros para os filhos (letras minúsculas e maiúsculas)
    char *nomeArquivo; //Nome do(s) arquivo(s) da palavra
} nodo;
```

##### Funções Desenvolvidas

- `nodo *inicializaTrie();`

- `void insereChaveNaTrie(nodo *raiz, char *chave);`

- `void destroiTrie(nodo *raiz);`

### Aplicações (aplicacoes.c e aplicacoes.h)

##### Aplicação insere(base, texto) 

Insere em uma estrutura trie (conforme descrito anteriormente) as palavras dispostas em um, ou mais, arquivos texto. Todo o caractere disposto no arquivo que não corresponda à letras minúsculas ou maiúsculas (não acentuadas) são desconsiderados, de forma que, no caso de uma palavra iniciar com um caractere acentuado, terá como o seu prefixo oficial o primeiro caractere não acentuado nela presente.<br>
Também se utiliza de um arquivo base, caso existente, ou cria um novo, caso contráio, correspondente ao nome fornecido na stdin e insere nele as palavras depositadas na trie, seguidas do nome de seu arquivo de origem entre parêntese:<br><br>
PALAVRA1[ARQUIVO_A]<br><br>
Na inserção de possíveis palavras duplicadas, provenientes de arquivos diferentes, no arquivo base, são concatenados os nomes dos seus arquivos de origem entre parênteses:<br><br>PALAVRA1[ARQUIVO_A][ARQUIVO_B][...]<br><br>
A aplicação insere inclui duas funções:

- `void insereTextoNaTrie(FILE *base, FILE *texto, char *nomeArqTexto, nodo *raiz);`
 
- `void escreveTrieNaBase(FILE *base, nodo *atual, char palavra[], int cont);`

##### Aplicação procura(base, prefixo) 

Busca palavras que contenham o prefixo indicado na stdin e as imprime na stdout, sucedidas pelo arquivo texto que as originou, ambos separados por espaço. Inclui uma função: 

- `void procuraPalavrasPorPrefixo(FILE *base, char *prefixo);`
