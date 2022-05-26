#include "Decimal.hpp"
#include "Function.hpp"
#include <iostream>








/* ---------Decimal--------- */




Decimal::Decimal() {
    nume = "";
    deno = "";
}

Decimal::Decimal(const char* num) {
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
    obj_name = NUM;                  //this line has a problem (done!!)
    bool isInt = true;
    for(int i = 0; i < NUM.length(); i++) {
        if(NUM[i] == '.') {
            isInt = false;
            nume = NUM.erase(i, 1);
            deno = "1";
            for(int j = 0; j < NUM.length()-i; j++) {
                deno = deno + "0";
            }
            if(nume != "0") {
                reverse(nume.begin(), nume.end());
                while(nume.back() == '0') nume.pop_back();
                reverse(nume.begin(), nume.end());
            }
            if(nume.empty()) nume = "0";
//            std::string divisor;
//            divisor = gcd(nume, deno);
//            nume = nume / divisor;
//            deno = deno / divisor;
            nume = dec_to_int(nume);
            deno = dec_to_int(deno);
            break;
        }
    }
    if(isInt) {
        nume = NUM;
        deno = "1";
    }
}

Decimal::Decimal(const Decimal& num) {
    isNegative = num.isNegative;
    obj_name = "";                  //this line has a problem
    nume = num.nume;
    deno = num.deno;
}

Decimal::Decimal(std::string NUM) {
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
    obj_name = NUM;                  //this line has a problem (done!!)
    bool isInt = true;
    for(int i = 0; i < NUM.length(); i++) {
        if(NUM[i] == '.') {
            isInt = false;
            nume = NUM.erase(i, 1);
            deno = "1";
            for(int j = 0; j < NUM.length()-i; j++) {
                deno = deno + "0";
            }
            if(nume != "0") {
                reverse(nume.begin(), nume.end());
                while(nume.back() == '0') nume.pop_back();
                reverse(nume.begin(), nume.end());
            }
            if(nume.empty()) nume = "0";
            std::string divisor;
            divisor = gcd(nume, deno);
            nume = nume / divisor;
            deno = deno / divisor;
            nume = dec_to_int(nume);
            deno = dec_to_int(deno);
            break;
        }
    }
    if(isInt) {
        nume = NUM;
        deno = "1";
    }
}

Decimal& Decimal::operator= (const char* num) {
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
        obj_name = num;                  //this line has a problem (done!!)
        bool isInt = true;
        for(int i = 0; i < NUM.length(); i++) {
            if(NUM[i] == '.') {
                isInt = false;
                nume = NUM.erase(i, 1);
                bool allZero = true;
                for(int k = 0; k < NUM.length()-1; k++) {
                    if(NUM[k] == '0') {
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
        }
    return *this;
}

Decimal& Decimal::operator= (string NUM) {
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
        }
    return *this;
}

Decimal& Decimal::operator= (const Decimal& num) {
    isNegative = num.isNegative;
    obj_name = "";                  //this line has a problem
    nume = num.nume;
    deno = num.deno;
    return *this;
}

istream& operator>> (istream& input, Decimal& num) {
    string tmp_in;
    input >> tmp_in;
    num = tmp_in;
    return input;
}

ostream& operator<< (ostream& output, const Decimal& num) {
    output << (num.nume/num.deno);
    return output;
}

Decimal::~Decimal() {
    
}






/* ---------Decimal--------- */
