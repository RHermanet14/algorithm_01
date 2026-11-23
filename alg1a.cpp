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
    network(std::istream& file) {
        std::string line;
        while (std::getline(file, line)) {
            int temp, key;
            std::stringstream line_stream(line);
        
            line_stream >> key;
            point p(key);
            while (line_stream >> temp) {
                p.connections.push_back(point(temp));
                auto con = std::find_if(points.begin(), points.end(), [temp](point point){return temp == point.data;});
                if (con != points.end()) {
                    // Add point key to con.connections
                    con->connections.push_back(key);
                } else {
                    // Create a new point and add key
                    point p2(temp);
                    p2.connections.push_back(key);
                    points.push_back(p2);
                }
                // NEEDS TO BE AN ACTUAL POINTER TO MAKE IT WORK! p.connections.find(temp) != p2
            }
            points.push_back(p);
        }
    }
    
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

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Error: could not open file\n";
        return 1;
    }
    network n(file);
    file.close();

    //network n(table);
    //std::cout << "Connections between point " << network_test << " and other points:\n";
    std::cout << "Enter a num to check its connections: ";
    int temp = 0;
    std::cin >> temp;
    n.print_point_connections(temp);

    return 0;
}