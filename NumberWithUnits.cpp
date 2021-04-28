#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <map>
using namespace std;
using namespace ariel;

namespace ariel{

    const double EPSILON = 0.000001;
    static map<string, map<string, double> > units;

    NumberWithUnits :: NumberWithUnits(double number, const string& type){
        units.at(type);
        this->number=number;
        this->type=type;
    }

    void NumberWithUnits::read_units(ifstream& units_file){
        if (!units_file)//if the program fails to open the file, print error message
        {
            cout<<"error, fails to open the file"<<endl;
            exit(1);
        }
        int num1 = 1; 
        double num2 = 0; 
        string type1;
        string type2;
        char equivalent;
        
        while(units_file >> num1 >> type1 >> equivalent >> num2 >> type2)
        {
            units[type1][type2] = num2; 
            units[type2][type1]= 1/num2; 
            
            for(auto &pair : units[type1])
            {
                double temp = units[type2][type1] * pair.second;
                units[type2][pair.first] = temp;
                units[pair.first][type2] = 1/temp;            
            }
            for(auto &pair : units[type2])
            {
                double temp = units[type1][type2] * pair.second;
                units[type1][pair.first] = temp;
                units[pair.first][type1] = 1/temp;
            }
        }
    }

    double convert_unit(double number, const string& from, const string& to){
        if(from == to)//have the same unit. no need to convert unit
        {
            return number;
        }
        if (units[to].contains(from))// able to convert
        {
            return number*units[from][to];// return the number* the convertion value
        }
        throw invalid_argument("invallid convertion");
    }

     int ratio(const NumberWithUnits& num1, const NumberWithUnits& num2)
     {
        double convert = convert_unit(num2.number, num2.type, num1.type);
        double difference = num1.number - convert;
        int is_equal = 0;
        if( difference> EPSILON)
        {
            is_equal = 1;
        }
        else if(difference < -EPSILON)
        {
            is_equal= -1;
        }
        return is_equal;
    }
    //+, +=, +, -, -=, -
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& n) 
    {
        double convert = convert_unit(n.number, n.type, this->type);
        double temp = this->number + convert;
        return NumberWithUnits(temp, this->type);
    }

    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits &n)
    {

        this->number += convert_unit(n.number, n.type, this->type);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator+()
    {
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& n)
    {
        double convert = convert_unit(n.number, n.type, this->type); 
        double temp = this->number - convert;
        return (NumberWithUnits(temp, this->type));
    }

    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& n) 
    {
        this->number-= convert_unit(n.number, n.type, this->type);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator-()
    {
        return NumberWithUnits(-number, type);
    }

    // >, >=, <, <=, ==, !=
    bool NumberWithUnits::operator>(const NumberWithUnits& num) const
    {
        return ratio(*this, num) > 0;
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits& num) const
    {      
        return ratio(*this, num) >= 0;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits& num) const
    {        
        return ratio(*this, num) < 0;
    }

	bool NumberWithUnits::operator<=(const NumberWithUnits& num) const
    {              
        return ratio(*this, num) <= 0;
    }

	bool NumberWithUnits::operator==(const NumberWithUnits& num)const
    {
        return ratio(*this, num) == 0;
    }

	bool NumberWithUnits::operator!=(const NumberWithUnits& num)const
    {
        return ratio(*this, num) != 0;
    }

    //++ before, ++ after, -- before, -- after
    NumberWithUnits& NumberWithUnits::operator++()
    {
        ++(this->number);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int t)
    {
        return  NumberWithUnits(this->number++, this->type);
    }    

    NumberWithUnits& NumberWithUnits::operator--()
    {
        --(this->number);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator--(int t)
    {
        return  NumberWithUnits(this->number--, this->type);
    }

    //*, *
	NumberWithUnits NumberWithUnits::operator*(double num)const
    {
        return NumberWithUnits(this->number*num, this->type);
    }

    NumberWithUnits operator*(const double num, const NumberWithUnits& n1 ){
        return NumberWithUnits(num*n1.number, n1.type);
         }

    // >> cin input, <<cout output
    istream& operator>>(istream& input, NumberWithUnits& n)
    {
        double number = 0;
        string type;
        char sign = ']';
        input >> number;
        input >> sign;
        while (sign != ']') {
            if (sign != '[') {
                type.push_back(sign);//while its not the ] and if it isnt [, keep addind the readen char
            }
            input>>sign;
        }
        if (units.find(type) != units.end())
        {
            n.number = number;
            n.type = type;
        }
        else
        {
            throw std::invalid_argument{"There is no such unit in the units file"};
        }
        return input;
    }

    ostream& operator<<(ostream& output, const NumberWithUnits& n)
    {           //for exampke return 50[g]
        return output << n.number << "[" << n.type << "]";
    }
        
}
