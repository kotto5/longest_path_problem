#include "../includes/main.hpp"
#include <limits>
#include <cmath>

std::vector<std::vector<double> > mult(std::vector<std::vector<double> > v, double multiple) {
    for (auto itr = v.begin(), end = v.end();
        itr != end; ++itr) {
        for (auto itr2 = itr->begin(), end2 = itr->end();
            itr2 != end2; ++itr2) {
            *itr2 *= multiple;
        }
    }
    return v;
}

std::vector<std::vector<double> > fillBlankOfInput(std::vector<std::vector<double> > v) {
    for (size_t i = 0, size = v.size(); i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (std::isnan(v[i][j])) {
                if (i == j)
                    v[i][j] = 0;
                else
                    v[i][j] = std::numeric_limits<double>::infinity();
            }
        }
    }
    return v;
}

std::vector<std::vector<double> > FloydWarshall(std::vector<std::vector<double> > d) {
    unsigned int n = d.size();
    for (unsigned int i = 0; i < n; i++){ // 経由する頂点
        for (unsigned int j = 0; j < n; j++) { // 始点
            for (unsigned int k = 0; k < n; k++) { // 終点
                d[j][k] = std::min(d[j][k], d[j][i] + d[i][k]);
            }
        }
    }
    return d;
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
    const std::vector<std::vector<double> > reverseDistances = fillBlankOfInput(mult(distances, -1));
    output_vector(reverseDistances);
    const std::vector<std::vector<double> > shortestDistances = FloydWarshall(reverseDistances);
    const std::vector<unsigned int> shortestPath = getShortestPath(shortestDistances);
    for (auto itr = shortestPath.begin(), end = shortestPath.end();
        itr != end; ++itr) {
        std::cout << *itr << "\r\n";
    }
    
    return 0;
}