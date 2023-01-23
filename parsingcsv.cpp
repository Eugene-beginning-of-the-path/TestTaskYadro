#include <iostream>
#include <array>
#include "parsingcsv.h"

struct XY
{
    size_t x = -1;
    size_t y = -1;
};

void pars::parsingCSV::replaceByValue(std::string& operand)
{
    XY xy; 
    size_t index = 0;

    for (size_t i = 0; i < countColumnsInRow[0]; i++)
    {
        index = operand.find(fieldsOfCSV[i]);
        if (index != std::string::npos)
        {
            xy.x = i;
            break;
        }
    }

    for (size_t i = countColumnsInRow[0]+1; i < fieldsOfCSV.size(); i+= countColumnsInRow[0]+1)
    {
        index = operand.find(fieldsOfCSV[i]);
        if (index != std::string::npos)
        {
            int value = std::stoi(operand.substr(index));
            if (std::to_string(value) == fieldsOfCSV[i])
            {
                xy.y = i;
                break;
            }
        }
    }

    if (xy.x == -1 || xy.y == -1)
        throw("Operand of a formula has invalid reference to value");
    else
        operand = fieldsOfCSV[xy.x + xy.y];    

}

std::string pars::parsingCSV::calculateFormula(std::string fieldFormula)
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

    replaceByValue(operands[0]);
    replaceByValue(operands[1]);

    return std::to_string(std::stoi(operands[0]) + std::stoi(operands[1]));

}

void pars::parsingCSV::analysisFields()
{
    std::vector<int> lineNumber;
    lineNumber.reserve(countColumnsInRow[0]);

    for (size_t i = 0; i < fieldsOfCSV.size(); i++)
    {
        if (fieldsOfCSV[i][0] == '=') 
        {
            fieldsOfCSV[i] = fieldsOfCSV[i].substr(1);
            fieldsOfCSV[i] = calculateFormula(fieldsOfCSV[i]);
        }

        if (i != 0 && i % (countColumnsInRow[0] + 1) == 0)
            lineNumber.push_back(std::stoi(fieldsOfCSV[i]));
        
    }
    
    for (auto el : lineNumber)
    {
        if (el <= 0)
            throw("One of the line numbers is less than or eaual to zero");

        int count = 0;
        int value = el;
        for (auto el_ : lineNumber)
        {
            if (el_ == value)
            {
                count++;
                if (count == 2)
                    throw("One of the line numbers is repeated");
            }   
        }
    }
    
}

pars::parsingCSV::parsingCSV(std::string nameFile) : nameFile(nameFile)
{
    fileRead.open(nameFile, std::ios::in);

    if (!fileRead.is_open())
    {
        throw("Could not open file " + nameFile);
    }
};

void pars::parsingCSV::parsingLinesCSV(const char devider)
{
    std::string line;
    size_t countRows = 0;

    while (!fileRead.eof())
    {
        fileRead >> line;

        //size_t index = line.find(devider);
        size_t countColumns = 0;

        if (line.find(devider) == 0) //значит перва€ €чейка пуста !!!! ,,?
        {
            //std::cout << "__the field is NULL" << std::endl << std::endl;
            fieldsOfCSV.push_back("///");
            countColumns++;
        }

        

        size_t start;
        size_t end = 0;
        int preEnd = -2;

        while ((start = line.find_first_not_of(devider, end)) != std::string::npos)
        {
            end = line.find(devider, start);
            fieldsOfCSV.push_back(line.substr(start, end - start));
            countColumns++;
        }
 
        fieldsOfCSV.push_back("/endLine/");

        countColumnsInRow.push_back(countColumns);
        countRows++;

    }

    auto tempEl = countColumnsInRow[0];
    for (auto el : countColumnsInRow)
    {
        if (!(tempEl == el))
            throw("The format .CSV file is invalid, because the file has different number counter");
        else
            tempEl = el;
    }

    analysisFields();
  
}

void pars::parsingCSV::showFields() const
{
    size_t plus = countColumnsInRow[2] + 1;
    size_t endline = countColumnsInRow[2];

    std::cout << "Perpesintation of field .CSV file(" << nameFile << "): "
        << std::endl;
    for (size_t i = 0; i < fieldsOfCSV.size(); i++)
    {
        if (i != 0 && i % endline == 0)
        {
            std::cout << std::endl;
            endline += plus;
            continue;
        }

        if (fieldsOfCSV[i] == "///")
        {
            std::cout << ',';
            continue;
        }
            
        if ((i + 1) % endline == 0)
        {
            std::cout << fieldsOfCSV[i];
            continue;
        }

        std::cout << fieldsOfCSV[i] << ',';
    }
}
