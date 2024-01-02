#ifndef MAIN_HPP
#define MAIN_HPP

#include <vector>
#include <exception>
#include <iostream>
#include <sstream>

std::vector<std::vector<double> > parseTo2Dvector(std::istream& is);
std::vector<std::vector<double> > reverse(std::vector<std::vector<double> > v);
std::vector<std::vector<double> > FloydWarshall(std::vector<std::vector<double> > v);
std::vector<unsigned int> getShortestPath(std::vector<std::vector<double> > v);
void    output_vector(std::vector<std::vector<double> > v);

#endif