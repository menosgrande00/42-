#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) 
    : AForm("ShrubberyCreationForm", 145, 137), target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &obj) 
    : AForm(obj), target(obj.target) {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &obj)
{
    if (this != &obj)
    {
        AForm::operator=(obj);
        target = obj.target;
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

std::string ShrubberyCreationForm::getTarget() const
{
    return target;
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
    checkExecution(executor);
    
    std::string filename = this->target + "_shrubbery";
    std::ofstream outfile(filename.c_str());
    
    if (outfile.is_open())
    {
        outfile << "               ,@@@@@@@," << std::endl;
        outfile << "       ,,,.   ,@@@@@@/@@,  .oo8888o." << std::endl;
        outfile << "    ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o" << std::endl;
        outfile << "   ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'" << std::endl;
        outfile << "   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'" << std::endl;
        outfile << "   %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'" << std::endl;
        outfile << "   `&%\\ ` /%&'    |.|        \\ '|8'" << std::endl;
        outfile << "       |o|        | |         | |" << std::endl;
        outfile << "       |.|        | |         | |" << std::endl;
        outfile << "    \\\\/ ._\\//_/__/  ,\\_//__\\\\/.  \\_//__/_" << std::endl;
        
        outfile.close();
    }
    else
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
    }
}