#ifndef NETWORK_H
#define NETWORK_H

#include "region.h"
#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <limits>
#include <utility>
#include <sstream>
using namespace std;
class Network
{

private:
    string name;
    vector<region *> region_vector;

public:
                Network(string _name) : name(_name){
                    cout<<"//program uses BST trees"<<endl;
                      for (int i = 0; i < 100; i++)region_vector.push_back(nullptr);
                   }
/*getters*/
                string get_name();
/*insert cust*/
                void add_new_cust(long long int ID, string cus_name, int family_num, int * ages,string region,string city,string district);
/*insert cust data*/
                void add_new_cust_data(long long int ID,int consumption,int production,int m,int y);
/*SHOW BILLS*/
                //bills of a certain customer in a certain period of time
                void show_bill_m(long long int CUS_ID, int m, int y);
                void show_bill_y(long long int CUS_ID, int y);
                void show_bill_period(long long int CUS_ID, int start_m, int start_y, int end_m, int end_y);
                //bills of all customers in a certain district in a certain period of time
                void show_ALL_DISTRICT_bill_m(int region_ID,int CITY_ID,int DISTRICT_ID, int m, int y); //not yet
                void show_ALL_DISTRICT_bill_y(int region_ID,int CITY_ID,int DISTRICT_ID, int y); // not yett
                void show_ALL_DISTRICT_bill_period(int region_ID,int CITY_ID,int DISTRICT_ID, int start_m, int start_y, int end_m, int end_y); // not yet
                //bills of all customers in a certain city in a certain period of time
                void show_ALL_CITY_bill_m(int region_ID,int CITY_ID, int m, int y); //not yet
                void show_ALL_CITY_bill_y(int region_ID,int CITY_ID, int y); // not yett
                void show_ALL_CITY_bill_period(int region_ID,int CITY_ID, int start_m, int start_y, int end_m, int end_y); // not yet
                //bills of all customers in a certain region in a certain period of time
                void show_ALL_region_bill_m(int region_ID, int m, int y);
                void show_ALL_region_bill_y(int region_ID, int y);
                void show_ALL_region_bill_period(int region_ID, int start_m, int start_y, int end_m, int end_y);
                //bills of all customers of the network in a certain period of time
                void show_ALL_Network_bill_m(int m, int y);
                void show_ALL_Network_bill_y(int y);
                void show_ALL_Network_bill_period(int start_m, int start_y, int end_m, int end_y);

/*CONSUMPTION-PRODUCTION*/
                // returns consumption-production of the whole network in a certain month
                double get_consumption(int m,int y);
                double get_production(int m,int y);
                //returns consumption-production of a certain customer in a month
                double get_consumption(long long int id ,int m, int y);
                double get_production (long long int id, int m, int y);
/*print*/
               void print_customer(long long id);//a certain customer
               void print_customers();//all customers of the network
               void print_ALL_DISTRICT_customers(int rid,int cid,int did);//all customers of a district
               void print_ALL_CITY_customers(int rid,int cid);//all customers of a city
               void print_ALL_REGION_customers(int rid);//all customers of a region
/*best customer*/
                //returns best customer of the whole network in a certain month ==> the winner for that month
                customer* get_best_customer_m(int m, int y);
/*display best customers of a period of time*/
                void show_best_customer_m(int m,int y);
                void show_best_customers_y(int y);
                void show_best_customers_period(int sm,int sy,int em,int ey);
/*departement*/
                void departement_ranking(int y);
/*insertion of deps*/
                void insert_All_Dep(int y,Departement_Performence*& tree);
                void insert_investment(int region_ID,int CITY_ID, int amount, int m, int y);
};

#endif // NETWORK_H



//Network.cpp
/*getters*/
                    string Network::get_name(){return name;}
/*customer insertion*/
                    void Network::add_new_cust(long long int ID, string cus_name, int family_num, int* ages, string regionn, string city, string district){
                                                        int reg = (ID%100);
                                                        if(region_vector[reg] != nullptr)
                                                            region_vector[reg]->add_new_cust(ID,cus_name,family_num,ages,regionn,city,district);
                                                        else
                                                        {
                                                            region_vector[reg] = new region(reg,regionn);
                                                            region_vector[reg]->add_new_cust(ID,cus_name,family_num,ages,regionn,city,district);
                                                        }
                                                    }
/*customer data insertion*/
                    void Network::add_new_cust_data(long long int ID,int consumption,int production,int m,int y){
                                                        int reg = (ID%100);
                                                        if(region_vector[reg] != nullptr)
                                                            region_vector[reg]->add_new_cust_data(ID,consumption,production,m,y);}
/*BILLS*/           //bill of a customer
                    void Network::show_bill_m(long long int CUS_ID, int m, int y){
                                                        int reg = CUS_ID%100;
                                                        if(region_vector[reg] != nullptr) {
                                                            region_vector[reg]->show_bill_m(CUS_ID,m,y);}
                                                        else
                                                            std::cout<<"customer doesn't exist "<<std::endl;  }
                    void Network::show_bill_y(long long int CUS_ID, int y){
                                                        int reg = CUS_ID%100;
                                                        if(region_vector[reg] != nullptr)
                                                            region_vector[reg]->show_bill_y(CUS_ID,y);
                                                        else
                                                            std::cout<<"customer doesn't exist "<<std::endl;}
                    void Network::show_bill_period(long long int CUS_ID, int start_m, int start_y, int end_m, int end_y){
                                                        int reg = CUS_ID%100;
                                                        if(region_vector[reg] != nullptr)
                                                            region_vector[reg]->show_bill_period(CUS_ID,start_m,start_y,end_m,end_y);
                                                        else
                                                            std::cout<<"customer doesn't exist "<<std::endl;}
                    //bills of customers in a certain district
                    void Network::show_ALL_DISTRICT_bill_m(int region_ID,int CITY_ID,int DISTRICT_ID, int m, int y){
                                                        if(region_vector[region_ID] != nullptr)
                                                            region_vector[region_ID]->show_ALL_DIST_bill_m(CITY_ID,DISTRICT_ID,m,y);
                                                        else
                                                            std::cout<<"District doesn't exist "<<std::endl;}
                    void Network::show_ALL_DISTRICT_bill_y(int region_ID,int CITY_ID,int DISTRICT_ID, int y){
                                                        if(region_vector[region_ID] != nullptr)
                                                            region_vector[region_ID]->show_ALL_DIST_bill_y(CITY_ID,DISTRICT_ID,y);
                                                        else
                                                            std::cout<<"District doesn't exist "<<std::endl;}
                    void Network::show_ALL_DISTRICT_bill_period(int region_ID,int CITY_ID,int DISTRICT_ID, int start_m, int start_y, int end_m, int end_y){
                                                        if(region_vector[region_ID] != nullptr)
                                                            region_vector[region_ID]->show_ALL_DIST_bill_period(CITY_ID,DISTRICT_ID,start_m,start_y,end_m,end_y);
                                                        else
                                                            std::cout<<"District doesn't exist "<<std::endl;}
                    //bills of customers in a certain city
                    void Network::show_ALL_CITY_bill_m(int region_ID,int CITY_ID, int m, int y){
                                                        if(region_vector[region_ID] != nullptr)
                                                            region_vector[region_ID]->show_ALL_CITY_bill_m(CITY_ID,m,y);
                                                        else
                                                            std::cout<<"City doesn't exist "<<std::endl;}
                    void Network::show_ALL_CITY_bill_y(int region_ID,int CITY_ID, int y){
                                                        if(region_vector[region_ID] != nullptr)
                                                            region_vector[region_ID]->show_ALL_CITY_bill_y(CITY_ID,y);
                                                        else
                                                            std::cout<<"City doesn't exist "<<std::endl; }
                    void Network::show_ALL_CITY_bill_period(int region_ID,int CITY_ID, int start_m, int start_y, int end_m, int end_y){
                                                        if(region_vector[region_ID] != nullptr)
                                                            region_vector[region_ID]->show_ALL_CITY_bill_period(CITY_ID,start_m,start_y,end_m,end_y);
                                                        else
                                                            std::cout<<"City doesn't exist "<<std::endl; }
                    //bills of customers in a certain region
                    void Network::show_ALL_region_bill_m(int region_ID, int m, int y){
                                                        if(region_vector[region_ID] != nullptr)
                                                            region_vector[region_ID]->show_ALL_region_bill_m(m,y);
                                                        else std::cout<<"region doesn't exist "<<std::endl;}
                    void Network::show_ALL_region_bill_y(int region_ID, int y){
                                                        if(region_vector[region_ID] != nullptr)
                                                            region_vector[region_ID]->show_ALL_region_bill_y(y);
                                                        else std::cout<<"region doesn't exist "<<std::endl;}
                    void Network::show_ALL_region_bill_period(int region_ID, int start_m, int start_y, int end_m, int end_y){
                                                        if(region_vector[region_ID] != nullptr)
                                                            region_vector[region_ID]->show_ALL_region_bill_period(start_m,start_y,end_m,end_y);
                                                        else std::cout<<"region doesn't exist "<<std::endl; }
                    //bills of all customers in the network
                    void Network::show_ALL_Network_bill_m(int m, int y){
                                                        std::cout << "The resume of the bills of the entire network " << name << " for " << m << "/" << y << " : " << std::endl;
                                                        for (int i = 0; i < region_vector.size(); i++)
                                                        {if (region_vector[i] != nullptr)
                                                            {region_vector[i]->show_ALL_region_bill_m(m, y); } } }

                    void Network::show_ALL_Network_bill_y(int y){
                                                        std::cout << "The resume of the bills of the entire network " << name << " for " << y << " : " << std::endl;
                                                        for (int j = 1; j <= 12; j++)
                                                        {show_ALL_Network_bill_m(j, y);} }

                    void Network::show_ALL_Network_bill_period(int start_m, int start_y, int end_m, int end_y){
                                                        std::cout << "The resume of the bills of the entire network " << name << " between " << start_m << "/" << start_y << " and " << end_m << "/" << end_y << " : " << std::endl;
                                                        int y = start_y;
                                                        while (y <= end_y)
                                                        {if (start_y == end_y)
                                                            {for (int j = start_m; j <= end_m; j++)
                                                             {show_ALL_Network_bill_m(j, y);} }
                                                            else if (y == start_y){
                                                                for (int j = start_m; j <= 12; j++){
                                                                show_ALL_Network_bill_m(j, y);
                                                                }}
                                                            else if (y == end_y)
                                                            {for (int j = 0; j <= end_m; j++)
                                                                {show_ALL_Network_bill_m(j, y);}
                                                            }
                                                            else
                                                            {for (int j = 1; j <= 12; j++)
                                                                {show_ALL_Network_bill_m(j, y);}
                                                            }++y;} }
/*CONSUMPTION-PRODUCTION getters*/
                    //consumption-production of all network
                    double Network::get_consumption(int m,int y){
                                                            double consumption = 0;
                                                            for(int i=0;i<region_vector.size();i++){
                                                                if(region_vector[i] != nullptr)
                                                                    consumption += region_vector[i]->get_consumption_m(m,y);
                                                            }
                                                            return consumption;}
                    double Network::get_production(int m,int y){
                                                            double production = 0;
                                                            for(int i=0;i<region_vector.size();i++){
                                                                if(region_vector[i] != nullptr)
                                                                    production += region_vector[i]->get_production_m(m,y);
                                                            }
                                                            return production;}
                    //consumption-production of one customer
                    double Network::get_consumption (long long int id,int m, int y){
                                                            int r=id%100;
                                                            if(region_vector[r]!=nullptr)
                                                                return region_vector[r]->get_consumption_m(id,m,y);
                                                            else { cout<<"region does not exist, customer not found"<<endl;return 0;}
                                                             }
                    double Network ::get_production (long long int id,int m, int y){
                                                            int r=id%100;
                                                            if(region_vector[r]!=nullptr)
                                                                return region_vector[r]->get_production_m(id,m,y);
                                                            else { cout<<"region does not exist, customer not found"<<endl;return 0;}
                                                             }
/*PRINT*/           //print one customer's informations
                    void Network:: print_customer(long long int id){
                                                               int r=id%100;
                                                               if(region_vector[r]!=nullptr)
                                                                    region_vector[r]->print_customer(id);
                                                                else {cout<<"the region of customer: "<<id<<" does not exist"<<endl;
                                                                cout<<"customer not found"<<endl;}
                                                           }
                    void Network::print_customers(){//print all customers in the network
                                                                cout<<"a list of the customers the network: "<<name<<" :"<<endl;
                                                                for(int i=0;i< region_vector.size();i++){
                                                                if(region_vector[i]!=nullptr) region_vector[i]->print_customers();
                                                                }}
                    void Network::print_ALL_REGION_customers(int rid){//print all customers in a region
                                                                 if(region_vector[rid]!=nullptr)
                                                                    region_vector[rid]->print_customers();
                                                                  else cout<<"the region :"<<rid<<" does not exist in network :"<<name<<endl;
                                                            }
                    void Network::print_ALL_CITY_customers(int rid,int cid){//print all customers in a city
                                                             if(region_vector[rid]!=nullptr)
                                                                region_vector[rid]->print_ALL_CITY_customers(cid);
                                                              else cout<<"the city :"<<cid<<" does not exist in network :"<<name<<endl;
                                                        }
                    void Network::print_ALL_DISTRICT_customers(int rid,int cid,int did){//print all customers in a district
                                                            if(region_vector[rid]!=nullptr)
                                                                region_vector[rid]->print_ALL_DISTRICT_customers(cid,did);
                                                            else cout<<"the district :"<<did<<" does not exist in network :"<<name<<endl;
                                                        }
/*best customer*/
                   customer* Network::get_best_customer_m(int m, int y){
                                                            customer *best_cus = nullptr;
                                                            customer *temp = nullptr;
                                                            for (int i = 0; i < region_vector.size(); i++){
                                                                if (region_vector[i] != nullptr){
                                                                    if (best_cus == nullptr)
                                                                        best_cus = region_vector[i]->get_best_customer_m(m, y);
                                                                    else{
                                                                        temp = region_vector[i]->get_best_customer_m(m, y);
                                                                        if (best_cus->get_best_injection_m(m, y) < temp->get_best_injection_m(m, y))
                                                                            best_cus = temp;}} }
                                                            return best_cus;
                                                        }
/*display best customers in each month of a period of time*/
                    void Network::show_best_customer_m(int m,int y){
                        cout<<"best customer of the network :"<<name<<" for month :"<<m<<" year:"<<y<<endl;
                        if(get_best_customer_m(m,y)==nullptr) cout<<"no best customer for this month"<<endl;
                        get_best_customer_m(m,y)->print_customer();
                    }
                    void Network :: show_best_customers_y(int y){
                        cout<<"list of best customers for network: "<<name<<" for year:"<<y<<endl;
                        for(int i=1;i<=12;i++){
                            show_best_customer_m(i,y);
                        }
                    }
                    void Network:: show_best_customers_period(int sm,int sy,int em,int ey){
                        cout<<"list of best customers for network: "<<name<<" from :"<<sm<<"/"<<sy<<" until:"<<em<<"/"<<ey<<" :"<<endl;
                        for(int i=sm;i<=12;i++){
                            show_best_customer_m(i,sy);
                        }
                        for(int i=sy+1; i<=ey-1;i++){
                            for(int j=1;j<=12;j++){
                            show_best_customer_m(j,i);
                            }
                        }
                        for(int i=1;i<=em;i++){
                            show_best_customer_m(i,ey);
                        }
                    }
/*departement*/     void Network::departement_ranking(int y)
                    {
                            Departement_Performence* tree = new Departement_Performence;
                            insert_All_Dep(y,tree);
                            tree->in_order_traversal();
                    }
/*insertion of deps*/
                    void Network::insert_All_Dep(int y,Departement_Performence*& tree){
                        for(int i=0;i<region_vector.size();i++){
                            if(region_vector[i] != nullptr)
                                region_vector[i]->insert_All_Dep(y,tree);}}
                    //insertion of investement
                    void Network::insert_investment(int region_ID,int CITY_ID, int amount, int m, int y){
                        if(region_vector[region_ID] != nullptr)
                            region_vector[region_ID]->insert_investment(CITY_ID,amount,m,y);
                    }
//end of Network.cpp

