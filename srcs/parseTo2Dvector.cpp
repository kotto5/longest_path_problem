#include "../includes/main.hpp"
#include <tuple>
#include <limits>

typedef std::tuple<unsigned int, unsigned int, double> t_input;

// debug function
void    output_vector(std::vector<std::vector<double> > v) {
    for (auto itr = v.begin(), end = v.end();
        itr != end; ++itr) {
        for (auto itr2 = itr->begin(), end2 = itr->end();
            itr2 != end2; ++itr2) {
            std::cout << *itr2 << ", ";
        }
        std::cout << "\r\n";
    }
}

static bool isdouble(const std::string& s)
{
    try
    {
        std::stod(s);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

static unsigned int stoui(const std::string& s)
{
    std::stringstream ss(s);
    unsigned int i;
    ss >> i;
    if (ss.fail())
        throw std::runtime_error("Invalid input (first and second value must be unsigned int): " + s);
    return i;    
}

static bool isuint(const std::string& s)
{
    try
    {
        stoui(s);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

// split with delimiter
static std::vector<std::string> split(std::string s, std::string delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}

static std::vector<t_input>    getTokenVector(std::istream& is) {
    std::vector<t_input> tokensVector;
    std::string s;
    while (std::getline(is, s)) {
        // not EOF && line must be end with CRLF
        if( !is.eof() && s[s.size() - 1] != '\r')
            throw std::runtime_error("Invalid input (line must be end with CRLF): " + s);
        else if (s[s.size() - 1] == '\r')
            s.pop_back();
        // split with ", "
        std::vector<std::string> tokens = split(s, ", ");
        if (tokens.size() != 3)
            throw std::runtime_error("Invalid input (line must contain 3 values): " + s);
        if (!isuint(tokens[0]) || !isuint(tokens[1]))
            throw std::runtime_error("Invalid input (first and second value must be unsigned int): " + s);
        if (!isdouble(tokens[2]))
            throw std::runtime_error("Invalid input (third value must be double): " + s);
        t_input t(stoui(tokens[0]), stoui(tokens[1]), std::stod(tokens[2]));
        tokensVector.push_back(t);
    }
    return tokensVector;
}

std::vector<std::vector<double> > parseTo2Dvector(std::istream& is) {
    std::vector<std::vector<double> > v;
    std::string s;
    std::vector<t_input> tokensVector = getTokenVector(is);
    if (tokensVector.size() == 0)
        throw std::runtime_error("Invalid input (input is empty)");

    // get value's size (width)
    unsigned int max = std::numeric_limits<unsigned int>::min();
    unsigned int min = std::numeric_limits<unsigned int>::max();
    for (auto itr = tokensVector.begin(), end = tokensVector.end();
        itr != end; ++itr) {
        if (std::get<0>(*itr) > max)
            max = std::get<0>(*itr);
        if (std::get<1>(*itr) > max)
            max = std::get<1>(*itr);
        if (std::get<0>(*itr) < min)
            min = std::get<0>(*itr);
        if (std::get<1>(*itr) < min)
            min = std::get<1>(*itr);
    }
    const unsigned int size = max - min + 1;

    // initialize v
    v.resize(size);
    for (auto itr = v.begin(), end = v.end();
        itr != end; ++itr) {
        itr->resize(size);
        for (auto itr2 = itr->begin(), end2 = itr->end();
            itr2 != end2; ++itr2) {
            *itr2 = std::numeric_limits<double>::quiet_NaN();
        }
    }

    // set values to v
    for (auto itr = tokensVector.begin(), end = tokensVector.end();
        itr != end; ++itr) {
        v[std::get<0>(*itr) - min][std::get<1>(*itr) - min] = std::get<2>(*itr);
    }
    #ifdef DEBUG
    output_vector(v);
    #endif
    return v;
}
