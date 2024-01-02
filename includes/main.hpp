#ifndef MAIN_HPP
#define MAIN_HPP

#include <vector>
#include <exception>
#include <iostream>

std::vector<std::vector<double> > input(void);
std::vector<std::vector<double> > reverse(std::vector<std::vector<double> > v);
std::vector<std::vector<double> > FloydWarshall(std::vector<std::vector<double> > v);
std::vector<unsigned int> getShortestPath(std::vector<std::vector<double> > v);

#endif