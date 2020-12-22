#include <iostream>
#include <string>

#include <fstream> //to work with files
#include <cstddef> // size_t
#include <cstring> //strlen, strcpy
#include <new>


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

struct ScopedPtr
{
    // реализуйте следующие методы:
    //
    explicit ScopedPtr(Expression *ptr = 0) {
        ptr_ = ptr;
    }
    ~ScopedPtr() {
        delete ptr_;
        ptr_ = nullptr;
    }
    Expression* get() const {
        if (ptr_)
            return ptr_;
        else
        {
            return nullptr;
        }
        
    }
     Expression* release() {
         Expression * res = ptr_;
         ptr_ = nullptr;
         return res;
    }
    void reset(Expression *ptr = 0) {
        if (ptr != ptr_)
		{
			delete ptr_;
			ptr_ = ptr;
		}
    }
    Expression& operator*() const {
        return *ptr_;
    }
    Expression* operator->() const {
        return ptr_;
    }


private:
    // запрещаем копирование ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
};

struct SharedPtr {

    explicit SharedPtr(Expression *ptr = 0): ptr_(ptr), counter_(0)
    {
        inc();
    }
    
    ~SharedPtr(){
        dec();
    }
    
    SharedPtr(const SharedPtr & sp): ptr_(sp.ptr_), counter_(sp.counter_) {
        inc();
    }
    
     SharedPtr& operator=(const SharedPtr & sp) {
        if (this != &sp)
        {
            dec();
            ptr_ = sp.ptr_;
            counter_ = sp.counter_;
            inc();
        }
        return *this;
    }
    
    Expression* get() const { 
        return ptr_;
    }
    
    void reset(Expression *ptr = 0) {
        dec();
        ptr_ = ptr;
        inc();
    }
    
    Expression& operator*() const {
        return *ptr_;
    }
    Expression* operator->() const {
        return ptr_;
    }
private:
    size_t * counter_;
    Expression *ptr_;
    void inc() { 
        if (counter_) {
            ++*counter_; 
        } else { 
            if (ptr_) 
                counter_ = new size_t(1); 
        }
    }

    void dec() { 
        if (counter_ && --*counter_==0) {
            if (ptr_)
            {
                delete ptr_;
                ptr_ = nullptr;
            }
            delete counter_;
            counter_ = nullptr;
        }
    }
};


template <typename T>
class Array
{
    T * data_;
    size_t size_;
public:
    explicit Array(size_t size = 0, const T& value = T(0))
    :size_(size){
        data_ = static_cast<T*>(operator new[] (size * sizeof(T)));
        for (size_t i = 0; i < size_; i++)
        {
            new (data_+i)T(value);
        }
    }



    Array(const Array & a)
        :size_(a.size_){
            data_ = static_cast<T*>(operator new[] (a.size_ * sizeof(T)));
            for (size_t i = 0; i < size_; i++)
            {
                new (data_+i)T(a.data_[i]);
            }
    }

    ~Array(){
        for (size_t i = 0; i < size_; i++)
        {
            data_[i].~T();
        }
        
        delete [] (char*) data_;
    }

    
    void swap(Array & a) {
        std::swap(size_, a.size_);
        std::swap(data_,a.data_);
    }
    
    
    Array& operator=(Array const& a){
        if (this != &a)
        {
            Array(a).swap(*this);
            return *this;
        }
    }

    
    size_t size() const{
        return size_;
    }


    T& operator[](size_t i){
        return data_[i];
    }

    const T& operator[](size_t i) const {
        return data_[i];
    }
   
   void prnt()
	 {
		 for (size_t i = 0; i < size_; ++i)
			 cout << *(data_ + i);
		 cout << endl;
	 }
};

template <typename Tx>
struct X
{
	X()
	{
		this->x_ = new Tx();
		*this->x_ = 1;
	}
	X(const X& inX)
	{
		this->x_ = new Tx();  
		*this->x_ = *inX.x_;
	}
	~X() { delete this->x_; }
	friend std::ostream& operator<< (std::ostream& s, const X& obj) 
	{ 
		s << *(obj.x_);
		return s; 
	}
	void set(Tx i)
	{
		*(this->x_) = i;
	}
private:
	X& operator=(const X& inX);
	Tx *x_;
};


/******************************T E S T *********************/
void test0();
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();

int main(int c, char** v)
{
	setlocale(LC_ALL, "");
	test0();
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();

	return 0;
}

void test0()
{
	cout << endl << "*****Test 0(primitives)**********" << endl;
	{
		cout << endl << "*****CHAR**********" << endl;
		Array<char> ar(size_t(5), '0');
		Array<char> x(size_t(4), '4');
		ar = x;
		ar.prnt();

		Array<char> x2(size_t(6), '6');
		ar = x2;
		ar.prnt();
	}
	cout << endl;
	{
		cout << endl << "*****STRING**********" << endl;
		Array<string> cr(size_t(5), "0");
		Array<string> cx(size_t(4), "4");
		cr = cx;
		cr.prnt();

		Array<string> cx2(size_t(6), "6");
		cr = cx2;
		cr.prnt();
	}
	cout << endl;
	{
		cout << endl << "*****INT**********" << endl;
		Array<int> ir(size_t(5), 0);
		Array<int> ix(size_t(4), 4);
		ir = ix;
		ir.prnt();

		Array<int> ix2(size_t(6), 6);
		ir = ix2;
		ir.prnt();
	}
	cout << endl;
	{
		cout << endl << "*****DOUBLE**********" << endl;
		Array<double> dr(size_t(5), 0.0);
		Array<double> dx(size_t(4), 4.0);
		dr = dx;
		dx.prnt();

		Array<double> ix2(size_t(6), 6.0);
		dr = ix2;
		dr.prnt();
	}
	cout << endl;
	return;
}


void test1()
{
	{
		cout << endl << "*****Test 1(assigment)**********" << endl;
		Array<char> ar(size_t(100), '0');
		Array<char> x(size_t(0), '1');
		ar = x;
		ar.prnt();
	}
	{
		cout << "*****STRING**********" << endl;
		Array<string> cr(size_t(100), "Str0");
		Array<string> cx(size_t(0), "Str1");
		cr = cx;
		cr.prnt();

		Array<string> cx2(size_t(2), "Str3");
		cr = cx2;
		cr.prnt();
	}
	{
		cout << "*****INT**********" << endl;
		Array<int> cr(size_t(100), 0);
		Array<int> cx(size_t(0), 15);
		cr = cx;
		cr.prnt();

		Array<int> cx2(size_t(2), 55);
		cr = cx2;
		cr.prnt();
	}
	return;
}

void test2()
{
	cout << endl << "*****Test 2(copy constructor)**********" << endl;
	{
		cout << "*****CHAR**********" << endl;
		Array<char> x(size_t(3), '3');
		Array<char> ar(x);
		ar.prnt();
	}
	{
		cout << "*****STRING**********" << endl;
		Array<string> x(size_t(3), "333");
		Array<string> ar(x);
		ar.prnt();
	}

	return;
}

void test3()
{
	cout << endl << "*****Test 3(Empty)**********" << endl;
	{
		cout << "*****CHAR**********" << endl;
		Array<char> ar(size_t(0), '0');
		ar = ar;
		ar.prnt();
	}
	{
		cout << "*****STRING**********" << endl;
		Array<string> ar(size_t(0), "0");
		ar = ar;
		ar.prnt();
	}
	return;
}

void test4()
{
	cout << endl << "*****Test 4(assigment A=A) **********" << endl;
	{
		Array<char> ar(size_t(4), '0');
		ar = ar;
		ar.prnt();
	}
	return;
}
void test5()
{
	cout << endl << "*****Test 5(out bound)**********" << endl;
	{
		cout << "*****more**********" << endl;
		Array<char> ar(size_t(4), '0');
		cout << ar[10] << endl;
	}
	{
		cout << "*****less**********" << endl;
		Array<char> ar(size_t(4), '0');
		cout << ar[-10] << endl;
	}
	return;
}

void test6()
{
	cout << endl << "*****Test 6(pointer)**********" << endl;
	{
		cout << "*****CHAR(copy)**********" << endl;
		Array<char> *ar = new Array<char>(size_t(4), '4');
		ar->prnt();
		delete ar;
	}
	{
		cout << "*****CHAR(=)**********" << endl;
		Array<char> *ar = new Array<char>(size_t(5), '5');
		ar->prnt();
		Array<char> *xr = ar;
		xr->prnt();
		delete ar;
	}
	return;
}
void test7()
{
	cout << endl << "*****Test 7(X-object)**********" << endl;
	{
		cout << "***** X<INT> **********" << endl;
		X<int> x;
		x.set(4);
		Array<X<int> > *ar = new Array<X<int> >(size_t(4), x);
		ar->prnt();
		delete ar;
	}
	{
		cout << "***** X<CHAR> (new, =, copy) **********" << endl;
		X<char> x;
		x.set('c');
		Array<X<char> > *ar = new Array<X<char> >(size_t(4), x);
		ar->prnt();
		Array<X<char> > *xr = ar;
		xr->prnt();
		Array<X<char> > y(*xr);
		y.prnt();
		delete ar;
	}
	{
		cout << "***** X<STRING> (new, =, copy)**********" << endl;
		X<string> x;
		x.set("There are no tests for this task");
		Array<X<string> > *ar = new Array<X<string> >(size_t(1),x );
		ar->prnt();
		Array<X<string> > *xr = ar;
		xr->prnt();
		Array<X<string> > y(*xr);
		y.prnt();
		delete ar;
	}
	return;
}
