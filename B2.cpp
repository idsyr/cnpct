0100
семантическое значение
value type - диапазон значений
имя
object type - совокупность операций
статическая типизация - тип связан с именем
адрес
CHAR_BIT char минимально адресуемая ячейка

int x, y;
int &xref = x;
xref = y;
int *xptr = &xref;
int &*xrefptr = &xref;//!
int *&xptrref = xptr;

int x;
int &y = x;
int[2] = {10, 20};
int &xref = x[0];
int* xptr = &x[0];
xref += 1;
xptr += 1;
assert(xref  == 11);
assert(*xptr == 20);

const char* &s1;
char const* $s2;
char* const s3;
cahr const * const s4;
char &r1 = r;
const char &r2 = r1;

int foo(const int *p){int t = *p; delete p; return t;}
int bar(const int &p){return p;}
foo(nullptr);//!bar
double d = 2.0;
int *q = *reinterpret_cast<int **>(&d);
foo(q);//!bar

int foo(){return 42;}
const int &l = foo();
c-инкапсуляция: обьект на стеке, проблемы с инлайном
инкапсуляция - сохранение инварианта класса
модификатор на имена данных
консистентное состояние
ссылка - инкапсуляция указателя
инкапусуляция это свойство типа:
(использовать имена внутри методов типа)
template <typename T> class list_t{
    node_t<T> *top_, *back_;
public:
    void concat_with(list_t<T> other){
        for(auto cur = other.top_;//такого же типа, он открыт. С другим параметром другой тип
            cur!=other.back_;
            cur = cur->next_)
        push(cur->data_); 
    }
};
теперь важны конструкторы

