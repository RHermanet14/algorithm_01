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
    std::vector<point*> connections;
    point(int val) {
        data = val;
    }
};

class network { // A network of points
private:
    std::vector<point*> points;

public:
    network(std::istream& file) {
        std::string line;
        while (std::getline(file, line)) {
            int temp, key;
            std::stringstream line_stream(line);
        
            line_stream >> key;
            auto find_key = std::find_if(points.begin(), points.end(), [key](point* point){return key == point->data;});
            bool repeat_key = (find_key != points.end());
            point* p = repeat_key ? *find_key : new point(key);
                
            while (line_stream >> temp) {
                point* p2 = new point(temp);
                auto con = std::find_if(points.begin(), points.end(), [temp](point* point){return temp == point->data;});
                if (con != points.end()) { // if temp is already a key
                    // Add point key to con.connections
                    (*con)->connections.push_back(p);
                } else {
                    // Create a new point and add key
                    p2->connections.push_back(p);
                    points.push_back(p2);
                }
                p->connections.push_back(p2);
            }
            if (!repeat_key)
                points.push_back(p);
        }
    }

    void print_all_connections() {
        std::ofstream ofile("output_a.txt"); // open output_a.txt for output
        for (auto const& i : points) {
            std::cout << i->data << ' ';
            ofile << i->data << ' ';
            for (auto const& j : i->connections) {
                std::cout << j->data << ' ';
                ofile << j->data << ' ';
            }
            std::cout << '\n';
            ofile << '\n';
        }
        ofile.close();
    }
    
    void print_point_connections(int key) {
        std::ofstream ofile("output_a.txt"); // open output_a.txt for output
        auto p = std::find_if(points.begin(), points.end(), [key](point* point){return key == point->data;});
        if (p == points.end()) return; // point does not exist in network
        for (auto const& i : (*p)->connections) {
            std::cout << i->data << ' ';
            ofile << i->data << ' ';
        }
        std::cout << '\n';
        ofile << '\n';
        ofile.close();
    }

    int get_size() {
        //include vector of points?
        std::size_t memory_allocated = 0;
        for (auto const& point : points) {
            memory_allocated += (point->connections.size() * sizeof(*point)) + sizeof(int);
        }
        
        return memory_allocated;
    }

    ~network() { // Will need to implement if memory is allocated
        for (auto const& i : points) {
            delete(i);
        }
        points.clear();
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

    //std::cout << "Enter a num to check its connections: ";
    //int temp = 0;
    //std::cin >> temp;
    //n.print_point_connections(temp);
    //n.print_all_connections();
    std::cout << "The network is " << n.get_size() << " bytes big.\n";

    return 0;
}