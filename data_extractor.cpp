#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    std::ifstream record_file("artigo.csv");
    std::ofstream output_file("artigo.txt");
    std::string line;

    while (std::getline(record_file, line)) {
        std::stringstream ss(line);
        std::string field;
        
        while (std::getline(ss, field, '\"')) {
            if (field.length() > 0 && field != ";") {
                output_file << field << std::endl;
            }
        }
        output_file << std::endl; // Adiciona uma linha em branco entre os registros
    }
    
    record_file.close();
    output_file.close();
    
    return 0;
}