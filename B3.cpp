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
//24:25





