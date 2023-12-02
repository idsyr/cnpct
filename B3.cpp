const& продлевает жизнь rvalue
контекст может инкапсулировать внутри себя данные
в линейной модели памяти сокрытие это механизм абстракции
сохранение инварианта
выполняется на протяжении жизни обьекта
new, new type[n], delete, delete[]
gdb: tui enable
x/20x T
x/20x T-2
int* p =new int[5];
int &x = p[3];
scope
lifetime

int a = 2;
void foo(){
    int b = a+3; int *pc;
    if(b>5){
        int c = (a+b)/2; pc = &c;
    }
    b+=*pc; //!
}


int *p = new int[5];
int &x = p[3];
delete[] p;
x+=1; //!


int& foo(){
    int x = 42;
    return x;
}
int x = foo(); //!


const int &lx = 0;
int x = lx; //ok
int foo();
const int &ly = 42 + foo();//int& const int&! 
int y = ly; //ok



struct S{
    int x;
    const int &y;
}
S x{1,2};
S *p = new {1,2};//!

int foo(int &x);
foo(1);//!
int &x - 1;//!

decaying
void foo(int *);
int arr[5];
int* t = arr + 3;//ok
foo(arr);//ok
arr = t;//!

lvalue rvalue
location value
y = x;
int& foo();//can be ok
foo() = x;//ok

void (*bar(int x, void (*func)(int&)))(int&);
typedef void (*ptr_to_fref)(&int&);
ptr_to_fref bar(int x, ptr_to_fref func);

using ptr_to_fref = void (*)(int&);
for template

Манглирование
гарантия имен, нет неявных ссылок
extern "C"

правила перегрузки
name resolutuion
float sqrt(float x);
double sqrt(double x);
sqrt(42);//!

int x;
int foo(){return ::x;}
namespace{
    int foo(){return 42;}
}
сложное уникальное имя и его using
видно только внутри модуля
никто не напишет extern foo как со static

не засорять глобальное пространство имен
никогда не писать using namespace в заголовочных файлах
использовать анонимное пространства имен вместо статических функций
не использовать анонимные прсотранства имен в заголовочных файлах
