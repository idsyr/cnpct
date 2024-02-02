-----------------------------------------------| Статические функции и друзья |----------------------
template <typename T> class Matrix{
	public:
		Matrix(int cols, int rows, T val = T{});
		template <typename It>
		Matrix(int cols, int rwos, It start, It fin);
};
-----//проблема: как написать конструктор для создания единичной матрицы? Верхнетреугольную?
-----//тегиурующие типы или статические функции
static Matrix eye(int n, int m);


инвариант любого raii класса - ресурсы никому кроме класса не принадлежат - ovnership - выделение и освобождение

----//кроме методов класса доступ к закрытому состоянию есть у статических и дружественных функций:
class S{
	int x = 0;
public:
	int get_x() const {return x;}
	static int s_get_x(const S *s){return s->x;}
	friend int f_get_x(const S *s);
};
int f_get_x(const S *s){return s->x;}

-----------------------------------------------| Проектирование матрицы |-----------------------
-----//srp
template <typename T> struct MatrixBuf{
	MatrixBuf(const Matrix &rhs);
	MatrixBuf(Matrix &&rhs);
	MatrixBuf operator=(const Matrix &rhs);
	MatricBuf operator=(Matrix &&rhs);
	~MatrixBuf();
}
-----//noexcept?
-----//static > global 
-----//binary operator must be out of the class


-----//селекторы
int ncols() const;
int nrows() const;
T trace() const;
bool equal(const Matrix& other) const;
bool less(const Matrix& other) const;
void dump(std::ostream& os) const;


-----//удобные методы
Matric& neagate() &;
Matrix& transpose() &; //change me, variant for return can be in term of this variant
bool equal(const Matrix& other) const;

-----------------------------------------------| Доступ к элементам |-----------------------
-----//индексаторы ходят по два
class Vec{
	Vec_buf<int> vb_;
public:
	int& operator[](int x) {return vb_[x];}
	const int& operator[](int x) const {return vb_[x];} //int op...
};


-----// return int* раскроет внутр структуру матрицы:
ProxyRow operator [](int) const;
struct ProxyRow{
	T* row_;
	const T& operator[](int n) const {return row[n];}
	T& operator[](int n){return row[n];}
};

-----------------------------------------------| unique ptr |-----------------------
C++11: unique_ptr
unique_ptr(unique_ptr& ptr) = delete;
unique_ptr(unique_ptr&& rhs) : ptr_(rhs.ptr_){rhs.ptr_ = nullptr;}
unique_ptr& operator= (unique_ptr &&rhs){swap(*this, rhs); return *this;}

-----//как он удаляет? в scopedpointer был указатель и по нему delete, но здесь все что угодно
auto res = std::make_unique<MyRes>(x, y);// но как? ведь только аргументы конструктора (потом)
std::unique_ptr<MyRes> res{new MyRes(x, y)};

const unique_ptr //блокирует еще и перемещение.

-----------------------------------------------| приведение типов |-----------------------
Типы участвуют в разрешении имен
Типы могут иметь ассоциированное поведение
За счет шаблонной параметризации, типов может быть куда больше, их куда проще порождать из обобщенного кода


float f = 1.0; char x = *((char *)&f + 2); //второй бит, приведение с-style делает много

int x; double y = 1.0; x = static_cast<int>(y);
const int *p = &x; int *q = const_cast<int*>(p);
long long uq = reinterpret_cast<long long>(q);


-----//побитовая реинтерпретация коварна:
float p = 1.0; int n = *reinterpret_cast<int*>(&p); //[basic.lval/11] UB
int m = std::bit_cast<int>(p); или std::memcpy(&m, &p, sizeof(int));


-----//func style cast
int b = int(y);

-----------------------------------------------| целочисленные продвижения |-----------------------
type op fptype => fptype op fptype
type op uns_itype => uns_itype op uns_itype
type op itype => itype op itype
(itype less then int) op (itype less then int) => int op int


-----------------------------------------------| унарный плюс и унарный минус |----------------------
-----//positive hack
struct Foo{operator long(){return 42;}};
void foo(int x); void foo(Foo x);
Foo f; foo(f); foo(+f);

operator in class and out -> win in class













