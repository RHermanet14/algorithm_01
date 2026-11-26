#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>

void print_map(std::unordered_map<int, std::vector<int>> table) {
    std::ofstream ofile("output_b.txt"); // open output_b.txt for output
    
    // Print to both stdout and output.txt
    for (auto const& i : table) {
        std::cout << i.first << ' ';
        ofile << i.first << ' ';
        for (auto const& j : i.second) {
            std::cout << j << ' ';
            ofile << j << ' ';
        }
        std::cout << '\n';
        ofile << '\n';
    }
    ofile.close();
    return;
}

int get_size(std::unordered_map<int, std::vector<int>> table) {
    std::size_t size = 0;
    for (auto const& key : table) {
        size += sizeof(key.first);
        for(auto const& value : key.second) {
            size += sizeof(value);
        }
    }
    return size;
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
            table[key].push_back(temp);
            table[temp].push_back(key); // Add key as a connection in the values node
        }
    }
    file.close();
    
    //print_map(table);
    std::cout << "The network is " << get_size(table) << " bytes big.\n";

    return 0;
}