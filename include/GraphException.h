#ifndef GRAPHS4_GRAPHEXCEPTION_H
#define GRAPHS4_GRAPHEXCEPTION_H


#include <string>
#include <stdexcept>


class GraphException : public std::runtime_error
{
public:
    GraphException(const std::string errorName) : std::runtime_error(errorName) {}
    const char * what() const noexcept override { return std::runtime_error::what();}
};

#endif //GRAPHS4_GRAPHEXCEPTION_H
