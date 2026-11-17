#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
int main(int argc, char* argv[]) {
    int num_points = 20, num_connections = 100;

    // Optionally change input file
    if (argc > 1)
        num_points = std::stoi(argv[1]);
    if (argc > 2)
        num_connections = std::stoi(argv[2]);
   
    srand(time(0));
    std::ofstream file("input.txt"); // open input.txt for output

    for(int i = 0; i < num_points; i++) {
        for(int j = 0; j < num_connections; j++) {
            file << (rand() % num_connections) + 1 << ' '; // Random number between 1 and num_connections
        }
        file << '\n';
    }
    file.close();
    return 0;
}