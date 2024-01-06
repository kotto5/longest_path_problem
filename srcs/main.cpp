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

t_data FloydWarshall(t_data data) {
    unsigned int n = data.n;
    for (unsigned int k = 0; k < n; k++){ // 経由する頂点
        for (unsigned int i = 0; i < n; i++) { // 始点
            for (unsigned int j = 0; j < n; j++) { // 終点
                if (data.d[i][j] > data.d[i][k] + data.d[k][j]) {
                    data.d[i][j] = data.d[i][k] + data.d[k][j];
                    // data.via[j][k] = k;
                    data.via[i][j] = data.via[i][k];
                }
                // data.d[j][k] = std::min(data.d[j][k], data.d[j][i] + data.d[i][k]);
            }
        }
    }
    return data;
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
    // std::vector<std::vector<double> > reverseDistances = fillBlankOfInput(mult(distances, -1));
    std::vector<std::vector<double> > reverseDistances = fillBlankOfInput(distances);
    output_vector(reverseDistances);
    t_data data(reverseDistances);
    data.printVia();
    t_data shortestDistances = FloydWarshall(data);
    output_vector(shortestDistances.d);
    shortestDistances.printVia();
    shortestDistances.printPath3(4, 4);
    (void)shortestDistances;
    // shortestDistances.printPath1(0, 2);
    // output_vector(shortestDistances);
    // const std::vector<unsigned int> shortestPath = getShortestPath(shortestDistances);
    // for (auto itr = shortestPath.begin(), end = shortestPath.end();
    //     itr != end; ++itr) {
    //     std::cout << *itr << "\r\n";
    // }
    
    return 0;
}