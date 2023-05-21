FROM ubuntu:latest

# Instala as bibliotecas do C++ no Ubuntu
RUN apt-get update && apt-get install -y \
    g++ \
    && rm -rf /var/lib/apt/lists/*

# Copia os arquivos do código-fonte para o diretório /app no container
COPY . /app
WORKDIR /app

# Compila o arquivo hash.cpp
RUN g++ -c hash.cpp

# Compila os programas upload.cpp, findrec.cpp e data_extractor.cpp
RUN g++ upload.cpp hash.o -o upload
RUN g++ findrec.cpp hash.o -o findrec
RUN g++ data_extractor.cpp -o data_extractor

# Executa os comandos ./upload artigo.txt e ./findrec 50 quando o container for iniciado
CMD ["./upload", "artigo.txt"]
CMD ["./findrec", "50"]