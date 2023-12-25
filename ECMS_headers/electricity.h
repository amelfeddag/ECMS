#ifndef ELECTRICITY_H
#define ELECTRICITY_H

#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <limits>
#include <utility>
#include <sstream>
using namespace std;
class electricity{

public:
                //constructors
                electricity(double prod, double cons, int m, int y): production(prod), consumption(cons), month(m), year(y){}//explicit constructor
                electricity(const electricity& other): production(other.production), consumption(other.consumption),month(other.month), year(other.year){}// Copy constructor
                ~electricity() {} //destructor
                electricity(electricity&& other): production(other.production),consumption(other.consumption),month(other.month),year(other.year){// Move constructor
                other.production = 0.0;
                other.consumption = 0.0;
                other.month = 0;
                other.year = 0;}
                //operator overloading
                electricity& operator=(const electricity& other) {// Copy assignment operator
                    if (this != &other) {
                        production = other.production;
                        consumption = other.consumption;
                        month = other.month;
                        year = other.year;
                    }
                    return *this;
                }
                electricity& operator=(electricity&& other) noexcept {// Move assignment operator
                if (this != &other) {
                    production = other.production;
                    consumption = other.consumption;
                    month = other.month;
                    year = other.year;
                    other.production = 0.0;
                    other.consumption = 0.0;
                    other.month = 0;
                    other.year = 0;
                }
                return *this;
                }
                //setters and getters
                void set_production(double pr){production=pr;}
                void set_consumption(double csp){consumption=csp;}
                void set_month(int m){if(m>=1 && m<=12)month=m; return;}
                void set_year(int y){year=y;}
                double get_consumption()const{return consumption;}
                double get_production()const{return production;}
                int get_month()const{return month;}
                int get_year()const{return year;}
private:
                double production;
                double consumption;
                int month;
                int year;
};
#endif // ELECTRICITY_H
