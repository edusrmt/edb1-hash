# EDB1 Hash Table

## Índice
**- [1. Introdução](#1-Introdução)**
**- [2. Compilação](#2-Compilação)**
**- [3. Usando](#3-Usando)**
**- [4. Autoria](#4-Autoria)**

## 1. Introdução

Esse projeto implementa a estrutura de dados _tabela de dispersão_ em C++. Como exemplo prático, utilizamos o cadastro de contas corrente.

Os dados das contas corrente serão armazenados em uma tabela de dispersão de tamanho a ser definido pelo cliente e, com os dados cadastrados, o cliente poderá inserir, consultar e remover contas correntes.

## 2. Compilação

Esse projeto pode ser compilado utilizando o CMake. CMake é uma ferramenta open_souce que constroi, testa e empacota softwares. Basicamente, CMake lê um script CMakeLists.txt com uma meta-information no projeto e cria um arquivo chamado Makefile, automaticamente, de acordo com seu sistema. Logo em seguida, você compila utilizando o comando make.

Para compilar esse projeto você pode rodar esses comando na pasta raíz.

cmake -G "Unix Makefiles" ..: Diz ao CMake para criar o arquivo Makefile baseado no script CMakeLists.txt.
make: Compila o código do projeto e gera um executável na pasta raiz.

> Usamos o GTest para testar todas as funcionalidades do projeto, esse arquivo poderá ser executado pelo cliente também. Basta rodar o executável `run_tests` na pasta raiz.

## 3. Usando

Você pode usar a documentação gerada a partir do [Doxygen](http://www.doxygen.nl/) para ler as informações dos métodos e os seus respectivos usos. 

## 4. Autoria 
Os autores desse projeto são **Carlos Eduardo Alves Sarmento** < _cealvesarmento@gmail.com_ > and **Victor Raphaell Vieira Rodrigues** < _victorvieira89@gmail.com_ >.