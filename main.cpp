#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <utility>

struct point {
    // Contains the value of the point, and all of the points connections
    // Think of it like a linked list with multiple doubly linked connections
    int data;
    std::pair<std::vector<point>, std::vector<point>> connections; // Needs to be changed to a pointer!
    point(int val) {
        data = val;
    }
};

class network { // A network of points
private:
    std::vector<point> points;
public:
    network(std::unordered_map<int, std::vector<int>> map) {
        for (auto const& i : map) {
            point p(i.first);
            for (auto const& j : i.second) {
                p.connections.first.push_back(point(j)); // Will most likey need to become a pointer
            }
            // Create algorithm that takes a key in the hashmap and determines if the key appears as a value in another key.
            points.push_back(p);
        }
    }

    ~network() { // Will need to implement if memory is allocated
    }

};

void print_map(std::unordered_map<int, std::vector<int>> map) {
    for (auto const& i : map) {
        std::cout << i.first << ' ';
        for (auto const& j : i.second) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
    return;
}

void print_all_connections() { // Recursive?
    // Print each degree of connection
    return;
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