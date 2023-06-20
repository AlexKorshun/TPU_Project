#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;
int ZAPYAT = 0;
struct StudentRecord {
public:
    StudentRecord(
        string табель,
        string фио,
        string отдел,
       string должность,
        string примечание,
        string время_прохода,
        string направление,
        string событие,
        string объект_прохода
    )
    {
        ТАБЕЛЬ = табель;
        ФИО = фио;
        ОТДЕЛ = отдел;
        ДОЛЖНОСТЬ = должность;
        ПРИМЕЧАНИЕ = примечание;
        ВРЕМЯ_ПРОХОДА = время_прохода;
        НАПРАВЛЕНИЕ = направление;
        СОБЫТИЕ = событие;
        ОБЪЕКТ_ПРОХОДА = объект_прохода;
    }
    void display() {
        cout << "                 ID: " << ТАБЕЛЬ << endl;
        cout << "                ФИО: " << ФИО << endl;
        cout << "              Отдел: " << ОТДЕЛ << endl;
        cout << "          Должность: " << ДОЛЖНОСТЬ << endl;
        cout << "примечание(комната): " << ПРИМЕЧАНИЕ << endl;
        cout << "      Время прохода: " << ВРЕМЯ_ПРОХОДА << endl;
        cout << "        Направление: " << НАПРАВЛЕНИЕ << endl;
        cout << "     Сбытие(да/нет): " << СОБЫТИЕ << endl;
        cout << "                Где: " << ОБЪЕКТ_ПРОХОДА << endl;
        cout << endl;
    }
    string ТАБЕЛЬ;
    string ФИО;
    string ОТДЕЛ;
    string ДОЛЖНОСТЬ;
    string ПРИМЕЧАНИЕ;
    string ВРЕМЯ_ПРОХОДА;
    string НАПРАВЛЕНИЕ;
    string СОБЫТИЕ;
    string ОБЪЕКТ_ПРОХОДА;
};

void displayStudents(vector<StudentRecord>& students) {
    for (auto student : students) {
        student.display();
    }
}
void displayStudentsOnly(vector<StudentRecord>& students,string needly) {
    for (auto student : students) {
        if(student.ФИО==needly) student.display();
    }
}

bool checker(vector<StudentRecord>& students, string place, string name, string path) {
    srand((unsigned)time(NULL));
    setlocale(LC_ALL, "ru");
    for (auto student : students) {
        if (name == student.ФИО) {   
            ofstream fout;
            fout.open(path, ofstream::app);
            if (ZAPYAT == 0) {
                fout << "\n\t{\n\t \"class_id\":" << rand() % 400 << ',' << endl
                    << " \t \"student_id\":" << student.ТАБЕЛЬ << ',' << endl
                    << " \t \"qr_check\":" << 1 << ',' << endl;
                ZAPYAT = 1;
            }
            else {
                fout << "\n\t,{\n\t \"class_id\":" << rand() % 400 << ',' << endl
                    << " \t \"student_id\":" << student.ТАБЕЛЬ << ',' << endl
                    << " \t \"qr_check\":" << 1 << ',' << endl;
            }

            if (place == student.ОБЪЕКТ_ПРОХОДА && student.НАПРАВЛЕНИЕ == "Вход") {
                cout << "\nНА МЕСТЕ";
                fout << "\t \"skud_check\":" << 1  << endl << "\t}";
                fout.close();
                return 1;
            }
            else {
                cout << "\nНЕТУ";
                fout << "\t \"skud_check\":" << 0  << endl << "\t}";
                fout.close();
                return 0;
            }
        }
    }
}

void displayStudentsOnlyStuding(vector<StudentRecord>& students,string needly) {
    for (auto student : students) {
        if    ((student.ОБЪЕКТ_ПРОХОДА[0] == 'У'
            || student.ОБЪЕКТ_ПРОХОДА[0] == 'Н'
            || student.ОБЪЕКТ_ПРОХОДА[0] == 'К') && student.НАПРАВЛЕНИЕ=="Вход" && student.ФИО == needly)
        student.display();
    }
}



string ТАБЕЛЬ;
string ФИО;
string ОТДЕЛ;
string ДОЛЖНОСТЬ;
string ПРИМЕЧАНИЕ;
string ВРЕМЯ_ПРОХОДА;
string НАПРАВЛЕНИЕ;
string СОБЫТИЕ;
string ОБЪЕКТ_ПРОХОДА;
string tempString;
vector<StudentRecord> students;
int main()
{
    time_t now = time(0);
    srand((unsigned)time(NULL));
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, std::size(buf), "%d.%m.%Y", localtime(&tm));
    ifstream inputFile;
    inputFile.open("C:\\temp\\NOVEMBER.csv");
    string line = "";
 
    string path = "C:\\bufer\\";
    path += buf;
    path += ".txt";
    ofstream fout;
    fout.open(path);
    fout << "[";
    fout.close();

    while (getline(inputFile, line) && ВРЕМЯ_ПРОХОДА[0] != '2' && ВРЕМЯ_ПРОХОДА[0] != '9') {
        stringstream inputString(line);
        getline(inputString, ТАБЕЛЬ, ';'); 
        getline(inputString, ФИО, ';');
        getline(inputString, ОТДЕЛ, ';');
        getline(inputString, ДОЛЖНОСТЬ, ';');
        getline(inputString, ПРИМЕЧАНИЕ, ';');
        getline(inputString, ВРЕМЯ_ПРОХОДА, ';');
        getline(inputString, НАПРАВЛЕНИЕ, ';');
        getline(inputString, СОБЫТИЕ, ';');
        getline(inputString, ОБЪЕКТ_ПРОХОДА, ';');
      //  if (ФИО == "Будзиаловский Павел Борисович") {
        StudentRecord student(ТАБЕЛЬ, ФИО, ОТДЕЛ, ДОЛЖНОСТЬ, ПРИМЕЧАНИЕ, ВРЕМЯ_ПРОХОДА, НАПРАВЛЕНИЕ, СОБЫТИЕ, ОБЪЕКТ_ПРОХОДА);
        students.push_back(student);
       
        line = "";
    }

    string Who;
    string Where;

    while (1) {
        cout << "Кого проверить...";
        getline(cin, Who);

        if (Who == "1") break;
        cout << "\nКуда должен был зайти студент?";
        getline(cin, Where);
        checker(students, Where, Who, path);
        cout << endl;
    }
    fout.open(path, ofstream::app);
    fout << "\n]";
    fout.close();
    //displayStudentsOnly(students, Who);
}
