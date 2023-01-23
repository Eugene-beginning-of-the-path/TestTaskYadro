#include <vector>
#include <string>
#include <fstream>

namespace pars
{
    class parsingCSV
    {
    private:
        std::fstream fileRead;
        const std::string nameFile;
        std::vector<std::string> fieldsOfCSV;
        std::vector<int> countColumnsInRow;
        //std::size_t countColumn;

        void replaceByValue(std::string& operand);

        std::string calculateFormula(std::string fieldFormula);

        //������ ���� ����� ��������, ���������� �� ����� .CSV, ����������� �� ��� ������� �
        //�����������, � �������, ���� ��� ������� ��� �������� �������� ����
        void analysisFields();



    public:
        parsingCSV(std::string nameFile);


        void parsingLinesCSV(const char devider = ',');

        //����� ��� ������������� ������������ ����� �� ����� .CSV 
        void showFields() const;

    };
}
