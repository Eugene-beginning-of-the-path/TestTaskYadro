#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void showCSV(std::vector<std::string>& filedsOfCsv)
{
    for (size_t i = 0; i < filedsOfCsv.size(); i++)
    {
        std::cout << i << ": " << filedsOfCsv[i] << std::endl;
    }
    std::cout << std::endl;
}

//Функция делит строку line по символу devider, сохраняя слова в wordsOfLine 
void parsingLine(std::string const& line, std::vector<std::string>& wordsOfLine,
    const char devider = ',')
{
    size_t index = line.find(devider);

    if (index == 0) //значит первая ячейка пуста !!!! ,,?
    {
        std::cout << "__the field is NULL" << std::endl << std::endl;
        wordsOfLine.push_back("");
    }

    size_t start;
    size_t end = 0;
    std::vector<std::string> te;
    while ((start = line.find_first_not_of(devider, end)) != std::string::npos)
    {
        end = line.find(devider, start);
        wordsOfLine.push_back(line.substr(start, end - start));
    }

    /*while ((start = lineCSV.find_first_not_of(devider, end)) != std::string::npos)
    {
        end = lineCSV.find(devider, start);
        wordsOfLine.push_back(lineCSV.substr(start, end - start));
    }*/
    
    //элемент контейнера, содержит информацию о том, что предыдущие элементы
    //контейнера были взяты из единой строки .CSV
    wordsOfLine.push_back("/endLine/"); 
}

//Функция делит строку lineCSV, полученную из файла .CSV, по символу devider,
//и сохраняет слова в вектор wordsOfLine
//void parsingCSV(std::string lineCSV, 
//    std::vector<std::string>& wordsOfLine, char devider = ',')
//{    
//
//    parsingLine(lineCSV, wordsOfLine, devider);
//
//    /*for (size_t i = 0; i < wordsOfLine.size(); i++)
//    {
//        std::cout << i << ": " << wordsOfLine[i] << std::endl;
//    }
//    std::cout << std::endl;*/
//}

void read_record(std::string nameFile)
{

    // File pointer
    std::fstream readFile;

    // Open an existing file
    readFile.open(nameFile, std::ios::in);
    if (!readFile.is_open())
    {
        std::cerr << nameFile << " is not opened" << std::endl;
    }
    else
    {
        //подсчитать кол-во строк и столбцов в CSV файле и записать
        //и создать матрицу соответств. размера на основе этих данных 

        //структура для хранения слов в строке
        std::vector<std::string> wordsOfLine;
        std::string line;
        while (!readFile.eof())
        {
            readFile >> line;
            parsingLine(line, wordsOfLine);
        }
        
        showCSV(wordsOfLine);

        
    }

    readFile.close(); 
    
}

int main()
{
    read_record("card.csv");

}

