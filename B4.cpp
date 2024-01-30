---------------------------------------| Поисковые деревья |------------------------------------
------//удобны для range queries:
template <typename C, typename T> int range_query(const C& s, T fst, T snd){
	using itt = typename C::iterator;
	itt start = s.lower_bound(fst);
	itt fin = s.upper_bound(snd);
	return std::distance(s, start, fin);
}



-----//Проектирование
namespace Trees{
    template <typename KeyT, typename Comp>
    class SearchTree{
        struct Node;
        using iterator = Node*;
        iterator top_;
    public:
        iterator lower_bound(KeyT key) const;
        iterator upper_bound(KeyT key) const;
        int distance(iterator fst, iterator snd) const;
    public:
        void insert(KeyT key);
    };
}





---------------------------------------| Проектирование узла |------------------------------------
    struct Node{
        KeyT key_;
        Node *parent_, *left, *reight_;
        int height_;
    };
    Node n = {key, nullptr, nullptr, nullptr, 0}; //agregate
    Node n = {key};//остальные нули
    Node n {key};//остальные нули с++11
------//Проблемы:агрегатная инициализация ломается при появлении private и прочего
      


    struct Node{
        KeyT key_;
        Node *parent_ = nullptr,
             *left_   = nullptr, 
             *right_  = nullptr;
        int height_ = 0;
        Node(KeyT key){key_ = key;}
    }
    Node n(key); //direct old
    Node n{key}; //direct new
    Node k = key;//copy init
------//Проблемы: двойной вызов конструктора, конструктор вошел в тело - все поля проинициализированы
------//поле - const ptr


Node(KeyT key, int val = 0) : key_(key), val_(val){} //выполняется в порядке полей в классе


class_c(int a, int b): class_c(int a){}//делегация конструкторов


-----//решение проблемы fun decl
myclass_t m(list_T(), list_t()); >>> myclass_t m{list_T(), list_t()};





------------------------------------------| Value-init |------------------------------------
SearchTree s;   //def init
SearchTree t{}; //def init
int n;          //def init
int m{};        //val init
int* p = new int[5]{}; //calloc



---------------------------------| Копирование и присваивание |------------------------------------
class Empty{Empty& operator=(const Empty&);}//1 байт

Copyable a;
Copyable b(a), c{a}; //прямое конструирование via copy ctor
Copyable d = a;      //копирующее конструирование
d = c = a = b;       //присваивание


------//compiler generate:
template <typename T> struct Point2D{
    T x_, y_;
    Point2D() : default-init x_, default-init y_{}
    ~Point2D(){}
    Point2D(const Point2D& rhs) : x_(rhs.x_), y_(rhs.y_){}
    Point2D& operator=(const Point2D& rhs){
    x_ = rhs.x_; y_ = rhs.y_; return *this;}
};

-----//тонкости
class Buffer{
	int n_; int *p_;
public:
	Buffer(int n): n_(n), p(new int[n]){}
	~Buffer(){delete[] p_;}
	Buffer(const Buffer& rhs) = delete;
	Buffer(const Buffer& rhs) : n_(rhs.n_), p(new int[n_]) {std::copy(p_, p_+n_, rhs.p_);}
	Buffer& operator=(const Buffer& rhs);

}
Buffer& Buffer::operator=(const Buffer& rhs){
	if(this==&rhs) return *this;
	n_ = rhs.n_;
	delete [] p_;
	p_ = new int[n_];
	std::copy(p_, p_+n_, rhs.p_);
	return *this;
}
//Может закончиться куча





cntr!template

---------------------------------| Спецсемантика копирования, RVO |------------------------------------
struct foo{
	foo(){cout<<"foo()"<<endl;}
	foo(const foo&){cout<<"foo(const foo&)"<<endl}//can be foo, foo&, cv cvalific foo&, but cant be foo<U>
	~foo(){cout<<"~foo()"<<endl}
};
foo bar(){foo local_foo; return local_foo;}
int main(){
	foo f = bar();
	use(f);//void use(foo&);
}

---------------------------------| Спецсемантика инициализации, explicit |------------------------------------
-----//обычные конструкторы определяют неявное преобразование типа
struct MyString{
	char *buf_; size_t len_;
	explicit MyString(size_t len) : buf_{new char[len]{}}, len_[len]{}
};
void foo(MyString);
foo(42);//ok if !explicit конструктор



struct Foo{explicit Foo(int x){}};
foo f{2};//ok прямая инициализация
foo f = 2;//! инициализация копированием



-----//преобразование из const char* в нас
struct my_string{
	char *buf_; size_t len_;
	/*explicit*/ operator const char*(){return buf_;}
}


------//конфликты
struct Foo{
	Foo(){}
	Foo(const Bar &){std::cout<<"Ctor Bar -> Foo"<<std::endl;}
};
struct Bar{
	Bar(){}
	bar(const Foo&){std::cout<<"Ctor Foo -> Bar"<<std::endl;}
	operator Foo(){std::cout<<"Op Bar -> Foo"<<std::endl; return Foo();}
};
int main(){
	Bar b;
	Foo f1{b}; //direct-init: все конструкторы даже explicit
	Foo f2 = b;//copy-init: только implict но еще и Op
}

Стандартные преобразования выигрывают у пользовательских но они у ...

struct Foo{Foo(long x = 0){}};
void foo(int x);
void foo(Foo x);
void bar(Foo x);
void bar(...);
long l; foo(l);// foo(int)
bar(1);//bar(foo)



