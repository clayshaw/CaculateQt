#include"big_int.h"
#include<algorithm>
#include<vector>
#include "other.h"

using namespace _big_int;
// 建構子
big_int::big_int()
{
    this->num = "0";
    this->pos = true;
}

big_int::big_int(int n)
{
    if(n<0){
        this->pos = false;
        this->num = std::to_string(-n);
    } else {
        this->pos = true;
        this->num = std::to_string(n);
    }
}

big_int::big_int(const big_int& s)
{
    this->num = s.num;
    this->pos = s.pos;
}

big_int::big_int(std::string s)
{
    if(s[0]=='-'){
        this->pos = false;
        this->num = s.substr(1);
    } else {
        this->pos = true;
        this->num = s;
    }
}

big_int big_int::operator=(big_int s)
{
    this->num = s.num;
    this->pos = s.pos;
    return *this;
}

big_int big_int::operator=(std::string s)
{
    if(s[0]=='-'){
        this->pos = false;
        this->num = s.substr(1);
    } else {
        this->pos = true;
        this->num = s;
    }
    return *this;
}






// 重載運算子
big_int big_int::operator+(big_int s)
{

    
    std::string a = this->num, b = s.num;
    std::string ans;
    int carry = 0;
    int i = a.length()-1, j = b.length()-1;
    while(i>=0 || j>=0){
        int x = (i>=0)?a[i]-'0':0;
        int y = (j>=0)?b[j]-'0':0;
        int sum = x+y+carry;
        carry = sum/10;
        ans += std::to_string(sum%10);
        i--;
        j--;
    }
    if(carry){
        ans += std::to_string(carry);
    }
    std::reverse(ans.begin(),ans.end());
    if(this->pos==false && s.pos==false){
        ans.insert(0,"-");
    }
    return big_int(dezero(ans));
}

big_int big_int::operator-(big_int s)
{

    std::string a = this->num, b = s.num;
    std::string ans;
    int carry = 0;
    int i = a.length()-1, j = b.length()-1;
    while(i>=0 || j>=0){
        int x = (i>=0)?a[i]-'0':0;
        int y = (j>=0)?b[j]-'0':0;
        int sum = x-y-carry;
        if(sum<0){
            sum += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        ans += std::to_string(sum);
        i--;
        j--;
    }
    std::reverse(ans.begin(),ans.end());
    if(*this < s){
        ans = dezero(ans);
        std::string zero ="1";
        for(int i=0;i<(int)ans.length();i++){
            zero += "0";
        }
        ans = (big_int(zero)-big_int(ans)).get();
        ans = dezero(ans);
        ans.insert(0,"-");
    }

    return big_int(dezero(ans));
}

big_int big_int::operator*(big_int s)
{
    // 宣告變數
    std::string a = this->num, b = s.num;
    big_int ans(0);
    int j = b.length()-1;
    std::string zero = "";

    // 值陣列
    big_int val[10];
    val[0] = big_int(0);
    val[1] = *this;
    for(int k=2;k<10;k++){
        val[k] = val[k-1]+*this;
    }
    
    while(j>=0){
        // 取得數字
        int y = (j>=0)?b[j]-'0':0;
        // 乘上10的次方
        // 並加到ans
        ans = ans + big_int(val[y].get()+zero);
        

        j--;
        zero += "0";
    }
    if(this->pos!=s.pos){
        ans = big_int("-"+dezero(ans.get()));
    } else {
        ans = big_int(dezero(ans.get()));
    }
    return ans;
}

big_int big_int::operator/(big_int s)
{
    std::string a = this->num, b = s.num;
    big_int cnt = 0;
    int startValue = s.length();

    // 補0
    while(a.length()-1>b.length()){
        b += "0";
    }

    // 除法
    while((int)b.length() != startValue){
        while(big_int(a)>=big_int(b)){
            a = (big_int(a)-big_int(b)).get();
            cnt++;
        }
        
        b = b.substr(0,b.length()-1);
        cnt*=10;
    }
    if(big_int(a)>=big_int(b)){
        while(big_int(a)>=big_int(b)){
            a = (big_int(a)-big_int(b)).get();
            cnt++;
        }
        b = b.substr(0,b.length()-1);
    }
    if(this->pos!=s.pos){
        cnt = big_int("-"+dezero(cnt.get()));
    }

    return big_int(cnt);
}

big_int big_int::operator%(big_int s)
{
    std::string a = this->num, b = s.num;
    int cnt = 0;
    big_int startValue = big_int(b);

    // 補0
    while(a.length()-1>b.length()){
        b += "0";
    }

    // 除法
    while(big_int(b)!=startValue){
        while(big_int(a)>=big_int(b)){
            a = (big_int(a)-big_int(b)).get();
            cnt++;
        }
        
        b = b.substr(0,b.length()-1);
        
        cnt*=10;
    }
    if(big_int(a)>=big_int(b)){
        while(big_int(a)>=big_int(b)){
            a = (big_int(a)-big_int(b)).get();
            cnt++;
        }
        b = b.substr(0,b.length()-1);
    }
    

    return big_int(dezero(a));
}

big_int big_int::operator^(big_int s)
{
    if(s<big_int(0)){
        return big_int("not allow integer");
    }
    big_int tmp = *this;
    if(s==1){
        return tmp;
    }
    big_int ans;

    if(s%2==big_int("0")){
        s=s/2;
        ans = (tmp^s);
        ans = ans*ans;
    } else {
        s = (s - 1)/2;
        ans = (tmp^s);
        ans = ans * ans * tmp;
    }
    
    return ans;
}

big_int big_int::operator+=(big_int s)
{
    *this = *this + s;
    return *this;
}

big_int big_int::operator-=(big_int s)
{
    *this = *this - s;
    return *this;
}

big_int big_int::operator*=(big_int s)
{
    *this = *this * s;
    return *this;
}

big_int big_int::operator/=(big_int s)
{
    *this = *this / s;
    return *this;
}

big_int big_int::operator++()
{
    *this = *this + 1;
    return *this;
}

big_int big_int::operator--()
{
    *this = *this - 1;
    return *this;
}

big_int big_int::operator++(int)
{
    *this = *this + 1;
    return *this;
}

big_int big_int::operator--(int)
{
    *this = *this - 1;
    return *this;
}


// 比較運算子
bool big_int::operator==(big_int s)
{
    return (this->num == s.num && this->pos == s.pos);
}

bool big_int::operator!=(big_int s)
{
    return (this->num != s.num || this->pos != s.pos);
}

bool big_int::operator>(big_int s)
{
    if(this->pos && !s.pos){
        return true;
    } else if(!this->pos && s.pos){
        return false;
    } else if(this->pos && s.pos){
        if(this->num.length() > s.num.length()){
            return true;
        } else if(this->num.length() < s.num.length()){
            return false;
        } else {
            for(int i=0;i<(int)this->num.length();i++){
                if(this->num[i] > s.num[i]){
                    return true;
                } else if(this->num[i] < s.num[i]){
                    return false;
                }
            }
            return false;
        }
    } else {
        if(this->num.length() > s.num.length()){
            return false;
        } else if(this->num.length() < s.num.length()){
            return true;
        } else {
            for(int i=0;i<(int)this->num.length();i++){
                if(this->num[i] > s.num[i]){
                    return false;
                } else if(this->num[i] < s.num[i]){
                    return true;
                }
            }
            return false;
        }
    }
}

bool big_int::operator<(big_int s)
{
    if(*this > s || *this == s){
        return false;
    } else {
        return true;
    }
}

bool big_int::operator>=(big_int s)
{
    if(*this > s || *this == s){
        return true;
    } else {
        return false;
    }
}

bool big_int::operator<=(big_int s)
{
    if(*this < s || *this == s){
        return true;
    } else {
        return false;
    }
}


