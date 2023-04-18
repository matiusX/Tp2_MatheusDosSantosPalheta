# Tp-2-BD-I
Este repositório contém a implementação de programas para armazenamento e consulta de dados em memória secundária, utilizando estruturas de arquivo de dados e índice estudadas em aula. Os programas oferecem suporte para inserção e diferentes formas de busca, seguindo as técnicas apresentadas nas aulas de organização e indexação de arquivos.

## Documentação
  No arquivo de documentação, está contido:
   * A estrutura de cada arquivo de dados e índices
   * Quais fontes formam cada programa
   * As funções que cada fonte contém
   * Qual o papel de cada função

## Arquivo de dados
Os dados necessários para testar e avaliar os programas implementados estão disponíveis [nesse link](https://drive.google.com/file/d/1EVoP0d9Wwzj1O6eoFIkel9I3cpe43Gbv/view?usp=sharing) no formato CSV, que será utilizado exclusivamente como entrada de dados.
    
Campo | Tipo | Descrição
| :---: | :---: | :---:
ID  | inteiro | Código identificador do artigo 
Título | alfa 300 | Título de artigo
Ano  | inteiro | Ano de publicação do artigo
Autores | alfa 150 | Lista dos autores do artigo
Citações |inteiro | Número de vezes que o artigo foi citado
Atualização  | data e hora | Data e hora da última atualização dos dados
Snippet| alfa entre 100 e 1024 | Resumo textual do artigo

## Busca no arquivo de dados
### Pesquisa utilizando índice primário
  * Utiliza-se um arquivo de índice primário armazenado em memória secundária usando B+Tree
  * O programa retorna o registro com ID correspondente ao informado, caso exista, realizando uma busca ***no arquivo de índice primário***. São exibidos todos os campos do registro, bem como a quantidade de blocos lidos para encontrá-lo no arquivo de índice e a quantidade total de blocos no arquivo de índice primário

### Pesquisa utilizando índice secundário
  * Utiliza-se um arquivo de índice secundário armazenado em memória secundária usando B+Tree
  * O programa exibe os dados do registro que tenha o Título correspondente ao informado, caso exista, realizando uma busca ***no arquivo de índice secundário***. São informados a quantidade de blocos lidos para encontrar o registro no arquivo de índice secundário e a quantidade total de blocos do arquivo de índice secundário
