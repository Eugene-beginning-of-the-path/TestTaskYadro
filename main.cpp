#include <iostream>
#include "parsingcsv.h"
//#include <iomanip>


void read_record(std::string nameFile)
{
    pars::parsingCSV pars(nameFile);
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

