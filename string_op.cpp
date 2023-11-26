#include <iostream>
#include <algorithm>
#include <cstring>
#include <ostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
struct String{
    char* str_;
    int sz_;
    String(char* r){
        sz_ = strlen(r); 
        str_ = new char[sz_];
        memcpy(str_, r, sz_);
    };
    String(String&& r){swap(sz_, r.sz_); swap(str_, r.str_);}
    String(String* r){
        sz_ = r->sz_;
        str_ = new char[sz_];
        memcpy(str_, r->str_, r->sz_);
    }
    String(String& r){
        sz_ = r.sz_;
        str_ = new char[sz_];
        memcpy(str_, r.str_, r.sz_);
    }
    void operator=(String* r){
        sz_ = r->sz_;
        delete[] str_;
        str_ = new char[sz_];
        memcpy(str_, r->str_, r->sz_);
    }
    void operator=(String& r){
        sz_ = r.sz_;
        delete[] str_;
        str_ = new char[sz_];
        memcpy(str_, r.str_, r.sz_);
    }
    void operator=(String&& r){
        sz_ = r.sz_;
        swap(str_, r.str_);
    }
    ostream& operator<<(ostream& os){
        for(int i = 0; i<sz_; ++i)
            os<<str_[i];
        return os;
    }
    void print(){
         for(int i = 0; i<sz_; ++i)
            cout<<str_[i];
        cout<<endl;
    }
    String& operator+=(String& rha){
        char* tmp = new char[sz_+rha.sz_];        
        memcpy(tmp, str_, sz_);
        delete str_; 
        memcpy((tmp+sz_), rha.str_, rha.sz_);
        str_ = tmp;
        sz_ = strlen(tmp);
        return *this;
    }
    String operator+(String& rha){
        String tmp(this);
        tmp+=rha;
        return tmp;
    }
    String splus(String& rha1, String& rha2){
        char* tmp = new char[rha1.sz_+rha2.sz_];
        memcpy(tmp, rha1.str_, rha1.sz_);
        memcpy((tmp+rha1.sz_), rha2.str_, rha2.sz_);
        return tmp;
    }
    ~String(){
        delete[] str_;
    }
};
int main(){
#ifdef START
    char in[]{'a','b','c'};
    String s1(in);
    s1.print();
    //cout<<s1<<endl;
    String s2("bca");
    s2.print();
    String s3(move(s2));
    s3.print();
    s1+=s3;
    s1.print();
    (s1+s3).print();
#endif
    
#ifdef OPRTR
    auto start1 = high_resolution_clock::now();
    String s1("q");
    for(int i = 0; i<10; ++i){
        s1 = s1+s1;
    }
    s1.print();
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    cout << duration1.count() << endl;
#endif 

#ifdef PLUS
    auto start2 = high_resolution_clock::now();
    String s2("q");
    for(int i = 0; i<7; ++i){
        s2 = s2.splus(s2,s2);
    }
    s2.print();
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout << duration2.count() << endl;
#endif

}
