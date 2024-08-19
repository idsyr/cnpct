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

typedef enum { A = 0, B, C, D } registr_t;
typedef enum { MOVI = 0x0, ADD = 0x8, SUB = 0x9,
							 MUL = 0xA,  DIV = 0xB, IN = 0x30,
							 OUT = 0x31 } opcode_t;

typedef enum {reg_load_format, ariphm_format, screen_format} instr_format_t;

typedef struct {
	uint8_t opcode  :1;
	uint8_t immediat :7;
} instr_format_reg_load_t;

typedef struct {
	uint8_t opcode  :4;
	registr_t reg_1 :2;
	registr_t reg_2 :2;
} instr_format_ariphm_t;

typedef struct {
	uint8_t opcode  :6;
	uint8_t reg_1   :2;
} instr_format_screen_t;



typedef struct {
	const char* hex_pattern;
	const char* asm_pattern;
	void (*print_as_asm)(uint8_t*);
	void (*print_as_hex)(uint8_t*);
} instr_info_t;




void print_movi_asm(uint8_t *hexcode){
	instr_format_reg_load_t *movi = hexcode;
	printf("MOVI %d", movi->immediat);
	
}

const char pattern_hex_movi[] = "0x[0-7].";
instr_info_t movi_info = {
	.hex_pattern  = pattern_hex_movi,
	.print_as_asm = print_movi_asm,
};




void print_add_asm(uint8_t *hexcode){
	instr_format_ariphm_t *add = hexcode;
	printf("ADD %c %c", add->reg_1 + 65, add->reg_2 + 65);
}

const char pattern_hex_add[] = "0x8.";
instr_info_t add_info = {
	.hex_pattern  = pattern_hex_add,
	.print_as_asm = print_add_asm,
};




void print_sub_asm(uint8_t *hexcode){
	instr_format_ariphm_t *sub = hexcode;
	printf("SUB %c %c", sub->reg_1 + 65, sub->reg_2 + 65;
}

const char pattern_hex_sub[] = "0x9.";
instr_info_t sub_info = {
	.hex_pattern  = pattern_hex_sub,
	.print_as_asm = print_sub_asm,
};




void print_mul_asm(uint8_t *hexcode){
	instr_format_ariphm_t *mul = hexcode;
	printf("MUL %c %c", mul->reg_1 + 65, mul->reg_2 + 65;
}

const char pattern_hex_mul[] = "0xA.";
instr_info_t mul_info = {
	.hex_pattern  = pattern_hex_mul,
	.print_as_asm = print_mul_asm,
};




void print_div_asm(uint8_t *hexcode){
	instr_format_ariphm_t *div = hexcode;
	printf("DIV %c %c", div->reg_1 + 65, div->reg_2 + 65;
}

const char pattern_hex_div[] = "0xB.";
instr_info_t div_info = {
	.hex_pattern  = pattern_hex_div,
	.print_as_asm = print_div_asm,
};


 

void print_in_asm(uint8_t *hexcode){
	instr_format_screen_t *in = hexcode;
	printf("IN %c", in->reg_1);
}

const char pattern_hex_in[] = "0xC[0-3]";
instr_info_t in_info = {
	.hex_pattern = pattern_hex_in,
	.print_as_asm = print_in_asm,
};




void print_out_asm(uint8_t *hexcode){
	instr_format_screen_t *out = hexcode;
	printf("OUT %c", out->reg_1);
}

const char pattern_hex_out[] = "0xC[4-7]";
instr_info_t out_info = {
	.hex_pattern = pattern_hex_out,
	.print_as_asm = print_out_asm,
};


 
typedef struct instruction{
	instr_info_t *info;
	uint8_t val;
} instruction_t;


int instruction_set_n;


void check_regcompexec(int res, regex_t* regex_arr, int i){
	if(res == 0 || res == REG_NOMATCH) return;
	char BUFFER[128];
	regerror(res, regex_arr + i, BUFFER, sizeof(BUFFER));
	fprintf(stderr, "Regex match failed: %s\n", BUFFER);
	for(int j = 0; j<i; ++j)
		regfree(regex_arr + j);
	exit(EXIT_FAILURE);
}




void read_hex_instruction_init(regex_t *regex_arr, instr_info_t *instr_set){
	for(int i = 0; i<instruction_set_n;){
		int res = regcomp(&regex_arr[i], instr_set[i].asm_pattern, REG_EXTENDED);
		check_regcompexec(res, regex_arr, ++i);
	}	
}



instruction_t read_hex_instruction(regex_t *regex_arr, instr_info_t *instr_set){
	instruction_t instr;	instr.info = NULL;
	char instr_asm[5];
	regmatch_t matches[1];

	int res = scanf("%4s", instr_asm);
	if(res!=1) return instr;

	for(int i = 0; i<instruction_set_n; ++i){
		res = regexec(regex_arr + i, instr_asm, 1, matches, 0);
		check_regcompexec(res, regex_arr, instruction_set_n);
		if(!res){
			instr.info = instr_set + i;
			
			char buff[2] = "";
			memcpy(buff,
						 instr_asm + matches[0].rm_so,
						 matches[i].rm_eo - matches[i].rm_so);

			instr.val = strtol(buff, NULL, 16);
			return instr;
		}
	}
	
	return instr;
}

int main(){
	instr_info_t instruction_set[] = 
		{movi_info, add_info, sub_info, mul_info, div_info, in_info, out_info};
	instruction_set_n = sizeof(instruction_set) / sizeof(instruction_set[0]);
	regex_t instruction_regex[instruction_set_n];
	read_hex_instruction_init(instruction_regex, instruction_set);
	for(;;){
		instruction_t i = read_hex_instruction(instruction_regex, instruction_set);
		if(i.info == NULL) break;
		i.info->print_as_asm(&i.val);
	}
}


/*
| MOVI | I   | 0IIIIIII |
| ADD  | R,R | 1000RRRR |
| SUB  | R,R | 1001RRRR |
| MUL  | R,R | 1010RRRR |
| DIV  | R,R | 1011RRRR |
| IN   | R   | 110000RR |
| OUT  | R   | 110001RR |
*/
