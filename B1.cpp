---------------------------------| problem |----------------------
struct page{
    int index;
    int sz;
    char *data;
};
void slow_get_page(int n, struct page *p);
---------------------------------| solution |---------------------
solution: cache 
simple: random, LRU(least recently used)
structure: list+hash_map


скрытая реализация (на С это в файле .с)
//list.c
struct list_node_t{
    struct list_node_t *next;
    struct list_node_t *prev;
    struct page_t *data;
};
struct list_t{
    struct list_node_t *top;
    struct list_node_t *back;
};

//list.h
struct list_t *list_create();
int list_size(const struct list_t *lst);
struct page_t *list_back(struct list_t *lst);
void list_pop_back(struct list_t *lst);
void list_push_front(struct list_t *lst struct page_t *q);
void list_move_front(struct list_t *lst, struct page_t *q);
coid lsit_move_upfront(struct list_t *lst, struct list_node_t *p);
void list_free(struct list_t *lst);

//hash_table.c
struct hashmap_entry_t{
    int key;
    list_node_t *node;
};
struct hashmap_node_t{
    struct hashmap_node_t *next
    struct hashmap_entry_t entry;
};
struct hash_t{
    struct hashmap_node_t **htab;
    int len;
};

//hash_table.h
struct hash_t *htable_create(int len);
list_node_t *htable_find(struct hash_t *h, int key);
void htable_insert(struct hash_t *h, int key, struct page_t *data);
void htable_erase(struct hash_t *h, int key);
void htable_free(struct hash_t *h);

struct cache_t *cache_create(int cache_size);
void cache_free(struct cache_t *c);
typedef struct page_t* (*slow_get_page_t)();
bool cache_lookup_update(struct cache_t *c, int ket, slow_get_page_T slow);

//cache.c
struct cache_t{
    int sz;
    struct hash_t hash;
    struct list_t lst;
};

//cache.h
bool cache_lookup_update(struct cache_T *c, int key, slow_get_page_t slow){
    struct list_node_t *pnode = htable_find(c->hash, key);
    if(pnode == nullptr){
        struct hashmap_entry_t newent;
        if(list_size(c->lst) == c->sz){
            int backid = list_back(c->lst)->id;
            htable_erase(c->hash, backid);
            lsit_pop_back(c->lst);
        }
        struct page_t *page = slow();
        lsit_push_front(c->lst, page);
        newent.key = key; 
        newent.node = lsit_begin($c->lst);
        htable_insert(&c->hash, newent);
        return false;
    }
    list_move_upfront(&c->lst, pnode);
    return true;
}
------------------------------------| solution problems |---------------
- изменение типа данных, ключей //void*, macros
- rehash - list, not array

C++ решает эту проблему:
Обьединение_данных_и_методов
Обобщение_типов_и_функций

template<typename T> struct Point{T x, y};
template<typename U> struct Triangle{
    Point<U> pts[3];
    U double_square(); //abs, div for U
}
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++










-------------------------------------| problem |-----------------------
#define MAX(x, y) (((x)>(y)))?(x):(y))
-побочные эффекты
-проблемы с производительностью
Y-------------------------------------| solution |---------------------
std::max
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++










-------------------------------------| problem |-----------------------
void qsort(void* base, size_t num, size_t size, int (*compare)(const void*, const void*));

0) comp inline problem
1) void*
2) size
3) *like object

------------------------------------| solution |-----------------------
template <typename T, typename Comp>
void qsortpp(T* base, size_t size, Comp compare);

template <typename T, typename Comp>
void qsortpp (T* start, T* fin, Comp compare);

template <typename T, typename Comp=std::less>
void qsortpp (It start, It fin, Comp compare);

------------------------------------| solution problems |---------------
должен жить в .h     решение->   explicit instantiate a template funstion
templates increases code size

template <typename T> class... public: void func(T arg){} //declaration in header
template <typename T> void func(T arg){} //definition in cpp
template void func<int>(int arg);        //explicit instantiation in cpp
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++










конструктор это шаг к value semantics - как int, такой же естественный


//jagged_arrays, **
__attribute__((noinline))
// /proc/cpuinfo
// -O1 -g0
//rdi - 1st argument

