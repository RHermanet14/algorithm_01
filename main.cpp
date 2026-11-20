#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>

struct point {
    // Contains the value of the point, and all of the points connections
    // Think of it like a linked list with multiple doubly linked connections
    int data;
    std::vector<point> connections; // Needs to be changed to a pointer!
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
                p.connections.push_back(point(j)); // Will most likey need to become a pointer
            }
            // check map for other connections to the current point
            for (auto const& k : map) { // k.first = key
                if (i.first != k.first) {
                    for (auto const& l : k.second) { // l = each int in std::vector<int>
                        if (i.first == l) {
                            p.connections.push_back(k.first);
                        }
                    }
                }         
            }
            points.push_back(p);
        }
    }

    /*
    network(std::istream& file) {
        std::string line;
        while (std::getline(file, line)) { // Generate data table
            int temp, key;
            std::stringstream line_stream(line);
        
            line_stream >> key;
            point p(key);
            while (line_stream >> temp) {
                p.connections.first.push_back(point(temp));
            }
            points.push_back(p);
        }
    }
    */
    
    void print_point_connections(int key) {
        auto p = std::find_if(points.begin(), points.end(), [key](point point){return key == point.data;});
        if (p == points.end()) return; // point does not exist in network
        for (auto const& i : p->connections) {
            std::cout << i.data << ' ';
        }
        std::cout << '\n';
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

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Error: could not open file\n";
        return 1;
    }

    //network n(file);
  
    // Better for data that is not uniform in size
    std::string line;
    std::unordered_map<int, std::vector<int>> table;
    int network_test = 0; // = the last key in the file. Used to test printing the network without having to manually switch each time a new input is generated.
    while (std::getline(file, line)) { // Generate data table
        int temp, key;
        std::vector<int> values;
        std::stringstream line_stream(line);
        
        line_stream >> key;
        while (line_stream >> temp) {
            values.push_back(temp);
        }
        table.insert({key, values});
        network_test = key;
    }
    file.close();
    
    //print_map(table);

    network n(table);
    std::cout << "Connections between point " << network_test << " and other points:\n";
    n.print_point_connections(network_test);

    return 0;
}