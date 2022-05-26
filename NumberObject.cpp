#include "NumberObject.hpp"
#include "Function.hpp"
#include <iostream>



/* ---------NumberObject--------- */

NumberObject::NumberObject() {
    isNegative = false;
    obj_name = "";
    nume = "";
    deno = "";
    int_val = "";
}

NumberObject& NumberObject::operator= (std::string NUM) {
    //    parameter num is supposed to be a calculation result number, not a formula (so we should deal with this problem)
    NUM = simplify(NUM, nums);
    div_final(NUM, nums);
        if(NUM[0] == '-') {
            isNegative = true;
            NUM.erase(0, 1);
        }
        else if(NUM[0] == '+') {
            NUM.erase(0, 1);
        }
        obj_name = NUM;                  //this line has a problem (done!!)
        bool isInt = true;
        for(int i = 0; i < NUM.length(); i++) {
            if(NUM[i] == '.') {
                isInt = false;
                nume = NUM.erase(i, 1);
                bool allZero = true;
                for(int k = 0; k < NUM.length(); k++) {
                    if(NUM[k] != '0') {
                        allZero = false;
                        break;
                    }
                }
                if(allZero) {
                    nume = "0";
                    deno = "1";
                    return *this;
                }
                deno = "1";
                for(int j = 0; j < NUM.length()-i; j++) {
                    deno = deno + "0";
                }
                if(nume != "0") {
                    reverse(nume.begin(), nume.end());
                    while(nume.back() == '0') nume.pop_back();
                    reverse(nume.begin(), nume.end());
                }
//                std::string divisor;
//                divisor = gcd(nume, deno);
//                nume = nume / divisor;
//                deno = deno / divisor;
                nume = dec_to_int(nume);
                deno = dec_to_int(deno);
                break;
            }
        }
        if(isInt) {
            nume = NUM;
            deno = "1";
            int_val = NUM;
        }
    return *this;
}

NumberObject& NumberObject::operator= (const NumberObject& num) {
    isNegative = num.isNegative;
    obj_name = num.obj_name;
    nume = num.nume;
    deno = num.deno;
    int_val = num.int_val;
    return *this;
}

std::istream& operator>> (std::istream& input, NumberObject& num) {
    string tmp_in;
    input >> tmp_in;
    num = tmp_in;
    return input;
}

std::ostream& operator<< (std::ostream& output, NumberObject& num) {
    if(num.isNegative) output << "-";
    if(num.int_val.empty()) {
        output << (num.nume/num.deno);
    }
    else {
        output << num.int_val;
    }
    return output;
}

NumberObject::~NumberObject() {
    
}

/* ---------NumberObject--------- */






