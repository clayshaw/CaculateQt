#ifndef BIG_INT
#define BIG_INT


#include<iostream>
#include<algorithm>
#include"other.h"

namespace _big_int{
    class big_int
    {
    private:
        std::string num;
        bool pos;


        void chg_pos(bool flag){this->pos = flag;};
        void chg_pos(){this->pos = !this->pos;};
    public:
        big_int();
        big_int(std::string );
        big_int(const big_int& s);
        big_int(int );

        ~big_int(){};

        big_int operator=(big_int );
        big_int operator=(std::string );
        big_int operator+(big_int ); 
        big_int operator-(big_int );
        big_int operator*(big_int );
        big_int operator/(big_int );
        big_int operator+=(big_int );
        big_int operator-=(big_int );
        big_int operator*=(big_int );
        big_int operator/=(big_int );
        big_int operator%(big_int );
        big_int operator^(big_int );
        big_int operator++();
        big_int operator++(int);
        big_int operator--();
        big_int operator--(int);
        bool operator<(big_int );
        bool operator>(big_int );
        bool operator<=(big_int );
        bool operator>=(big_int );
        bool operator==(big_int );
        bool operator!=(big_int );


        std::string get(){return this->num;};
        int length(){return this->num.length();};
        big_int abs(){return big_int(this->num);};
        bool get_pos(){return this->pos;};


        friend std::ostream& operator<<(std::ostream &os,_big_int::big_int s){
            if(s.get()[0]=='0'){
                os<<'0';
                return os;
            }
            if(s.pos==false){
                os<<"-";
            }
            os<<s.num;
            return os;
        } 
        friend std::istream& operator>>(std::istream &os,_big_int::big_int &s){
            os>>s.num;
            s = big_int(dezero(s.get()));
            return os;
        }


    };
};





#endif
