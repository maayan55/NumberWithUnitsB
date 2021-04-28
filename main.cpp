#include "NumberWithUnits.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace ariel;
using namespace std;
 int main()
 {
    //open file
    ofstream MyFile("filename.txt");
    // Write to the file
    MyFile << "1 km = 1000 m\n1 m = 100 cm\n1 kg = 1000 g\n1 ton = 1000 kg\n1 USD = 3.33 ILS";
    MyFile.close();
    ifstream units_MyFile{"filename.txt"};
    NumberWithUnits::read_units(units_MyFile);
    NumberWithUnits a{2, "km"};
    NumberWithUnits b{2, "km"};
    NumberWithUnits c{4, "m"};
    NumberWithUnits d{3, "USD"};
    NumberWithUnits e{9, "ILS"};
    NumberWithUnits f{6, "kg"};
    NumberWithUnits g{-500, "g"};
    cout<< a<< endl;
    cout<< (a+b) << endl;
    cout<< (a+c) << endl;
    cout<< (a+=b)<< endl;
    cout<< (c+=a)<<endl;
    cout<< (a==b)<<endl;//trie--->0
    cout<<(c<a)<<endl;// true---> 0
    cout<< (c>a)<<endl;//false----> 1
    cout<< (c<=a)<<endl;//true--->0
    cout<< (e>=d)<<endl;//true--->0
    cout<< (a-=c)<<endl;
    cout<< (-a)<<endl;
    cout<< (3*d)<<endl;
    cout<< (a*-100)<<endl;
    cout<< (-g)<<endl;
    cout<< ((-1*g))<<endl;
    cout<< (g+=f)<<endl;
    cout<< (g)<<endl;
}