#ifndef NumberObject_hpp
#define NumberObject_hpp


#include <string>


/* ---------NumberObject--------- */

class NumberObject {
public:
    bool isNegative;
    std::string obj_name;
    std::string nume;
    std::string deno;
    std::string int_val;
    NumberObject();
    NumberObject& operator= (std::string NUM);
    NumberObject& operator= (const NumberObject& num);
    friend std::istream& operator>> (std::istream& input, NumberObject& num);
    friend std::ostream& operator<< (std::ostream& output, NumberObject& num);
    ~NumberObject();
};

/* ---------NumberObject--------- */




#endif /* NumberObject_hpp */
