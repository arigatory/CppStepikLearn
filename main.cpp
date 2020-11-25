#include <iostream>
#include <string>

//to work with files
#include <fstream>

using namespace std;

char *resize(const char *str, unsigned size, unsigned new_size)
{
    char *res = new char[new_size];
    int temp_size = size;
    if (new_size < size)
    {
        temp_size = new_size;
    }

    for (const char *p = str; p < str + temp_size; ++p)
    {
        res[p - str] = *p;
    }
    delete[] str;
    return res;
}

/* somebody's solution */
char *resize2(const char *str, unsigned size, unsigned new_size)
{
    char *new_str = new char[new_size];
    int min = size < new_size ? size : new_size;
    for (int i = 0; i < min; new_str[i] = str[i], ++i)
        ;
    delete[] str;
    return new_str;
}

// using built-in algorithm
char *resize3(const char *mem, unsigned size, unsigned new_size)
{
    char *new_mem = new char[new_size];
    std::copy(mem, mem + std::min(size, new_size), new_mem);
    delete[] mem;
    return new_mem;
}

char *getline()
{
    int n = 10;
    char *res = new char[n];
    char temp;
    int i = 0;
    temp = '1';

    while (cin.get(temp) && temp != '\n')
    {
        if (i >= n)
        {
            res = resize(res, n, 2 * n);
            n *= 2;
        }
        res[i++] = temp;
    };
    res[i] = '\0';
    return res;
}

int **transpose(const int *const *m, unsigned rows, unsigned cols)
{
    int **res = new int *[cols];
    res[0] = new int[cols * rows];
    for (int i = 1; i != cols; ++i)
    {
        res[i] = res[i - 1] + rows;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            res[j][i] = m[i][j];
        }
    }
    return res;
}

void swap_min(int *m[], unsigned rows, unsigned cols)
{
    int min_row = 0;
    int min_value = m[0][0];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (m[i][j] < min_value)
            {
                min_value = m[i][j];
                min_row = i;
            }
        }
    }
    int *temp = m[0];
    m[0] = m[min_row];
    m[min_row] = temp;
}

void print_matrix(int *m[], const unsigned rows, const unsigned cols)
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
            std::cout << m[i][j] << ' ';
        std::cout << "\n";
    }
}

void input_matrix(int *m[], const unsigned rows, const unsigned cols)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
        {
            std::cout << "Input matrix[" << i << "," << j << "]: ";
            std::cin >> m[i][j];
        }
}

//not recommended
void c_style_string()
{
    char s1[100] = "Hello";
    cout << strlen(s1) << endl;

    char s2[] = ", world!";
    //must be careful, can damage stack
    strcat(s1, s2);

    char s3[6] = {72, 101, 108, 111};
    if (strcmp(s1, s3) == 0)
        cout << "s1 == s3" << endl;
}

void cpp_style_string()
{
    string s1 = "Hello";
    cout << s1.size() << endl;

    string s2 = ", world!";
    s1 = s1 + s2;

    if (s1 == s2)
    {
        cout << "s1 == s2" << endl;
    }
}

void working_with_files()
{
    string name;
    ifstream input("input.txt");
    input >> name;

    ofstream output("output.txt");
    output << "Hi, " << name << endl;
}

int main()
{
    unsigned rows, columns;
    std::cout << "Input number of rows: ";
    std::cin >> rows;
    std::cout << "Input number of columns: ";
    std::cin >> columns;
    int **matrix = new int *[rows];
    for (size_t count = 0; count < rows; count++)
        matrix[count] = new int[columns];
    input_matrix(matrix, rows, columns);
    std::cout << "\nYour matrix is... \n\n";
    print_matrix(matrix, rows, columns);
    std::cout << "\nChange row with first row ... \n\n";
    swap_min(matrix, rows, columns);
    std::cout << "Modified matrix... \n\n";
    print_matrix(matrix, rows, columns);
    std::cout << "\nFree memory... \n";
    for (size_t count = 0; count < rows; count++)
        delete[] matrix[count];
    return 0;
}
