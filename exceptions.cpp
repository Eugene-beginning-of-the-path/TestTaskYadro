#include <iostream>
#include "exceptions.h"

pars::exc::exceptParsCSV::exceptParsCSV(const char* text, std::string field) : exception(text), field_(field) { }

void pars::exc::exceptParsCSV::info() const
{
	std::cout << "Information: " << std::exception::what() << std::endl;
	std::cout << "The field with problem: " << field_ << std::endl;
}


