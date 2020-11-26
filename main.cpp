#include <iostream>
#include <string>

#include <fstream> //to work with files
#include <cstddef> // size_t
#include <cstring> //strlen, strcpy

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

struct String
{
    String(const char *str = ""){
        if (str != 0)
        {
            this->size = strlen(str);
            this->str = new char[this->size+1]; 
            strcpy(this->str,str);
            this->str[this->size] = '\0';
        } 
        else 
        {
            this->size = 0;
        }
    }

    String(size_t n, char c)
    {
        this->str = new char[this->size+1]; 
        for (size_t i = 0; i < n; i++)
        {
            this->str[i] = c;
        }
        this->str[n] = '\0';
        this->size = n;
    }

    ~String(){
        if (this->str != 0)
        {
            delete [] this->str;
            this->size;
        }
    }


    size_t size;
    char  *str;

    void append(String &s)
    {
        
        if (s.size == 0)
            return;
        if (this-> size == 0) {
            delete [] this->str;
            this-> str = new char[s.size+1];
            strcpy(this->str,s.str);
            this->size = s.size;
            return;
        }
        char* temp1 = new char[this->size+1];
        char* temp2 = new char[s.size+1];
        strcpy(temp1,this->str);
        strcpy(temp2,s.str);
        size_t new_length = this->size + s.size;
        delete [] this->str;
        this->str = new char[new_length+1];
        strcpy(this->str, temp1);
        strcat(this->str,temp2);
        delete [] temp1;
        delete [] temp2;
        this->size = new_length;
    }
};



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
   const size_t ntest = 10;
    
    std::string tests[ntest][2] = {
                                {"", ""},
                                {"", "test"},
                                {"test", ""},
                                {"test", "test"},
                                {"Hello ", " world!"},
                                {"Supercalifragilistic", "expialidocious"}
                              };
    
    for (size_t i=0; i<ntest; ++i) {
        String t1(tests[i][0].c_str());
        String t2(tests[i][1].c_str());
        
        t1.append(t2);
        
        std::string res(t1.str);
        if (res != tests[i][0]+tests[i][1]) {
            std::cout << "Test " << i+1 << " failed!" << std::endl;
            std::cout << "Must be " << tests[i][0]+tests[i][1] << std::endl;
            std::cout << "But result is " << res << std::endl;
        } else {
            std::cout << "Test " << i+1 << " passed!" << std::endl;
        }
        
    }
    
    
    std::string last = "Same pointer test";
    String t(last.c_str());
    cout << t.str << endl;
    t.append(t);
    
    std::string res(t.str);
    cout << t.str <<endl;
    if (res != last+last) {
        std::cout << "Test " << ntest+1 << " failed!" << std::endl;
        std::cout << "Must be " << last+last << std::endl;
        std::cout << "But result is " << res << std::endl;
    } else {
        std::cout << "Test " << ntest+1 << " passed!" << std::endl;
    }
        
    return 0;
}
