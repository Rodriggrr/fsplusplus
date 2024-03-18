#include <iostream>
#include <fstream>
#include <ctime>
#include "fstreamapi.h"

int main() {
    // ofstream é uma classe que representa um arquivo de saída. funciona como cout, exceto que escreve em um arquivo,
    // e não no buffer de saída padrão (stdout).
    std::ofstream fileIn("test.txt"); // pode ter qualquer extensão, mas é comum usar .txt para arquivos de texto.
    fileIn << "Hello, world!" << std::endl;
    fileIn << "This is a test." << std::endl;
    fileIn.close(); // fecha o arquivo. é importante fechar o arquivo para garantir que todos os dados sejam escritos.


    // ifstream é uma classe que representa um arquivo de entrada, ao invés de um de saida.
    std::ifstream fileOut("test.txt");
    std::string str;
    while (std::getline(fileOut, str)) { 
        std::cout << str << std::endl;
    }

    // observe os operadores << e >>. eles são sobrecarregados para funcionar com arquivos, e funcionam como se fossem
    // operadores de entrada e saída padrão.

    // agora, vamos abrir um arquivo, porem uma linha específica e aleatória.
    srand(time(0));

    fileOut = std::ifstream("words.txt");
    int line = rand() % 1000;
    for (int i = 0; i < line; i++) {
        std::getline(fileOut, str);
    }
    std::cout << str << std::endl;

    // usando minha api

    File file("test.txt");
    file.emptyFile();
    file << "API Test";
    file << "Ole mundoooo";
    std::cout << file.read() << std::endl;
    std::cout << file.read() << std::endl;

    file.write("funcao write");
    std::cout << file.read() << std::endl;

    file.setPath("words.txt");
    std::cout << file.readLine(rand() % 1000) << std::endl;

    file.emptyFile();

    // nunca esqueça de fechar o arquivo.
    file.close();

}