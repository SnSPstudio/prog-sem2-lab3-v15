
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool check_file(string f_name) {
    
    int size_w, size_h;
    int i = 0;
    int temp;
    char symb = ' ';
    

    ifstream ifs(f_name);
    if (!ifs.is_open()) {
        cout << "\nОшибка открытия файла \'"<<f_name<<"\'.\n";
        return false;
    }  
    while (symb == ' ') {
        symb = ifs.get();
        if (ifs.eof()) {
            cout << "\nФайл пуст.\n";
            return false;
        }
    }
    ifs.clear();
    ifs.seekg(0);
    ifs >> size_w;
    
    if (ifs.eof()) {
        cout << "\nВ файле нет данных.\n";
        return false;
    }
    ifs >> size_h;
   
    do {
        if (ifs.fail()) {
            cout << "\nВ файле обнаружены недопустимые символы.\n";
            return false;
        }
        i++;
        ifs >> temp;
    } while (!ifs.eof());

    if (i != size_w * size_h) {
        cout << "\nРазмеры матрицы в файле \'" << f_name << "\' заданы неверно\n";
        return false;
    }
    if ((size_w<1)||(size_h<1)) {
        cout << "Размер матрицы должен быть больше либо равен 1*1\n";
        return false;
    }
    ifs.clear();
    ifs.close();    
    return true;
}

int** input(string f_name) {
    
    
    int size_w, size_h;
    int** matrix;
    ifstream ifs(f_name);
    ifs >> size_w;
    ifs >> size_h;
    matrix = new int*[size_w+1];

    matrix[0] = new int[2];
    for (int i = 1; i <= size_w; i++) {
        matrix[i] = new int[size_h];
    }
    
    matrix[0][0] = size_w;
    matrix[0][1] = size_h;

    for (int i = 1; i <= size_w; i++) {
        for (int j = 0; j < size_h; j++) {
            ifs >> matrix[i][j];
            //cout << matrix[i][j] << ' ';
        }
        //cout << endl;
    }
    
    ifs.clear();
    ifs.close();
    return matrix;
}

int* sum(int** matrix) {

    int* sum_el;    
    int size_w = matrix[0][0];
    int size_h = matrix[0][1];
    sum_el = new int[size_w];

    for (int i = 1; i <= size_w; i++) {
        sum_el[i-1] = 0;
        for (int j = 0; j < size_h; j++) {
            sum_el[i-1] += matrix[i][j]; 
        }
        cout << "Сумма элементов " << i << "-ой строки:"<< sum_el[i-1] << endl;
    }
    cout << endl;
    return sum_el;
}

int sum_max(int *sum_el) {
    int max_s;
    int size = sizeof(sum_el);

    max_s = sum_el[0];

    for (int i = 0; i < size; i++) {
        if (max_s <= sum_el[i]) {
            max_s = sum_el[i];
        }
    }
    cout << "Максимальная сумма = " << max_s << endl;
    return max_s;
}

void print_matrix(int** matrix) {

    int size_w = matrix[0][0];
    int size_h = matrix[0][1];

    for (int i = 1; i <= size_w; i++) {
        for (int j = 0; j < size_h; j++) {
            cout << matrix[i][j]<< ' ';
        }
        cout << endl;
    }
    cout << endl;
}


int main()
{
    setlocale(LC_ALL, "Russian");

    int **matrix1;
    int **matrix2;
    int err_code = 0;



    int size_w1 = 0;
    int size_h1 = 0;

    int size_w2 = 0;
    int size_h2 = 0;

    const char file_matr_1[] = "correct_01 (1).txt";
    const char file_matr_2[] = "correct_01 (2).txt"; 

    //const char file_matr_1[] = "correct_02 (1).txt";
    //const char file_matr_2[] = "correct_02 (2).txt"; 
      

    //const char file_matr_1[] = "incorrect_01(1).txt";   //Файл пуст
    //const char file_matr_2[] = "incorrect_01(2).txt";   

    //const char file_matr_1[] = "incorrect_02(1).txt"; //одни пробелы да новые строки
    //const char file_matr_2[] = "incorrect_02(2).txt";

    //const char file_matr_1[] = "incorrect_03(1).txt"; //Есть недопустимые символы
    //const char file_matr_2[] = "incorrect_03(2).txt";

    //const char file_matr_1[] = "incorrect_04(1).txt"; //Некорректные размеры матрицы
    //const char file_matr_2[] = "incorrect_04(2).txt"; 

    if (check_file(file_matr_1)) {
        cout << "Первая матрица:" << endl;    //Начало работы с перво матрицей

        matrix1 = input(file_matr_1);         //Считываем матрицу 1

        print_matrix(matrix1);                //Печать матрицы

        int* sum1;                            //Массив с суммами строк
        int max_sum1;
                    
        sum1 = sum(matrix1);                  //Суммирование элементов строк матрицы
        max_sum1 = sum_max(sum1);             //Поиск максимального значения
        
    }
    else {
        cout << "\nВ файле с матрицей 1 обнаружены ошибки. (см. выше) \nПереход к следующей матрице\n\n\n";
    }

    
    if (check_file(file_matr_2)) {
        cout << "Вторая матрица:" << endl;
        matrix2 = input(file_matr_2);   //Считываем матрицу 2
        print_matrix(matrix2);

        int max_sum2;
        int* sum2;
        sum2 = new int[size_w2];

        sum2 = sum(matrix2);

        max_sum2 = sum_max(sum2);
    }
    else {
        cout << "\nВ файле с матрицей 2 обнаружены ошибки. (см. выше)\n\n";
    }
    return 0;
}