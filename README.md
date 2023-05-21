# Trabalho Prático 2 - Banco de Dados I
Este repositório contém a implementação de programas para armazenamento e consulta de dados em memória secundária, utilizando estruturas de arquivo de dados e índice. Os programas oferecem suporte para inserção e diferentes formas de busca, seguindo as técnicas apresentadas nas aulas de organização e indexação de arquivos.

## Documentação
  No arquivo de documentação, está contido:
   * A estrutura de cada arquivo de dados e índices
   * Quais fontes formam cada programa
   * As funções que cada fonte contém
   * Qual o papel de cada função

## Entrada do programa
Os dados necessários para testar e avaliar os programas implementados estão disponíveis [nesse link](https://drive.google.com/file/d/1EVoP0d9Wwzj1O6eoFIkel9I3cpe43Gbv/view?usp=sharing) no formato CSV, que será utilizado exclusivamente como entrada de dados, no seguinte formato: 
    
Campo | Tipo | Descrição
| :---: | :---: | :---:
ID  | inteiro | Código identificador do artigo 
Título | alfa 300 | Título de artigo
Ano  | inteiro | Ano de publicação do artigo
Autores | alfa 150 | Lista dos autores do artigo
Citações |inteiro | Número de vezes que o artigo foi citado
Atualização  | data e hora | Data e hora da última atualização dos dados
Snippet| alfa entre 100 e 1024 | Resumo textual do artigo

### Otimização da entrada
Visando diminuir o custo ao ler a entrada, foi utilizado um parser externo para ajustar o "artigo.csv". O arquivo utilizado pelo programa é o "artigo.txt" no qual cada linha representa um campo de um artigo. Essa decisão foi tomada após tentar utilizar regex.

## Arquivo de dados
Os dados extraídos estão num arquivo de dados organizado por **Hashing**

### Busca no próprio arquivo de dado
  * `findrec <ID>`
  * O programa tem como função realizar uma busca direta no arquivo de dados por um registro com o ID informado. Caso o registro exista, o programa retorna os campos do registro, bem como a quantidade de blocos lidos para encontrá-lo e a quantidade total de blocos do arquivo de dados.

### Busca utilizando índice primário
  * `seek1 <ID>`
  * Utiliza-se um arquivo de índice primário armazenado em memória secundária usando B+Tree.
  * O programa retorna o registro com ID correspondente ao informado, caso exista, realizando uma busca ***no arquivo de índice primário***. São exibidos todos os campos do registro, bem como a quantidade de blocos lidos para encontrá-lo no arquivo de índice e a quantidade total de blocos no arquivo de índice primário.

### Busca utilizando índice secundário
  * `seek2 <Titulo>`
  * Utiliza-se um arquivo de índice secundário armazenado em memória secundária usando B+Tree.
  * O programa exibe os dados do registro que tenha o Título correspondente ao informado, caso exista, realizando uma busca ***no arquivo de índice secundário***. São informados a quantidade de blocos lidos para encontrar o registro no arquivo de índice secundário e a quantidade total de blocos do arquivo de índice secundário.

## Fontes e funções
   * hash.cpp: modifica tudo na tabela hash, incluindo registros e buckets.
   * bpt_sk1.cpp: Árvore b+ implementada para a busca utilizando arquivo de índice primário (inteiro).
   * bpt_sk2.cpp: Árvore b+ implementada para a busca utilizando arquivo de índice secundário (string).
 
upload | findrec | seek 1 | seek 2
| :---: | :---: | :---: | :---:
hash.cpp, bpt_sk1.cpp, bpt_sk2.cpp | hash.cpp | bpt_sk1.cpp | bpt_sk2.cpp

## Papel de cada função
nome | descrição | programa
| :---: | :---: | :---: 
adiciona_el_bk | insere chave no bucket | hash.cpp
le_bucket | retorna um bucket a partir da chave | hash.cpp
cria_bucket | cria um bucket | hash.cpp
funcao_hash | retorna o id a partir de uma chave | hash.cpp
hash_table | cria tabela hash | hash.cpp
get_registro | procura registro no bloco | hash.cpp
cria_bucket | cria um bucket | hash.cpp
retorna_bloco | retorna um bloco | hash.cpp
adiciona_chave_hash | adiciona um elemento na hash | hash.cpp
get_bucket | retorna um bucket a partir de uma chave | hash.cpp
inicia_hash | começa a tabela | hash.cpp

