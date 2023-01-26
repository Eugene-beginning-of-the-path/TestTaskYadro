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
    catch (std::exception& ob)
    {
        std::cout << ob.what() << std::endl;
    }
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

