#ifndef PARSINGCSV_H
#define PARSINGCSV_H

#include <fstream>
#include <vector>
#include <string>

namespace pars
{
    typedef std::vector<std::string> vecstr;
    typedef std::vector<int> vecint;

    struct XY
    {
    public:
        size_t x = -1;
        size_t y = -1;
    };

    class parsingCSV
    {
    private:
        std::fstream fileRead;
        const std::string nameFile;
        vecstr fieldsCSV;
        vecint countColumnsInRows;
        int countColumns = -1;
        XY xy;

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

        ~parsingCSV() { fileRead.close(); }
    };
}

#endif
