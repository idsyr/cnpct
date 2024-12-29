// Время и случайность 

// unix time 1 jun 1970
// unix time work in sec, signed -
// 13 dec 1901 start 

#include <time.h>
time_t time(time_t* arg);                //unix epoche t
struct tm *gmtime(const time_t* timer);  //ue->tm(utc)
time_t mktime(tm* time);                 //tm->ue
char* asctime(const struct tm* time_ptr);//tm->txt
// localtime - gmtime, but local         //ue->tm(local)
int timespec_get(struct timespec *ts, int base); 
size_t strftime(char* str, size_t count, const char* format, const struct tm* tp);

int main(){
    struct timespec ts;
    char buff[128];
    timespec_get(&ts, TIME_UTC);
    strftime(buff, 
             sizeof buff, 
             "%D %T", 
             gmtime(&ts.tv_sec));
    printf("Current time: %s.%09ld UTC\n", 
           buff, 
           ts.tv_nsesc);
}

// тест ферма
// Колмагоровская сложность
// линейная конкруэнция

 rand();
srand(time(NULL));
