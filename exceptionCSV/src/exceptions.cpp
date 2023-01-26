#include <iostream>
#include "exceptions.h"

pars::exc::exceptParsCSV::exceptParsCSV(std::string text, std::string field) : 
runtime_error(text.c_str()), field_(field) { }

void pars::exc::exceptParsCSV::info() const
{
	std::cout << "Information: " << std::exception::what() << std::endl;
	std::cout << "The field with problem: " << field_ << std::endl;
}


