#include "Integer.hpp"
#include "Function.hpp"
#include <iostream>


/* ---------Integer--------- */

Integer::Integer() {
    int_val = "";
}

Integer::Integer(const char* num) {
    //    parameter num is supposed to be a calculation result number, not a formula (so we should deal with this problem)
    string NUM = num;
    NUM = simplify(NUM, nums);
    div_final(NUM, nums);
    
    if(NUM[0] == '-') {
        isNegative = true;
        NUM.erase(0, 1);
    }
    else if(NUM[0] == '+') {
        NUM.erase(0, 1);
    }
    obj_name = num;              //this line has a problem (done!!)
    bool isInt = true;
    for(int i = 0; i < NUM.length(); i++) {
        if(NUM[i] == '.') {
            isInt = false;
            int_val = NUM.substr(0, i);
            break;
        }
    }
    if(isInt) {
        int_val = NUM;
    }
    nume = int_val;
    deno = "1";
}

Integer::Integer(std::string NUM) {
    //    parameter num is supposed to be a calculation result number, not a formula (so we should deal with this problem)
//    string NUM = num;
    NUM = simplify(NUM, nums);
    div_final(NUM, nums);
    
    if(NUM[0] == '-') {
        isNegative = true;
        NUM.erase(0, 1);
    }
    else if(NUM[0] == '+') {
        NUM.erase(0, 1);
    }
    obj_name = NUM;              //this line has a problem (done!!)
    bool isInt = true;
    for(int i = 0; i < NUM.length(); i++) {
        if(NUM[i] == '.') {
            isInt = false;
            int_val = NUM.substr(0, i);
            break;
        }
    }
    if(isInt) {
        int_val = NUM;
    }
    nume = int_val;
    deno = "1";
}

Integer::Integer(const Integer& num) {
    isNegative = num.isNegative;
    obj_name = "";                  //this line has a probrem
    int_val = num.int_val;
    nume = num.nume;
    deno = num.deno;
}

Integer::Integer(const Decimal& num) {
    isNegative = num.isNegative;
    obj_name = "";                   //this lien has a problem
    
    string tmp_result = num.nume - num.deno;
    int tmp_ans_intPart = 0;
    while(tmp_result[0] != '-') {
        tmp_ans_intPart++;
        tmp_result = tmp_result - num.deno;
    }
    int_val.push_back(tmp_ans_intPart + 0x30);
    nume = int_val;
    deno = "1";
}

Integer& Integer::operator= (const Integer& num) {
    isNegative = num.isNegative;
    obj_name = "";                  //this line has a probrem
    int_val = num.int_val;
    nume = num.nume;
    deno = num.deno;
    return *this;
}

Integer& Integer::operator= (const Decimal& num) {
    isNegative = num.isNegative;
    obj_name = "";                   //this lien has a problem
    
    string tmp_result = num.nume - num.deno;
    int tmp_ans_intPart = 0;
    while(tmp_result[0] != '-') {
        tmp_ans_intPart++;
        tmp_result = tmp_result - num.deno;
    }
    int_val.push_back(tmp_ans_intPart + 0x30);
    nume = int_val;
    deno = "1";
    return *this;
}

Integer& Integer::operator= (const char* num) {
    //    parameter num is supposed to be a calculation result number, not a formula (so we should deal with this problem)
    string NUM = num;
    NUM = simplify(NUM, nums);
    div_final(NUM, nums);
    
    if(NUM[0] == '-') {
        isNegative = true;
        NUM.erase(0, 1);
    }
    else if(NUM[0] == '+') {
        NUM.erase(0, 1);
    }
    obj_name = num;                      //this line has a problem (done!!)
    bool isInt = true;
    for(int i = 0; i < NUM.length(); i++) {
        if(NUM[i] == '.') {
            isInt = false;
            int_val = NUM.substr(0, i);
            break;
        }
    }
    if(isInt) {
        int_val = NUM;
    }
    nume = int_val;
    deno = "1";
    return *this;
};

Integer& Integer::operator= (string NUM) {
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
    obj_name = NUM;                      //this line has a problem (done!!)
    bool isInt = true;
    for(int i = 0; i < NUM.length(); i++) {
        if(NUM[i] == '.') {
            isInt = false;
            int_val = NUM.substr(0, i);
            break;
        }
    }
    if(isInt) {
        int_val = NUM;
    }
    nume = int_val;
    deno = "1";
    return *this;
}

istream& operator>> (istream& input, Integer& num) {
    string tmp_in;
    input >> tmp_in;
    num = tmp_in;
    return input;
}

ostream& operator<< (ostream& output, Integer& num) {
    output << num.int_val;
    return output;
}

Integer::~Integer() {
    
}

/* ---------Integer--------- */
