#include <vector>
#include <string>
#include <fstream>

namespace pars
{
    class parsingCSV
    {
    private:
        std::fstream fileRead;
        const std::string nameFile;
        std::vector<std::string> fieldsOfCSV;
        std::vector<int> countColumnsInRow;
        //std::size_t countColumn;

        void replaceByValue(std::string& operand);

        std::string calculateFormula(std::string fieldFormula);

        // аждое поле после парсинга, полученное из файла .CSV, провер€етс€ на р€д условий и
        //исправлении, к примеру, если это формула дл€ подсчета значени€ пол€
        void analysisFields();



    public:
        parsingCSV(std::string nameFile);


        void parsingLinesCSV(const char devider = ',');

        //ћетод дл€ представлени€ обработанных полей из файла .CSV 
        void showFields() const;

    };
}
