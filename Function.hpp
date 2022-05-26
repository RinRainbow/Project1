#ifndef Function_hpp
#define Function_hpp

#include <string>
#include <vector>
#include "NumberObject.hpp"
#include "Decimal.hpp"
#include "Integer.hpp"

using namespace std;

static vector<NumberObject*> nums;         //Set用

/* ----------基本演算の関数---------- */

string add(string str1, string str2);
string operator- (string str1, string str2);
string operator* (string str1, string str2);
string operator/ (string str1, string str2);        //全部小数で返される
string operator% (string str1, string str2);
bool operator> (string str1, string str2);
bool operator< (string str1, string str2);
bool operator>= (string str1, string str2);
bool operator<= (string str1, string str2);
string Power(string str1, string str2);
string Factorial(string str);
string gcd(string a, string b);
string lcm(string a, string b);
string dec_to_int(string dec);
bool isInt(string str);
string sqrt(string str);



/* ----------クラス同士の演算の関数---------- */

Integer operator+ (const Integer& Int1, const Integer& Int2);
Decimal operator+ (const Integer& Int1, const Decimal& Int2);
Decimal operator+ (const Decimal& Int1, const Integer& Int2);
Decimal operator+ (const Decimal& Int1, const Decimal& Int2);

Integer operator- (const Integer& Int1, const Integer& Int2);
Decimal operator- (const Integer& Int1, const Decimal& Int2);
Decimal operator- (const Decimal& Int1, const Integer& Int2);
Decimal operator- (const Decimal& Int1, const Decimal& Int2);

Integer operator* (const Integer& Int1, const Integer& Int2);
Decimal operator* (const Integer& Int1, const Decimal& Int2);
Decimal operator* (const Decimal& Int1, const Integer& Int2);
Decimal operator* (const Decimal& Int1, const Decimal& Int2);

Integer operator/ (const Integer& Int1, const Integer& Int2);
Decimal operator/ (const Integer& Int1, const Decimal& Int2);
Decimal operator/ (const Decimal& Int1, const Integer& Int2);
Decimal operator/ (const Decimal& Int1, const Decimal& Int2);



/* ----------エラー処理---------- */

void bracket_error();
void expo_error();
void root_error();
void input_error();



/* ----------式の処理---------- */

string simplify(string& a, vector<NumberObject*>& nums);           //式を計算して結果を置き換える
void bracket(string& input, vector<NumberObject*>& nums);
void facto(string& input, vector<NumberObject*>& nums);
void pow(string& input, vector<NumberObject*>& nums);
void pm(string& input, vector<NumberObject*>& nums);
void md(string& input, vector<NumberObject*>& nums);
void add_dif(string& input, vector<NumberObject*>& nums);
void ad(string& input, vector<NumberObject*>& nums);
void dif(string& input, vector<NumberObject*>& nums);

string div_final(string& input, vector<NumberObject*>& nums);



#endif /* Function_hpp */
