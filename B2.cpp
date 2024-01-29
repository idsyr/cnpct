----------------------------------------------------| Genesis |---------------------------------------------
	0100
->семантическое значение 4
->value диапазон         -7_8  
->имя                    a


vaule type - диапазон значений
object type - совокупность операций


статическая типизация - тип не связан с конкретной ячейкой, навсегда связан с именем


адрес, тип адреса - указатель


CHAR_BIT char минимально адресуемая ячейка
nullptr важен из за перегрузок
p[2] == *(p + 2) //2[p]

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++










----------------------------------------------------| lvalue ref |---------------------------------------------
ссылки - инкапсуляция указателя
int x; int &y = x; //another name


int x[2] = {10, 20};
int &xref =  x[0]; xref += 1;
int* xptr = &x[0]; xptr += 1;
assert(xref  == 11); assert(*xptr == 20);


int x, y;
int &xref = x;
int* xptr = &xref;
int &*xrefptr = &xref;//ошибка, ссылки не имеют адреса
int* &xptrref = xptr;


const char* &s1; char const* $s2;
char* const s3; //error
char const * const s4; //error


char &r1 = r;
const char &r2 = r1;


const ref with rvalue create temp object
int foo(){return 42;}
const int &l = foo();


out arg is bad


int foo(const int *p){int t = *p; delete p; return t;}
int bar(const int &p){return p;}


foo(nullptr);//!bar


double d = 2.0;
int *q = *reinterpret_cast<int **>(&d);
foo(q);//!bar
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++










-------------------------------------------------| Инкапсуляция |---------------------------------------------
инкапсуляция - сохранение инварианта класса(избежание неконсистентного состояния)
c   инкапсуляция(header have struct declaration): обьект на стеке не создать, проблемы с инлайном
с++ инкапсуляция: модификаторы private public определяют доступ к именам, а не сокрытие данных

инкапусуляция это не свойство обьекта типа, это свойство типа:
template <typename T> class list_t{
    node_t<T> *top_, *back_;
public:
    void concat_with(list_t<T> other){
        for(auto cur = other.top_;//такого же типа, поле top_ обьекта other открыто
            cur!=other.back_;
            cur = cur->next_)
        push(cur->data_); 
    }
    template<typename U> 
    void concat_with(list_t<U> other){
        for(auto cur = other.top_;//нарушение инкапсуляции, тип иной
            cur!=other.back_;
            cur = cur->next_)
        push(cur->data_); 
    }
};

использование имен внутри методов типа







