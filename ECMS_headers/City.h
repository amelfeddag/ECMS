#ifndef CITY_H
#define CITY_H

#include "Department.h"
#include "district_bst.h"

#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <limits>
#include <utility>
#include <sstream>
using namespace std;

class City{
private:
                int ID;
                string name;
                Departement* dep;

                vector<district*> district_vector;

public:

                City(int id,string c_name) : ID(id),name(c_name)
                { dep = new Departement();
                  for(int i=0;i<100;i++)district_vector.push_back(nullptr);
                }
/*getters*/
                int get_ID();
                string get_name();

/*customer insertion*/
                void add_new_cust(long long int ID,string cus_name,int family_num ,int* ages,string region_name,string city_name,string district_name);
/*customer data insertion*/
                void add_new_cust_data(long long int ID,int consumption,int production,int m,int y);

/*BILLS*/       //show bill of one customer in a period of time
                void show_bill_m(long long int CUS_ID,int m,int y);
                void show_bill_y(long long int CUS_ID,int y);
                void show_bill_period(long long int CUS_ID,int start_m,int start_y,int end_m,int end_y);
                //show bills of all customers in a certain district in a period of time
                void show_ALL_DIST_bill_y(int DIST_ID,int y);//DONE
                void show_ALL_DIST_bill_m(int DIST_ID,int m,int y);//DONE
                void show_ALL_DIST_bill_period(int DIST_ID,int start_m,int start_y,int end_m,int end_y);
                //show bills of all customers in the city in a period of time
                void show_ALL_City_bill_m(int m,int y);//DONE
                void show_ALL_City_bill_y(int y);//DONE
                void show_ALL_City_bill_period(int start_m,int start_y,int end_m,int end_y);

/*CONSUMPTION-PRODUCTION*/
                //consumption / productionof the whole city in a certain month
                double get_consumption_m(int m, int y);
                double get_production_m(int m, int y);
                //consumption/production of a certain customer in the city in a month
                double get_consumption_m(long long int id, int m , int y);
                double get_production_m(long long int id,int m,int y);
/*print*/

                void print_customer(long long int id);//print a certain customer
                void print_customers();//print all customers of the city
                void print_ALL_DISTRICT_customers(int did);//print all customers of a district in the city

/*best_customer*/
                //returns best customer of the city in a month
                customer* get_best_customer_m(int m,int y);

/*investement insertion*/
                void insert_investment(int amount,int m,int y);
/*investement getter*/
                int get_investment_y(int y);
/*is departement win*/
                //returns the total of the bills of the customers over a year , it is used to determine which departement is the winner
                double get_city_income_y(int y);
/*departement*/
                //returns performance of the departement
                int get_dep_performence_y(int y);
/*add dep insertion*/
                //to insert the information of the departement in the city
                void add_dep_performence(int y,Departement_Performence* &p);
};


#endif // CITY_H




//CITY.CPP
 //GETTERS
                    int City::get_ID(){return ID;}
                    string City::get_name(){return name;}
//customer insertion
                    void City::add_new_cust(long long int ID,string cus_name,int family_num,int* ages,string region_name,string city_name,string district_name){
                                                int cus_district= (ID/10000)%100;
                                                if(district_vector[cus_district] != nullptr)
                                                {
                                                    district_vector[cus_district]->add_new_cust( cus_name ,ID,  family_num, region_name, district_name, city_name, ages);
                                                }
                                                else
                                                {
                                                    district_vector.insert(district_vector.begin() + cus_district, std::move(new district(cus_district,district_name)));
                                                    district_vector[cus_district]->add_new_cust( cus_name,ID,  family_num, region_name, district_name, city_name, ages);
                                                }
                                            }
                    void City::add_new_cust_data(long long int ID,int consumption,int production,int m,int y){
                                                int cus_district= (ID/10000)%100;
                                                if(district_vector[cus_district] != nullptr)
                                                    district_vector[cus_district]->add_new_cust_data( ID,y , m ,consumption, production );
                                            }
//SHOW BILL FUNCTION
//show_ bill  bill of one customer in  a period of time
                    void City::show_bill_m(long long int CUS_ID,int m,int y){
                                                int cus_district = (CUS_ID / 10000) % 100;
                                                if (cus_district < district_vector.size() && cus_district >= 0 && district_vector[cus_district] != nullptr)
                                                {district_vector[cus_district]->show_bill_customer_m(CUS_ID, y, m);}
                                                else
                                                {cout << "Customer doesn't exist in the city" << endl;}
                                                }

                    void City::show_bill_y(long long int CUS_ID,int y){
                                                int cus_district = (CUS_ID / 10000) % 100;
                                                if (cus_district < district_vector.size() && cus_district >= 0 && district_vector[cus_district] != nullptr)
                                                { district_vector[cus_district]->show_bills_customer_y(CUS_ID, y);}
                                                else
                                                {cout << "Customer doesn't exist in the city" << endl;}
                                                }
                    void City::show_bill_period(long long int CUS_ID,int start_m,int start_y,int end_m,int end_y) {
                                                int cus_district = (CUS_ID / 10000) % 100;
                                                if (cus_district < district_vector.size() && cus_district >= 0 && district_vector[cus_district] != nullptr)
                                                {
                                                    district_vector[cus_district]->show_bills_customer_period(CUS_ID,start_m,start_y,end_m,end_y);
                                                }
                                                else
                                                   { cout << "Customer doesn't exist in the city" << endl; }
                                                }
                    void City::show_ALL_DIST_bill_m(int DIST_ID,int m,int y)
                                                {
                                                    if(district_vector[DIST_ID] != nullptr)
                                                        district_vector[DIST_ID]->show_bill_customers_m(m,y);
                                                    else
                                                        cout<<"district doesn't exist"<<endl;
                                                }
                    void City::show_ALL_DIST_bill_y(int DIST_ID,int y)
                                                {
                                                    if(district_vector[DIST_ID] != nullptr)
                                                        district_vector[DIST_ID]->show_bills_customers_y(y);
                                                    else
                                                        cout<<"customer doesn't exist"<<endl;
                                                }
                    void City::show_ALL_DIST_bill_period(int DIST_ID,int start_m,int start_y,int end_m,int end_y)
                                                {
                                                    if(district_vector[DIST_ID] != nullptr)
                                                        district_vector[DIST_ID]->show_bills_customers_period(start_m,start_y,end_m,end_y);
                                                    else
                                                        cout<<"customer doesn't exist"<<endl;
                                                }
                    void City::show_ALL_City_bill_m(int m,int y){
                                                    std::cout<<"The resume of the bills of all the city "<<name<<", ID : "<<ID<<", for "<<m<<"/"<<y<<" : "<<std::endl;
                                                    for(int i=0; i < district_vector.size();i++)
                                                    {
                                                        if(district_vector[i] != nullptr)
                                                        {
                                                            district_vector[i]->show_bill_customers_m(m,y);
                                                        }
                                                    }
                                                }
                    void City::show_ALL_City_bill_y(int y)
                                                {
                                                    std::cout<<"The resume of the bills of all the city "<<name<<", ID : "<<ID<<", for "<<y<<" : "<<std::endl;
                                                    for(int j=1;j<=12;j++)
                                                    {
                                                        show_ALL_City_bill_m(j,y);
                                                    }
                                                }
                    void City::show_ALL_City_bill_period(int start_m,int start_y,int end_m,int end_y){
                                                    std::cout<<"The resume of the bills of all the city "<<name<<", ID : "<<ID<<", between "<<start_m<<"/"<<start_y<<" and "<<end_m<<"/"<<end_y<<" : "<<std::endl;
                                                    int y = start_y;
                                                    while(y<=end_y)
                                                    {
                                                        if(start_y==end_y)
                                                        {
                                                            for(int j=start_m;j<=end_m;j++)
                                                            {
                                                                show_ALL_City_bill_m(j,y);
                                                            }
                                                        }
                                                        else if(y==start_y)
                                                        {
                                                            for(int j=start_m ;j<=12;j++)
                                                            {
                                                                show_ALL_City_bill_m(j,y);
                                                            }
                                                        }
                                                        else if(y==end_y)
                                                        {
                                                            for(int j=0;j<=end_m;j++)
                                                            {
                                                                show_ALL_City_bill_m(j,y);
                                                            }
                                                        }
                                                        else
                                                        {
                                                            for(int j=1;j<=12;j++)
                                                            {
                                                                show_ALL_City_bill_m(j,y);
                                                            }
                                                        }
                                                        ++y;
                                                    }
                                                }
/*CONSUMPTION-PRODUCTION GETTERS*/
                    //consumption-production of the whole city in a period of time
                    double City::get_consumption_m(int m,int y){
                                                        double consumption = 0;
                                                        for(int i=0;i<district_vector.size();i++)
                                                        {
                                                            if(district_vector[i] != nullptr)
                                                                consumption += district_vector[i]->get_consumption_m(m,y);
                                                        }
                                                        return consumption;
                                                        }
                    double City::get_production_m(int m,int y){
                                                        double production = 0;
                                                        for(int i=0;i<district_vector.size();i++)
                                                        {
                                                            if(district_vector[i] != nullptr)
                                                                production += district_vector[i]->get_production_m(m,y);
                                                        }
                                                        return production;
                                                        }
                    //consumption-production for a certain customer
                    double City::get_consumption_m(long long int id,int m, int y){
                                                        int d=(id/10000)%100;
                                                        if(district_vector[d]!=nullptr)
                                                            return district_vector[d]->get_consumption_m(id,m,y);
                                                        else return 0;
                                                    }
                    double City:: get_production_m(long long int id,int m, int y){
                                                        int d=(id/10000)%100;
                                                        if(district_vector[d]!=nullptr)
                                                            return district_vector[d]->get_production_m(id,m,y);
                                                        else return 0;
                                                    }
/*PRINT*/
                    //print the informations of a certain customer
                    void City:: print_customer(long long int id){
                                                        int r=(id/10000)%100;
                                                        if(district_vector[r]!=nullptr)
                                                            district_vector[r]->print_customer(id);
                                                        else {cout<<"the district of customer: "<<id<<" does not exist"<<endl;
                                                        cout<<"customer not found"<<endl;}
                                                    }
                     //print a the list of the customers in the city
                     void City:: print_customers(){
                                                        cout<<"a list of the customers in city: "<<ID<<" :"<<endl;
                                                        for(int i=0;i< district_vector.size();i++){
                                                        if(district_vector[i]!=nullptr) district_vector[i]->print_customers();
                                                        }
                                                        }
                    //print the list of customers in a district
                    void City:: print_ALL_DISTRICT_customers(int did){
                                                        if(district_vector[did]!=nullptr)
                                                            district_vector[did]->print_customers();
                                                        else cout<<"the district :"<<did<<" does not exist in city :"<<ID<<endl;
                                                    }
/*best customer*/   customer* City::get_best_customer_m(int m,int y){
                                                        customer* best = nullptr;
                                                        customer* temp = nullptr;
                                                        for (int i = 0; i < district_vector.size(); i++) {
                                                            if (district_vector[i] != nullptr) {
                                                                temp = district_vector[i]->get_best_customer_m(y, m);
                                                                if (best == nullptr || temp->get_best_injection_m(m, y) > best->get_best_injection_m(m, y)) {
                                                                    best = temp;
                                                                }
                                                            } else{continue;}
                                                        }
                                                        return best;
                                                    }
/*investement insertion*/
                    void City:: insert_investment(int amount,int m,int y){
                                                         dep->insert_investement(amount,m,y);
                                                     }
/*get investement*/  int City::get_investment_y(int y){return dep->get_investment_y(y);}
/*city income*/      // returns the total of the bills of the customers of the city in a year to determine the winning departement
                     double City::get_city_income_y(int y)
                                                        {int income = 0;
                                                            for(int i=0;i<district_vector.size();i++)
                                                            {
                                                                if(district_vector[i] != nullptr)
                                                                {
                                                                    income += district_vector[i]->get_district_income_y(y);
                                                                }
                                                            }return income;
                                                        }
/*departement*/     // returns the performance of the departement
                    int City::get_dep_performence_y(int y){
                                                        return get_city_income_y(y) - get_investment_y(y);}
/*add dep insertion*/
                    void City::add_dep_performence(int y,Departement_Performence* & p){
                                                        p->insert(ID,name,get_dep_performence_y(y));}
//end of city.CPP
