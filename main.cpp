#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Error: could not open file\n";
        return 1;
    }

    // Better for data that is not uniform in size
    std::string line;
    while (std::getline(file, line)) {
        int temp;
        std::stringstream line_stream(line);
        while (line_stream >> temp) {
            std::cout << temp << ' ';
        }
        std::cout << '\n';
    }
    
    file.close();
    return 0;
}