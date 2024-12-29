// Интермелия: командная строка, файлы и вариабельные аргументы
// нужно много файлов на вход

//FILE* fopen (char const * name, char const* mode);
// r/w/a
// int fclose

//f = fopen("myfile", "r");
//if(f == NULL){
//    perror("ERROR: opening file"); abort();
//}

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void erprintf(const char* fstr, ...){
    char buf[256];
    va_list vl;
    va_start(vl, fstr);
    
    vsprintf(buf, fstr, vl);
    perror(buf);

    va_end(vl);
}

int find_in_file(const char* name, int needle){
    int count = 0; FILE* file_ptr;
    file_ptr = fopen(name, "r");
    if(file_ptr == NULL){
        erprintf("ERROR: opening file: %s", name);
        abort();
    }

    for(;;){
        int res, n;
        res = fscanf(file_ptr, "%d", &n);
        if(res == EOF)
            break;
        if(res != 1){
            fprintf(stderr, 
                    "ERROR: File %s have"
                    "broken format\n",
                    name);
        }
        if(needle == n)
            ++count;
    }

    fclose(file_ptr);
    return count;
}

int main(int argc, char **argv){
    int n; char* endptr; FILE* file_ptr; int count;
    if(argc < 3){
        fprintf(stderr, 
                "Usage: %s <n> <files...>\n", 
                argv[0]);
        return 1;
    }
    n = strtol(argv[1], &endptr, 10);
    if(endptr == argv[1]){
        fprintf(stderr,
                "<%s> cannot be converted to int\n",
                argv[1]);
        return 1;
    }
    count = find_in_file(argv[2], n);
    printf("Count: %d\n", count);
}

// ftell fseek

//sprintf

//variable functions ...
//va_list type
int sum_all(int n, ...){
    int res = 0;
    va_list args;
    va_start(args, n);
    for(int i = 0; i<n; ++i)
        res += va_arg(args, int);
    va_end(args);
    return res;
}
//vfprintf
