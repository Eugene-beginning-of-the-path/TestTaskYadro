Test task of Yadro for __Intern C++__
___
+ __Сборка проекта__
  + Требование к сборке
  + Пример сборки через консоль
+ __Запуск программы__
+ __Описание реализации__
+ __Ошибочные ситуации и выброс исключения__
+ ___Тесты___
___
- [X] __Сборка проекта__:
  
  Сборка проекта осуществляется на [CMake](https://cmake.org/download/). Компилятор должен поддерживать __C++11__.

  1. Скачать репозиторий:
  `$ git clone https://github.com/Eugene-beginning-of-the-path/TestTaskYadro`

  2. В папке проекта создать папку _build_ для сборки проекта и в ней осуществлять дальнейшую сборку:
  `mkdir build && cd build`

  3. Сгенерировать проектные файлы под вашу систему (см. доступные на вашей платофрмы генераторы `cmake --help`): `cmake ..`
  
  4. Осуществить сборку проекта `cmake --build .` 
   
   :heavy_exclamation_mark: Бинарный исполняемый файл после успешной сборки будет находиться в __build/src/csvreader__. В данную директорию поместить .CSV файлы, которые __будут использоваться__ в качестве аргументов. 

___

- [X] __Запуск программы через консоль__:
  
  Предположим, вы хотите передать файл __card.csv__ в программу, убедитесь, что данный файл лежит по пути __TestTaskYadro/build/src/__.

  Вызовите бинарник из папки __TestTaskYadro/build/src/__ и через пробел укажите имя и формат файла, который вы поместили ранее в текущую папку: `./csvreader card.csv`

___

- [X] __Описание реализации__:

> Чтение .CSV файла реализовано через класс __pars::parsingCSV__ из написанной собственноручно статической библиотеки (`#include "parsingcsv.h"`), который параметром конструктора принимает имя файла std::string. 
>
> Интерфейс класса pars::parsingCSV:
> ```C++
> parsingCSV(std::string nameFile);
> void parsingLinesCSV(const char devider = ','); 
> void showFields() const;
> ```
> При вызове метода _parsingLinesCSV()_, переданный в программу файл будет прочтён построчно и пропарсен, далее поля проверяются на "корректность", в противном случае будет брошено и обработано исключение _pars::exc::exceptParsCSV_, итогом обработки будет информирование пользователя текстом соответствующей ошибки, иногда и значением самого поля, которое вызвало к возникновению ошибочной ситуации, в консоли. Далее через _showFields()_ выводятся поля переданного .CSV файла в таком же формате как и в файле, т.е. через запятую, построчно.

___

- [X] __Ошибочные ситуации и выброс исключения__:

> Ниже перечислен ряд ошибочных ситуаций, на которых будет брошено и обработано исключение. В результате обработки, на экран будет выведена информация с причиной прерванности программы, и если причина связана с конкретным полем .CSV файла, будет выведено и соответствующее поле.

Ошибочные ситуации:

1. Поле с формулой содержит ошибку в одном из операндов, который ссылается на несуществущую "ячейку/поле" файла .CSV.
   
| NULL       | A                | B | Cell |
| ------------- |:------------------:| -----:| -----:|
| 1 | 50 | 60 | 70 |
| 2 | 80 | 90 | 10 |
| 3 | __=A1/Cell30__ | 60 | 70 |

> В поле с формулой "=A1/Cell30" операнд __Cell30__ ссылается на существующий столбик __Cell__, но на несуществующую строку __30__.
> 
> Вывод в консоль:
> 
> __Operand of a formula has invalid reference to value__
>
> __The field with problem: Cell30__
   
2. Поле с формулой не содержит операнда.

3. Поле с формулой содержит деление на нуль.

4. Число, отвечающее за нумерацию строки, меньше или равно нулю.

5.  Число, отвечающее за нумерацию строки, повторяется.

6. Файл не открылся, т.е. скорее всего передано неверное имя файла или его расширение.

7. Строки .CSV файла имеют разное кол-во столбцов, т.е. нарушен формат таблицы

___

- [X] __Тесты__:

В папке TestTaskYadro/fileTestsCSV находятся тестовые файлы формата .CSV, над которыми испытал корректность работы программы:

- :heavy_check_mark: current.csv

Содержимое файла current.csv:

,A,B,Cell

1,1,0,1

2,2,=A1+Cell30,0

30,0,=B1+A1,5

| NULL       | A                | B | Cell |
| ------------- |:------------------:| -----:| -----:|
| 1 | 1 | 0 | 1 |
| 2 | 2 | =A1+Cell30 | 0 |
| 30 | 0 | =B1+A1 | 5 |

Вывод в консоль:

> Perpesintation of field .CSV file(current.csv):
> ,A,B,Cell
> 1,1,0,1
> 2,2,6,0
> 30,0,1,5

1. test1.csv

Содержимое файла test1.csv: 

| NULL       | A                | B | Cell |
| ------------- |:------------------:| -----:| -----:|
| 1 | 1 | 0 | 1 |
| 2 | 2 | ___=A1+Cell300___ | 0 |
| 30 | 0 | =B1+A1 | 5 |

Вывод в консоль:

> Information: Operand of a formula has invalid reference to value
>
> The field with problem: Cell300

2. test2.csv

Содержимое файла test2.csv:

| NULL       | A                | B | Cell |
| ------------- |:------------------:| -----:| -----:|
| 1 | 1 | 0 | 1 |
| 2 | 2 | ___=A1Cell30___ | 0 |
| 30 | 0 | =B1+A1 | 5 |

Вывод в консоль:

> Information: The field with formuala has no operand
>
> The field with problem: A1Cell30

3. test3.csv

Содержимое файла test3.csv:

| NULL       | A                | B | Cell |
| ------------- |:------------------:| -----:| -----:|
| 1 | ___0___ | 0 | 1 |
| 2 | 2 | =A1+Cell30 | 0 |
| 30 | 0 | ___=B1/A1___ | 5 |

Вывод в консоль:

> Information: Can not devide by zero
>
>The field with problem: B1/A1

4. test4.csv

Содержимое файла test4.csv:

| NULL       | A                | B | Cell |
| ------------- |:------------------:| -----:| -----:|
| ___-15___ | 1 | 0 | 1 |
| 2 | 2 | =A1Cell30 | 0 |
| 30 | 0 | =B1+A1 | 5 |

Вывод в консоль:

> Information: One of the line numbers is less than or equal to zero

5. test5.csv

Содержимое файла test5.csv:

| NULL       | A                | B | Cell |
| ------------- |:------------------:| -----:| -----:|
| 1 | 1 | 0 | 1 |
| ___30___ | 2 | =A1Cell30 | 0 |
| ___30___ | 0 | =B1+A1 | 5 |

Вывод в консоль:

> Information: One of the line numbers is repeated

6. test6.csv

Содержимое файла test6.csv:

| NULL       | A                | B | Cell |
| ------------- |:------------------:| -----:| -----:|
| 1 | ___0___ | 0 | 1 | ___0___ |
| 2 | 2 | =A1+Cell30 | 0 |
| 30 | 0 | =B1/A1 | 5 | ___11___ |

Вывод в консоль:

>Information: The format .CSV file is invalid, because the file has different number counter
