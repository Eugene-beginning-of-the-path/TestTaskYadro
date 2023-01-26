#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <exception>

namespace pars
{
	namespace exc
	{
		class exceptParsCSV : public std::runtime_error
		{
			private:
				std::string field_;
				//std::runtime_error error_;

			public:
				exceptParsCSV(std::string text, std::string field);
				void info() const ;
				~exceptParsCSV() = default;
		};
	}
}

#endif