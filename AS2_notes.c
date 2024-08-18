#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <inttypes.h>

/*
| MOVI | I   | 0IIIIIII |
| ADD  | R,R | 1000RRRR |
| SUB  | R,R | 1001RRRR |
| MUL  | R,R | 1010RRRR |
| DIV  | R,R | 1011RRRR |
| IN   | R   | 110000RR |
| OUT  | R   | 110001RR |
*/

typedef enum { A = 65, B, C, D } registr_t;
typedef enum { MOVI = 0, ADD, SUB, MUL, DIV, IN, OUT } command_type_t;

typedef struct {
	uint8_t opcode  :1;
	uint8_t imideat :7;
} command_reg_load_format;

typedef struct {
	uint8_t opcode  :4;
	registr_t reg_1 :2;
	registr_t reg_2 :2;
} command_ariphm_format;

typedef struct {
	uint8_t opcode  :6;
	uint8_t reg_1   :2;
} command_screen_format;


const char MOVI_pattern[] = "[0-7].";
const char ADD_pattern[] = "8.";
const char SUB_pattern[] = "9.";
const char MUL_pattern[] = "A.";
const char DIV_pattern[] = "B.";
const char IN_pattern[] = "C[0-3]";
const char OUT_pattern[] = "C[4-7]";


char* patterns[] = {MOVI_pattern, ADD_pattern, SUB_pattern, MUL_pattern, DIV_pattern, 
IN_pattern, OUT_pattern};
#define patterns_n 7


typedef struct command {
	command_type_t command_type;
	union {
		uint8_t value;
		union{
			command_reg_load_format f1;
			command_ariphm_format   f2;
			command_screen_format   f3;
		};
	};
} command_t;


void check_regcomp(int res, regex_t* regex_arr, int i){
	char BUFFER[128];
	regerror(res, regex_arr + i, BUFFER, sizeof(BUFFER));
	fprintf(stderr, "Regex match failed: %s\n", BUFFER);
	for(int j = 0; j<=i; ++j)
		regfree(regex_arr + j);
	exit(EXIT_FAILURE);
}


regex_t regex_arr[patterns_n];
regmatch_t matches[1];
void read_command_init(){
	for(int i = 0; i<patterns_n; ++i){
		int res = regcomp(&regex_arr[i], patterns[i], REG_EXTENDED);
		check_regcomp(res, regex_arr, i);
	}	
}

command_t read_command(){
	command_t command;	command.value = 0xFF;
	char scom[5];

	for(;;){
		int res = scanf("%4s", scom);
		if(res!=1) break;
		for(int i = 0; i<patterns_n; ++i){
			res = regexec(regex_arr + i, scom, 1, matches, 0);
			if(!res){
				//ok case
			}
		}
	}
	
	return command;
}

int main(){
	command_t command;
}

