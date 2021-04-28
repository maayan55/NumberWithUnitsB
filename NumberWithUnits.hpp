#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace ariel{

class NumberWithUnits{
    
      double number; 
	std::string type;   

    public:
  
        NumberWithUnits(double number, const std::string& type);
        ~NumberWithUnits(){};

        static void read_units(std::ifstream& units_file);
        friend int ratio(const NumberWithUnits& obj1, const NumberWithUnits& obj2);
        // +, +=, +, -, -=, -
        NumberWithUnits operator+(const NumberWithUnits& n);
        NumberWithUnits& operator+=(const NumberWithUnits& n);
        NumberWithUnits operator+();
        NumberWithUnits operator-(const NumberWithUnits& n);
        NumberWithUnits& operator-=(const NumberWithUnits& n);
        NumberWithUnits operator-();

        // >, >=, <, <=, ==, !=
        bool operator>(const NumberWithUnits& num) const;
        bool operator>=(const NumberWithUnits& num) const;
        bool operator<(const NumberWithUnits& num) const;
        bool operator<=(const NumberWithUnits& num) const;
        bool operator==(const NumberWithUnits& num) const;
        bool operator!=(const NumberWithUnits& num) const;

        //++ before, ++ after, -- before, -- after
        NumberWithUnits& operator++();
        NumberWithUnits operator++(int t);
        NumberWithUnits& operator--();  
        NumberWithUnits operator--(int t);

        //*, *
        NumberWithUnits operator*(double num) const;
        friend  NumberWithUnits operator*(const double num, const NumberWithUnits& n1);

        // >> cin input, <<cout output
        friend std::istream& operator>>(std::istream& input, NumberWithUnits& n);
        friend std::ostream& operator<<(std::ostream& output, const NumberWithUnits& n);

  };

}





