#include <iostream>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstring>
#include "NumberObject.hpp"
#include "Integer.hpp"
#include "Decimal.hpp"
#include "Function.hpp"
using namespace std;


int main() {
    
//    Integer x;
//    Decimal y;
//
//    cin >> x; // 123456789
//    cin >> y; // 3.1415926
//
//    cout << x + y << endl;
//    cout << x - y << endl;
//    cout << x * y << endl;
//    cout << x / y << endl;

    Integer x = "123 * 8 + 456";
    Decimal y = "-1.0 / 3 - 45 / 13.0";

    vector<NumberObject*> nums;
    nums.push_back(&x);
    nums.push_back(&y);
    for(const auto& num : nums)
        cout << *num << endl;
    
//    vector<NumberObject*> nums;         //Set用
    string input;
    while(getline(cin, input)) {
        
        if(input.substr(0, 11) == "Set Integer") {
            input.erase(0, 12);                         // "Set Integer "を消去
            string::size_type pos = input.find(" ");
            string name = input.substr(0, pos);
            input.erase(0, name.length()+3);            // 変数名と " = " を消去。これでinputは式のみになった
            string result = simplify(input, nums);
            div_final(result, nums);
            result = dec_to_int(result);
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == name) {
                    cout << "INPUT ERROR: YOU ALREADY HAVE THIS VARIABLE T_T" << endl;
                    exit(EXIT_FAILURE);
                }
            }
            Integer A = result;
            A.obj_name = name;
            nums.push_back(&A);
            
        }
        else if(input.substr(0, 11) == "Set Decimal") {
            input.erase(0, 12);                         // "Set Decimal "を消去
            string::size_type pos = input.find(" ");
            string name = input.substr(0, pos);
            input.erase(0, name.length()+3);            // 変数名と " = " を消去。これでinputは式のみになった
            string result = simplify(input, nums);
            div_final(result, nums);
//            dec_to_int(result);
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == name) {
                    cout << "INPUT ERROR: YOU ALREADY HAVE THIS VARIABLE T_T" << endl;
                    exit(EXIT_FAILURE);
                }
            }
            Decimal A = result;
            A.obj_name = name;
            NumberObject C = A;
            nums.push_back(&C);
            
        }
        else if(input.find("=") != string::npos) {
            string::size_type pos = input.find(" ");
            string name = input.substr(0, pos);
            input.erase(0, name.length()+3);            // 変数名と " = " を消去。これでinputは式のみになった
            
            for(int i = 0; i < nums.size(); i++) {
                if(nums[i]->obj_name == name) {
                    string result = simplify(input, nums);
                    div_final(result, nums);
                    *(nums[i]) = result;
                    nums[i]->obj_name = name;
                    break;
                }
            }
        }
        else {
            string result = simplify(input, nums);
            result = simplify(result, nums);
            div_final(result, nums);
            if(result.find("(") != string::npos) input_error();
            else if(result.find(")") != string::npos) input_error();
            else if(result.find("!") != string::npos) input_error();
            else if(result.find("^") != string::npos) input_error();
            else if(result.find("*") != string::npos) input_error();
            else if(result.find("/") != string::npos) input_error();
            else if(result.find("+") != string::npos) input_error();
//            else if(result.find("-") != string::npos) input_error();
            else if(result.find(" ") != string::npos) input_error();
            else cout << result << endl;
            
        }
        
    }
    return 0;
}
