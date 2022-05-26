#ifndef Integer_hpp
#define Integer_hpp

#include "Decimal.hpp"



/* ---------Integer--------- */

class Integer : public Decimal {
public:
//    std::string int_val;
    Integer();
    Integer(const char* num);
    Integer(std::string NUM);
    Integer(const Integer& num);
    Integer(const Decimal& num);
    Integer& operator= (const Integer& num);
    Integer& operator= (const Decimal& num);
    Integer& operator= (const char* num);
    Integer& operator= (std::string NUM);
    friend std::istream& operator>> (std::istream& input, Integer& num);
    friend std::ostream& operator<< (std::ostream& output, Integer& num);
    ~Integer();
};

/* ---------Integer--------- */



#endif /* Integer_hpp */
