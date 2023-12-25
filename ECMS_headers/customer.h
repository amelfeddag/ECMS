#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "electricity.h"
#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <limits>
#include <utility>
#include <sstream>
using namespace std;

class customer{
public:
/*CONSTRUCTORS + OVERLOADING OF =*/
                customer(string name ="/" , long long int ID=0, int numf=0, string regionn="/" , string diss="/", string cityy="/", int* ages=nullptr);//assignement constructor
                customer(const  customer& other);//copy constructor
                ~customer();//destructor
                customer& operator= (  const customer& other);//copy assignement = overloading
                customer(customer&& other);//move constructor
                customer& operator=(customer&& other);//move assignement

/*GETTERS AND SETTERS*/
                int get_height(){return height;}
                string get_customer_name()const;
                long long int get_cust_id()const;
                int get_number_of_family_members()const;
                int* get_ages_of_fam_members()const;
                customer* get_left()const{return left;}
                customer*& get_left(){return left;}
                customer* get_right()const{return right;}
                customer* &get_right(){return right;}
                void print_fam_ages();

                void set_height(int h){height=h;}
                void set_customer_name(string name);
                void set_cust_id(long long int id);
                void set_number_of_fmamily_members(int num);
                void set_familyages(int* ages);
                void set_cust_region(string re);
                void set_cust_district(string di);
                void set_cust_city(string ci);
                void set_address_of_cust(string add);
                void set_left(customer* l){left=l;}
                void set_right(customer* l){right=l;}
/*FUNCTIONS*/

/*print*/       void print_customer();//print informations about the customer

/*bills*/       //shows the bill of the customer in every month of the year/month/period
                void show_bills_y(int y);
                void show_bill_m(int month,int year);
                void show_bills_period(int startingmonth, int startingyear, int endmonth, int endyear);
                //helper functions
                bool date_exists(int m, int y);
                void print_bill(double totalconsumption, double totalproduction);
                //to show total bill of customer in a period of time
                void show_bill_y(int y);
                void show_bill_period(int startingmonth, int startingyear, int endmonth, int endyear);
                //to use to count bills of district and show the bills of customers, returns the calculated bill of the customer in the month/year/period
                double get_bill_y(int year) ;
                double get_bill_m(int month,int year);
                double get_bill_period(int startingmonth, int startingyear, int endmonth, int endyear);

/*consumption-production getters*/
                //returns the calculated consumption/production of a month/year/period
                double get_consumption_y(int year) ;
                double get_consumption_m(int month,int year);
                double get_consumption_period(int startingmonth, int startingyear, int endmonth, int endyear);

                double get_production_y(int year) ;
                double get_production_m(int month,int year);
                double get_production_period(int startingmonth, int startingyear, int endmonth, int endyear);

/*customer data insertion*/
                void add_new_cust_data(double consumption,double production,int month,int year);//inserts new data into the vector of electricity of the customer
/*is win*/
                double get_best_injection_m(int m,int y);//returns the cumulative amount of electricity injected into the network, used to determine if the customer is winning the prize or not

private:
                string customer_name;
                long long int cust_id;
                int number_of_family_members;
                int* ages_of_fam_members;
                string region_of_cust;
                string district_of_cust;
                string city_of_cust;
                customer* left;
                customer* right;
                int height;

                vector<electricity> cust_data;
};


#endif // CUSTOMER_H




//customer.cpp
//CONSTRUCTORS + OVERLOADING OF =
                //explicit constructor
                   customer::customer(string name , long long int ID, int numf, string regionn, string diss, string cityy,  int* ages){
                                                    set_customer_name(name);
                                                    set_cust_id(ID);
                                                    set_number_of_fmamily_members(numf);
                                                    set_familyages(ages);
                                                    set_cust_region(regionn);
                                                    set_cust_district(diss);
                                                    set_cust_city(cityy);
                                                    left=right=nullptr;
                                                    set_height(0);
                                                    if (ages != nullptr) {
                                                            ages_of_fam_members = new int[numf];
                                                            for (int i = 0; i < numf; ++i) {
                                                                ages_of_fam_members[i] = ages[i];
                                                            }
                                                        } else {
                                                            ages_of_fam_members = nullptr;
                                                        }
                                                }
// Copy constructor
                    customer::customer(const customer& other)
                                                        : customer_name(other.customer_name), cust_id(other.cust_id),
                                                        number_of_family_members(other.number_of_family_members),
                                                        region_of_cust(other.region_of_cust), district_of_cust(other.district_of_cust),
                                                        city_of_cust(other.city_of_cust), 
                                                        left(nullptr), right(nullptr) {
                                                        if (other.ages_of_fam_members != nullptr) {
                                                            ages_of_fam_members = new int[other.number_of_family_members];
                                                            for (int i = 0; i < other.number_of_family_members; ++i) {
                                                                ages_of_fam_members[i] = other.ages_of_fam_members[i];
                                                            }
                                                        } else {
                                                            ages_of_fam_members = nullptr;
                                                        }
                                                        cust_data.reserve(other.cust_data.size());
                                                        for (const auto& elec : other.cust_data) {
                                                            cust_data.push_back(elec);
                                                        }
                                                        if (other.left != nullptr) {
                                                            left = new customer(*other.left);
                                                        }
                                                        if (other.right != nullptr) {
                                                            right = new customer(*other.right);
                                                        }
                                                    }
//destructor
                  customer::~customer() {delete[] ages_of_fam_members;}
//copy assignement = overloading
                 customer& customer:: operator=(const customer& other) {
                                                    if (this != &other) {
                                                        delete[] ages_of_fam_members;
                                                        customer_name = other.customer_name;
                                                        cust_id = other.cust_id;
                                                        number_of_family_members = other.number_of_family_members;
                                                        region_of_cust = other.region_of_cust;
                                                        district_of_cust = other.district_of_cust;
                                                        city_of_cust = other.city_of_cust;
                                                        if (other.ages_of_fam_members != nullptr) {
                                                            ages_of_fam_members = new int[other.number_of_family_members];
                                                            for (int i = 0; i < other.number_of_family_members; ++i) {
                                                                ages_of_fam_members[i] = other.ages_of_fam_members[i];
                                                            }
                                                        } else {
                                                            ages_of_fam_members = nullptr;
                                                        }
                                                        cust_data = other.cust_data;
                                                        if (other.left != nullptr) {
                                                            left = new customer(*other.left);
                                                        }
                                                        if (other.right != nullptr) {
                                                            right = new customer(*other.right);
                                                        }
                                                    }
                                                    return *this;
                                                }
//move constructor

                customer::customer(customer&& other)
                                                    : customer_name(std::move(other.customer_name)),
                                                    cust_id(other.cust_id),
                                                    number_of_family_members(other.number_of_family_members),
                                                    ages_of_fam_members(other.ages_of_fam_members),
                                                    region_of_cust(std::move(other.region_of_cust)),
                                                    district_of_cust(std::move(other.district_of_cust)),
                                                    city_of_cust(std::move(other.city_of_cust)),
                                                    left(other.left),
                                                    right(other.right),
                                                    cust_data(std::move(other.cust_data)) {

                                                    other.ages_of_fam_members = nullptr;
                                                    other.left = nullptr;
                                                    other.right = nullptr;
                                                }
//move assignement

                customer& customer::operator=(customer&& other){
                                                    if (this != &other) {
                                                        delete[] ages_of_fam_members;
                                                        customer_name = std::move(other.customer_name);
                                                        cust_id = other.cust_id;
                                                        number_of_family_members = other.number_of_family_members;
                                                        ages_of_fam_members = other.ages_of_fam_members;
                                                        region_of_cust = std::move(other.region_of_cust);
                                                        district_of_cust = std::move(other.district_of_cust);
                                                        city_of_cust = std::move(other.city_of_cust);
                                                        left = other.left;
                                                        right = other.right;
                                                        cust_data = std::move(other.cust_data);
                                                        other.ages_of_fam_members = nullptr;
                                                        other.left = nullptr;
                                                        other.right = nullptr;
                                                    }
                                                    return *this;
                                                }

//GETTERS AND SETTERS
                string customer::get_customer_name()const{return customer_name;}
                long long int customer:: get_cust_id()const{return cust_id; }
                int customer::get_number_of_family_members()const{return number_of_family_members;}
                int* customer:: get_ages_of_fam_members()const{return ages_of_fam_members;}
                void customer::print_fam_ages(){
                                if(ages_of_fam_members==nullptr)return;
                                for(int i=0;i<number_of_family_members;i++){
                                    cout<<ages_of_fam_members[i]<<" , ";
                                }
                                cout<<endl;
                            }
                void customer:: set_customer_name(string name){customer_name=name;}
                void customer::set_cust_id(long long int id){cust_id=id;}
                void customer::set_number_of_fmamily_members(int num){number_of_family_members=num;}
                void customer::set_familyages(int* ages){ages_of_fam_members=ages;}
                void customer::set_cust_region(string re){region_of_cust=re;}
                void customer::set_cust_district(string di){district_of_cust=di;}
                void customer:: set_cust_city(string ci){city_of_cust=ci;}
 //FUNCTIONS
/*print*/
                void customer::print_customer(){
                                cout<<endl;
                                cout<<"customer informations:"<<endl;
                                cout<<"ID:"<<cust_id<<endl;
                                cout<<"name :"<<customer_name<<endl;
                                cout<<"region:"<<region_of_cust<<endl;
                                cout<<"district:"<<district_of_cust<<endl;
                                cout<<"city:"<<city_of_cust<<endl;
                                cout<<"number of family members:"<<number_of_family_members<<endl;
                                if(ages_of_fam_members!=nullptr){
                                cout<<" their ages: "; this->print_fam_ages();}
                                cout<<endl;
                            }

//BILLS
//SHOW BILLS FUNCTIONS
                //each month individually
                void customer::show_bills_y(int y){
                                    cout<<endl;
                                    cout<<"bills for year  :"<<y<<" customer: "<<cust_id<<endl;
                                    for(int i=1; i<=12; i++){
                                        show_bill_m(i,y);
                                    }
                                    show_bill_y(y);
                                    cout<<endl;
                                }
                void customer::show_bill_m(int m,int y){
                                    cout<<endl;
                                    cout<<"bill for customer:"<<cust_id<<" , year:"<<y<<" , month:"<<m<<endl;
                                    if(date_exists(m,y)){
                                    print_bill(this->get_consumption_m(m,y),this->get_production_m(m,y));}
                                    else cout<<" no activity for month: "<<m<<" year:"<<y<<endl;
                                    cout<<endl;
                                    return;
                                }
                 void customer::show_bills_period(int startingmonth, int startingyear, int endmonth, int endyear){
                                    cout<<endl;
                                    cout<<"list of bills of customer: "<<cust_id<<" from "<<startingmonth<<"/"<<startingyear<<" until:"<<endmonth<<"/"<<endyear<<endl;
                                    if(endyear==startingyear  && startingmonth!=endmonth) {
                                        for(int i=startingmonth; i<=endmonth;i++){
                                            show_bill_m(i,startingyear);
                                        }
                                        show_bill_period(  startingmonth,  startingyear,   endmonth,endyear);return;
                                    }
                                    else {if(endyear==startingyear  && startingmonth==endmonth){ show_bill_m(startingmonth,startingyear);
                                    show_bill_period( startingmonth,  startingyear,   endmonth,endyear);
                                    return;}
                                    else{
                                        for(int i=startingmonth; i<=12;i++){
                                            show_bill_m(i,startingyear);
                                        }
                                        for(int j=startingyear+1;j<endyear;j++){
                                        for(int i=1;i<=12;i++){
                                            show_bill_m(i,j);
                                        }
                                        }
                                        for(int i=1; i<=endmonth; i++){
                                            show_bill_m(i,endyear);
                                        }
                                    }
                                        show_bill_period(startingmonth, startingyear,endmonth,endyear);
                                        cout<<endl;return;
                                    }}
                //helper of show bill to avoid unexisting months
                bool customer::date_exists(int m, int y){
                                        for (const auto& value : cust_data) {
                                            if (value.get_month() == m && value.get_year()==y) {
                                                return true;  // Element found
                                            }
                                        }
                                        return false;
                                    }
                //helper of the show functions
                void customer::print_bill(double totalconsumption, double totalproduction){
                                        cout<<endl;
                                        cout<<"       total consmuption (5DA per killowat per hour):"<<totalconsumption<<endl;
                                        cout<<"       total cost:"<<5*totalconsumption<<"DA"<<endl;
                                        cout<<"       total production (3DA per killowat per hour):"<<totalproduction<<endl;
                                        cout<<"       total earnings:"<<3*totalproduction<<"DA"<<endl;
                                        double bill=5*totalconsumption-3*totalproduction;
                                        if(bill>0){
                                            cout<<"bill comes to:"<<bill<<"DA"<<endl;
                                        }
                                        else { if(bill<0){
                                            cout<<"bonus comes to:"<<(-1)*bill<<"DA"<<endl;}
                                            else cout<<"the bill is null: 0DA"<<endl;}
                                    }
                //total functions used in the show_bill functions
                //year
                void customer::show_bill_y(int y){cout<<endl;
                                        cout<<"total bill for customer:"<<cust_id<<" , year:"<<y<<endl;
                                        print_bill(get_consumption_y(y),get_production_y(y));
                                        cout<<endl;return;
                                    }
                //period of time
                void customer::show_bill_period(int startingmonth, int startingyear, int endmonth, int endyear){cout<<endl;
                                        cout<<"total bill for customer:"<<cust_id<<" , from year:"<<startingyear<<",month:"<<startingmonth<<" , until year:"<<endyear<<",month:"<<endmonth<<endl;
                                        print_bill(this->get_consumption_period(startingmonth,startingyear,endmonth,endyear),this->get_production_period(startingmonth,startingyear,endmonth,endyear));
                                        cout<<endl;return;
                                    }
//GETBILLFUNCTIONS
                //used in show bills of customers
                double customer::get_bill_y(int year){
                                    return this->get_consumption_y(year)*5-this->get_production_y(year)*3;
                }
                double customer::get_bill_m(int month, int year){
                                    return this->get_consumption_m(month,year)*5-this->get_production_m(month,year)*3;
                }
                double customer::get_bill_period(int startingmonth, int startingyear, int endmonth, int endyear){
                                    return this->get_consumption_period(startingmonth,startingyear,endmonth,endyear)*5-this->get_production_period(startingmonth,startingyear,endmonth,endyear)*3;
                }
//GETPRODUCTION GETCONSUMPTION FUNCTIONS;
                //consumption
                double customer:: get_consumption_y(int y) {
                                            double totalconsumption=0;
                                            int starting;
                                            for(int i=0;i < cust_data.size();i++){
                                                if(cust_data[i].get_year()== y){
                                                    starting=i;break;
                                                }
                                            }
                                            for(int i=starting;i<cust_data.size();i++){
                                                if(cust_data[i].get_year()== y){
                                                    totalconsumption += cust_data[i].get_consumption();
                                                    continue;
                                                }
                                                if(cust_data[i].get_year() > y)break;
                                                break;
                                            }
                                        return totalconsumption;
                                        }
                double customer::get_consumption_m(int m,int y){
                                            if(date_exists(m,y)){
                                            double totalconsumption=0;
                                            int starting;
                                            for(int i=0;i<cust_data.size();i++){
                                                if(cust_data[i].get_year()== y && cust_data[i].get_month()==m){
                                                    totalconsumption=cust_data[i].get_consumption();
                                                    break;
                                                }
                                            }
                                            return totalconsumption;}
                                        }
                double customer::get_consumption_period(int startingmonth, int startingyear, int endmonth, int endyear){
                                            double totalconsumption=0;
                                            int starting=0;
                                            for(int i=0;i<cust_data.size();i++){
                                                if((cust_data[i].get_year()== startingyear && cust_data[i].get_month()>=startingmonth) || ( cust_data[i].get_year()> startingyear )){
                                                    starting=i;break;
                                                }
                                            }
                                            int i=starting;
                                                while(cust_data[i].get_year()<endyear ){
                                                    totalconsumption+=cust_data[i].get_consumption();
                                                    i++;
                                                }
                                                while(cust_data[i].get_year()== endyear && cust_data[i].get_month()<=endmonth){
                                                    totalconsumption+=cust_data[i].get_consumption();
                                                    i++;
                                                }

                                            return totalconsumption;
                                        }
                //production
                double customer::get_production_y(int y){
                                            double totalproduction=0;
                                            int starting;
                                            for(int i=0;i<cust_data.size();i++){
                                                if(cust_data[i].get_year()== y){
                                                    starting=i;break;
                                                }
                                            }
                                            for(int i=starting;i<cust_data.size();i++){
                                                if(cust_data[i].get_year()== y){
                                                    totalproduction+=cust_data[i].get_production();
                                                    continue;
                                                }
                                                break;
                                            }
                                            return totalproduction;
                                            }
                double customer::get_production_m(int m,int y){
                                            double totalproduction=0;
                                            int starting;
                                            for(int i=0;i<cust_data.size();i++){
                                                if(cust_data[i].get_year()== y && cust_data[i].get_month()==m){
                                                    totalproduction=cust_data[i].get_production();
                                                    break;
                                                }
                                            }
                                            return totalproduction;
                                        }
                double customer::get_production_period(int startingmonth, int startingyear, int endmonth, int endyear){
                                            double totalproduction=0;
                                            int starting=0;
                                            for(int i=0;i<cust_data.size();i++){
                                                if((cust_data[i].get_year()== startingyear && cust_data[i].get_month()>=startingmonth) || ( cust_data[i].get_year()> startingyear )){
                                                    starting=i;break;
                                                }
                                            }
                                            int i=starting;
                                                while(cust_data[i].get_year()<endyear ){
                                                    totalproduction+=cust_data[i].get_production();
                                                    i++;
                                                }
                                                while(cust_data[i].get_year()== endyear && cust_data[i].get_month()<=endmonth){
                                                    totalproduction+=cust_data[i].get_production();
                                                    i++;
                                                }

                                            return totalproduction;
                                        }
                //electricity
                void customer::add_new_cust_data(double cons,double prod,int m,int y){
                                            electricity test(prod, cons, m, y);

                                            if (cust_data.size() == 0) {
                                                cust_data.push_back(test);
                                            } else {
                                                auto pos = cust_data.begin();
                                                while (pos != cust_data.end()) {
                                                    int a = pos->get_year();
                                                    int b = pos->get_month();
                                                    if (y < a || (y == a && m < b)) {
                                                        break;
                                                    }
                                                    if(y==a && m==b) {pos->set_year(y);pos->set_month(m); return;}
                                                    ++pos;
                                                }
                                                cust_data.insert(pos, test);
                                            }
                                            return;
                                        }
//FUNCTION TO BE USED WHEN LOOKING FOR THE BEST customer
                double customer::get_best_injection_m(int m,int y){
                                            double total=0;
                                            for(int i=0;i<cust_data.size();i++){
                                                    total+=cust_data[i].get_production();
                                                    if(cust_data[i].get_year()==y && cust_data[i].get_month()==m){
                                                    break;}}
                                                    return total;
                                        }

//end of customer.cpp
