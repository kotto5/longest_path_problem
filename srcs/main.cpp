#include "../includes/main.hpp"

std::vector<std::vector<double> > reverse(std::vector<std::vector<double> > v) {
    return v;
}

std::vector<std::vector<double> > FloydWarshall(std::vector<std::vector<double> > v) {
    return v;
}

std::vector<unsigned int> getShortestPath(std::vector<std::vector<double> > v) {
    (void)v;
    std::vector<unsigned int> shortestPath;
    return shortestPath;
}

int main() {
    std::vector<std::vector<double> > distances;
    try {
        distances = parseTo2Dvector(std::cin);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    const std::vector<std::vector<double> > reverseDistances = reverse(distances);
    const std::vector<std::vector<double> > shortestDistances = FloydWarshall(reverseDistances);
    const std::vector<unsigned int> shortestPath = getShortestPath(shortestDistances);
    for (auto itr = shortestPath.begin(), end = shortestPath.end();
        itr != end; ++itr) {
        std::cout << *itr << "\r\n";
    }
    
    return 0;
}