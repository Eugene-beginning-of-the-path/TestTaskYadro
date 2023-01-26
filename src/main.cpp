#include <iostream>
#include "parsingcsv.h"
#include "exceptions.h"

void read_record(std::string nameFile)
{
    try 
    {
        pars::parsingCSV pars(nameFile);
        pars.parsingLinesCSV();
        pars.showFields();
    }
    catch (pars::exc::exceptParsCSV& ob)
    {
        ob.info();
    }
    catch (std::runtime_error& ob)
    {
        std::cout << ob.what() << std::endl;
    }
}

int main(int  argc, char** argv)
{
    read_record(argv[1]);
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

