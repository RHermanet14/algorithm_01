#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

void print_map(std::unordered_map<int, std::vector<int>> map) {
    for (auto const& i : map) {
        std::cout << i.first << ' ';
        for (auto const& j : i.second) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Error: could not open file\n";
        return 1;
    }

    // Better for data that is not uniform in size
    std::string line;
    std::unordered_map<int, std::vector<int>> table;
    while (std::getline(file, line)) { // Generate data table
        int temp, key;
        std::vector<int> values;
        std::stringstream line_stream(line);
        
        line_stream >> key;
        while (line_stream >> temp) {
            values.push_back(temp);
        }
        table.insert({key, values});
    }
    
    print_map(table);
    
    // Check if each of the keys values are keys themselves
    
    file.close();
    return 0;
}