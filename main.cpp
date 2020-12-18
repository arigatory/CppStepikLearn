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

    String(const String &other) : size(other.size), str(new char[other.size+1])
    {
        strcpy(str,other.str);
    }
    void swap(String &s) {
        size_t const t1 = size;
        size = s.size;
        s.size = t1;

        char * const t2 = str;
        str = s.str;
        s.str = t2;
    }

    String & operator=(String const &other)
    {
        if (this != &other)
        {
            String(other).swap(*this);
        }
        return *this;
    }

    struct Proxy
    {
        Proxy(size_t n, const char *str = ""){
            start_i = n;
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
        ~Proxy()
        {
            if (this->str != 0)
            {
                delete [] this->str;
                this->size;
            }

        }

        String operator[](size_t i) {
            size_t s = i-start_i;
            String res(s,' ');
            strncpy(res.str,this->str,s);
            return res;
        }
        size_t size;
        size_t start_i;
        char *str;
    };
    
    
    Proxy operator[](size_t i) const {
        return Proxy(i,str+i);
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



// Так лучше не делать, но для понимания очень полезно!
/*
 * Класс Cls определен точно таким образом:
 */
struct Cls {
    Cls(char c, double d, int i): c(c), d(d), i(i) {}
    ~Cls(){}
private:
    char c;
    double d;
    int i;
};

struct ClsPubl
{
    ClsPubl(char _c, double _d, int _i): c(c), d(d), i(i) {}
    ~ClsPubl(){}
public:
    char c;
    double d;
    int i;
};



// Эта функция должна предоставить доступ к полю c объекта cls.
// Обратите внимание, что возвращается ссылка на char, т. е.
// доступ предоставляется на чтение и запись.
char &get_c(Cls &cls) {
    void* voidptr = static_cast<void*>(&cls);
    struct ClsPubl * p = static_cast<ClsPubl*>(voidptr);
    return p->c;
}

// Эта функция должна предоставить доступ к полю d объекта cls.
// Обратите внимание, что возвращается ссылка на double, т. е.
// доступ предоставляется на чтение и запись.
double &get_d(Cls &cls) {
    void * voidptr = static_cast<void*>(&cls);
    struct ClsPubl * p = static_cast<ClsPubl*>(voidptr);
    return p->d;
}

// Эта функция должна предоставить доступ к полю i объекта cls.
// Обратите внимание, что возвращается ссылка на int, т. е.
// доступ предоставляется на чтение и запись.
int &get_i(Cls &cls) {
     void * voidptr = static_cast<void*>(&cls);
    struct ClsPubl * p = static_cast<ClsPubl*>(voidptr);
    return p->i;
}

struct Foo {
    void say() const { std::cout << "Foo says: " << msg << "\n"; }
protected:
    Foo(const char *msg) : msg(msg) { }
private:
    const char *msg;
};

struct Foo2 : Foo {
    Foo2(const char *msg) : Foo(msg) { }
};

void foo_says(const Foo& foo) { foo.say(); }

Foo get_foo(const char *msg) {
    return Foo(Foo2(msg));
}


//START of VISITOR TASK

struct Number;
struct BinaryOperation;

struct Visitor {
    virtual void visitNumber(Number const * number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const * operation) = 0;
    virtual ~Visitor() { }
};

struct Expression
{
    virtual double evaluate() const = 0;
    virtual void visit(Visitor * vistitor) const = 0;
    virtual ~Expression() { }
};

struct Number : Expression
{
    Number(double value)
        : value(value)
    {}
    double evaluate() const 
    {
        return this->value;
    }

    double get_value() const { return value; }

    void visit(Visitor * visitor) const { visitor->visitNumber(this); }

private:
    double value;
};

struct BinaryOperation : Expression
{
    BinaryOperation(Expression const * left, char op, Expression const * right)
        : left(left), op(op), right(right)
    { }
    virtual ~BinaryOperation(){
        delete left;
        delete right;
    }
    double evaluate() const 
    {
        if (op == '+') {
            return this->left->evaluate() + this->right->evaluate();
        } else if (op == '-') {
            return this->left->evaluate() - this->right->evaluate();
        } else if (op == '*') {
            return this->left->evaluate() * this->right->evaluate();
        } else if (op == '/') {
            return this->left->evaluate() / this->right->evaluate();
        } 
        return 0;
    }

    Expression const * get_left() const { return left; }
    Expression const * get_right() const { return right; }
    char get_op() const { return op; }

    void visit(Visitor * visitor) const { visitor->visitBinaryOperation(this); }

private:
    Expression const * left;
    Expression const * right;
    char op;
};

//END

struct PrintVisitor : Visitor {
    void visitNumber(Number const * number)
    {
        cout << number->get_value();
    }

    void visitBinaryOperation(BinaryOperation const * bop)
    {
        cout << "(";
        bop->get_left()->visit(this);
        cout << ")" << bop->get_op() << "(";
        bop->get_right()->visit(this);
        cout << ")";
    }
};

struct Rational
{
    Rational(int numerator = 0, int denominator = 1) :
        numerator_(numerator), denominator_(denominator) {};

    void add(Rational rational) {
        numerator_ = numerator_ * rational.denominator_ + rational.numerator_*denominator_;
        denominator_ *= rational.denominator_;
    }
    void sub(Rational rational){
        numerator_ = numerator_ * rational.denominator_ - rational.numerator_*denominator_;
        denominator_ *= rational.denominator_;
    }
    void mul(Rational rational) {
        numerator_ *= rational.numerator_;
        denominator_ *= rational.denominator_;
    }
    void div(Rational rational){
        numerator_ /= rational.numerator_;
        denominator_ /= rational.denominator_;
    }

    Rational operator-() const {return Rational(-numerator_,denominator_); }
    Rational operator+() const {return Rational(numerator_,denominator_); }



    void neg() {
        numerator_ = -numerator_;
    }
    void inv(){}

    double to_double() {
        return numerator_/(double) denominator_;
    }

    Rational & operator+=(Rational const& r) {
        add(r);
        return *this;
    }

    Rational & operator-=(Rational const& r) {
        sub(r);
        return *this;
    }

    Rational & operator*=(Rational const& r) {
        mul(r);
        return *this;
    }

    Rational & operator/=(Rational const& r) {
        div(r);
        return *this;
    }

    friend bool operator==(Rational const& left, Rational const &right){
        return left.numerator_*right.denominator_==left.denominator_*right.numerator_;
    }
    
    friend bool operator<(Rational const& left, Rational const &right){
        if (left.numerator_*left.denominator_>=0)
            if (right.denominator_*right.numerator_>=0)
                return left.numerator_*right.denominator_<left.denominator_*right.numerator_;
            else
                return false;
        else
            if (right.denominator_*right.numerator_<=0)
                return left.numerator_*right.denominator_>left.denominator_*right.numerator_;
            else
                return true;
    }

    private:
    int numerator_;
    int denominator_;
};

bool operator<=(Rational const& left, Rational const &right){
        return !(right<left);
}
bool operator>(Rational const& left, Rational const &right){
        return right<left;
}
bool operator!=(Rational const& left, Rational const &right){
        return !(right==left);
}
bool operator>=(Rational const& left, Rational const &right){
        return !(left<right);
}

Rational operator+(Rational r1, Rational r2) {
    return r1 += r2;
}

Rational operator-(Rational r1, Rational r2) {
    return r1 -= r2;
}

Rational operator*(Rational r1, Rational r2) {
    return r1 *= r2;
}

Rational operator/(Rational r1, Rational r2) {
    return r1 /= r2;
}


int main()
{
    String const hello("hello");
    String const hell = hello[0][4]; // теперь в hell хранится подстрока "hell"
    String const ell  = hello[1][4]; // теперь в ell хранится подстрока "ell"
    cout << hell.str << endl;
    cout << ell.str << endl;
}
