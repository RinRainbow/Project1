#include "Function.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>

/* ----------基本演算の関数---------- */

string add(string str1, string str2) {
//            str1 and str2 represent positive Interger
                string ans;
                reverse(str1.begin(), str1.end());
                reverse(str2.begin(), str2.end());
                int up = 0;
                for(int i = 0; i < max(str1.length(), str2.length()); i++) {
                    int tmp_ans = 0;
                    if(i < min(str1.length(), str2.length())) {
                        tmp_ans = (str1[i] - 0x30) + (str2[i] - 0x30) + up;
                        ans.push_back(0x30 + tmp_ans%10);
                        up = tmp_ans / 10;
                    }
                    else {
                        if(str1.length() < str2.length()) {
                            tmp_ans = (str2[i] - 0x30) + up;
                            ans.push_back(0x30 + tmp_ans%10);
                            up = tmp_ans / 10;
                        }
                        else {
                            tmp_ans = (str1[i] - 0x30) + up;
                            ans.push_back(0x30 + tmp_ans%10);
                            up = tmp_ans / 10;
                        }
                    }
                }
                if(up > 0) ans.push_back(0x30 + up);
                reverse(ans.begin(), ans.end());
                return ans;
}

string operator- (string str1, string str2) {
    //            str1 and str2 represent positive Integer
                string ans;
                if(str1.length() < str2.length()) {
    //                str2 have more digits than str1
                    reverse(str1.begin(), str1.end());
                    reverse(str2.begin(), str2.end());
                    for(int i = 0; i < (str2.length() - str1.length()); i++) {
                        str1.push_back('0');
                    }
                    reverse(str1.begin(), str1.end());
                    reverse(str2.begin(), str2.end());
                    ans = str2 - str1;
                    ans = "-" + ans;
                    return ans;
                }
                else if(str1.length() == str2.length()) {
                    bool ansisNegative = false;
                    for(int i = 0; i < str1.length(); i++) {
                        if(str1[i] > str2[i]) {
                            ansisNegative = false;
                            break;
                        }
                        else if(str1[i] < str2[i]) {
                            ansisNegative = true;
                            break;
                        }
                        if(i == str1.length()-1) {
                            ans = "0";
                            return ans;
                        }
                    }
                    if(ansisNegative) {
    //                    str1 and str2 have the same digits, and str2 are larger than str1
                        ans = str2 - str1;
                        ans = "-" + ans;
                        return ans;
                    }
                    else {
    //                    str1 and str2 have the same digits, and str1 is larger than str2
                        string str1_cp = str1;
                        reverse(str1.begin(), str1.end());
                        reverse(str2.begin(), str2.end());
                        int tmp_ans = 0, down = 0;
                        for(int i = 0; i < str1.length(); i++) {
                            if(str1[i] >= str2[i]) {
                                tmp_ans = (str1[i] - 0x30) - (str2[i] - 0x30);
                                ans.push_back(0x30 + tmp_ans);
                            }
                            else {
                                string tmp = str1_cp.substr(0, str1_cp.length()-i-1);
                                tmp = tmp - "1";
                                str1_cp.replace(0, str1_cp.length()-i-1, tmp);
                                reverse(tmp.begin(), tmp.end());
                                str1.replace(str1.begin()+i+1, str1.end(), tmp);
                                down = 10;
                                tmp_ans = (str1[i] - 0x30 + down) - (str2[i] - 0x30);
                                ans.push_back(0x30 + tmp_ans);
                            }
                        }
                        while(ans.back() == '0') {
                            ans.pop_back();
                        }
                        reverse(ans.begin(), ans.end());
                        return ans;
                    }
                }
                else {
    //                str1 have more digits than str2
                    reverse(str2.begin(), str2.end());
                    for(int i = 0; i < (str1.length() - str2.length()); i++) {
                        str2.push_back('0');
                    }
                    reverse(str2.begin(), str2.end());
                    return str1 - str2;
                }
}

string operator* (string str1, string str2) {
//    str1 and str2 represent positive Integer
    if(str1 == "1") return str2;
    if(str1 == "0") return "0";
    string count = "1";
    string ans = "0";
    string limit = add(str2, "1");
    while(count != limit) {
        ans = add(ans, str1);
        count = add(count, "1");
    }
    return ans;
}

string operator/ (string str1, string str2) {
//    str1 and str2 represent positive Integer?
//    bool isInt1, isInt2;
//    isInt1 = isInt(str1);
//    isInt2 = isInt(str2);
//    if(isInt1 && isInt2)
    if(str2 == "0") {
        cout << "CALCULATION FAILED: CANNOT DEVIDED BY ZERO >_<;" << endl;
        exit(EXIT_FAILURE);
    }
//    if(str2 == "1") {
//        return str1;
//    }
    string ans;
    string tmp_result = "";
    tmp_result = str1.substr(0, 1);
    for(int i = 0; i < str1.length(); i++) {
        int tmp_ans_intPart = 0;
        tmp_result = tmp_result - str2;
        while(tmp_result[0] != '-') {
            tmp_ans_intPart++;
            tmp_result = tmp_result - str2;
        }
        ans.push_back(tmp_ans_intPart + 0x30);
        tmp_result.erase(0, 1);
        tmp_result = str2 - tmp_result;
        if(i != str1.length()-1) {
            tmp_result = tmp_result + str1[i+1];
        }
    }
    if(ans != "0") {
        reverse(ans.begin(), ans.end());
        while(ans.back() == '0') ans.pop_back();
        if(ans.empty()) ans.push_back(0x30);
        reverse(ans.begin(), ans.end());
    }
    ans.push_back('.');
    for(int i = 0; i < 100; i++) {
        tmp_result = tmp_result * "10" - str2;
        int tmp_ans_decimal = 0;
        while(tmp_result[0] != '-') {
            tmp_ans_decimal++;
            tmp_result = tmp_result - str2;
        }
        ans.push_back(tmp_ans_decimal + 0x30);
        tmp_result.erase(0, 1);
        tmp_result = str2 - tmp_result;
    }
    return ans;
}

string operator% (string str1, string str2) {
//    str1 is supposed to be lager than str2 (integer)
    if(str2 == "10") return str1.substr(str1.length()-1, 1);
    if(str2 == "100000000") return str1.substr(str1.length()-7, 7);
    string ans = str1 - str2;
    while(ans[0] != '-') {
        ans = ans - str2;
    }
    ans.erase(0, 1);
    ans = str2 - ans;
    return ans;
}

bool operator> (string str1, string str2) {
    string gap = str1 - str2;
    if(gap[0] == '-' || gap == "0") {
//        str1 <= str2
        return false;
    }
    return true;
}

bool operator< (string str1, string str2) {
    string gap = str1 - str2;
    if(gap[0] == '-') {
//        str1 < str2
        return true;
    }
    return false;
}

bool operator>= (string str1, string str2) {
    string gap = str1 - str2;
    if(gap[0] == '-') {
//        str1 < str2
        return false;
    }
    return true;
}

bool operator<= (string str1, string str2) {
    string gap = str1 - str2;
    if(gap[0] == '-' || gap == "0") {
//        str1 <= str2
        return true;
    }
    return false;
}

string Power(string str1, string str2) {
    bool isInt1 = isInt(str1), isInt2 = isInt(str2);
    
    if(isInt1 && isInt2) {
//        str1 と str2 がどちらも整数
        Integer base, expo;
        base = str1;
        expo = str2;
        
        if(!base.isNegative && !expo.isNegative) {
//            str1 と str2 がどちらも正
            string ans = "1";
            while(expo.int_val != "0") {
                ans = ans * base.int_val;
                expo.int_val = expo.int_val - "1";
            }
            return ans;
        }
        else if(!base.isNegative && expo.isNegative) {
//            str1は正 str2は負
            string ans = "1";
            while(expo.int_val != "0") {
                ans = ans * base.int_val;
                expo.int_val = expo.int_val - "1";
            }
            ans = "1 / " + ans;
            return ans;
        }
        else if(base.isNegative && !expo.isNegative) {
//            str1は負 str2は正
            bool odd_expo = false;
            if(expo.int_val % "2" != "0") odd_expo = true;
            string ans = "1";
            while(expo.int_val != "0") {
                ans = ans * base.int_val;
                expo.int_val = expo.int_val - "1";
            }
            if(odd_expo) {
                ans = "-" + ans;
            }
            return ans;
        }
        else {
//            str1 と str2 はどちらも負
            bool odd_expo = false;
            if(expo.int_val % "2" != "0") odd_expo = true;
            string ans = "1";
            while(expo.int_val != "0") {
                ans = ans * base.int_val;
                expo.int_val = expo.int_val - "1";
            }
            ans = "1 / " + ans;
            if(odd_expo) {
                ans = "-" + ans;
            }
            return ans;
        }
    }
    else if(isInt1 && !isInt2) {
//        str1は整数 str2は小数
        while(str2.back() == '0') str2.pop_back();
        Integer base;
        Decimal expo;
        base = str1;
        expo = str2;
        
        if(expo.deno != "1" && expo.deno != "0") expo_error();
        
        if(!base.isNegative && !expo.isNegative) {
//            str1 と str2 がどちらも正
            string ans = "1";
            while(expo.nume != "0") {
                ans = ans * base.int_val;
                expo.nume = expo.nume - "1";
            }
            if(expo.deno == "2") ans = sqrt(ans);
            return ans;
        }
        else if(!base.isNegative && expo.isNegative) {
//            str1は正 str2は負
            string ans = "1";
            while(expo.nume != "0") {
                ans = ans * base.int_val;
                expo.nume = expo.nume - "1";
            }
            if(expo.deno == "2") ans = sqrt(ans);
            ans = "1 / " + ans;
            return ans;
        }
        else if(base.isNegative && !expo.isNegative) {
//            str1は負 str2は正
            if(expo.deno == "1") {
                bool odd_expo = false;
                if(expo.nume % "2" != "0") odd_expo = true;
                
                string ans = "1";
                while(expo.nume != "0") {
                    ans = ans * base.int_val;
                    expo.nume = expo.nume - "1";
                }
                if(odd_expo) {
                    ans = "-" + ans;
                }
                return ans;
            }
            root_error();
        }
        else {
//            str1 と str2 はどちらも負
            if(expo.deno == "1") {
                bool odd_expo = false;
                if(expo.nume % "2" != "0") odd_expo = true;
                string ans = "1";
                while(expo.nume != "0") {
                    ans = ans * base.int_val;
                    expo.nume = expo.nume - "1";
                }
                ans = "1 / " + ans;
                if(odd_expo) {
                    ans = "-" + ans;
                }
                return ans;
            }
            root_error();
        }
    }
    else if(!isInt1 && isInt2) {
//        str1は小数 str2は整数
        while(str1.back() == '0') str1.pop_back();
        Decimal base;
        Integer expo;
        base = str1;
        expo = str2;
        
        if(!base.isNegative && !expo.isNegative) {
//            str1 と str2 がどちらも正
            string ans_nume = "1";
            string ans_deno = "1";
            while(expo.int_val != "0") {
                ans_nume = ans_nume * base.nume;
                ans_deno = ans_deno * base.deno;
                expo.int_val = expo.int_val - "1";
            }
            string ans = ans_nume + " / " + ans_deno + ".0";
            return ans;
        }
        else if(!base.isNegative && expo.isNegative) {
//            str1は正 str2は負
            string ans_nume = "1";
            string ans_deno = "1";
            while(expo.int_val != "0") {
                ans_nume = ans_nume * base.nume;
                ans_deno = ans_deno * base.deno;
                expo.int_val = expo.int_val - "1";
            }
            string ans = ans_deno + " / " + ans_nume + ".0";
            return ans;
        }
        else if(base.isNegative && !expo.isNegative) {
//            str1は負 str2は正
            bool odd_expo = false;
            if(expo.int_val % "2" != "0") odd_expo = true;
            
            string ans_nume = "1";
            string ans_deno = "1";
            while(expo.int_val != "0") {
                ans_nume = ans_nume * base.nume;
                ans_deno = ans_deno * base.deno;
                expo.int_val = expo.int_val - "1";
            }
            
            string ans = ans_nume + " / " + ans_deno + ".0";
            if(odd_expo) {
                ans = "-" + ans;
            }
            return ans;
        }
        else {
//            str1 と str2 はどちらも負
            bool odd_expo = false;
            if(expo.int_val % "2" != "0") odd_expo = true;
            
            string ans_nume = "1";
            string ans_deno = "1";
            while(expo.int_val != "0") {
                ans_nume = ans_nume * base.nume;
                ans_deno = ans_deno * base.deno;
                expo.int_val = expo.int_val - "1";
            }
            
            string ans = ans_deno + " / " + ans_nume + ".0";
            if(odd_expo) ans = "-" + ans;
            
            return ans;
        }
    }
    else {
//        str1 と str2 がどちらも小数
        while(str1.back() == '0') str1.pop_back();
        while(str2.back() == '0') str2.pop_back();
        Decimal base;
        Decimal expo;
        base = str1;
        expo = str2;
        
        if(expo.deno != "1" && expo.deno != "0") expo_error();
        
        if(!base.isNegative && !expo.isNegative) {
//            str1 と str2 がどちらも正
            string ans_nume = "1";
            string ans_deno = "1";
            while(expo.nume != "0") {
                ans_nume = ans_nume * base.nume;
                ans_deno = ans_deno * base.deno;
                expo.nume = expo.nume - "1";
            }
            
            if(expo.deno == "2") {
                ans_nume = sqrt(ans_nume);
                ans_deno = sqrt(ans_deno);
            }
            
            string ans = ans_nume + " / " + ans_deno + ".0";
            return ans;
        }
        else if(!base.isNegative && expo.isNegative) {
//            str1は正 str2は負
            string ans_nume = "1";
            string ans_deno = "1";
            while(expo.nume != "0") {
                ans_nume = ans_nume * base.nume;
                ans_deno = ans_deno * base.deno;
                expo.nume = expo.nume - "1";
            }
            
            if(expo.deno == "2") {
                ans_nume = sqrt(ans_nume);
                ans_deno = sqrt(ans_deno);
            }
            
            string ans = ans_deno + " / " + ans_nume + ".0";
            return ans;
        }
        else if(base.isNegative && !expo.isNegative) {
//            str1は負 str2は正
            if(expo.deno == "1") {
                bool odd_expo = false;
                if(expo.nume % "2" != "0") odd_expo = true;
                
                string ans_nume = "1";
                string ans_deno = "1";
                while(expo.nume != "0") {
                    ans_nume = ans_nume * base.nume;
                    ans_deno = ans_deno * base.deno;
                    expo.nume = expo.nume - "1";
                }
                
                string ans = ans_nume + " / " + ans_deno + ".0";
                if(odd_expo) {
                    ans = "-" + ans;
                }
                return ans;
            }
            root_error();
        }
        else {
//            str1 と str2 はどちらも負
            if(expo.deno == "1") {
                bool odd_expo = false;
                if(expo.nume % "2" != "0") odd_expo = true;
                
                string ans_nume = "1";
                string ans_deno = "1";
                while(expo.nume != "0") {
                    ans_nume = ans_nume * base.nume;
                    ans_deno = ans_deno * base.deno;
                    expo.nume = expo.nume - "1";
                }
                string ans = ans_deno + " / " + ans_nume + ".0";
                if(odd_expo) ans = "-" + ans;
                return ans;
            }
            root_error();
        }
    }
    /*
    string ans = "1";
    while(str2 != "0") {
        ans = ans * str1;
        str2 = str2 - "1";
    }
    return ans;
    */
    
    return "POWER FUNCTION HAS TROUBLE!!";
}

string Factorial(string str) {
    string ans = "1";
    while(str != "0") {
        ans = ans * str;
        str = str - "1";
    }
    return ans;
}

string gcd(string a, string b) {
//    string gap = a - b;
    if(a < b) {
//        a < b
        if(a == "0") return b;
        else if(a == "1") return a;
        else {
            string r = b % a;
            return gcd(a, r);
        }
    }
    else {
//        a >= b
        if(b == "0") return a;
        else if(b == "1") return b;
        else {
            string r = a % b;
            return gcd(b, r);
        }
    }
}

string lcm(string a, string b) {
    if(a == b) return a;
    string ans = a * b / gcd(a, b);
    return dec_to_int(ans);
}

string dec_to_int(string dec) {
    std::string::size_type pos = dec.find('.');
    if(pos != std::string::npos) {
//        string INT;
        decltype(dec)::iterator from = dec.begin() + pos;
        dec.erase(from, dec.end());
//        INT = dec;
//        return INT;
    }
    return dec;
}

bool isInt(string str) {
    for(int i = 0; i < str.length(); i++) {
        if(str[i] == '.' || str[i] == '/') return false;
    }
    return true;
}

string sqrt(string str) {
    vector<string> root = {"0", "1", "4", "9", "16", "25", "36", "49", "64", "81"};
    vector<string> base = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    vector<string> sep;
    if(str.length() % 2 != 0) {
        sep.push_back(str.substr(0, 1));
        str.erase(0, 1);
    }
    while(!str.empty()) {
        sep.push_back(str.substr(0, 2));
        str.erase(0, 2);
    }
    
    string ans, step1, step2, step3, step4;
    step3 = sep[0];
    for(int j = 0; j < 10; j++) {
        if(root[j] > step3) {
            ans = ans + base[j-1];
            step1 = base[j-1];
            step2 = base[j-1];
            step4 = root[j-1];
            break;
        }
    }
    
    if(sep.size() > 1) {
        for(int i = 1; i < sep.size(); i++) {
            step1 = add(step1, step2);
            step3 = step3 - step4;
            step3 = step3 + sep[i];
            
            string N = "0";
            while(true) {
                step1 = step1 + N;
                string step1_n = step1 * N;
                if(step1_n > step3) {
                    N = N - "1";
                    step1.pop_back();
                    ans = ans + N;
                    step1 = step1 + N;
                    step2 = N;
                    step4 = step1 * N;
                    break;
                }
                else {
                    N = add(N, "1");
                    step1.pop_back();
                }
            }
        }
    }
    
    ans = ans + ".";
    for(int i = 0; i < 100; i++) {
        step1 = add(step1, step2);
        step3 = step3 - step4;
        step3 = step3 + "00";
        
        string N = "0";
        while(true) {
            step1 = step1 + N;
            string step1_n = step1 * N;
            if(step1_n > step3) {
                N = N - "1";
                for(int j = 0; j < N.length(); j++) step1.pop_back();
                ans = ans + N;
                step1 = step1 + N;
                step2 = N;
                step4 = step1 * N;
                break;
            }
            else {
                N = add(N, "1");
                for(int j = 0; j < N.length(); j++) step1.pop_back();
            }
        }
    }
    
    return ans;
}



/* ----------クラス同士の演算の関数---------- */

Integer operator+ (const Integer& Int1, const Integer& Int2) {
//    Int1 and Int2 are supposed to be positive
    Integer ans;
    ans.int_val = add(Int1.int_val, Int2.int_val);
    return ans;
}

Decimal operator+ (const Integer& Int1, const Decimal& Int2) {
//    Int1 and Int2 are supposed to be positive
    Decimal ans;
    ans.nume = add(Int1.nume * Int2.deno, Int2.nume);
    ans.deno = Int2.deno;
//    string divisor;
//    divisor = gcd(ans.nume, ans.deno);
//    ans.nume = ans.nume / divisor;
//    ans.deno = ans.deno / divisor;
    ans.nume = dec_to_int(ans.nume);
    ans.deno = dec_to_int(ans.deno);
    return ans;
}

Decimal operator+ (const Decimal& Int1, const Integer& Int2) {
//    Int1 and Int2 are supposed to be positive
    Decimal ans;
    ans.nume = add(Int2.nume * Int1.deno, Int1.nume);
    ans.deno = Int1.deno;
    string divisor;
    divisor = gcd(ans.nume, ans.deno);
    ans.nume = ans.nume / divisor;
    ans.deno = ans.deno / divisor;
    ans.nume = dec_to_int(ans.nume);
    ans.deno = dec_to_int(ans.deno);
    return ans;
}

Decimal operator+ (const Decimal& Int1, const Decimal& Int2) {
//    Int1 and Int2 are supposed to be positive
    Decimal ans;
    ans.deno = lcm(Int1.deno, Int2.deno);
    string time1, time2;
    time1 = ans.deno / Int1.deno;
    time1 = dec_to_int(time1);
    time2 = ans.deno / Int2.deno;
    time2 = dec_to_int(time2);
    ans.nume = add(Int1.nume * time1, Int2.nume * time2);
//    std::string divisor;
//    divisor = gcd(ans.nume, ans.deno);
//    ans.nume = ans.nume / divisor;
//    ans.deno = ans.deno / divisor;
    ans.nume = dec_to_int(ans.nume);
    ans.deno = dec_to_int(ans.deno);
    return ans;
}

Integer operator- (const Integer& Int1, const Integer& Int2) {
//    Int1 and Int2 are supposed to be positive
    Integer ANS;
    string ans = Int1.int_val - Int2.int_val;
    if(ans[0] == '-') {
        ANS.isNegative = true;
        ans.erase(0, 1);
    }
    ANS.int_val = ans;
    return ANS;
}

Decimal operator- (const Integer& Int1, const Decimal& Int2) {
//    Int1 and Int2 are supposed to be positive
    Decimal ans;
    ans.nume = Int1.nume * Int2.deno - Int2.nume;
    ans.deno = Int2.deno;
    if(ans.nume[0] == '-') {
        ans.isNegative = true;
        ans.nume.erase(0, 1);
    }
//    string divisor;
//    divisor = gcd(ans.nume, ans.deno);
//    ans.nume = ans.nume / divisor;
//    ans.deno = ans.deno / divisor;
    ans.nume = dec_to_int(ans.nume);
    ans.deno = dec_to_int(ans.deno);
    return ans;
}

Decimal operator- (const Decimal& Int1, const Integer& Int2) {
    //    Int1 and Int2 are supposed to be positive
        Decimal ans;
        ans.nume = Int2.nume * Int1.deno - Int1.nume;
        ans.deno = Int1.deno;
        if(ans.nume[0] == '-') {
            ans.isNegative = true;
            ans.nume.erase(0, 1);
        }
        string divisor;
        divisor = gcd(ans.nume, ans.deno);
        ans.nume = ans.nume / divisor;
        ans.deno = ans.deno / divisor;
        ans.nume = dec_to_int(ans.nume);
        ans.deno = dec_to_int(ans.deno);
        return ans;
}

Decimal operator- (const Decimal& Int1, const Decimal& Int2) {
//    Int1 and Int2 are supposed to be positive
    Decimal ans;
    ans.deno = lcm(Int1.deno, Int2.deno);
    string time1, time2;
    time1 = ans.deno / Int1.deno;
    time1 = dec_to_int(time1);
    time2 = ans.deno / Int2.deno;
    time2 = dec_to_int(time2);
    ans.nume = Int1.nume * time1 - Int2.nume * time2;
    if(ans.nume[0] == '-') {
        ans.isNegative = true;
        ans.nume.erase(0, 1);
    }
//    std::string divisor;
//    divisor = gcd(ans.nume, ans.deno);
//    ans.nume = ans.nume / divisor;
//    ans.deno = ans.deno / divisor;
    ans.nume = dec_to_int(ans.nume);
    ans.deno = dec_to_int(ans.deno);
    return ans;
}

Integer operator* (const Integer& Int1, const Integer& Int2) {
//    Int1 and Int2 are supposed to be positive
    Integer ans;
    ans.int_val = Int1.int_val * Int2.int_val;
    return ans;
}

Decimal operator* (const Integer& Int1, const Decimal& Int2) {
//    Int1 and Int2 are supposed to be positive
    Decimal ans;
    ans.nume = Int1.nume * Int2.nume;
    ans.deno = Int2.deno;
//    string divisor;
//    divisor = gcd(ans.nume, ans.deno);
//    ans.nume = ans.nume / divisor;
//    ans.deno = ans.deno / divisor;
    ans.nume = dec_to_int(ans.nume);
    ans.deno = dec_to_int(ans.deno);
    return ans;
}

Decimal operator* (const Decimal& Int1, const Integer& Int2) {
//    Int1 and Int2 are supposed to be positive
        Decimal ans;
        ans.nume = Int2.nume * Int1.nume;
        ans.deno = Int1.deno;
//        string divisor;
//        divisor = gcd(ans.nume, ans.deno);
//        ans.nume = ans.nume / divisor;
//        ans.deno = ans.deno / divisor;
        ans.nume = dec_to_int(ans.nume);
        ans.deno = dec_to_int(ans.deno);
        return ans;
}

Decimal operator* (const Decimal& Int1, const Decimal& Int2) {
//    Int1 and Int2 are supposed to be positive
    Decimal ans;
    ans.nume = Int1.nume * Int2.nume;
    ans.deno = Int1.deno * Int2.deno;
//    std::string divisor;
//    divisor = gcd(ans.nume, ans.deno);
//    ans.nume = ans.nume / divisor;
//    ans.deno = ans.deno / divisor;
    ans.nume = dec_to_int(ans.nume);
    ans.deno = dec_to_int(ans.deno);
    return ans;
}

Integer operator/ (const Integer& Int1, const Integer& Int2) {
//    Int1 and Int2 are supposed to be positive
    Integer ANS;
    string ans;
    ans = Int1.int_val / Int2.int_val;
    ANS.int_val = dec_to_int(ans);
    return ANS;
}

Decimal operator/ (const Integer& Int1, const Decimal& Int2) {
//    Int1 and Int2 are supposed to be positive
    Decimal newInt2;
    newInt2.nume = Int2.deno;
    newInt2.deno = Int2.nume;
    return Int1 * newInt2;
}

Decimal operator/ (const Decimal& Int1, const Integer& Int2) {
//    Int1 and Int2 are supposed to be positive
    Decimal newInt1;
    newInt1.nume = Int1.deno;
    newInt1.deno = Int1.nume;
    return newInt1 * Int2;
}

Decimal operator/ (const Decimal& Int1, const Decimal& Int2) {
//    Int1 and Int2 are supposed to be positive
    Decimal newInt2;
    newInt2.nume = Int2.deno;
    newInt2.deno = Int2.nume;
    return Int1 * newInt2;
}

/* ----------エラー処理---------- */

void bracket_error() {
    cout << "INPUT ERROR: THE NUMBER OF BRACkETS DOES NOT MATCH >_<;" << endl;
    exit(EXIT_FAILURE);
}

void expo_error() {
    cout << "INPUT ERROR: EXPONENT MUST BE 0.5*n (n IS INT) >_<;" << endl;
    exit(EXIT_FAILURE);
}

void root_error() {
    cout << "INPUT ERROR: NEGATIVE NUMBER CANNOT DO ROOT >_<;" << endl;
    exit(EXIT_FAILURE);
}

void input_error() {
    cout << "INPUT ERROR" << endl;
    exit(EXIT_FAILURE);
}



/* ----------式の処理---------- */

string simplify(string& a, vector<NumberObject*>& nums) {
//                aがNumberObject変数だったら置き換える
    for(int i = 0; i < nums.size(); i++) {
        if(nums[i]->obj_name == a) {
            if(nums[i]->int_val != "") {
                if(nums[i]->isNegative) {
                    a = "-" + nums[i]->int_val;
                    break;
                }
                else {
                    a = nums[i]->int_val;
                    break;
                }
                
            }
            else {
                if(nums[i]->isNegative) {
                    a = "-" + nums[i]->nume + " / " + nums[i]->deno;
                    break;
                }
                else {
                    a = nums[i]->nume + " / " + nums[i]->deno;
                    break;
                }
            }
        }
    }
    if(a.find("(") != string::npos) bracket(a, nums);
    if(a.find("!") != string::npos) facto(a, nums);
    if(a.find("^") != string::npos) pow(a, nums);
    if(a.find("+") != string::npos || a.find("-") != string::npos) pm(a, nums);
//    if(a.find("*") != string::npos) md(a, nums);
    md(a, nums);
    if(a.find("+") != string::npos || a.find("-") != string::npos) add_dif(a, nums);
    return a;
}

void bracket(string& input, vector<NumberObject*>& nums) {
//        括弧内の処理（完成）
    bool found = true;
    while(found) {
        found = false;
        vector<int> LBI;            // left_bracket_index
        for(int i = 0; i < input.length(); i++) {
            if(input[i] == '(') {
                if(i == input.length()-1) {
                    bracket_error();
                }
                LBI.push_back(i);
            }
            else if(input[i] == ')') {
                if(!LBI.empty()) {
                    //                    エラーじゃない時は正常計算を実行して結果を置き換える
                    found = true;
                    string token = input.substr(LBI.back(), i - LBI.back() + 1);          //括弧付きの式を抜き取る
                    //                    char* formula = nullptr;
                    string formula = token;
                    formula.erase(0, 1);
                    formula.pop_back();
                    //                    sscanf(token.c_str(), "(%s)", formula);
                    string ans = simplify(formula, nums);
                    ans = simplify(ans, nums);
                    input.replace(input.find(token), token.length(), ans);
                    LBI.pop_back();
                    i = LBI.back();
                }
                else {
                    bracket_error();
                }
            }
            else if(i == input.length()-1) {
                if(!LBI.empty()) {
                    bracket_error();
                }
            }
        }
    }
//        括弧内処理終了
}

void facto(string& input, vector<NumberObject*>& nums) {
//        階乗の処理（完成）
        stringstream find_facto;
        find_facto << input;
        while(!find_facto.eof()) {
            string token;
            find_facto >> token;
            unsigned long last_index = token.length()-1;
            if(token[last_index] == '!') {
                string num;
                num = token.substr(0, last_index);
                num = simplify(num, nums);
//                if(token[0] == '(') {
////                    num = token.substr(1, last_index);
//                    char* formula = nullptr;
//                    sscanf(token.c_str(), "(%s)!", formula);
//                    string a = formula;
//                    num = simplify(a, nums);
//                }
//                else {
//                    num = token.substr(0, last_index);
//                }
//                numがNumberObject変数だったら置き換える
                for(int i = 0; i < nums.size(); i++) {
                    if(nums[i]->obj_name == num) {
                        if(nums[i]->int_val != "" && nums[i]->isNegative == false) {
                            num = nums[i]->int_val;
                            break;
                        }
                        else {
                            cout << "CALCULATION FAILED: NOT POSITIVE INTTERGER @_@" << endl;
                            exit(EXIT_FAILURE);
                        }
                    }
                }
//                    正の整数かどうか
                for(int i = 0; i < num.length(); i++) {
                    if(num[i] == '-') {
                        cout << "CALCULATION FAILED: NOT POSITIVE INTTERGER @_@" << endl;
                        exit(EXIT_FAILURE);
                    }
                    else if(num[i] == '.') {
                        for(int j = i+1; j < num.length(); j++) {
                            if(num[j] != '0') {
                                cout << "CALCULATION FAILED: NOT POSITIVE INTTERGER @_@" << endl;
                                exit(EXIT_FAILURE);
                            }
                        }
                        num = dec_to_int(num);
                    }
                }
//                正の整数で階乗計算が実行できるとき　計算を実行して結果を置き換える
                string ans = Factorial(num);
//                Integer Int = (char*)ans.c_str();
//                nums.push_back(&Int);
                input.replace(input.find(token), token.length(), ans);
            }
        }
//        階乗の処理終了
}

void pow(string& input, vector<NumberObject*>& nums) {
//        冪乗の処理（未完成）
        stringstream find_pow;
        find_pow << input;
        while(!find_pow.eof()) {
            string token;
            find_pow >> token;
            if(token.find("^") != string::npos) {
                
                string base, expo;
                std::string::size_type pos = token.find('^');
                base = token.substr(0, pos);
                expo = token.substr(pos+1);
//                sscanf(token.c_str(), "%s^%s", base, expo);
                string str1, str2;
                str2 = simplify(expo, nums);
                str1 = simplify(base, nums);
//                str1がNumberObject変数だったら置き換える
                for(int i = 0; i < nums.size(); i++) {
                    if(nums[i]->obj_name == str1) {
                        if(nums[i]->int_val != "") {
                            if(nums[i]->isNegative) {
                                str1 = "-" + nums[i]->int_val;
                                break;
                            }
                            else {
                                str1 = nums[i]->int_val;
                                break;
                            }
                            
                        }
                        else {
                            if(nums[i]->isNegative) {
//                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                                str1 = "-" + nums[i]->nume / nums[i]->deno;
                                break;
                            }
                            else {
//                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
                                str1 = nums[i]->nume / nums[i]->deno;
                                break;
                            }
                        }
                    }
                }
//                str2がNumberObject変数だったら置き換える
                for(int i = 0; i < nums.size(); i++) {
                    if(nums[i]->obj_name == str2) {
                        if(nums[i]->int_val != "") {
                            if(nums[i]->isNegative) {
                                str2 = "-" + nums[i]->int_val;
                                break;
                            }
                            else {
                                str2 = nums[i]->int_val;
                                break;
                            }
                            
                        }
                        else {
                            if(nums[i]->isNegative) {
//                                    str2 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                                str2 = "-" + nums[i]->nume / nums[i]->deno;
                                break;
                            }
                            else {
//                                    str2 = nums[i]->nume + " / " + nums[i]->deno;
                                str2 = nums[i]->nume / nums[i]->deno;
                                break;
                            }
                        }
                    }
                }
                
//                here str1 and str2 are supposed to be numbers not formula
                string ans = Power(str1, str2);
                input.replace(input.find(token), token.length(), ans);
            }
        }
//        冪乗処理終了
}

void pm(string& input, vector<NumberObject*>& nums) {
//        符号の処理（完成）
    if(input.substr(0, 2) == "+-") {
//                inputがNumberObject変数だったら置き換える
        for(int i = 0; i < nums.size(); i++) {
        if(nums[i]->obj_name == input.substr(2)) {
            if(nums[i]->int_val != "") {
                if(nums[i]->isNegative) {
//                    input = "-" + nums[i]->int_val;
                    input.replace(0, input.length(), nums[i]->int_val);
                    break;
                }
                else {
//                    input = nums[i]->int_val;
                    input.replace(0, input.length(), "-" + nums[i]->int_val);
                    break;
                }
                
            }
            else {
                if(nums[i]->isNegative) {
//                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
//                    input = "-" + nums[i]->nume / nums[i]->deno;
                    input.replace(0, input.length(), nums[i]->nume / nums[i]->deno);
//                    break;
                }
                else {
//                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
//                    input = nums[i]->nume / nums[i]->deno;
                    input.replace(0, input.length(), "-" + nums[i]->nume / nums[i]->deno);
//                    break;
                }
                while(input.back() == '0') input.pop_back();
                break;
            }
        }
    }
        input.replace(input.find("+-"), 2, "-");
    }
    else if(input.substr(0, 2) == "-+") {
//                inputがNumberObject変数だったら置き換える
        for(int i = 0; i < nums.size(); i++) {
        if(nums[i]->obj_name == input.substr(2)) {
            if(nums[i]->int_val != "") {
                if(nums[i]->isNegative) {
//                    input = "-" + nums[i]->int_val;
                    input.replace(0, input.length(), nums[i]->int_val);
                    break;
                }
                else {
//                    input = nums[i]->int_val;
                    input.replace(0, input.length(), "-" + nums[i]->int_val);
                    break;
                }
                
            }
            else {
                if(nums[i]->isNegative) {
//                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
//                    input = "-" + nums[i]->nume / nums[i]->deno;
                    input.replace(0, input.length(), nums[i]->nume / nums[i]->deno);
//                    break;
                }
                else {
//                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
//                    input = nums[i]->nume / nums[i]->deno;
                    input.replace(0, input.length(), "-" + nums[i]->nume / nums[i]->deno);
//                    break;
                }
                while(input.back() == '0') input.pop_back();
                break;
            }
        }
    }
        input.replace(input.find("-+"), 2, "-");
    }
    else if(input.substr(0, 2) == "--") {
        input.erase(0, 2);
//                inputがNumberObject変数だったら置き換える
        for(int i = 0; i < nums.size(); i++) {
        if(nums[i]->obj_name == input) {
            if(nums[i]->int_val != "") {
                if(nums[i]->isNegative) {
//                    input = "-" + nums[i]->int_val;
                    input.replace(0, input.length(), "-" + nums[i]->int_val);
                    break;
                }
                else {
//                    input = nums[i]->int_val;
                    input.replace(0, input.length(), nums[i]->int_val);
                    break;
                }
                
            }
            else {
                if(nums[i]->isNegative) {
//                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
//                    input = "-" + nums[i]->nume / nums[i]->deno;
                    input.replace(0, input.length(), "-" + nums[i]->nume / nums[i]->deno);
//                    break;
                }
                else {
//                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
//                    input = nums[i]->nume / nums[i]->deno;
                    input.replace(0, input.length(), nums[i]->nume / nums[i]->deno);
//                    break;
                }
                while(input.back() == '0') input.pop_back();
                break;
            }
        }
    }
    }
    else if(input.substr(0, 2) == "++") {
        input.erase(0, 2);
//                inputがNumberObject変数だったら置き換える
        for(int i = 0; i < nums.size(); i++) {
        if(nums[i]->obj_name == input) {
            if(nums[i]->int_val != "") {
                if(nums[i]->isNegative) {
//                    input = "-" + nums[i]->int_val;
                    input.replace(0, input.length(), "-" + nums[i]->int_val);
                    break;
                }
                else {
//                    input = nums[i]->int_val;
                    input.replace(0, input.length(), nums[i]->int_val);
                    break;
                }
                
            }
            else {
                if(nums[i]->isNegative) {
//                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
//                    input = "-" + nums[i]->nume / nums[i]->deno;
                    input.replace(0, input.length(), "-" + nums[i]->nume / nums[i]->deno);
//                    break;
                }
                else {
//                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
//                    input = nums[i]->nume / nums[i]->deno;
                    input.replace(0, input.length(), nums[i]->nume / nums[i]->deno);
//                    break;
                }
                while(input.back() == '0') input.pop_back();
                break;
            }
        }
    }
    }
    else if(input.substr(0, 1) == "+") {
        input.erase(0, 1);
//                inputがNumberObject変数だったら置き換える
        for(int i = 0; i < nums.size(); i++) {
        if(nums[i]->obj_name == input) {
            if(nums[i]->int_val != "") {
                if(nums[i]->isNegative) {
//                    input = "-" + nums[i]->int_val;
                    input.replace(0, input.length(), "-" + nums[i]->int_val);
                    break;
                }
                else {
//                    input = nums[i]->int_val;
                    input.replace(0, input.length(), nums[i]->int_val);
                    break;
                }
                
            }
            else {
                if(nums[i]->isNegative) {
//                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
//                    input = "-" + nums[i]->nume / nums[i]->deno;
                    input.replace(0, input.length(), "-" + nums[i]->nume / nums[i]->deno);
//                    break;
                }
                else {
//                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
//                    input = nums[i]->nume / nums[i]->deno;
                    input.replace(0, input.length(), nums[i]->nume / nums[i]->deno);
//                    break;
                }
                while(input.back() == '0') input.pop_back();
                break;
            }
        }
    }
    }
    else if(input.substr(0, 1) == "-") {
//                inputがNumberObject変数だったら置き換える
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i]->obj_name == input.substr(1)) {
                if(nums[i]->int_val != "") {
                    if(nums[i]->isNegative) {
    //                    input = "-" + nums[i]->int_val;
                        input.replace(0, nums[i]->obj_name.length(), nums[i]->int_val);
                        break;
                    }
                    else {
    //                    input = nums[i]->int_val;
                        input.replace(1, nums[i]->obj_name.length(), nums[i]->int_val);
                        break;
                    }
                    
                }
                else {
                    if(nums[i]->isNegative) {
    //                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
    //                    input = "-" + nums[i]->nume / nums[i]->deno;
                        input = nums[i]->nume / nums[i]->deno;
//                        break;
                    }
                    else {
    //                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
    //                    input = nums[i]->nume / nums[i]->deno;
                        input.replace(1, nums[i]->obj_name.length(), nums[i]->nume / nums[i]->deno);
//                        break;
                    }
                    while(input.back() == '0') input.pop_back();
                    break;
                }
            }
        }
    }
//        符号の処理終了
    return;
}

void md(string& input, vector<NumberObject*>& nums) {
//        掛け算、割り算の処理（完成）
    string tmp = input;
    stringstream mul_div;
    mul_div << input;
    while(!mul_div.eof()) {
        bool found = false;
        string str1, op1, str2, op2, str3;
        str1 = "";
        op1 = "";
        str2 = "";
        op2 = "";
        str3 = "";
        mul_div >> str1 >> op1 >> str2 >> op2 >> str3;
        
        if(op1 == "/" && op2 == "*") {
            found = true;
            string formula = str1 + " " + op1 + " " + str2 + " " + op2 + " " + str3;
//                str1がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str1) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str1 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str1 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str1 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str1.back() == '0') str1.pop_back();
                            break;
                        }
                        else {
//                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
                            str1 = nums[i]->nume / nums[i]->deno;
                            while(str1.back() == '0') str1.pop_back();
                            break;
                        }
                    }
                }
            }
//                str2がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str2) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str2 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str2 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str2 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str2 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str2.back() == '0') str2.pop_back();
                            break;
                        }
                        else {
//                                    str2 = nums[i]->nume + " / " + nums[i]->deno;
                            str2 = nums[i]->nume / nums[i]->deno;
                            while(str2.back() == '0') str2.pop_back();
                            break;
                        }
                    }
                }
            }
//                str3がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str3) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str3 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str3 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str3 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str3 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str3.back() == '0') str3.pop_back();
                            break;
                        }
                        else {
//                                    str3 = nums[i]->nume + " / " + nums[i]->deno;
                            str3 = nums[i]->nume / nums[i]->deno;
                            while(str3.back() == '0') str3.pop_back();
                            break;
                        }
                    }
                }
            }
            bool isInt1, isInt2, isInt3;
            isInt1 = isInt(str1);
            isInt2 = isInt(str2);
            isInt3 = isInt(str3);
            if(isInt1 && isInt2 && isInt3) {
                Integer int_1, int_2, int_3;
                int_1 = str1;
                int_2 = str2;
                int_3 = str3;
                Integer ans;
                ans = int_1 * int_3;
                string Ans;
                if(!int_1.isNegative && !int_2.isNegative && !int_3.isNegative) {
                    Ans = ans.int_val + " / " + str2;
                }
                else if(int_1.isNegative && int_2.isNegative && int_3.isNegative) {
                    Ans = ans.int_val + " / " + str2;
                }
                else if(!int_1.isNegative && !int_2.isNegative && int_3.isNegative) {
                    Ans = "-" + ans.int_val + " / " + str2;
                }
                else if(!int_1.isNegative && int_2.isNegative && !int_3.isNegative) {
                    Ans = ans.int_val + " / " + str2;
                }
                else if(int_1.isNegative && !int_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + ans.int_val + " / " + str2;
                }
                else if(int_1.isNegative && int_2.isNegative && !int_3.isNegative) {
                    Ans = ans.int_val + " / " + int_2.int_val;
                }
                else if(int_1.isNegative && !int_2.isNegative && int_3.isNegative) {
                    Ans = ans.int_val + " / " + str2;
                }
                else if(!int_1.isNegative && int_2.isNegative && int_3.isNegative) {
                    Ans = ans.int_val + " / " + int_2.int_val;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(!isInt1 && !isInt2 && !isInt3) {
                while(str1.back() == '0') str1.pop_back();
                while(str2.back() == '0') str2.pop_back();
                while(str3.back() == '0') str3.pop_back();
                Decimal dec_1, dec_2, dec_3;
                dec_1 = str1;
                dec_2 = str2;
                dec_3 = str3;
                Decimal ans;
                string Ans;
                ans = dec_1 * dec_3;
                Ans = ans.nume * dec_2.deno + " / " + ans.deno * dec_2.nume + ".0";
                if(dec_1.isNegative && dec_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && !dec_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && dec_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(dec_1.isNegative && !dec_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(isInt1 && isInt2 && !isInt3) {
                while(str3.back() == '0') str3.pop_back();
                Integer int_1, int_2;
                Decimal dec_3;
                int_1 = str1;
                int_2 = str2;
                dec_3 = str3;
                string Ans;
                Ans = int_1.int_val * dec_3.nume + " / " + int_2.int_val * dec_3.deno + ".0";
                if(int_1.isNegative && int_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!int_1.isNegative && !int_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!int_1.isNegative && int_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(int_1.isNegative && !int_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(isInt1 && !isInt2 && isInt3) {
                while(str2.back() == '0') str2.pop_back();
                Integer int_1, int_3;
                Decimal dec_2;
                int_1 = str1;
                dec_2 = str2;
                int_3 = str3;
                Integer ans;
                ans = int_1 * int_3;
                string Ans;
                Ans = ans.int_val * dec_2.deno + " / " + dec_2.nume + ".0";
                if(int_1.isNegative && dec_2.isNegative && int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!int_1.isNegative && !dec_2.isNegative && int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!int_1.isNegative && dec_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(int_1.isNegative && !dec_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(!isInt1 && isInt2 && isInt3) {
                while(str1.back() == '0') str1.pop_back();
                Integer int_2, int_3;
                Decimal dec_1;
                dec_1 = str1;
                int_2 = str2;
                int_3 = str3;
                string Ans;
                Ans = dec_1.nume * int_3.int_val + " / " + dec_1.deno * int_2.int_val + ".0";
                if(dec_1.isNegative && int_2.isNegative && int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && !int_2.isNegative && int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && int_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(dec_1.isNegative && !int_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(!isInt1 && !isInt2 && isInt3) {
                while(str2.back() == '0') str2.pop_back();
                while(str1.back() == '0') str1.pop_back();
                Integer int_3;
                Decimal dec_1, dec_2;
                dec_1 = str1;
                dec_2 = str2;
                int_3 = str3;
                string Ans;
                Ans = dec_1.nume * dec_2.deno * int_3.int_val + " / " + dec_1.deno * dec_2.nume + ".0";
                if(dec_1.isNegative && dec_2.isNegative && int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && !dec_2.isNegative && int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && dec_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(dec_1.isNegative && !dec_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(!isInt1 && isInt2 && !isInt3) {
                while(str1.back() == '0') str1.pop_back();
                while(str3.back() == '0') str3.pop_back();
                Integer int_2;
                Decimal dec_1, dec_3;
                dec_1 = str1;
                int_2 = str2;
                dec_3 = str3;
                string Ans;
                Ans = dec_1.nume * dec_3.nume + " / " + dec_1.deno * dec_3.deno * int_2.int_val + ".0";
                if(dec_1.isNegative && int_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && !int_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && int_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(dec_1.isNegative && !int_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(isInt1 && !isInt2 && !isInt3) {
                while(str2.back() == '0') str2.pop_back();
                while(str3.back() == '0') str3.pop_back();
                Integer int_1;
                Decimal dec_2, dec_3;
                int_1 = str1;
                dec_2 = str2;
                dec_3 = str3;
                string Ans;
                Ans = dec_2.deno * dec_3.nume * int_1.int_val + " / " + dec_2.nume * dec_3.deno + ".0";
                if(int_1.isNegative && dec_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!int_1.isNegative && !dec_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!int_1.isNegative && dec_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(int_1.isNegative && !dec_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
        }
        else if(op1 == "/" && op2 == "/") {
            found = true;
            string formula = str1 + " " + op1 + " " + str2 + " " + op2 + " " + str3;
//                str1がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str1) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str1 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str1 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str1 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str1.back() == '0') str1.pop_back();
                            break;
                        }
                        else {
//                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
                            str1 = nums[i]->nume / nums[i]->deno;
                            while(str1.back() == '0') str1.pop_back();
                            break;
                        }
                    }
                }
            }
//                str2がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str2) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str2 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str2 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str2 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str2 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str2.back() == '0') str2.pop_back();
                            break;
                        }
                        else {
//                                    str2 = nums[i]->nume + " / " + nums[i]->deno;
                            str2 = nums[i]->nume / nums[i]->deno;
                            while(str2.back() == '0') str2.pop_back();
                            break;
                        }
                    }
                }
            }
//                str3がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str3) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str3 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str3 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str3 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str3 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str3.back() == '0') str3.pop_back();
                            break;
                        }
                        else {
//                                    str3 = nums[i]->nume + " / " + nums[i]->deno;
                            str3 = nums[i]->nume / nums[i]->deno;
                            while(str3.back() == '0') str3.pop_back();
                            break;
                        }
                    }
                }
            }
            
            bool isInt1, isInt2, isInt3;
            isInt1 = isInt(str1);
            isInt2 = isInt(str2);
            isInt3 = isInt(str3);
            if(isInt1 && isInt2 && isInt3) {
                Integer int_1, int_2, int_3;
                int_1 = str1;
                int_2 = str2;
                int_3 = str3;
                Integer ans;
                ans = int_2 * int_3;
                string Ans;
                if(!int_1.isNegative && !int_2.isNegative && !int_3.isNegative) {
                    Ans = str1 + " / " + ans.int_val;
                }
                else if(int_1.isNegative && int_2.isNegative && int_3.isNegative) {
                    Ans = int_1.int_val + " / " + ans.int_val;
                }
                else if(!int_1.isNegative && !int_2.isNegative && int_3.isNegative) {
                    Ans = int_1.int_val + " / -" + ans.int_val;
                }
                else if(!int_1.isNegative && int_2.isNegative && !int_3.isNegative) {
                    Ans = int_1.int_val + " / -" + ans.int_val;
                }
                else if(int_1.isNegative && !int_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + int_1.int_val + " / " + ans.int_val;
                }
                else if(int_1.isNegative && int_2.isNegative && !int_3.isNegative) {
                    Ans = int_1.int_val + " / " + ans.int_val;
                }
                else if(int_1.isNegative && !int_2.isNegative && int_3.isNegative) {
                    Ans = int_1.int_val + " / " + ans.int_val;
                }
                else if(!int_1.isNegative && int_2.isNegative && int_3.isNegative) {
                    Ans = int_1.int_val + " / " + ans.int_val;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(!isInt1 && !isInt2 && !isInt3) {
                while(str1.back() == '0') str1.pop_back();
                while(str2.back() == '0') str2.pop_back();
                while(str3.back() == '0') str3.pop_back();
                Decimal dec_1, dec_2, dec_3;
                dec_1 = str1;
                dec_2 = str2;
                dec_3 = str3;
                string Ans;
                Ans = dec_1.nume * dec_2.deno * dec_3.deno + " / " + dec_1.deno * dec_2.nume * dec_3.nume + ".0";
                if(dec_1.isNegative && dec_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && !dec_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && dec_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(dec_1.isNegative && !dec_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(isInt1 && isInt2 && !isInt3) {
                while(str3.back() == '0') str3.pop_back();
                Integer int_1, int_2;
                Decimal dec_3;
                int_1 = str1;
                int_2 = str2;
                dec_3 = str3;
                string Ans;
                Ans = int_1.int_val * dec_3.deno + " / " + int_2.int_val * dec_3.nume + ".0";
                if(int_1.isNegative && int_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!int_1.isNegative && !int_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!int_1.isNegative && int_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(int_1.isNegative && !int_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(isInt1 && !isInt2 && isInt3) {
                while(str2.back() == '0') str2.pop_back();
                Integer int_1, int_3;
                Decimal dec_2;
                int_1 = str1;
                dec_2 = str2;
                int_3 = str3;
                string Ans;
                Ans = int_1.int_val * dec_2.deno + " / " + int_3.int_val * dec_2.nume + ".0";
                if(int_1.isNegative && dec_2.isNegative && int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!int_1.isNegative && !dec_2.isNegative && int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!int_1.isNegative && dec_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(int_1.isNegative && !dec_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(!isInt1 && isInt2 && isInt3) {
                while(str1.back() == '0') str1.pop_back();
                Integer int_2, int_3;
                Decimal dec_1;
                dec_1 = str1;
                int_2 = str2;
                int_3 = str3;
                string Ans;
                Ans = dec_1.nume + " / " + dec_1.deno * int_2.int_val * int_3.int_val + ".0";
                if(dec_1.isNegative && int_2.isNegative && int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && !int_2.isNegative && int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && int_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(dec_1.isNegative && !int_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(!isInt1 && !isInt2 && isInt3) {
                while(str1.back() == '0') str1.pop_back();
                while(str2.back() == '0') str2.pop_back();
                Integer int_3;
                Decimal dec_1, dec_2;
                dec_1 = str1;
                dec_2 = str2;
                int_3 = str3;
                string Ans;
                Ans = dec_1.nume * dec_2.deno + " / " + dec_1.deno * dec_2.nume * int_3.int_val + ".0";
                if(dec_1.isNegative && dec_2.isNegative && int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && !dec_2.isNegative && int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && dec_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(dec_1.isNegative && !dec_2.isNegative && !int_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(!isInt1 && isInt2 && !isInt3) {
                while(str1.back() == '0') str1.pop_back();
                while(str3.back() == '0') str3.pop_back();
                Integer int_2;
                Decimal dec_1, dec_3;
                dec_1 = str1;
                int_2 = str2;
                dec_3 = str3;
                string Ans;
                Ans = dec_1.nume * dec_3.deno + " / " + dec_1.deno * dec_3.nume * int_2.int_val + ".0";
                if(dec_1.isNegative && int_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && !int_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!dec_1.isNegative && int_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(dec_1.isNegative && !int_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else if(isInt1 && !isInt2 && !isInt3) {
                while(str2.back() == '0') str2.pop_back();
                while(str3.back() == '0') str3.pop_back();
                Integer int_1;
                Decimal dec_2, dec_3;
                int_1 = str1;
                dec_2 = str2;
                dec_3 = str3;
                string Ans;
                Ans = dec_2.deno * dec_3.deno * int_1.int_val + " / " + dec_2.nume * dec_3.nume + ".0";
                if(int_1.isNegative && dec_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!int_1.isNegative && !dec_2.isNegative && dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(!int_1.isNegative && dec_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                else if(int_1.isNegative && !dec_2.isNegative && !dec_3.isNegative) {
                    Ans = "-" + Ans;
                }
                input.replace(input.find(formula), formula.length(), Ans);
            }
        }
        else if(op1 == "*") {
            found = true;
            string formula = str1 + " " + op1 + " " + str2;
//                str1がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str1) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str1 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str1 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str1 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str1.back() == '0') str1.pop_back();
                            break;
                        }
                        else {
//                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
                            str1 = nums[i]->nume / nums[i]->deno;
                            while(str1.back() == '0') str1.pop_back();
                            break;
                        }
                    }
                }
            }
//                str2がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str2) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str2 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str2 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str2 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str2 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str2.back() == '0') str2.pop_back();
                            break;
                        }
                        else {
//                                    str2 = nums[i]->nume + " / " + nums[i]->deno;
                            str2 = nums[i]->nume / nums[i]->deno;
                            while(str2.back() == '0') str2.pop_back();
                            break;
                        }
                    }
                }
            }
            
            bool str1_isInt, str2_isInt;
            str1_isInt = isInt(str1);
            str2_isInt = isInt(str2);
            
            if(str1_isInt && str2_isInt) {
//                str1 と str2 はどちらも整数
                Integer ad1, ad2, ans;
                ad1 = str1;
                ad2 = str2;
                if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
                    ans = ad1 * ad2;
                    input.replace(input.find(formula), formula.length(), ans.int_val);
                }
                else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
                    ans = ad1 * ad2;
                    input.replace(input.find(formula), formula.length(), ans.int_val);
                }
                else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
                    ans = ad1 * ad2;
                    string Ans = "-" + ans.int_val;
                    input.replace(input.find(formula), formula.length(), Ans);
                }
                else {
//                    ad1は負 ad2は正
                    ans = ad1 * ad2;
                    string Ans = "-" + ans.int_val;
                    input.replace(input.find(formula), formula.length(), Ans);
                }
            }
            else if(str1_isInt && !str2_isInt){
                while(str2.back() == '0') str2.pop_back();
//                str1 は整数 str2は小数
                Integer ad1; Decimal ad2;
                ad1 = str1;
                ad2 = str2;
                if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
                    string dec = ad1.int_val * ad2.nume + " / " + ad2.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
                    string dec = ad1.int_val * ad2.nume + " / " + ad2.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
                    string dec = "-" + ad1.int_val * ad2.nume + " / " + ad2.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else {
//                    ad1は負 ad2は正
                    string dec = "-" + ad1.int_val * ad2.nume + " / " + ad2.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
            }
            else if(!str1_isInt && str2_isInt) {
                while(str1.back() == '0') str1.pop_back();
//                str1は小数 str2は整数
                Decimal ad1; Integer ad2;
                ad1 = str1;
                ad2 = str2;
                if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
                    string dec = ad1.nume * ad2.int_val + " / " + ad1.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
                    string dec = ad1.nume * ad2.int_val + " / " + ad1.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
                    string dec = "-" + ad1.nume * ad2.int_val + " / " + ad1.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else {
//                    ad1は負 ad2は正
                    string dec = "-" + ad1.nume * ad2.int_val + " / " + ad1.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
            }
            else {
                while(str1.back() == '0') str1.pop_back();
                while(str2.back() == '0') str2.pop_back();
//                str1 と str2は小数
                Decimal ad1, ad2;
                ad1 = str1;
                ad2 = str2;
                if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
                    string dec = ad1.nume * ad2.nume + " / " + ad1.deno * ad2.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
                    string dec = ad1.nume * ad2.nume + " / " + ad1.deno * ad2.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
                    string dec = "-" + ad1.nume * ad2.nume + " / " + ad1.deno * ad2.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else {
//                    ad1は負 ad2は正
                    string dec = "-" + ad1.nume * ad2.nume + " / " + ad1.deno * ad2.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
            }
        }
        else if(op1 == "/") {
            found = true;
            string formula = str1 + " " + op1 + " " + str2;
//                str1がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str1) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str1 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str1 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str1 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str1.back() == '0') str1.pop_back();
                            break;
                        }
                        else {
//                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
                            str1 = nums[i]->nume / nums[i]->deno;
                            while(str1.back() == '0') str1.pop_back();
                            break;
                        }
                    }
                }
            }
//                str2がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str2) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str2 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str2 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str2 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str2 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str2.back() == '0') str2.pop_back();
                            break;
                        }
                        else {
//                                    str2 = nums[i]->nume + " / " + nums[i]->deno;
                            str2 = nums[i]->nume / nums[i]->deno;
                            while(str2.back() == '0') str2.pop_back();
                            break;
                        }
                    }
                }
            }
            
            bool str1_isInt, str2_isInt;
            str1_isInt = isInt(str1);
            str2_isInt = isInt(str2);
            
            if(str1_isInt && str2_isInt) {
//                str1 と str2 はどちらも整数
                Integer ad1, ad2, ans;
                ad1 = str1;
                ad2 = str2;
                if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
                    ans = ad1 / ad2;
                    input.replace(input.find(formula), formula.length(), ans.int_val);
                }
                else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
                    ans = ad1 / ad2;
                    input.replace(input.find(formula), formula.length(), ans.int_val);
                }
                else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
                    ans = ad1 / ad2;
                    string Ans = "-" + ans.int_val;
                    input.replace(input.find(formula), formula.length(), Ans);
                }
                else {
//                    ad1は負 ad2は正
                    ans = ad1 / ad2;
                    string Ans = "-" + ans.int_val;
                    input.replace(input.find(formula), formula.length(), Ans);
                }
            }
            else if(str1_isInt && !str2_isInt){
                while(str2.back() == '0') str2.pop_back();
                if(str2.back() == '.') str2.push_back(0x30);
//                str1 は整数 str2は小数
                Integer ad1; Decimal ad2;
                ad1 = str1;
                ad2 = str2;
                if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
//                    string dec = ad1.int_val * ad2.deno + " / " + ad2.nume + ".0";
                    string dec = ad1.int_val * ad2.deno / ad2.nume;
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
//                    string dec = ad1.int_val * ad2.deno + " / " + ad2.nume + ".0";
                    string dec = ad1.int_val * ad2.deno / ad2.nume;
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
//                    string dec = "-" + ad1.int_val * ad2.deno + " / " + ad2.nume + ".0";
                    string dec = "-" + ad1.int_val * ad2.deno / ad2.nume;
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else {
//                    ad1は負 ad2は正
//                    string dec = "-" + ad1.int_val * ad2.deno + " / " + ad2.nume + ".0";
                    string dec = "-" + ad1.int_val * ad2.deno / ad2.nume;
                    input.replace(input.find(formula), formula.length(), dec);
                }
            }
            else if(!str1_isInt && str2_isInt) {
                while(str1.back() == '0') str1.pop_back();
                if(str1.back() == '.') str1.push_back(0x30);
//                str1は小数 str2は整数
                Decimal ad1; Integer ad2;
                ad1 = str1;
                ad2 = str2;
                if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
//                    string dec = ad1.nume + " / " + ad1.deno * ad2.int_val + ".0";
                    string dec = ad1.nume / ad1.deno * ad2.int_val;
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
//                    string dec = ad1.nume + " / " + ad1.deno * ad2.int_val + ".0";
                    string dec = ad1.nume / ad1.deno * ad2.int_val;
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
//                    string dec = "-" + ad1.nume + " / " + ad1.deno * ad2.int_val + ".0";
                    string dec = "-" + ad1.nume / ad1.deno * ad2.int_val;
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else {
//                    ad1は負 ad2は正
//                    string dec = "-" + ad1.nume + " / " + ad1.deno * ad2.int_val + ".0";
                    string deno = ad1.deno * ad2.int_val;
                    string dec = "-" + (ad1.nume / deno);
                    input.replace(input.find(formula), formula.length(), dec);
                }
            }
            else {
                while(str1.back() == '0') str1.pop_back();
                while(str2.back() == '0') str2.pop_back();
//                str1 と str2は小数
                Decimal ad1, ad2;
                ad1 = str1;
                ad2 = str2;
                if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
//                    string dec = ad1.deno * ad2.deno + " / " + ad1.nume * ad2.nume + ".0";
                    string dec = (ad1.nume * ad2.deno) / (ad1.deno * ad2.nume);
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
//                    string dec = ad1.deno * ad2.deno + " / " + ad1.nume * ad2.nume + ".0";
                    string dec = (ad1.nume * ad2.deno) / (ad1.deno * ad2.nume);
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
//                    string dec = "-" + ad1.deno * ad2.deno + " / " + ad1.nume * ad2.nume + ".0";
                    string dec = "-" + (ad1.nume * ad2.deno) / (ad1.deno * ad2.nume);
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else {
//                    ad1は負 ad2は正
//                    string dec = "-" + ad1.deno * ad2.deno + " / " + ad1.nume * ad2.nume + ".0";
                    string dec = "-" + (ad1.nume * ad2.deno) / (ad1.deno * ad2.nume);
                    input.replace(input.find(formula), formula.length(), dec);
                }
            }
        }
        
        if(found) {
            tmp = input;
        }
        string trash;
        mul_div.str("");
        mul_div.clear();
        mul_div << tmp;
        mul_div >> trash;
        tmp.erase(0, trash.length()+1);
    }
//    simplify(input, nums);
    div_final(input, nums);
//        掛け算、割り算の処理終了
}

void ad(string& input, vector<NumberObject*>& nums) {
//        足し算の処理（完成）
        stringstream find_add;
        find_add << input;
        string str1, op, str2;                  // str1 and str2 are supposed to be positive, so we should deal with this problem!! (done)
        find_add >> str1 >> op >> str2;
        if(op == "+") {
            string formula = str1 + " " + op + " " + str2;
//                str1がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str1) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str1 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str1 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str1 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str1.back() == '0') str1.pop_back();
                            break;
                        }
                        else {
//                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
                            str1 = nums[i]->nume / nums[i]->deno;
                            while(str1.back() == '0') str1.pop_back();
                            break;
                        }
                    }
                }
            }
//                str2がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str2) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str2 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str2 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str2 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str2 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str2.back() == '0') str2.pop_back();
                            break;
                        }
                        else {
//                                    str2 = nums[i]->nume + " / " + nums[i]->deno;
                            str2 = nums[i]->nume / nums[i]->deno;
                            while(str2.back() == '0') str2.pop_back();
                            break;
                        }
                    }
                }
            }
            bool str1_isInt, str2_isInt;
            str1_isInt = isInt(str1);
            str2_isInt = isInt(str2);
            
            if(str1_isInt && str2_isInt) {
//                str1 と str2 はどちらも整数
                Integer ad1, ad2, ans;
                ad1 = str1;
                ad2 = str2;
                if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
                    ans = ad1 + ad2;
                    input.replace(input.find(formula), formula.length(), ans.int_val);
                }
                else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
                    ans = ad1 + ad2;
                    string Ans = "-" + ans.int_val;
                    input.replace(input.find(formula), formula.length(), Ans);
                }
                else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
                    ans = ad1 - ad2;
                    if(ans.isNegative) {
                        string Ans = "-" + ans.int_val;
                        input.replace(input.find(formula), formula.length(), Ans);
                    }
                    else {
                        input.replace(input.find(formula), formula.length(), ans.int_val);
                    }
                }
                else {
//                    ad1は負 ad2は正
                    ans = ad2 - ad1;
                    if(ans.isNegative) {
                        string Ans = "-" + ans.int_val;
                        input.replace(input.find(formula), formula.length(), Ans);
                    }
                    else {
                        input.replace(input.find(formula), formula.length(), ans.int_val);
                    }
                }
            }
            else if(str1_isInt && !str2_isInt){
                while(str2.back() == '0') str2.pop_back();
//                str1 は整数 str2は小数
                Integer ad1; Decimal ad2, ans;
                ad1 = str1;
                ad2 = str2;
                if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
                    ans = ad1 + ad2;
                    string dec = ans.nume + " / " + ans.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
                    ans = ad1 + ad2;
                    string dec = "-" + ans.nume + " / " + ans.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
                    ans = ad1 - ad2;
                    string dec = ans.nume + " / " + ans.deno + ".0";
                    if(ans.isNegative) dec = "-" + dec;
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else {
//                    ad1は負 ad2は正
                    ans = ad2 - ad1;
                    string dec = ans.nume + " / " + ans.deno + ".0";
                    if(ans.isNegative) dec = "-" + dec;
                    input.replace(input.find(formula), formula.length(), dec);
                }
            }
            else if(!str1_isInt && str2_isInt) {
                while(str1.back() == '0') str1.pop_back();
//                str1は小数 str2は整数
                Decimal ad1, ans; Integer ad2;
                ad1 = str1;
                ad2 = str2;
                if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
                    ans = ad1 + ad2;
                    string dec = ans.nume + " / " + ans.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
                    ans = ad1 + ad2;
                    string dec = "-" + ans.nume + " / " + ans.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
                    ans = ad1 - ad2;
                    string dec = ans.nume + " / " + ans.deno + ".0";
                    if(ans.isNegative) dec = "-" + dec;
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else {
//                    ad1は負 ad2は正
                    ans = ad2 - ad1;
                    string dec = ans.nume + " / " + ans.deno + ".0";
                    if(ans.isNegative) dec = "-" + dec;
                    input.replace(input.find(formula), formula.length(), dec);
                }
            }
            else {
                while(str1.back() == '0') str1.pop_back();
                while(str2.back() == '0') str2.pop_back();
//                str1 と str2は小数
                Decimal ad1, ad2, ans;
                ad1 = str1;
                ad2 = str2;
                if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
                    ans = ad1 + ad2;
                    string dec = ans.nume + " / " + ans.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
                    ans = ad1 + ad2;
                    string dec = "-" + ans.nume + " / " + ans.deno + ".0";
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
                    ans = ad1 - ad2;
                    string dec = ans.nume + " / " + ans.deno + ".0";
                    if(ans.isNegative) dec = "-" + dec;
                    input.replace(input.find(formula), formula.length(), dec);
                }
                else {
//                    ad1は負 ad2は正
                    ans = ad2 - ad1;
                    string dec = ans.nume + " / " + ans.deno + ".0";
                    if(ans.isNegative) dec = "-" + dec;
                    input.replace(input.find(formula), formula.length(), dec);
                }
            }
        }
//        足し算の処理終了
//    simplify(input, nums);
}

void dif(string& input, vector<NumberObject*>& nums) {
    //        引き算の処理（完成）
            stringstream find_add;
            find_add << input;
            string str1, op, str2;                  // str1 and str2 are supposed to be positive, so we should deal with this problem!! (done)
            find_add >> str1 >> op >> str2;
            if(op == "-") {
                string formula = str1 + " " + op + " " + str2;
    //                str1がNumberObject変数だったら置き換える
                for(int i = 0; i < nums.size(); i++) {
                    if(nums[i]->obj_name == str1) {
                        if(nums[i]->int_val != "") {
                            if(nums[i]->isNegative) {
                                str1 = "-" + nums[i]->int_val;
                                break;
                            }
                            else {
                                str1 = nums[i]->int_val;
                                break;
                            }
                            
                        }
                        else {
                            if(nums[i]->isNegative) {
    //                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                                str1 = "-" + nums[i]->nume / nums[i]->deno;
                                while(str1.back() == '0') str1.pop_back();
                                break;
                            }
                            else {
    //                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
                                str1 = nums[i]->nume / nums[i]->deno;
                                while(str1.back() == '0') str1.pop_back();
                                break;
                            }
                        }
                    }
                }
    //                str2がNumberObject変数だったら置き換える
                for(int i = 0; i < nums.size(); i++) {
                    if(nums[i]->obj_name == str2) {
                        if(nums[i]->int_val != "") {
                            if(nums[i]->isNegative) {
                                str2 = "-" + nums[i]->int_val;
                                break;
                            }
                            else {
                                str2 = nums[i]->int_val;
                                break;
                            }
                            
                        }
                        else {
                            if(nums[i]->isNegative) {
    //                                    str2 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                                str2 = "-" + nums[i]->nume / nums[i]->deno;
                                while(str2.back() == '0') str2.pop_back();
                                break;
                            }
                            else {
    //                                    str2 = nums[i]->nume + " / " + nums[i]->deno;
                                str2 = nums[i]->nume / nums[i]->deno;
                                while(str2.back() == '0') str2.pop_back();
                                break;
                            }
                        }
                    }
                }
                bool str1_isInt, str2_isInt;
                str1_isInt = isInt(str1);
                str2_isInt = isInt(str2);
                
                if(str1_isInt && str2_isInt) {
    //                str1 と str2 はどちらも整数
                    Integer ad1, ad2, ans;
                    ad1 = str1;
                    ad2 = str2;
                    if(!ad1.isNegative && !ad2.isNegative) {
    //                    ad1 と ad2 はどちらも正
                        ans = ad1 - ad2;
                        if(ans.isNegative) {
                            string Ans = "-" + ans.int_val;
                            input.replace(input.find(formula), formula.length(), Ans);
                        }
                        else {
                            input.replace(input.find(formula), formula.length(), ans.int_val);
                        }
                    }
                    else if(ad1.isNegative && ad2.isNegative) {
    //                    ad1 と ad2 はどちらも負
                        ans = ad2 - ad1;
                        if(ans.isNegative) {
                            string Ans = "-" + ans.int_val;
                            input.replace(input.find(formula), formula.length(), Ans);
                        }
                        else {
                            input.replace(input.find(formula), formula.length(), ans.int_val);
                        }
                    }
                    else if(!ad1.isNegative && ad2.isNegative) {
    //                    ad1は正 ad2は負
                        ans = ad1 + ad2;
                        input.replace(input.find(formula), formula.length(), ans.int_val);
                    }
                    else {
    //                    ad1は負 ad2は正
                        ans = ad1 + ad2;
                        string Ans = "-" + ans.int_val;
                        input.replace(input.find(formula), formula.length(), Ans);
                    }
                }
                else if(str1_isInt && !str2_isInt){
                    while(str2.back() == '0') str2.pop_back();
    //                str1 は整数 str2は小数
                    Integer ad1; Decimal ad2, ans;
                    ad1 = str1;
                    ad2 = str2;
                    if(!ad1.isNegative && !ad2.isNegative) {
    //                    ad1 と ad2 はどちらも正
                        ans = ad1 - ad2;
                        string dec = ans.nume + " / " + ans.deno + ".0";
                        if(ans.isNegative) {
                            dec = "-" + dec;
                        }
                        input.replace(input.find(formula), formula.length(), dec);
                    }
                    else if(ad1.isNegative && ad2.isNegative) {
    //                    ad1 と ad2 はどちらも負
                        ans = ad2 - ad1;
                        string dec = ans.nume + " / " + ans.deno + ".0";
                        if(ans.isNegative) {
                            dec = "-" + dec;
                        }
                        input.replace(input.find(formula), formula.length(), dec);
                    }
                    else if(!ad1.isNegative && ad2.isNegative) {
    //                    ad1は正 ad2は負
                        ans = ad1 + ad2;
                        string dec = ans.nume + " / " + ans.deno + ".0";
                        input.replace(input.find(formula), formula.length(), dec);
                    }
                    else {
    //                    ad1は負 ad2は正
                        ans = ad1 + ad2;
                        string dec = ans.nume + " / " + ans.deno + ".0";
                        dec = "-" + dec;
                        input.replace(input.find(formula), formula.length(), dec);
                    }
                }
                else if(!str1_isInt && str2_isInt) {
                    while(str1.back() == '0') str1.pop_back();
    //                str1は小数 str2は整数
                    Decimal ad1, ans; Integer ad2;
                    ad1 = str1;
                    ad2 = str2;
                    if(!ad1.isNegative && !ad2.isNegative) {
    //                    ad1 と ad2 はどちらも正
                        ans = ad1 - ad2;
                        string dec = ans.nume + " / " + ans.deno + ".0";
                        if(ans.isNegative) dec = "-" + dec;
                        input.replace(input.find(formula), formula.length(), dec);
                    }
                    else if(ad1.isNegative && ad2.isNegative) {
    //                    ad1 と ad2 はどちらも負
                        ans = ad2 - ad1;
                        string dec = ans.nume + " / " + ans.deno + ".0";
                        if(ans.isNegative) dec = "-" + dec;
                        input.replace(input.find(formula), formula.length(), dec);
                    }
                    else if(!ad1.isNegative && ad2.isNegative) {
    //                    ad1は正 ad2は負
                        ans = ad1 + ad2;
                        string dec = ans.nume + " / " + ans.deno + ".0";
                        input.replace(input.find(formula), formula.length(), dec);
                    }
                    else {
    //                    ad1は負 ad2は正
                        ans = ad1 + ad2;
                        string dec = ans.nume + " / " + ans.deno + ".0";
                        dec = "-" + dec;
                        input.replace(input.find(formula), formula.length(), dec);
                    }
                }
                else {
                    while(str1.back() == '0') str1.pop_back();
                    while(str2.back() == '0') str2.pop_back();
    //                str1 と str2は小数
                    Decimal ad1, ad2, ans;
                    ad1 = str1;
                    ad2 = str2;
                    if(!ad1.isNegative && !ad2.isNegative) {
    //                    ad1 と ad2 はどちらも正
                        ans = ad1 - ad2;
                        string dec = ans.nume + " / " + ans.deno + ".0";
                        if(ans.isNegative) dec = "-" + dec;
                        input.replace(input.find(formula), formula.length(), dec);
                    }
                    else if(ad1.isNegative && ad2.isNegative) {
    //                    ad1 と ad2 はどちらも負
                        ans = ad2 - ad1;
                        string dec = ans.nume + " / " + ans.deno + ".0";
                        if(ans.isNegative) dec = "-" + dec;
                        input.replace(input.find(formula), formula.length(), dec);
                    }
                    else if(!ad1.isNegative && ad2.isNegative) {
    //                    ad1は正 ad2は負
                        ans = ad1 + ad2;
                        string dec = ans.nume + " / " + ans.deno + ".0";
                        input.replace(input.find(formula), formula.length(), dec);
                    }
                    else {
    //                    ad1は負 ad2は正
                        ans = ad1 + ad2;
                        string dec = ans.nume + " / " + ans.deno + ".0";
                        dec = "-" + dec;
                        input.replace(input.find(formula), formula.length(), dec);
                    }
                }
            }
    //        引き算の処理終了
//    simplify(input, nums);
}

string div_final(string& input, vector<NumberObject*>& nums) {
    stringstream find_div;
    string str1, op1, str2;
    find_div << input;
    find_div >> str1 >> op1 >> str2;
    if(op1 == "/") {
        string formula = str1 + " " + op1 + " " + str2;
        
//                str1がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str1) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str1 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str1 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str1 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str1 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str1.back() == '0') str1.pop_back();
                            break;
                        }
                        else {
//                                    str1 = nums[i]->nume + " / " + nums[i]->deno;
                            str1 = nums[i]->nume / nums[i]->deno;
                            while(str1.back() == '0') str1.pop_back();
                            break;
                        }
                    }
                }
            }
//                str2がNumberObject変数だったら置き換える
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == str2) {
                    if(nums[i]->int_val != "") {
                        if(nums[i]->isNegative) {
                            str2 = "-" + nums[i]->int_val;
                            break;
                        }
                        else {
                            str2 = nums[i]->int_val;
                            break;
                        }
                        
                    }
                    else {
                        if(nums[i]->isNegative) {
//                                    str2 = "-" + nums[i]->nume + " / " + nums[i]->deno;
                            str2 = "-" + nums[i]->nume / nums[i]->deno;
                            while(str2.back() == '0') str2.pop_back();
                            break;
                        }
                        else {
//                                    str2 = nums[i]->nume + " / " + nums[i]->deno;
                            str2 = nums[i]->nume / nums[i]->deno;
                            while(str2.back() == '0') str2.pop_back();
                            break;
                        }
                    }
                }
            }
        
        bool str1_isInt, str2_isInt;
        str1_isInt = isInt(str1);
        str2_isInt = isInt(str2);
        
        if(str1_isInt && str2_isInt) {
//                str1 と str2 はどちらも整数
            Integer ad1, ad2, ans;
            ad1 = str1;
            ad2 = str2;
            if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
                ans = ad1 / ad2;
                input.replace(input.find(formula), formula.length(), ans.int_val);
            }
            else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
                ans = ad1 / ad2;
                input.replace(input.find(formula), formula.length(), ans.int_val);
            }
            else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
                ans = ad1 / ad2;
                string Ans = "-" + ans.int_val;
                input.replace(input.find(formula), formula.length(), Ans);
            }
            else {
//                    ad1は負 ad2は正
                ans = ad1 / ad2;
                string Ans = "-" + ans.int_val;
                input.replace(input.find(formula), formula.length(), Ans);
            }
        }
        else if(str1_isInt && !str2_isInt){
            while(str2.back() == '0') str2.pop_back();
//                str1 は整数 str2は小数
            Integer ad1; Decimal ad2;
            ad1 = str1;
            ad2 = str2;
            if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
                string dec = (ad1.int_val * ad2.deno) / ad2.nume;
                input.replace(input.find(formula), formula.length(), dec);
            }
            else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
                string dec = (ad1.int_val * ad2.deno) / ad2.nume;
                input.replace(input.find(formula), formula.length(), dec);
            }
            else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
                string dec = "-" + (ad1.int_val * ad2.deno) / ad2.nume;
                input.replace(input.find(formula), formula.length(), dec);
            }
            else {
//                    ad1は負 ad2は正
                string dec = "-" + (ad1.int_val * ad2.deno) / ad2.nume;
                input.replace(input.find(formula), formula.length(), dec);
            }
        }
        else if(!str1_isInt && str2_isInt) {
            while(str1.back() == '0') str1.pop_back();
//                str1は小数 str2は整数
            Decimal ad1; Integer ad2;
            ad1 = str1;
            ad2 = str2;
            if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
                string dec = (ad1.deno * ad2.int_val) / ad1.nume;
                input.replace(input.find(formula), formula.length(), dec);
            }
            else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
                string dec = (ad1.deno * ad2.int_val) / ad1.nume;
                input.replace(input.find(formula), formula.length(), dec);
            }
            else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
                string dec = "-" + (ad1.deno * ad2.int_val) / ad1.nume;
                input.replace(input.find(formula), formula.length(), dec);
            }
            else {
//                    ad1は負 ad2は正
                string dec = "-" + (ad1.deno * ad2.int_val) / ad1.nume;
                input.replace(input.find(formula), formula.length(), dec);
            }
        }
        else {
            while(str1.back() == '0') str1.pop_back();
            while(str2.back() == '0') str2.pop_back();
//                str1 と str2は小数
            Decimal ad1, ad2;
            ad1 = str1;
            ad2 = str2;
            if(!ad1.isNegative && !ad2.isNegative) {
//                    ad1 と ad2 はどちらも正
                string dec = (ad1.deno * ad2.deno) / (ad1.nume * ad2.nume);
                input.replace(input.find(formula), formula.length(), dec);
            }
            else if(ad1.isNegative && ad2.isNegative) {
//                    ad1 と ad2 はどちらも負
                string dec = (ad1.deno * ad2.deno) / (ad1.nume * ad2.nume);
                input.replace(input.find(formula), formula.length(), dec);
            }
            else if(!ad1.isNegative && ad2.isNegative) {
//                    ad1は正 ad2は負
                string dec = "-" + (ad1.deno * ad2.deno) / (ad1.nume * ad2.nume);
                input.replace(input.find(formula), formula.length(), dec);
            }
            else {
//                    ad1は負 ad2は正
                string dec = "-" + (ad1.deno * ad2.deno) / (ad1.nume * ad2.nume);
                input.replace(input.find(formula), formula.length(), dec);
            }
        }
    }
    return input;
}

void add_dif(string& input, vector<NumberObject*>& nums) {
    ad(input, nums);
    dif(input, nums);
    dif(input, nums);
    ad(input, nums);
    div_final(input, nums);
//    simplify(input, nums);
}
