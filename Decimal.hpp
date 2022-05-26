#ifndef Decimal_hpp
#define Decimal_hpp


#include <string>
#include "NumberObject.hpp"





/* ---------Decimal--------- */

class Decimal : public NumberObject {
public:
//    std::string nume;
//    std::string deno;
    Decimal();
    Decimal(const char* num);
    Decimal(std::string NUM);
    Decimal(const Decimal& num);
//    Decimal(const Integer& num);          PROBLEM!!
    Decimal& operator= (const char* num);
    Decimal& operator= (std::string NUM);
    Decimal& operator= (const Decimal& num);
//    Decimal& operator= (conats Integer& num);     PROBLEM!!
    friend std::istream& operator>> (std::istream& input, Decimal& num);
    friend std::ostream& operator<< (std::ostream& output, const Decimal& num);
    ~Decimal();
};

/* ---------Decimal--------- */







#endif /* Decimal_hpp */
