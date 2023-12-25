#ifndef DISTRICT_BST_H
#define DISTRICT_BST_H

#include "customer.h"

#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <limits>
#include <utility>
#include <sstream>
using namespace std;

class district{
public:
/*CONSTRUCTORS + OVERLOADING OF =*/
                district ( int ID= 0,string name ="a" );//assignement constructor
                ~district();//destructor
                void delete_customer_tree(customer* root);//helper of distructor

/*SETTERS AND GETTERS*/
                void set_district_id(long long int ID);
                void set_district_name(string name);
                int get_district_id()const;
                string get_district_name()const;
/*FUNCTIONS*/
/*best_customer*/
                //return the best customer of the month in the district
                customer* get_best_customer_m( int y,int m);
                customer* helper_get_best_customer_district_m(customer* root, int y, int m,customer*& bst_cust);//helper
/*print*/
                //print the list of customers in the district
                void print_customers();
                void print_customers(customer* root);//helper
                //print one customer's informations in the district
                void print_customer(long long int id);
                void print_customer(long long int id, customer*& root);//helper

/*customer insertion*/
                //insert  (add new customer in the district)
                void add_new_cust(string name , long long int ID, int numf, string regionn, string diss, string cityy,  int* ages);
                customer* add_new_cust(string name, long long int x, int numf, string regionn, string diss, string cityy,  int* ages, customer* &t);//helper
                int get_balance(customer* root){
                    if (root==nullptr)return 0;
                    return (root->get_left() == nullptr ? -1 : root->get_left()->get_height()) - (root->get_right() == nullptr ? -1 : root->get_right()->get_height());

                }
                customer* rotate_left(customer* y){
                    customer* x = y->get_right();
                    y->set_right(x->get_left());
                    x->set_left(y);
                    int leftheight = (y->get_left() == nullptr) ? -1 : y->get_left()->get_height();
                    int rightheight = (y->get_right() == nullptr) ? -1 : y->get_right()->get_height();
                    y->set_height(1 + max(leftheight, rightheight));
                    leftheight = (x->get_left() == nullptr) ? -1 : x->get_left()->get_height();
                    rightheight = (x->get_right() == nullptr) ? -1 : x->get_right()->get_height();
                    x->set_height(1 + max(leftheight, rightheight));
                    return x;
                }
                customer* rotate_right(customer* x) {
                customer* y = x->get_left();
                x->set_left(y->get_right());
                y->set_right(x);
                int leftheight = (x->get_left() == nullptr) ? -1 : x->get_left()->get_height();
                int rightheight = (x->get_right() == nullptr) ? -1 : x->get_right()->get_height();
                x->set_height(1 + max(leftheight, rightheight));
                leftheight = (y->get_left() == nullptr) ? -1 : y->get_left()->get_height();
                rightheight = (y->get_right() == nullptr) ? -1 : y->get_right()->get_height();
                y->set_height(1 + max(leftheight, rightheight));
                return y;
                }
/*customer data insertion*/
                //insert electricity informations about the customer
                void add_new_cust_data(long long int ID, int y, int m, double consumption, double prodution);
                void add_new_cust_data(long long int id, int y, int m, double consumption, double prodution, customer* &root);//helper
/*search*/      //returns true if the customer exists in the district
                bool contains(long long int ID);//returns yes if the customer is in the district
                bool contains(long long int ID,customer* &root);//helper
/*SHOW BILLS*/
/*all bills of all customers*/
                // show list of bills of each customer in each month in a period of time in the district
                void show_bills_customers_y(int year);
                void show_bill_customers_m(int month,int year);
                void show_bills_customers_period(int startingmmonth,int startingyear, int endmonth, int endyear);
                //helper functions
                void show_bills_customers_y(int year,customer* &root);
                void show_bill_customers_m(int m,int y,customer* &root);
                void show_bills_customers_period(int startingmmonth,int startingyear, int endmonth, int endyear,customer* &root);
/*bill of a customer*/
                //showing bills of only one customer in every month of a period of time
                void show_bills_customer_y(long long int id,int y);
                void show_bill_customer_m(long long int id, int y , int m);
                void show_bills_customer_period(long long int id, int startingmmonth,int startingyear, int endmonth, int endyear);
                //helper functions
                void show_bills_customer_y(long long int id,int y,customer* &root);
                void show_bill_customer_m(long long int id,int y ,int m,customer* &root);
                void show_bills_customer_period(long long int id, int startingmmonth,int startingyear, int endmonth, int endyear,customer* &root);

/*CONSUMPTION-PRODUCTION getters*/
/*for a customer*/
                //get consumption/production of a customer in a period of time
                double get_consumption_y(long long int cust_id,int year) ;
                double get_consumption_m(long long int cust_id,int month,int year);
                double get_consumption_period(long long int cust_id,int startingmonth, int startingyear, int endmonth, int endyear);

                double get_production_y(long long int cust_id,int year) ;
                double get_production_m(long long int cust_id,int month,int year);
                double get_production_period(long long int cust_id,int startingmonth, int startingyear, int endmonth, int endyear);
                //helpers
                double get_consumption_y(long long int cust_id,int year,customer*& root) ;
                double get_consumption_m(long long int cust_id,int month,int year,customer*& root);
                double get_consumption_period(long long int cust_id,int startingmonth, int startingyear, int endmonth, int endyear,customer*& root);

                double get_production_y(long long int cust_id,int year,customer*& root) ;
                double get_production_m(long long int cust_id,int month,int year,customer*& root);
                double get_production_period(long long int cust_id,int startingmonth, int startingyear, int endmonth, int endyear,customer*& root);

/*total for district*/
                //total production total consumption of the district
                double get_consumption_y(int year){double t=0;return this->get_consumption_y(year,t,customers_treehead);}
                double get_consumption_m(int month,int year){double t=0;return this->get_consumption_m(month,year,t,customers_treehead);}
                double get_consumption_period(int startingmonth, int startingyear, int endmonth, int endyear){double t=0;return get_consumption_period(startingmonth,startingyear,endmonth,endyear,t,customers_treehead);}

                double get_production_y(int year){double t=0;return this->get_production_y(year,t,customers_treehead);}
                double get_production_m(int month,int year){double t=0;return this->get_production_m(month,year,t,customers_treehead);}
                double get_production_period(int startingmonth, int startingyear, int endmonth, int endyear){double t=0; return get_production_period(startingmonth,startingyear,endmonth,endyear,t,customers_treehead);}
                //helpers
                double get_consumption_y(int year,double& t,customer*& root) ;
                double get_consumption_m(int month,int year,double& t,customer*& root);
                double get_consumption_period(int startingmonth, int startingyear, int endmonth, int endyear,double& t,customer*& root);

                double get_production_y(int year,double& t,customer*& root) ;
                double get_production_m(int month,int year,double& t,customer*& root);
                double get_production_period(int startingmonth, int startingyear, int endmonth, int endyear,double& t,customer*& root);

/*is departement win*/
                //returns the total of the bills of the customers over a year , it is used to determine which departement is the winner
                double  get_district_income_y(int y);
                double get_district_income_y(int y, customer* root, double& total);//helper function

private:
                long long int district_id;
                string district_name;
                customer* customers_treehead;
};

#endif // DISTRICT_BST_H



//district.cpp

//CONSTRUCTORS + OVERLOADING OF =
// constructor
                    district::district(  int ID,string name)
                                            {
                                                district_name= name;
                                                district_id=ID;
                                                customers_treehead=nullptr;
                                            }

//destructor
                    district::~district(){delete_customer_tree(customers_treehead);}
                    void district::delete_customer_tree(customer* root) {
                                            if (root != nullptr) {
                                                delete_customer_tree(root->get_left());
                                                delete_customer_tree(root->get_right());
                                                delete root;
                                            }
                                        }
//SETTERS AND GETTERS
                    void district::set_district_id(long long int ID){district_id =ID;}
                    void district::set_district_name(string name){district_name=name;}

                    int district::get_district_id()const{return district_id;}
                    string district::get_district_name()const{return district_name;}
//functions
                    //best_customer_functions
                    //return best_customer_in_month
                    customer* district::get_best_customer_m(int y, int m) {
                                                    customer* bst_cust = nullptr;
                                                    return helper_get_best_customer_district_m(customers_treehead, y, m, bst_cust);
                                                }
                    //helper
                    customer* district::helper_get_best_customer_district_m(customer* root, int y, int m, customer*& bst_cust) {
                                                    if (root == nullptr)
                                                        return bst_cust;

                                                    customer* left = helper_get_best_customer_district_m(root->get_left(), y, m, bst_cust);
                                                    customer* right = helper_get_best_customer_district_m(root->get_right(), y, m, bst_cust);

                                                    if (left != nullptr && (right == nullptr || left->get_best_injection_m(m, y) >= right->get_best_injection_m(m, y))) {
                                                        if (bst_cust == nullptr || left->get_best_injection_m(m, y) >= bst_cust->get_best_injection_m(m, y)) {
                                                            bst_cust = left;
                                                        }
                                                    } else if (right != nullptr) {
                                                        if (bst_cust == nullptr || right->get_best_injection_m(m, y) >= bst_cust->get_best_injection_m(m, y)) {
                                                            bst_cust = right;
                                                        }
                                                    }

                                                    if (bst_cust == nullptr || root->get_best_injection_m(m, y) >= bst_cust->get_best_injection_m(m, y)) {
                                                        bst_cust = root;
                                                    }

                                                    return bst_cust;
                                                }
//PRINT             //print all customers
                    void district:: print_customers(){cout<<endl;
                                                cout<<"list of customers of district:"<<district_id<<endl;
                                                if(customers_treehead==nullptr){
                                                cout<<"this districtis empty, it has no customers"<<endl;}
                                                else
                                                print_customers(customers_treehead);
                                                cout<<endl;
                                            }
                    void district:: print_customers(customer* root){//helper function: inorder travesral of tree of customers, all functions follow inorder traversal
                                                if(root==nullptr){
                                                    return;
                                                }
                                                print_customers(root->get_left());
                                                cout<<root->get_cust_id()<<endl;
                                                print_customers(root->get_right());
                                            }
                    //print one customer by its id
                    void district::print_customer(long long int id){
                                                int d=(id/10000)%100;
                                                if(contains(id))
                                                print_customer(id,customers_treehead);
                                                else cout<<"customer not found in district "<<d<<endl;
                                            }
                    void district::print_customer(long long int id,customer*& root){//helper
                                                if (root == nullptr) {
                                                    return;
                                                }
                                                if (root->get_cust_id() == id) {
                                                    root->print_customer();
                                                } else if (root->get_cust_id() < id) {
                                                    print_customer(id,root->get_right());
                                                } else {
                                                    print_customer( id,root->get_left());
                                                }
                                            }
//customer insertion
                    void district::add_new_cust(string name, long long int ID, int numf, string regionn, string diss, string cityy, int* ages) {
                                                customers_treehead=add_new_cust(name, ID, numf, regionn, diss, cityy,  ages, customers_treehead);
                                                }
                     // Helper function for insertion
                    customer* district::add_new_cust(string name, long long int x, int numf, string regionn, string diss, string cityy,   int* ages, customer* &t) {
                                                if (t == nullptr) {
                                                    return new customer(name, x, numf, regionn, diss, cityy,   ages);
                                                } else if (x < t->get_cust_id()) {
                                                    t->set_left(add_new_cust(name, x, numf, regionn, diss, cityy, ages, t->get_left()));
                                                } else if (t->get_cust_id() < x) {
                                                    t->set_right(add_new_cust(name, x, numf, regionn, diss, cityy, ages, t->get_right()));
                                                } else {
                                                    }
                                                int leftheight = (t->get_left() == nullptr) ? -1 : t->get_left()->get_height();
                                                int rightheight = (t->get_right() == nullptr) ? -1 : t->get_right()->get_height();
                                                t->set_height(1 + max(leftheight, rightheight));
                                                int balance = get_balance(t);
                                                if (balance > 1) {
                                                    if (x < t->get_left()->get_cust_id()) {
                                                        return rotate_right(t);}
                                                    else {
                                                        t->set_left(rotate_left(t->get_left()));
                                                        return rotate_right(t);}
                                                }
                                                if (balance < -1) {
                                                    if (x > t->get_right()->get_cust_id()) {
                                                        return rotate_left(t);}

                                                    else {
                                                            t->set_right(rotate_right(t->get_right()));
                                                            return rotate_left(t);
                                                         }
                                                }
                                                return t;
                                            }
//customer data insertion
                    void district::add_new_cust_data(long long int id, int y, int m, double consumption, double production){
                                                add_new_cust_data( id,  y,  m,  consumption,  production, customers_treehead);
                                                }
                    //helper of data insertion
                    void district::add_new_cust_data(long long int id, int y, int m, double consumption, double production, customer* &root){
                                                if(root==nullptr){
                                                    return;
                                                }
                                                if (root->get_cust_id() == id) {
                                                    root->add_new_cust_data(consumption, production, m, y); return;}
                                                if(root->get_cust_id() > id)
                                                add_new_cust_data(id, y, m, consumption, production, root->get_left());
                                                if(root->get_cust_id() <id)
                                                add_new_cust_data(id, y, m, consumption, production, root->get_right());
                                            }
//CHECK returns yes if the customer is in the district
                    bool district::contains(long long int ID){
                                                 return contains(ID,customers_treehead); }
                    //helper of check
                    bool district:: contains(long long int x ,customer* &t){
                                                if( t == nullptr )
                                                    return false;
                                                else {if( x < t->get_cust_id() )
                                                    return contains( x, t->get_left() );
                                                else {if( t->get_cust_id() < x )
                                                    return contains( x, t->get_right() );
                                                else
                                                    return true;}
                                                    }
                                        }
//SHOW BILL FUNCTIONS
//all bills of all customers
                    //month
                    void district::show_bill_customers_m(int month,int year){
                                                cout<<endl;
                                                cout<<"list of bills of customers of district:"<<district_id<<" for month: "<<month<<" year:"<<year<<endl;
                                                if(customers_treehead==nullptr)
                                                cout<<"this districtis empty, it has no customers"<<endl;
                                                else{
                                                show_bill_customers_m(month,year,customers_treehead);}
                                                cout<<endl;
                                            }
                    //helper function //month
                    void district:: show_bill_customers_m(int m,int y,customer* &root){
                                                if(root==nullptr){
                                                    return;
                                                }
                                                show_bill_customers_m(m,y,root->get_left());
                                                root->show_bill_m(m,y);
                                                show_bill_customers_m(m,y,root->get_right());
                                            }
                    // year
                    void district::show_bills_customers_y(int year){cout<<endl;
                                                cout<<"list of customers of district:"<<district_id<<endl;
                                                if(customers_treehead==nullptr)
                                                cout<<"this districtis empty, it has no customers"<<endl;
                                                else
                                                show_bills_customers_y(year,customers_treehead);
                                                cout<<endl;
                                            }
                    //helper function //year
                    void district::show_bills_customers_y(int y,customer* &root){
                                                if(root==nullptr){
                                                    return;
                                                }
                                                show_bills_customers_y(y,root->get_left());
                                                root->show_bills_y(y);
                                                show_bills_customers_y(y,root->get_right());

                                            }
                    //period
                    void district:: show_bills_customers_period(int startingmonth,int startingyear, int endmonth, int endyear){cout<<endl;
                                                cout<<"list of customers of district:"<<district_id<<endl;
                                                if(customers_treehead==nullptr)
                                                cout<<"this districtis empty, it has no customers"<<endl;
                                                else
                                                show_bills_customers_period(startingmonth,startingyear,endmonth,endyear,customers_treehead);
                                                cout<<endl;
                                            }
                    //helper function//period
                    void district:: show_bills_customers_period(int startingmonth,int startingyear, int endmonth, int endyear,customer* &root){
                                                if(root==nullptr){
                                                    return;
                                                }
                                                show_bills_customers_period(startingmonth,startingyear,endmonth,endyear,root->get_left());
                                                root->show_bills_period(startingmonth,startingyear,endmonth,endyear);
                                                show_bills_customers_period(startingmonth,startingyear,endmonth,endyear,root->get_right());
                                            }
// show bills of only one customer in a period of time
                    // year
                    void district::show_bills_customer_y(long long int id,int y){cout<<endl;
                                                show_bills_customer_y(id,y,customers_treehead);
                                                cout<<endl;
                                            }
                    //helper//year
                    void district::show_bills_customer_y(long long int id,int y,customer* &root){
                                                if(root==nullptr) cout<<"customer not found"<<endl;
                                                if(root->get_cust_id()==id){
                                                    root->show_bills_y(y);
                                                }
                                                if(root->get_cust_id() < id)
                                                show_bills_customer_y(id,y,root->get_right());
                                                if(root->get_cust_id() > id)
                                                show_bills_customer_y(id,y,root->get_left());
                                            }

                    void district::show_bill_customer_m(long long int id, int y, int m) {cout<<endl;
                                                show_bill_customer_m(id, y, m, customers_treehead);
                                                cout<<endl;
                                            }
                    //helper//month
                    void district::show_bill_customer_m(long long int id, int y, int m, customer* &root) {
                                                if (root == nullptr) {
                                                    // customer not found
                                                    return;
                                                }
                                                if (root->get_cust_id() == id) {
                                                    root->show_bill_m(m, y);
                                                    return;
                                                } else if (root->get_cust_id() < id) {
                                                    show_bill_customer_m(id, y, m, root->get_right());
                                                } else {  // root->get_cust_id() > id
                                                    show_bill_customer_m(id, y, m, root->get_left());
                                                }
                                            }
                    //period
                    void district::show_bills_customer_period(long long int id, int startingmmonth,int startingyear, int endmonth, int endyear){cout<<endl;
                                                show_bills_customer_period(id,  startingmmonth, startingyear,  endmonth,  endyear, customers_treehead);
                                                cout<<endl;
                                            }
                    //helper
                    void district::show_bills_customer_period(long long int id, int startingmmonth,int startingyear, int endmonth, int endyear,customer* &root){
                                                if(root==nullptr) cout<<"customer not found"<<endl;
                                                if(root->get_cust_id()==id){
                                                    root->show_bills_period( startingmmonth, startingyear,  endmonth,  endyear);
                                                }
                                                if(root->get_cust_id() < id)
                                                show_bills_customer_period(id,  startingmmonth, startingyear,  endmonth,  endyear, root->get_right());
                                                if(root->get_cust_id() > id)
                                                show_bills_customer_period(id,  startingmmonth, startingyear,  endmonth,  endyear, root->get_left());
                                            }

//CONSUMPTION-PRODUCTION functions
//getters of consumption-production for a customer
                    //cn
                    double district:: get_consumption_y(long long int cust_id,int year){
                                                return get_consumption_y(cust_id,year,customers_treehead);
                                            }
                    double district::get_consumption_m(long long int cust_id,int month,int year){
                                                return get_consumption_m(cust_id,month,year,customers_treehead);
                                            }
                    double district::get_consumption_period(long long int cust_id,int startingmonth, int startingyear, int endmonth, int endyear){
                                                return get_consumption_period(cust_id,startingmonth,startingyear,endmonth,endyear,customers_treehead);
                                            }
                    //pr
                    double district:: get_production_y(long long int cust_id,int year){
                                                return get_production_y(cust_id,year,customers_treehead);
                                            }
                    double district::get_production_m(long long int cust_id,int month,int year){
                                                return get_production_m(cust_id,month,year,customers_treehead);
                                            }
                    double district::get_production_period(long long int cust_id,int startingmonth, int startingyear, int endmonth, int endyear){
                                                return get_production_period(cust_id,startingmonth,startingyear,endmonth,endyear,customers_treehead);
                                            }
//helpers
                    //cn
                    double district::get_consumption_y(long long int id,int y,customer* &root){
                                                if (root == nullptr) {
                                                    return 0;
                                                }
                                                if (root->get_cust_id() == id) {
                                                    return root->get_consumption_y(y);
                                                } else if (root->get_cust_id() < id) {
                                                    get_consumption_y(id,y, root->get_right());
                                                } else {
                                                    get_consumption_y( id, y, root->get_left());
                                                }
                                            }
                    double district::get_consumption_m(long long int id, int m,int y,customer*& root){
                                                if (root == nullptr) {
                                                    return 0;
                                                }
                                                if (root->get_cust_id() == id) {
                                                    return root->get_consumption_m(m,y);
                                                } else if (root->get_cust_id() < id) {
                                                    get_consumption_m(id,m,y, root->get_right());
                                                } else {
                                                    get_consumption_m( id,m,y , root->get_left());
                                                }
                                            }
                    double district::get_consumption_period(long long int id, int sm,int sy,int em,int ey,customer*& root){
                                                if (root == nullptr) {
                                                    return 0;
                                                }
                                                if (root->get_cust_id() == id) {
                                                    return root->get_consumption_period(sm,sy,em,ey);
                                                } else if (root->get_cust_id() < id) {
                                                    get_consumption_period(id,sm,sy,em,ey, root->get_right());
                                                } else {
                                                    get_consumption_period( id,sm,sy,em,ey, root->get_left());
                                                }
                                            }
                    //pr
                    double district::get_production_y(long long int id,int y,customer* &root){
                                                if (root == nullptr) {
                                                    return 0;
                                                }
                                                if (root->get_cust_id() == id) {
                                                    return root->get_production_y(y);
                                                } else if (root->get_cust_id() < id) {
                                                    get_production_y(id,y, root->get_right());
                                                } else {
                                                    get_production_y( id, y, root->get_left());
                                                }
                                            }
                    double district::get_production_m(long long int id, int m,int y,customer*& root){
                                                if (root == nullptr) {
                                                    return 0;
                                                }
                                                if (root->get_cust_id() == id) {
                                                    return root->get_production_m(m,y);
                                                } else if (root->get_cust_id() < id) {
                                                    get_production_m(id,m,y, root->get_right());
                                                } else {
                                                    get_production_m( id,m,y , root->get_left());
                                                }
                                            }
                    double district::get_production_period(long long int id, int sm,int sy,int em,int ey,customer*& root){
                                            if (root == nullptr) {
                                                return 0;
                                            }
                                            if (root->get_cust_id() == id) {
                                                return root->get_production_period(sm,sy,em,ey);
                                            } else if (root->get_cust_id() < id) {
                                                get_production_period(id,sm,sy,em,ey, root->get_right());
                                            } else {
                                                get_production_period( id,sm,sy,em,ey, root->get_left());
                                            }
                                        }
//total helpers  the functions are in the header
//calculating the total bill of the district in a period of time
                    //cn
                    double district::get_consumption_y(int y,double& t,customer*& root) {
                                            if(root==nullptr) return t;
                                            t=get_consumption_y(y,t,root->get_left());
                                            t+=root->get_consumption_y(y);
                                            t=get_consumption_y(y,t,root->get_right());
                                            return t;
                                        }
                    double district::get_consumption_m(int m,int y,double& t,customer*& root){
                                            if(root==nullptr) return t;
                                            t=get_consumption_m(m,y,t,root->get_left());
                                            t+=root->get_consumption_m(m,y);
                                            t=get_consumption_m(m,y,t,root->get_right());
                                            return t;
                                        }
                    double get_consumption_period(int startingmonth, int startingyear, int endmonth, int endyear,double& t,customer*& root){
                                            if(root==nullptr) return t;
                                            t=get_consumption_period(startingmonth,startingyear,endmonth,endyear,t,root->get_left());
                                            t+=root->get_consumption_period(startingmonth,startingyear,endmonth,endyear);
                                            t=get_consumption_period(startingmonth,startingyear,endmonth,endyear,t,root->get_right());
                                            return t;
                                        }
                    //pr
                    double district:: get_production_y(int y,double& t,customer*& root) {
                                            if(root==nullptr) return t;
                                            t=get_production_y(y,t,root->get_left());
                                            t+=root->get_production_y(y);
                                            t=get_production_y(y,t,root->get_right());
                                            return t;
                                        }
                    double district:: get_production_m(int m,int y,double& t,customer*& root){
                                            if(root==nullptr) return t;
                                            t=get_production_m(m,y,t,root->get_left());
                                            t+=root->get_production_m(m,y);
                                            t=get_production_m(m,y,t,root->get_right());
                                            return t;
                                        }
                    double district::get_production_period(int startingmonth, int startingyear, int endmonth, int endyear,double& t,customer*& root){
                                            if(root==nullptr) return t;
                                            t=get_production_period(startingmonth,startingyear,endmonth,endyear,t,root->get_left());
                                            t+=root->get_production_period(startingmonth,startingyear,endmonth,endyear);
                                            t=get_production_period(startingmonth,startingyear,endmonth,endyear,t,root->get_right());
                                            return t;
                                        }
//returns the total of the bills of the customers over a year to help determine the best departement ofthe year
                    double district:: get_district_income_y(int y){
                                            double total=0;
                                            get_district_income_y(y, customers_treehead, total);
                                            }
                    //helper function
                    double district:: get_district_income_y(int y, customer* root, double& total){
                                            if(root==nullptr) return total;
                                            total=get_district_income_y(y,root->get_left(),total);
                                            total+=root->get_bill_y(y);
                                            total=get_district_income_y(y,root->get_right(),total);
                                            return total;
                                        }
//end of district.cpp
