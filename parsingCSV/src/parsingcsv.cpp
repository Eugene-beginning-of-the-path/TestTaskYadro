#include <iostream>
#include "exceptions.h"
#include "parsingcsv.h"

//The method is replacing operand of formula with some value from .CSV fields 
void pars::parsingCSV::replaceByValue(std::string& operand)
{ 
    size_t index = 0;
    xy.x = -1;
    xy.y = -1;
    for (size_t i = 0; i < countColumns; i++)
    {
        index = operand.find(fieldsCSV[i]);
        if (index != std::string::npos)
        {
            std::string col = operand.substr(0, fieldsCSV[i].size());
            if ((col == fieldsCSV[i]) && ((48 <= operand[col.size()]) && (operand[col.size()] <=57)))
            {
                xy.x = i;
                break;
            }

        }
    }

    for (size_t i = countColumns+1; i < fieldsCSV.size(); i += countColumns+1)
    {
        index = operand.find(fieldsCSV[i]);
        if (index != std::string::npos)
        {
            int value = std::stoi(operand.substr(index));
            if (std::to_string(value) == fieldsCSV[i])
            {
                xy.y = i;
                break;
            }
        }
    }

    if (xy.x == -1 || xy.y == -1)
        throw pars::exc::exceptParsCSV("Operand of a formula has invalid reference to value", operand);
    else
        operand = fieldsCSV[xy.x + xy.y];    

}

//If a field has a formula, than the field will be parsed into operands and an 
//operator and replaced on some value
std::string pars::parsingCSV::calculateFormula(std::string fieldFormula)
{
    vecstr operands;
    operands.reserve(2);

    size_t indexOfOperator = fieldFormula.find_first_of("+-*/");
    if (indexOfOperator == std::string::npos)
        throw pars::exc::exceptParsCSV("The field with formuala has no operand", fieldFormula);

    //operands = parsingFormula(fieldFormula, indexOfOperator);
    operands.push_back(fieldFormula.substr(0, indexOfOperator - 0));
    operands.push_back(fieldFormula.substr(indexOfOperator + 1));

    replaceByValue(operands[0]);
    replaceByValue(operands[1]);

    int result;
    switch (fieldFormula[indexOfOperator])
    {
    case '+':
        result = std::stoi(operands[0]) + std::stoi(operands[1]);
        break;

    case '-':
        result = std::stoi(operands[0]) - std::stoi(operands[1]);
        break;

    case '*':
        result = std::stoi(operands[0]) * std::stoi(operands[1]);
        break;

    case '/':
    {
        if (std::stoi(operands[1]) == 0)
            throw pars::exc::exceptParsCSV("Can not devide by zero", fieldFormula);
        else
            result = std::stoi(operands[0]) / std::stoi(operands[1]);
        break;
    }
    }

    return std::to_string(result);

}

//The method for testing fields of .CSV on a number of conditions 
void pars::parsingCSV::analysisFields()
{
    vecint lineNumber;

    for (size_t i = countColumns+1; i < fieldsCSV.size()-countColumns; i+= countColumns+1)
    {
        lineNumber.push_back(std::stoi(fieldsCSV[i]));
    }

    for (auto el : lineNumber)
    {
        if (el <= 0)
            throw std::runtime_error("Information: One of the line numbers is less than or equal to zero");

        int count = 0;
        int value = el;
        for (auto el_ : lineNumber)
        {
            if (el_ == value)
            {
                count++;
                if (count == 2)
                    throw std::runtime_error("Information: One of the line numbers is repeated");
            }
        }
    }

    for (size_t i = 0; i < fieldsCSV.size(); i++)
    {
        if (fieldsCSV[i][0] == '=')
        {
            fieldsCSV[i] = fieldsCSV[i].substr(1);
            fieldsCSV[i] = calculateFormula(fieldsCSV[i]);
        }
    }
    
}

//The constructor gets the .CSV file
pars::parsingCSV::parsingCSV(std::string nameFile) : nameFile(nameFile)
{
    fileRead.open(nameFile, std::ios::in);

    if (!fileRead.is_open())
    {
        throw std::runtime_error("Information: Could not open file");
    }
};

//The method for reading .CSV file and saving its fields
void pars::parsingCSV::parsingLinesCSV(const char devider)
{
    std::string line;

    while (!fileRead.eof())
    {
        fileRead >> line;

        size_t countColumns = 0;

        if (line.find(devider) == 0) 
        {
            fieldsCSV.push_back("///");
            countColumns++;
        }

        size_t start;
        size_t end = 0;

        while ((start = line.find_first_not_of(devider, end)) != std::string::npos)
        {
            end = line.find(devider, start);
            fieldsCSV.push_back(line.substr(start, end - start));
            countColumns++;
        }
 
        fieldsCSV.push_back("/endLine/");
        countColumnsInRows.push_back(countColumns);
    }

    auto tempEl = countColumnsInRows[0];
    for (auto el : countColumnsInRows)
    {
        if (!(tempEl == el))
            throw std::runtime_error("Information: The format .CSV file is invalid, because the file has different number counter");
        else
            tempEl = el;
    }

    countColumns = countColumnsInRows[0];

    analysisFields();
  
}

//The method for presentation fields of .CSV file
void pars::parsingCSV::showFields() const
{
    size_t plus = countColumns + 1;
    size_t endline = countColumns;

    std::cout << "Perpesintation of field .CSV file(" << nameFile << "): "
        << std::endl;
    for (size_t i = 0; i < fieldsCSV.size(); i++)
    {
        if (i != 0 && i % endline == 0)
        {
            std::cout << std::endl;
            endline += plus;
            continue;
        }

        if (fieldsCSV[i] == "///")
        {
            std::cout << ',';
            continue;
        }
            
        if ((i + 1) % endline == 0)
        {
            std::cout << fieldsCSV[i];
            continue;
        }

        std::cout << fieldsCSV[i] << ',';
    }
}
