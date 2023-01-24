#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include "parsingcsv.h"

namespace pars
{
	namespace exc
	{
		class exceptParsCSV : public std::exception
		{
			private:
				pars::parsingCSV& ob_;

			public:
				exceptParsCSV(const char* text, pars::parsingCSV& ob);
				void closeCSV();
				~exceptParsCSV() = default;
		};
	}
}

#endif