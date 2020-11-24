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

/* somebody's solution */
char *resize2(const char *str, unsigned size, unsigned new_size)
{
	char *new_str = new char[new_size];
    int min = size < new_size ? size : new_size;
	for (int i = 0; i < min; new_str[i] = str[i], ++i);
	delete[] str;
	return new_str;
}

// using built-in algorithm
char* resize3(const char* mem, unsigned size, unsigned new_size)
{
	char* new_mem = new char[new_size];
	std::copy(mem, mem + std::min(size, new_size), new_mem);
	delete[] mem;
	return new_mem;
}

int main()
{
    int * n = new int(5);
    cout << *n << " " << n << endl;
    delete n;
    n = new int[1000];
    delete n;
    cout << "test\n";
    //test
}
