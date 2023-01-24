#include "exceptions.h"

pars::exc::exceptParsCSV::exceptParsCSV(const char* text, parsingCSV& ob) : exception(text), ob_(ob){}

void pars::exc::exceptParsCSV::closeCSV()
{
	ob_.~parsingCSV();
}
