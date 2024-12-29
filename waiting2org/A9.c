// Семинар 3.1. Линейный поиск и простые сортировки

#if 0

typedef int* pint_t;
pint_t const x; // int* const x
const pint_t x; // !!!const int* x

void foo(int* arr, unsigned len);
void bar(const int *arr, unsigned len);
void foo(int  arr[], usnigned len); //same
void bar(const int arr[], unsigned len); // same

#endif


unsigned search(const int* parr, unsigned len, int elem);

// Тасование Фищера-Йетса shuffle
// Сортировка вставками
// Сортировка выбором
// Сортировка пузырьком
// O(N^2) потому что принимают только локальные решения



