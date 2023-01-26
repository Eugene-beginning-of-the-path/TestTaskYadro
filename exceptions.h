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
				std::string field_;

			public:
				exceptParsCSV(const char* text, std::string field);
				void info() const ;
				~exceptParsCSV() = default;
		};
	}
}

#endif