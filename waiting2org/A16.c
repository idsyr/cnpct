// Семинар 5.1. Строки и символы

// Специальные символы
// <ctype.h> <ctype.h>

// ASCI
// nullterm
// litetral - nameless constant

#include <malloc.h>
#include <ctype.h>
#include <string.h>

int main(){
	char const * cinv = "Hello, world"; // global
	char cmut[] = "Hello, world"; // global or stack
	char *cheap = (char*) malloc(50);
	strcpy(cheap, cinv);

	cheap = cinv;
	cinv = 0;
	cmut = cheap;


	free(cheap);
}

// API для работы с С-строкам

// realloc(void *ptr, size_t new_size);
// int *arr = (int *)malloc(100)
// narr = (int *) realloc(arr, 1000);

// Мнемоника, Операнды - регистры, имидеаты
// add                   r0, r1,   14
// Задача лексического анализа 

// Union

// Enum

#include <time.h>

enum DTS { DT_DAY = 0, DT_TIME };

struct DT {
	enum DTS what;
	union DayOrRIme{
		int day;
		time_t time;
	} u;
};

#if 0
typedef enum mnem      {ADD = 0, OR, AND} mnem_t;
typedef enum oper_type {REG = 0, IMID} oper_type_t;
typedef enum reg       {R0 = 1, R1, R2} reg_t;

typedef struct lexem {
	mnem_t mnemo;
	struct {
	oper_type_t oper_type;
		union {
			reg_t reg;
			int imid;
		};
	} op1, op2, op3;
} lexem_t;
#endif

typedef enum lexem_type{
	MNEMON = 0,
	REGIST,
	IMIDEAT,
} lexem_type_t;
typedef enum mnemon{
	ADD = 0,
	OR,
	AND,
} mnemon_t;
typedef enum regist{
	R0 = 0,
	R1,
	R2,
	R3,
	R4,
} regist_t;

typedef struct lexem {
	lexem_type_t lexem_type;
	union {
		mnemon_t mnemon;
		regist_t regist;
		int      imideat;
	};
} lexem_t;

