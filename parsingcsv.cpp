#include <iostream>
#include <array>
#include "parsingcsv.h"

struct XY
{
public:
    size_t x = -1;
    size_t y = -1;
};

void pars::parsingCSV::replaceByValue(std::string& operand)
{
    XY xy; 
    size_t index = 0;

    for (size_t i = 0; i < countColumns; i++)
    {
        index = operand.find(fieldsCSV[i]);
        if (index != std::string::npos)
        {
            xy.x = i;
            break;
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
        throw("Operand of a formula has invalid reference to value");
    else
        operand = fieldsCSV[xy.x + xy.y];    

}

std::string pars::parsingCSV::calculateFormula(std::string fieldFormula)
{
    vecstr operands;
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
            throw("Can not devide by zero");
        else
            result = std::stoi(operands[0]) / std::stoi(operands[1]);
        break;
    }
    }

    return std::to_string(result);

}

void pars::parsingCSV::analysisFields()
{
    vecint lineNumber;
    lineNumber.reserve(countColumns);

    for (size_t i = 0; i < fieldsCSV.size(); i++)
    {
        if (fieldsCSV[i][0] == '=') 
        {
            fieldsCSV[i] = fieldsCSV[i].substr(1);
            fieldsCSV[i] = calculateFormula(fieldsCSV[i]);
        }

        if (i != 0 && i % (countColumns + 1) == 0)
            lineNumber.push_back(std::stoi(fieldsCSV[i]));
        
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
            fieldsCSV.push_back("///");
            countColumns++;
        }

        

        size_t start;
        size_t end = 0;
        int preEnd = -2;

        while ((start = line.find_first_not_of(devider, end)) != std::string::npos)
        {
            end = line.find(devider, start);
            fieldsCSV.push_back(line.substr(start, end - start));
            countColumns++;
        }
 
        fieldsCSV.push_back("/endLine/");

        countColumnsInRows.push_back(countColumns);
        countRows++;

    }

    auto tempEl = countColumnsInRows[0];
    for (auto el : countColumnsInRows)
    {
        if (!(tempEl == el))
            throw("The format .CSV file is invalid, because the file has different number counter");
        else
            tempEl = el;
    }

    countColumns = countColumnsInRows[0];

    analysisFields();
  
}

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
