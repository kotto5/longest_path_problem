#ifndef MAIN_HPP
#define MAIN_HPP

#include <vector>
#include <exception>
#include <iostream>
#include <sstream>

#define CRLF true
#define DELIMITER ", "

std::vector<std::vector<double> > parseTo2Dvector(std::istream& is);
std::vector<std::vector<double> > reverse(std::vector<std::vector<double> > v);
std::vector<std::vector<double> > FloydWarshall(std::vector<std::vector<double> > v);
std::vector<unsigned int> getShortestPath(std::vector<std::vector<double> > v);
void    output_vector(std::vector<std::vector<double> > v);

typedef struct s_data
{
    unsigned int n;
    std::vector<std::vector<double> >   d;
    std::vector<std::vector<unsigned int> >   via;

    s_data(std::vector<std::vector<double> > d)
        : n(d.size()), d(d), via(n, std::vector<unsigned int>(n))
    {
        for (unsigned int i = 0; i < n; i++) {
            for (unsigned int j = 0; j < n; j++) {
                via[i][j] = j;
            }
        }
    };

    // void printPath1_aux(unsigned int begin, unsigned int end) {
    //     if (via[begin][end] == begin) {
    //         if (begin != end)
    //             printf("%d ", begin);
    //         return;
    //     }

    //     printPath1_aux(begin, via[begin][end]);
    //     printPath1_aux(via[begin][end], end);
    // }

    // void printPath1(unsigned int start, unsigned int goal) {
    //     printPath1_aux(start, via[start][goal]);
    //     printPath1_aux(via[start][goal], goal);
    //     printf("%d\n", goal);
    // }

    void printPath3(unsigned int start, unsigned int goal) {
        for (unsigned int cur = start; cur != goal; cur = via[cur][goal])
            printf("%d ", cur);
        printf("%d\n", goal);
    }
    
    void printVia() {
        for (unsigned int i = 0; i < n; i++) {
            for (unsigned int j = 0; j < n; j++) {
                printf("%d ", via[i][j]);
            }
            printf("\n");
        }
    }
} t_data;

#endif