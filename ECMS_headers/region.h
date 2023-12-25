#ifndef REGION_H
#define REGION_H
#include "City.h"

#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <limits>
#include <utility>
#include <sstream>
using namespace std;
class region{
private:
                int ID;
                string name;
                vector<City*> region_vector;
public:
/*constructor*/
                region(int id,string c_name) : ID(id),name(c_name){
                           for(int i=0;i<100;i++)region_vector.push_back(nullptr); }
/*getters-setters*/
                int get_ID();
                string get_name();
                void set_id(long long int n){ID=n;}
/*customer insertion*/
                void add_new_cust(long long int ID,string cus_name,int family_num ,int* ages,string region_name,string city_name,string district_name);//DONE
/*customer data insertion*/
                void add_new_cust_data(long long int ID,int consumption,int production,int m,int y);
/*SHOW BILLS*/
                //show bills of a certain customer in every month of a certain period
                void show_bill_m(long long int CUS_ID,int m,int y);
                void show_bill_y(long long int CUS_ID,int y);
                void show_bill_period(long long int CUS_ID,int start_m,int start_y,int end_m,int end_y);
                //show bills of a all customers in a each month of certain period of time in a certain district
                void show_ALL_DIST_bill_y(int CITY_ID,int DIST_ID,int y);
                void show_ALL_DIST_bill_m(int CITY_ID,int DIST_ID,int m,int y);//DONE
                void show_ALL_DIST_bill_period(int CITY_ID,int DIST_ID,int start_m,int start_y,int end_m,int end_y);
                //show bills of a all customers in a each month of certain period of time in a certain city
                void show_ALL_CITY_bill_y(int CITY_ID,int y);
                void show_ALL_CITY_bill_m(int CITY_ID,int m,int y);
                void show_ALL_CITY_bill_period(int CITY_ID,int start_m,int start_y,int end_m,int end_y);
                //show bills of a all customers in a each month of certain period of time in the region
                void show_ALL_region_bill_m(int m,int y);
                void show_ALL_region_bill_y(int y);
                void show_ALL_region_bill_period(int start_m,int start_y,int end_m,int end_y);

/*CONSUMPTION-PRODUCTION getters*/
                //consumption/production of the whole region in a certain month
                double get_consumption_m(int m,int y);
                double get_production_m(int m,int y);
                //consumption/production of a certain customer in the region in a certain month
                double get_consumption_m(long long int id,int m, int y);
                double get_production_m(long long int id,int m,int y);
/*print*/
                void print_customer(long long int id);//print a certain customer in the region
                void print_customers();//print all customers of the region
                void print_ALL_DISTRICT_customers(int cid,int did);//print all customers of a district
                void print_ALL_CITY_customers(int cid);//print all customers of a city
/*best customer*/
                //returns best customer of the region in a certain month
                customer* get_best_customer_m(int m,int y);
/*departement*/
                double get_region_income_y(int y);
/*insertion of deps*/
                void insert_All_Dep(int y,Departement_Performence*& tree);
/*insert investment*/
                void insert_investment(int city_id,int amount,int m,int y);
/*investment getter*/
                int get_investment_y(int y);
};

#endif // REGION_H



//region.cpp
/*getters*/
                    int region::get_ID(){return ID;}
                    string region::get_name(){return name;}
/*customer insertion*/
                    void region::add_new_cust(long long int ID,string cus_name,int family_num,int* ages,string region_name,string City_name,string district_name){
                                                    int cus_City= (ID/100)%100;
                                                    if(region_vector[cus_City] != nullptr)
                                                    {
                                                        region_vector[cus_City]->add_new_cust( ID,cus_name , family_num, ages, region_name, City_name, district_name);
                                                    }
                                                    else
                                                    {
                                                        region_vector[cus_City] = new City(cus_City,City_name);
                                                        region_vector[cus_City]->add_new_cust( ID,cus_name , family_num, ages, region_name, City_name, district_name);
                                                    }
                                                }
/*customer data insertion*/
                    void region::add_new_cust_data(long long int ID,int consumption,int production,int m,int y){
                                                    int cus_City= (ID/100)%100;
                                                    if(region_vector[cus_City] != nullptr)
                                                        region_vector[cus_City]->add_new_cust_data( ID,consumption, production,m , y  );
                                                }
/*SHOW BILLS*/
                   //bills of a certain customer
                    void region::show_bill_m(long long int CUS_ID,int m,int y){
                                                    int cus_City = (CUS_ID / 100) % 100;

                                                    if (cus_City >= 0 && cus_City < region_vector.size() && region_vector[cus_City] != nullptr)
                                                     {
                                                    region_vector[cus_City]->show_bill_m(CUS_ID, m, y);
                                                                                                     }
                                                     else
                                                    {cout << "Customer doesn't exist in the region" << endl;}
                                                    }

                    void region::show_bill_y(long long int CUS_ID,int y){
                                                    int cus_City = (CUS_ID / 100) % 100;

                                                    if (cus_City >= 0 && cus_City < region_vector.size() && region_vector[cus_City] != nullptr)
                                                     {region_vector[cus_City]->show_bill_y(CUS_ID,y); }
                                                     else
                                                    {
                                                     cout << "Customer doesn't exist in the region" << endl;
                                                            }
                                                    }
                    void region::show_bill_period(long long int CUS_ID,int start_m,int start_y,int end_m,int end_y)
                                                    {
                                                        int cus_City = (CUS_ID / 100) % 100;

                                                    if (cus_City >= 0 && cus_City < region_vector.size() && region_vector[cus_City] != nullptr)
                                                     {
                                                    region_vector[cus_City]->show_bill_period(CUS_ID,start_m,start_y,end_m,end_y);
                                                                                                     }
                                                     else
                                                    {
                                                     cout << "Customer doesn't exist in the region" << endl;
                                                            }
                                                    }
                    //bills of all customers in a certain district
                    void region:: show_ALL_DIST_bill_y(int CITY_ID,int DIST_ID,int y){
                                                    if(region_vector[CITY_ID] != nullptr)
                                                        region_vector[CITY_ID]->show_ALL_DIST_bill_y(DIST_ID,y);
                                                    else
                                                        cout<<"District doesn't exist "<<std::endl;
                                                }
                    void region::show_ALL_DIST_bill_m(int CITY_ID,int DIST_ID,int m,int y){
                                                    if(region_vector[CITY_ID] != nullptr)
                                                        region_vector[CITY_ID]->show_ALL_DIST_bill_m(DIST_ID,m,y);
                                                    else
                                                        cout<<"District doesn't exist "<<std::endl;
                                                }
                    void region::show_ALL_DIST_bill_period(int CITY_ID,int DIST_ID,int start_m,int start_y,int end_m,int end_y){
                                                    if(region_vector[CITY_ID] != nullptr)
                                                        region_vector[CITY_ID]->show_ALL_DIST_bill_period(DIST_ID,start_m,start_y,end_m,end_y);
                                                    else
                                                        cout<<"District doesn't exist "<<std::endl;
                                                }
                    //show bills of all customers in a certain CITY
                    void region::show_ALL_CITY_bill_m(int CITY_ID,int m,int y){
                                                    if(region_vector[CITY_ID] != nullptr)
                                                        region_vector[CITY_ID]->show_ALL_City_bill_m(m,y);
                                                    else
                                                        cout<<"City doesn't exist"<<endl;
                                                }
                    void region::show_ALL_CITY_bill_y(int CITY_ID,int y){
                                                    if(region_vector[CITY_ID] != nullptr)
                                                        region_vector[CITY_ID]->show_ALL_City_bill_y(y);
                                                    else
                                                        cout<<"customer doesn't exist"<<endl;
                                                }
                    void region::show_ALL_CITY_bill_period(int CITY_ID,int start_m,int start_y,int end_m,int end_y){
                                                    if(region_vector[CITY_ID] != nullptr)
                                                        region_vector[CITY_ID]->show_ALL_City_bill_period(start_m,start_y,end_m,end_y);
                                                    else
                                                        cout<<"customer doesn't exist"<<endl;
                                                }
                    //show bills of all customers in the district
                    void region::show_ALL_region_bill_m(int m,int y){
                                                    std::cout<<"The resume of the bills of all the region "<<name<<", ID : "<<ID<<", for "<<m<<"/"<<y<<" : "<<std::endl;
                                                    for(int i=0; i < region_vector.size();i++)
                                                    {
                                                        if(region_vector[i] != nullptr)
                                                        {
                                                            region_vector[i]->show_ALL_City_bill_m(m,y);
                                                        }
                                                    }
                                                }
                    void region::show_ALL_region_bill_y(int y){
                                                    std::cout<<"The resume of the bills of all the region "<<name<<", ID : "<<ID<<", for "<<y<<" : "<<std::endl;
                                                    for(int j=1;j<=12;j++)
                                                    {
                                                        show_ALL_region_bill_m(j,y);
                                                    }
                                                }
                    void region::show_ALL_region_bill_period(int start_m,int start_y,int end_m,int end_y){
                                                        std::cout<<"The resume of the bills of all the region "<<name<<", ID : "<<ID<<", between "<<start_m<<"/"<<start_y<<" and "<<end_m<<"/"<<end_y<<" : "<<std::endl;
                                                        int y = start_y;
                                                        while(y<=end_y)
                                                        {
                                                            if(start_y==end_y)
                                                            {
                                                                for(int j=start_m;j<=end_m;j++)
                                                                {
                                                                    show_ALL_region_bill_m(j,y);
                                                                }
                                                            }
                                                            else if(y==start_y)
                                                            {
                                                                for(int j=start_m ;j<=12;j++)
                                                                {
                                                                    show_ALL_region_bill_m(j,y);
                                                                }
                                                            }
                                                            else if(y==end_y)
                                                            {
                                                                for(int j=0;j<=end_m;j++)
                                                                {
                                                                    show_ALL_region_bill_m(j,y);
                                                                }
                                                            }
                                                            else
                                                            {
                                                                for(int j=1;j<=12;j++)
                                                                {
                                                                    show_ALL_region_bill_m(j,y);
                                                                }
                                                            }++y;}}
/*CONSUMPTION-PRODUCTION getters*/
                    //total consumption/production of the region in a month
                    double region ::get_consumption_m(int m,int y){
                                                            double consumption = 0;
                                                            for(int i=0;i<region_vector.size();i++)
                                                            {
                                                                if(region_vector[i] != nullptr)
                                                                    consumption += region_vector[i]->get_consumption_m(m,y);
                                                            }
                                                            return consumption;
                                                            }
                    double region::get_production_m(int m,int y){
                                                            double production = 0;
                                                            for(int i=0;i<region_vector.size();i++)
                                                            {
                                                                if(region_vector[i] != nullptr)
                                                                    production += region_vector[i]->get_production_m(m,y);
                                                            }
                                                            return production;
                                                            }
                    //consumption/production of a certain customer
                    double region::get_consumption_m(long long int id,int m, int y){
                                                            int c=(id/100)%100;
                                                            if(region_vector[c]!=nullptr)
                                                                return region_vector[c]->get_consumption_m(id,m,y);
                                                            else return 0;
                                                            }
                    double region::get_production_m(long long int id,int m, int y){
                            int c=(id/100)%100;
                            if(region_vector[c]!=nullptr)
                                return region_vector[c]->get_production_m(id,m,y);
                            else return 0;
                    }
/*PRINT*/          //print one customer
                    void region::print_customer(long long int id){
                                                           int r=(id/100)%100;
                                                           if(region_vector[r]!=nullptr)
                                                                region_vector[r]->print_customer(id);
                                                            else {cout<<"the city of customer: "<<id<<" does not exist"<<endl;
                                                            cout<<"customer not found"<<endl;}
                                                                 }
                    void region::print_customers(){//print all customers in the region
                        cout<<"a list of the customers in region: "<<ID<<" "<<name<<" :"<<endl;
                                                        for(int i=0;i< region_vector.size();i++){
                                                        if(region_vector[i]!=nullptr) region_vector[i]->print_customers();
                                                        }}
                    void region::print_ALL_CITY_customers(int did){//print all customers in a city
                                                         if(region_vector[did]!=nullptr)
                                                            region_vector[did]->print_customers();
                                                          else cout<<"the city :"<<did<<" does not exist in region :"<<ID<<endl;
                                                    }
                    void region::print_ALL_DISTRICT_customers(int cid,int did){//print all customers in a district
                                                        if(region_vector[cid]!=nullptr)
                                                            region_vector[cid]->print_ALL_DISTRICT_customers(did);
                                                        else cout<<"the district :"<<did<<" does not exist in region :"<<ID<<endl;
                                                    }
/*best customer*/   //returns best customer of the region
                    customer* region::get_best_customer_m(int m,int y){
                                                        customer* best = nullptr;
                                                        customer* temp = nullptr;
                                                        for (int i = 0; i < region_vector.size(); i++) {
                                                            if (region_vector[i] != nullptr) {
                                                                temp = region_vector[i]->get_best_customer_m(m,y);

                                                                if (best == nullptr || temp->get_best_injection_m(m, y) > best->get_best_injection_m(m, y)) {
                                                                    best = temp;
                                                                }
                                                            } else{continue;}
                                                        }
                                                        return best;
                                                    }
/*region income*/
                    double region::get_region_income_y(int y){
                                                            int income = 0;
                                                            for(int i=0;i<region_vector.size();i++)
                                                            {
                                                                if(region_vector[i] != nullptr)
                                                                {
                                                                    income += region_vector[i]->get_city_income_y(y);
                                                                }
                                                            }
                                                            return income;
                                                        }
/*insertion of deps*/
                    void region::insert_All_Dep(int y,Departement_Performence*& tree)
                                                        {
                                                            for(int i=0;i<region_vector.size();i++)
                                                            {
                                                                if(region_vector[i] != nullptr)
                                                                    region_vector[i]->add_dep_performence(y,tree);
                                                            }
                                                        }
                    void region::insert_investment(int city_id,int amount,int m,int y){
                                                        if(region_vector[city_id] != nullptr)
                                                        region_vector[city_id]->insert_investment(amount,m,y);
                                                        }
//end of region.Cpp
