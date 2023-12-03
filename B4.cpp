search tree
range quires
template <typename C, typename T>
int range_query(const C& s, T fst, T snd){
using itt = typename C::iterator;
itt start = s.lower_bound(fst);
itt fin = s.upper_bound(snd);
return std::distance(s, start, fin);
}
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
    struct Node{
        KeyT key_;
        Node *parent_, *left, *reight_;
        int height_;
    }
    Node n = {key, nullptr, nullptr, nullptr, 0}; //agregate
    Node n = {key};
    Node n {key};
    //private, etc
    struct Node{
        KeyT key_;
        Node *parent_ = nullptr,
             *left_ = nullptr, 
             *right_ = nullptr;
        int height_ = 0;
        Node(KeyT key){key_ = key;}
    }
    Node n(key); //direct old
    Node n{key}; //direct new
    Node k = key;//copy
}

old init
myclass_t m(list_T(), list_t());
myclass_t m{list_T(), list_t()};

struct S{
S() {std::cout<<"default"<<std::endl;}
S(KeyT key){std::cout<<"direct"<<std::endl;}
};
S key_; int val_;
Node(KeyT key, int val){key_ = key; val_ = val;}
//def dir
//key -> ref -> *const
Node(KeyT key, int val) : key_(key), val_(val){}
 

struct Node{
    S key_; T key2_;
    Node(KeyT ket) : key2_(key){}//S,T
};
struct Node{
    S key_ = 1; T key2_;
    Node(KeyT key) : key2_(key){}//st

S key_;
Node(KeyT key = 1) : key_(key) {}
};

делегация конструкторов

~Node(){delete left_; delete right_;}
//on stack? or overflow

SearchTree s;  //def init
SearchTree t{};//def init
int n;  //def init
int m{};//val init
int* p = new int[5]{}; //calloc

class Empty{
Empty& operator=(const Empty&);
}

Copyable a;
Copyable b(a), c{a}; //dir ctr
Copyable d = a;      //copy ctr
a = b; //assignment
d = c = a = b;

template <typename T> struct Point2D{
    T x_, y_;
    Point2D() : default-init x_, default-init y_{}
~Point2D(){}
Point2D(const Point2D& rhs) : x_(rhs.x_), y_(rhs.y_){}
Point2D& operator=(const Point2D& rhs){
x_ = rhs.x_; y_ = rhs.y_; return *this;
}
};
побитовое копирование
Buffer(const Buffer& rhs) = delete;
Buffer(const Buffer& rhs) : 
    n_(rhs.n_), 
    p(new int[n_])
    {std::copy(p_, p_+n_, rhs.p_);}

Buffer& Buffer::operator=(const Buffer& rhs){
n_ = rhs.n_;
delete [] p_;
p_ = new int[n_];
std::copy(p_, p_+n_, rhs.p_);
return *this;
}
a=a;//!
if(this==&rhs) return *this;
heap//!

cv cval
cntr!template

struct foo{
foo(){cout<<"foo()"<<endl;}
foo(const foo&){cout<<"foo(const foo&)"<<endl}
~foo(){cout<<"~foo()"<<endl}
};
foo bar(){foo local_foo; return local_foo;}
int main(){
foo f = bar();
use(f);//void use(foo&);
}

struct MyString{
char *buf_; size_t len_;
explicit MyString(size_t len) : buf_{new char[len]{}}, len_[len]{}
};
void foo(MyString);
foo(42);//ok if !explicit
foo f{2};//ok
foo f = 2;//!

/*explicit*/ operator const char*(){return buf_;}


struct Foo{
Foo(){}
Foo(const Bar &){std::cout<<"Ctor Bar -> Foo"<<std::endl;}
};
struct Bar{
Bar(){}
bar(const Foo&){std::cout<<"Ctor Foo -> Bar"<<std::endl;}
operator Foo(){
std::cout<<"Op Bar -> Foo"<<std::endl;
return Foo();
}
};

int main(){
Bar b;
Foo f1{b}; //dir все конструкторы даже explicit
Foo f2 = b;//cp только implict но еще и Op
}

Стандартные преобразования выигрывают у пользовательских но они у ...

struct Foo{Foo(long x = 0){}};
void foo(int x);
void foo(Foo x);
void bar(Foo x);
void bar(...);
long l; foo(l);// foo(int)
bar(1);//bar(foo)



