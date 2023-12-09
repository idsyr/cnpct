resource aquisition is init
S *p = new S;
foo(p); //delete p;
delete p;
кто выделяет и освобождает
goto break continue
template<typename S> class ScopedPointer{
    T* ptr_;
public:
    ScopedPointer(T* ptr = nullptr):ptr_(ptr){}//implicit!
    ~ScopedPointer(){delete ptr_;}
}
//copy assign

ScopedPointer(const ScopedPointer& rhs):
ptr_(new T{&rhs.ptr_}){}

T& access(){return *ptr_;}
const T& access() const {return *ptr_;}
//int x = p.access().x; 

T& operator*(){return *ptr_;}
//and const variant
//(*p).x

T* operator->(){return ptr_;}//drill down behavior


S *a = new S(1), *b = newS(2);
std::swap(a, b);

ScopedPointer<S> x{new S(1)}, y{mew S(2)};
std::swap(x, y);

int&& y = x+1;//in memory
std::move

int x = 4;
int &&y = x+1;
std::cout<<&x<<" "<<&y<<std::endl;
int &&z = std::move(x);
z = z+1;
y = y+1;
std::cout<<x<<" "<<y<<std::endl;

struct S{
    int n = 0;
    int& access(){return n;}
};
S x;
int& y = x.access();
int& z = S{}.access();

struct S{
    int foo()&;
    int foo()&&;
}
(время жизни продлено на фрейме вызванной)
int& foo(int& x) {return x;} //ok
const int& bar(const int& x) {return x;} //temp -> dangle
int&& buz(int&& x) {return std::move(x);} //dangle, after fun ret, temp obj get dstr
int& bat(int&& x){return x;}//temp -> dangle

template <typename T> class ScopedPointer{
T* ptr_;
public:
ScopedPointer(scopedPointer&& rhs) : ptr_(rhs.ptr_){
    rhs.ptr_ = nullptr
}
ScopedPointer(const ScopedPointer):ptr_(new T{*rhs.ptr_}){}
}

ScopedPointer& operator=(ScopedPointer&& rhs){
    if(this==&rhs) return *this;
    std::swap(ptr_, rhs.ptr_);
    return *this;
}

int x = 1;
int a = std::move(x);
assert(x==b);

ScopedPointer y{new int(10)};
ScopedPointer b = std::move(y);
assert(y == b); //operator==, ScopedPointer(ScopedPointer&&)
//правило 5
//srp + правило 0

row major order(c++) for jagged arrays
coumn major order(fortran)

extern int *a;
extern int b[];
i = a[5];
i = b[5];


