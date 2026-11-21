#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;

// спеціальність студента
enum Specialnist { KOMP_NAUKY, INFORMATYKA, MAT_TA_EKON, FIZ_TA_INF, TRUD_NAVCH };

// відомості про студента
struct Student
{
    string      prizv;        // прізвище
    int         kurs;         // курс
    Specialnist spec;         // спеціальність
    int         fizyka;       // оцінка з фізики
    int         matematyka;   // оцінка з математики
    union                     // третя оцінка – залежить від спеціальності:
    {
        int prohramuvannya;   // «Комп'ютерні науки» – з програмування
        int chyselni_metody;  // «Інформатика» – з чисельних методів
        int pedahohika;       // інші спеціальності – з педагогіки
    };
};

void   Create(Student* p, const int N);
void   Print(Student* p, const int N);
string SpecStr(const Specialnist spec);
int    CountProhramuvannyaMark(Student* p, const int N, const int mark);
double PercentPhysMathFourOrFive(Student* p, const int N);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів N: "; cin >> N;
    cout << endl;

    Student* p = new Student[N];   // динамічний масив структур

    Create(p, N);
    Print(p, N);

    //кількість оцінок «5», «4», «3» з програмування
    cout << "Кількість оцінок з програмування:" << endl;
    cout << "   «5»: " << CountProhramuvannyaMark(p, N, 5) << endl;
    cout << "   «4»: " << CountProhramuvannyaMark(p, N, 4) << endl;
    cout << "   «3»: " << CountProhramuvannyaMark(p, N, 3) << endl;
    cout << endl;

    //процент студентів з оцінками «4» або «5» і з фізики, і з математики
    cout << "Процент студентів, які отримали і з фізики, і з математики оцінки «4» або «5»: "
        << PercentPhysMathFourOrFive(p, N) << "%" << endl;

    delete[] p;
    return 0;
}

// Формування масиву структур: введення даних з клавіатури
void Create(Student* p, const int N)
{
    int spec;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        cin.get();  // очищення буферу клавіатури – бо залишаються символи
        cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

        cout << "     прізвище: ";             getline(cin, p[i].prizv);
        cout << "     курс: ";                 cin >> p[i].kurs;
        cout << "     спеціальність (0 - Комп'ютерні науки, 1 - Інформатика," << endl
            << "                    2 - Математика та економіка, 3 - Фізика та інформатика," << endl
            << "                    4 - Трудове навчання): ";
        cin >> spec;
        p[i].spec = (Specialnist)spec;
        cout << "     оцінка з фізики: ";      cin >> p[i].fizyka;
        cout << "     оцінка з математики: ";  cin >> p[i].matematyka;

        // третя оцінка залежить від спеціальності
        switch (p[i].spec)
        {
        case KOMP_NAUKY:
            cout << "     оцінка з програмування: "; cin >> p[i].prohramuvannya;
            break;
        case INFORMATYKA:
            cout << "     оцінка з чисельних методів: "; cin >> p[i].chyselni_metody;
            break;
        case MAT_TA_EKON:
        case FIZ_TA_INF:
        case TRUD_NAVCH:
            cout << "     оцінка з педагогіки: "; cin >> p[i].pedahohika;
            break;
        }
        cout << endl;
    }
}

// Назва спеціальності за значенням переліку
string SpecStr(const Specialnist spec)
{
    switch (spec)
    {
    case KOMP_NAUKY:  return "Комп'ютерні науки";
    case INFORMATYKA: return "Інформатика";
    case MAT_TA_EKON: return "Математика та економіка";
    case FIZ_TA_INF:  return "Фізика та інформатика";
    case TRUD_NAVCH:  return "Трудове навчання";
    }
    return "";
}

// Вивід масиву структур у вигляді таблиці (із заголовком і шапкою)
void Print(Student* p, const int N)
{
    cout << "==============================================================================================================================" << endl;
    cout << "|                                                      СПИСОК СТУДЕНТІВ                                                      |" << endl;
    cout << "==============================================================================================================================" << endl;
    cout << "| №  | Прізвище        | Курс | Спеціальність           | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        // клітинки 1–6: заповнені для студентів усіх спеціальностей
        cout << "| " << setw(2) << right << i + 1 << " "
            << "| " << setw(15) << left << p[i].prizv << " "
            << "| " << setw(4) << right << p[i].kurs << " "
            << "| " << setw(23) << left << SpecStr(p[i].spec) << " "
            << "| " << setw(6) << right << p[i].fizyka << " "
            << "| " << setw(10) << right << p[i].matematyka << " ";

        // клітинки 7–9: заповнена лише одна – залежно від спеціальності
        switch (p[i].spec)
        {
        case KOMP_NAUKY:
            cout << "| " << setw(13) << right << p[i].prohramuvannya << " "
                << "| " << setw(15) << "" << " "
                << "| " << setw(10) << "" << " |" << endl;
            break;
        case INFORMATYKA:
            cout << "| " << setw(13) << "" << " "
                << "| " << setw(15) << right << p[i].chyselni_metody << " "
                << "| " << setw(10) << "" << " |" << endl;
            break;
        case MAT_TA_EKON:
        case FIZ_TA_INF:
        case TRUD_NAVCH:
            cout << "| " << setw(13) << "" << " "
                << "| " << setw(15) << "" << " "
                << "| " << setw(10) << right << p[i].pedahohika << " |" << endl;
            break;
        }
    }
    cout << "==============================================================================================================================" << endl;
    cout << endl;
}

//послідовний пошук – кількість оцінок mark з програмування
int CountProhramuvannyaMark(Student* p, const int N, const int mark)
{
    int k = 0;
    for (int i = 0; i < N; i++)
        if (p[i].spec == KOMP_NAUKY && p[i].prohramuvannya == mark)
            k++;
    return k;
}

//послідовний пошук – процент студентів, які отримали і з фізики, і з математики оцінки «4» або «5»
double PercentPhysMathFourOrFive(Student* p, const int N)
{
    int k = 0;
    for (int i = 0; i < N; i++)
        if ((p[i].fizyka == 4 || p[i].fizyka == 5) &&
            (p[i].matematyka == 4 || p[i].matematyka == 5))
            k++;
    return 100.0 * k / N;
}