#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <iomanip>

class parsingCSV
{
private:
    std::fstream fileRead;
    const std::string nameFile;
    std::vector<std::string> fieldsOfCSV;
    std::vector<int> countColumnsInRow;
    std::size_t countColumn;

    //Метод для вычисления поля с формулой
    std::string calculateFormula(std::string fieldFormula)
    {
        std::vector<std::string> operands;
        operands.reserve(2);

        size_t indexOfOperator = fieldFormula.find_first_of("+-*/");
        if (indexOfOperator == std::string::npos)
            throw("The field with formuala =" + fieldFormula + " has no operand");
        //std::cout << fieldFormula[indexOfOperator] << std::endl;

        //operands = parsingFormula(fieldFormula, indexOfOperator);
        operands.push_back(fieldFormula.substr(0, indexOfOperator - 0));
        operands.push_back(fieldFormula.substr(indexOfOperator + 1));

        return "temp";
    }

    //Каждое поле после парсинга, полученное из файла .CSV, проверяется на ряд условий и
    //исправлении, к примеру, если это формула для подсчета значения поля
    void analysisFields()
    {
        for (auto el : fieldsOfCSV)
        {
            if (el[0] == '=') //если текущее поле - формула
            {
                el = el.substr(1);
                el = calculateFormula(el);

            }
        }
    }


    
public:
    parsingCSV(std::string nameFile) : countColumn(0), nameFile(nameFile)
    {
        fileRead.open(nameFile, std::ios::in);

        if (!fileRead.is_open())
        {
            throw("Could not open file " + nameFile);
        }
    }

    // 
    void parsingLinesCSV(const char devider = ',')
    {
        //Будем хранить строку из файла .CSV
        std::string line;

        while (!fileRead.eof())
        {
            fileRead >> line;

            size_t index = line.find(devider);
            size_t countColumns = 0;

            if (index == 0) //значит первая ячейка пуста !!!! ,,?
            {
                std::cout << "__the field is NULL" << std::endl << std::endl;
                fieldsOfCSV.push_back("");
                countColumns++;
            }

            size_t start;
            size_t end = 0;
            std::string field;

            while ((start = line.find_first_not_of(devider, end)) != std::string::npos)
            {
                end = line.find(devider, start);
                //field = line.substr(start, end - start);
                fieldsOfCSV.push_back(line.substr(start, end - start));
                countColumns++;
            }

            //элемент контейнера, содержит информацию "/endLine/" о том, 
            //что предыдущие элементы контейнера были взяты из единой строки .CSV 
            fieldsOfCSV.push_back("/endLine/");

            countColumnsInRow.push_back(countColumns);

            //!!!!!!!!!Метод тестов вызывается здесь!!!!!!!!!
            //! 
            auto tempEl = countColumnsInRow[0];
            //Проверка на формат таблицы .CSV (одинаковое ли кол-во столбцов в каждой строке)
            for (auto el : countColumnsInRow)
            {
                if (!(tempEl == el))
                    throw("The rows of .CSV file have different number counter");
                else
                    tempEl = el;
            }

        }
        analysisFields();
    }



    //Метод для парсинга файла .CSV
    /*void parsingLineCSV(const char devider = ',')
    {
        parsingLine(this->fieldsOfCSV, devider);
    }*/

    /*std::string replaceFieldWithValue(std::string field)
    {
        std::string finalField;
        std::cout << field << std::endl;
        field = field.substr(1, std::string::npos);
        std::cout << field << std::endl;

        std::vector<std::string> words;
        parsingLine(words, '+');

        return finalField;
    }*/

    //Метод для представления обработанных полей из файла .CSV 
    void showFields() const
    {
        size_t plus = countColumnsInRow[2] + 1;
        size_t endline = countColumnsInRow[2];

        std::cout << "Perpesintation of field .CSV file(" << nameFile << "): " 
            << std::endl;
        for (size_t i = 0; i < fieldsOfCSV.size(); i++)
        {
            if (i != 0 && i%endline == 0)
            {
                std::cout << std::endl;
                endline += plus;
                continue;
            }

            std::cout << fieldsOfCSV[i];
            std::cout << ",";

        }
    }

};

void read_record(std::string nameFile)
{
    parsingCSV pars(nameFile);
    pars.parsingLinesCSV();
    pars.showFields();
    
}

int main()
{
    read_record("card.csv");

}

/*
* class parsingCSV
Данные:
    Указатель на файл (std::fstream)
    Название файла .CSV (std::string)
    Вектор для хранения полей .CSV файла
    Вектор для хранения полей в каждой строке .CSV

Методы:
    Парсинг строки
    Получение значения ячейки по координатам
    Вывод в консоль полей .CSV файла
    Тесты ошибочных ситуаций
*/

