#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
    (void)other;
    return *this;
}
ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string& literal)
{
    if (literal == "nan" || literal == "nanf" ||
        literal == "+inf" || literal == "+inff" ||
        literal == "-inf" || literal == "-inff")
    {
        
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        
        if (literal == "nan" || literal == "nanf")
            std::cout << "float: nanf\ndouble: nan" << std::endl;
        else if (literal == "+inf" || literal == "+inff")
            std::cout << "float: +inff\ndouble: +inf" << std::endl;
        else
            std::cout << "float: -inff\ndouble: -inf" << std::endl;
        return;
    }

    if (literal.length() == 1 && !std::isdigit(literal[0]))
    {
        char c = literal[0];
        std::cout << "char: '" << c << "'" << std::endl;
        std::cout << "int: " << static_cast<int>(c) << std::endl;
        std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
        std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
        return;
    }

    char* endptr;
    
    long intVal = std::strtol(literal.c_str(), &endptr, 10);
    
    if (*endptr == '\0')
    {
        if (intVal >= 32 && intVal <= 126)
            std::cout << "char: '" << static_cast<char>(intVal) << "'" << std::endl;
        else if (intVal >= 0 && intVal <= 127)
            std::cout << "char: Non displayable" << std::endl; // 
        else
            std::cout << "char: impossible" << std::endl;

        if (intVal > std::numeric_limits<int>::max() || intVal < std::numeric_limits<int>::min())
            std::cout << "int: impossible" << std::endl;
        else
            std::cout << "int: " << static_cast<int>(intVal) << std::endl;

        std::cout << "float: " << static_cast<float>(intVal) << ".0f" << std::endl;
        std::cout << "double: " << static_cast<double>(intVal) << ".0" << std::endl;
        return;
    }

    double doubleVal = std::strtod(literal.c_str(), &endptr);
    
    if (*endptr == 'f' && *(endptr + 1) == '\0')
    {
        float floatVal = static_cast<float>(doubleVal);
        
        if (floatVal >= 32 && floatVal <= 126)
            std::cout << "char: '" << static_cast<char>(floatVal) << "'" << std::endl;
        else if (floatVal >= 0 && floatVal <= 127)
            std::cout << "char: Non displayable" << std::endl;
        else
            std::cout << "char: impossible" << std::endl;

        if (doubleVal > std::numeric_limits<int>::max() || doubleVal < std::numeric_limits<int>::min())
            std::cout << "int: impossible" << std::endl;
        else
            std::cout << "int: " << static_cast<int>(floatVal) << std::endl;

        if (floatVal == static_cast<int>(floatVal))
        {
            std::cout << "float: " << floatVal << ".0f" << std::endl;
            std::cout << "double: " << static_cast<double>(floatVal) << ".0" << std::endl;
        }
        else
        {
            std::cout << "float: " << floatVal << "f" << std::endl;
            std::cout << "double: " << static_cast<double>(floatVal) << std::endl;
        }
        return;
    }

    else if (*endptr == '\0')
    {
        if (doubleVal >= 32 && doubleVal <= 126)
            std::cout << "char: '" << static_cast<char>(doubleVal) << "'" << std::endl;
        else if (doubleVal >= 0 && doubleVal <= 127)
            std::cout << "char: Non displayable" << std::endl;
        else
            std::cout << "char: impossible" << std::endl;

        if (doubleVal > std::numeric_limits<int>::max() || doubleVal < std::numeric_limits<int>::min())
            std::cout << "int: impossible" << std::endl;
        else
            std::cout << "int: " << static_cast<int>(doubleVal) << std::endl;

        if (doubleVal == static_cast<int>(doubleVal))
        {
            std::cout << "float: " << static_cast<float>(doubleVal) << ".0f" << std::endl;
            std::cout << "double: " << doubleVal << ".0" << std::endl;
        }
        else
        {
            std::cout << "float: " << static_cast<float>(doubleVal) << "f" << std::endl;
            std::cout << "double: " << doubleVal << std::endl;
        }
        return;
    }
    std::cout << "Error: Invalid literal format." << std::endl;
}