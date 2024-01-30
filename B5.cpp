-----------------------------------------------------| Владение ресурсом |---------------------------------------
Владение - выделение и освобождение


S *p = new S;
foo(p); //delete p, ресурс утек
delete p;
-----//не только опасно но и неудобно, потребуется goto cleanup:


goto - произвольный граф, break continue маскируют
goto может пересекать жизнь обьекта
и чтобы не писать goto cleanup используются деструкторы


------------------------------------------------------------| RAII |---------------------------------------------
-----//решение: raii обертка:
template<typename S> class ScopedPointer{
    T* ptr_;
public:
    ScopedPointer(T* ptr = nullptr):ptr_(ptr){}//implicit преобразование из указателя в нас
    ~ScopedPointer(){delete ptr_;}
}
-----//проблемы: 1)копирование 2)присваивание, 3)как сделать что то полезное не дав утечь указателю


-----//1)переложить копирование на T
ScopedPointer(const ScopedPointer& rhs):ptr_(new T{&rhs.ptr_}){}
-----//проблемы: хотелось бы управлять и некопируемыми ресурсами


-----//3) сделать функцию
T& access(){return *ptr_;}
const T& access() const {return *ptr_;}
-----//проблемы: int x = p.access().x; а хотели бы (*p).x


----------------------------------------------| указателе-подобность |--------------------------------------------

-----//3) сделать оператор dereference
T& operator*(){return *ptr_;}
const T& operator*() const {return *ptr_;}
-----//проблемы: int x = (*p).x, а хотели бы p->x


-----//3) сделать оператор ->
T* operator->(){return ptr_;}//drill down behavior спецсемантика
указатель не получить, только поле


----------------------------------------------| семантика перемещения |--------------------------------------------
-----//4)проблема при swap
S *a = new S(1), *b = newS(2);
std::swap(a, b);

ScopedPointer<S> x{new S(1)}, y{mew S(2)};
std::swap(x, y);




-----//методы над rvalues
struct S{
    int n = 0;
    int& access(){return n;}
};
S x;
int& y = x.access();
int& z = S{}.access();//UB
-----//проблема решается lvalue ref аннотацией метода

-----//ref аннотация
struct S{
    int foo()&;
    int foo()&&;
}
T && data() && {return std::move(data_;}



-----//возврат ref (у int другое поведение)
int& foo(int& x) {return x;} //ok
const int& bar(const int& x) {return x;} //if x temp, время жизни продлено на фрейме -> dangle
int&& buz(int&& x) {return std::move(x);} //dangle, after funuction returns, temp object will get destructed, but...
int& bat(int&& x){return x;}//if move arg from parent stack-> !dangle

----------------------------------------------| перемещающие конструкторы |--------------------------------------------
-----//
template <typename T> class ScopedPointer{
	T* ptr_;
public:
	ScopedPointer(scopedPointer&& rhs) : ptr_(rhs.ptr_){rhs.ptr_ = nullptr}
	ScopedPointer(const ScopedPointer):ptr_(new T{*rhs.ptr_}){}
}

-----//
ScopedPointer& operator=(ScopedPointer&& rhs){
    if(this==&rhs) return *this;
    std::swap(ptr_, rhs.ptr_);
    return *this;
}


-----//
int x = 1;
int a = std::move(x);
assert(x==b);

ScopedPointer y{new int(10)};
ScopedPointer b = std::move(y); //как определен
assert(y == b);


//правило 5
//srp + правило 0


row major order(c++)
coumn major order(fortran)


extern int *a;
extern int b[];
i = a[5];
i = b[5];



















int x = 4;
int &&y = x+1;
std::cout<<&x<<" "<<&y<<std::endl;
int &&z = std::move(x);
z = z+1;
y = y+1;
std::cout<<x<<" "<<y<<std::endl;



