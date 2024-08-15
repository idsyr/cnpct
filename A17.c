// Семинар 5.2. Регулярные выражения и автоматы

// {a,b,c}      - alphbet
// {a, a, c, b} - string

// concat w = aacb z = ba wz = aaxbba
// pow w^3 = www

// Принадлежность
// Порождение
// Эквивалентность
// Отрицание


// Q = {1, 2}
// S = {a, b}
// q0 = 1
// F = {2}
// P = {{{1,a},1}, {{1,b}, 2}, {{2, a}, 1}, {{2,b}, 2}}

// Работа с регулярными языками описывается регулярными выражениями

// a.c  ->  abc aac acc
// [azs] -> a z c
// [a-z] -> any a-z
// [^a-c] -> any not a-c
// ^abc, bcd$ -> abcd
// ab*c -> abc abbc abbbc
// a\{3\} -> aaa
// a\{3,\} -> aaa aaaa ...
#if 0
#include <regex.h>
#include <stdlib.h>
#include <stdio.h>

const char *cregex = "^[[:alnum:]]";
const char *cline = "abracadabra";

int main(){
	int res;
	regex_t regex;
	regcomp(&regex, cline, 0);
	res = regexec(&regex, cline, 0, NULL, 0);
	if(res == 0)
		puts("Match");
	if(res == REG_NOMATCH)
		puts("NO match");
	regfree(&regex);
}
#endif
// Эпсилон переход
// Алгоритм Рабина Скота NFA -> DFA
// Машины Тьюринга
// Лемма о накачке w = xyz -> xy^nz

// Алгоритм Кнута Морриса Прата - поиск подстроки
// Префиксная функция для needle дает автомат перехода позиции
// Найденной подстроки

#if 0
void copy(int *to, int const *from, int count){
	int n = (count + 3) / 4;
	switch(count%4){
		case 0: do { *to++ = *from++;
		case 3:      *to++ = *from++;
		case 2:      *to++ = *from++;
		case 1:      *to++ = *from++;
		        } while (--n > 0);
	}
}
#endif

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MATCHES 10

int main(){
	regex_t regex;
	int res;
	char BUFFER[128];
	const char* sz1 = "hello world test";
	const char* pattern1 = "wo.*d";
	regmatch_t matches[MAX_MATCHES];

	res = regcomp(&regex, pattern1, REG_EXTENDED);
	if(res) {
		regerror(res, &regex, BUFFER, sizeof(BUFFER));
		fprintf(stderr, "Regex match failed: %s\n", BUFFER);
		exit(EXIT_FAILURE);
	}
	printf("Nsubs = %zu\n", regex.re_nsub);

	res = regexec(&regex, sz1, MAX_MATCHES, matches, 0);

	if(!res){ for(size_t i = 0; i <= regex.re_nsub; i++){
			char buff[20] = "";
			printf("szso[%zu]=%lld\n", i, matches[i].rm_so);
			printf("szeo[%zu]=%lld\n", i, matches[i].rm_eo);
			memcpy(buff,
						 sz1+matches[i].rm_so,
						 matches[i].rm_eo - matches[i].rm_so);
			printf("group[%zu]: [%s]\n", i, buff); 
		}
	} else if (res == REG_NOMATCH)
		puts("NO MATCH");
	else {
		regerror(res, &regex, BUFFER, sizeof(BUFFER));
		fprintf(stderr, "Regex match failed: %s\n", BUFFER);
		exit(EXIT_FAILURE);
	}
	regfree(&regex);
}
