#include <iostream>

using namespace std;

char *resize(const char *str, unsigned size, unsigned new_size)
{
	char * res = new char[new_size];
    int temp_size = size;
    if (new_size<size)
    {
        temp_size = new_size;
    }
    
    for (const char * p = str; p < str + temp_size; ++p)
    {
        res[p-str] = *p;
    }  
    delete [] str;
    return res;
}


int main()
{
    int * n = new int(5);
    cout << *n << " " << n << endl;
    delete n;
    n = new int[1000];
    delete n;
}