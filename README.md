# Tp-2-BD-I
Este repositório contém a implementação de programas para armazenamento e consulta de dados em memória secundária, utilizando estruturas de arquivo de dados e índice estudadas em aula. Os programas oferecem suporte para inserção e diferentes formas de busca, seguindo as técnicas apresentadas nas aulas de organização e indexação de arquivos.

## Documentação
  No arquivo de documentação, está contido:
   * A estrutura de cada arquivo de dados e índices
   * Quais fontes formam cada programa
   * As funções que cada fonte contém
   * Qual o papel de cada função

## Arquivo de dados

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
      Arquivo de índice primário usando uma B+Tree armazenada em memória secundária

  ### Pesquisa utilizando índice secundário
      Arquivo de índice secundário usando uma outra B+Tree em memória secundária
