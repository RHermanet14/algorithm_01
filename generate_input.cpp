#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
int main(int argc, char* argv[]) {
    int num_points = 20; // The number of unique keys
    int num_connections = 100; // The number of values each key has
    int max_num = 100; // The maximum value of the keys and values
    
    // Optionally change input file
    if (argc > 1)
        num_points = std::stoi(argv[1]);
    if (argc > 2)
        num_connections = std::stoi(argv[2]);
    if (argc > 3)
        max_num = std::stoi(argv[3]);

    if (num_points > max_num) {
        std::cerr << "Error: number of points cannot exceed number of unique values." << '\n';
        return -1;
    }

    srand(time(0));
    std::ofstream file("input.txt"); // open input.txt for output
    std::vector<int> keys;

    for(int i = 0; i < num_points; i++) {
        int temp = (rand() % max_num) + 1;
        while(std::find(keys.begin(), keys.end(), temp) != keys.end()) {
            temp = (rand() % max_num) + 1;
        }
        file << temp << ' ';
        keys.push_back(temp);

        std::vector<int> points;
        for(int j = 0; j < num_connections - 1; j++) {
            while(std::find(points.begin(), points.end(), temp) != points.end()) {
                temp = (rand() % max_num) + 1;
            }
            file << temp << ' '; // Random number between 1 and max_num
            points.push_back(temp);
        }
        file << '\n';
    }
    file.close();
    return 0;
}