#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "Department_Performance_avl.h"

#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <limits>
#include <utility>
#include <sstream>
using namespace std;

class Departement{
private:
            class investment {

            private:
                int inv;
                int mounth;
                int year;
            public:
                investment(int dep_inv,int m,int y) : inv(dep_inv),mounth(m),year(y){}
                int get_inv(){return inv;}
                int get_mounth(){return mounth;}
                int get_year(){return year;}
            };
            vector<investment *> investments;

public:
            Departement(){}

            int get_investment_m(int m,int y);
            int get_investment_y(int y);
            int get_investment_period(int start_m,int start_y,int end_m,int end_y);

            void insert_investement(int amount,int m,int y);
};

#endif // DEPARTMENT_H




//departement.cpp
                    int Departement::get_investment_m(int m,int y){
                                            for(auto& obj : investments)
                                            {
                                                if((obj->get_year()>y) || (obj->get_year()==y && obj->get_mounth()>m))
                                                    return 0;
                                                else if(obj->get_year()==y && obj->get_mounth()==m)
                                                    return obj->get_inv();
                                            }
                                            return 0;
                                        }
                    int Departement::get_investment_y(int y){
                                            int inv = 0;
                                            for(auto& obj : investments)
                                            {
                                                if(obj->get_year() > y)
                                                    break;
                                                else if(obj->get_year()==y)
                                                    inv += obj->get_inv();
                                            }
                                            return inv;
                                        }

                    int Departement::get_investment_period(int start_m,int start_y,int end_m,int end_y){
                                            if((start_y>end_y) || (start_y==end_y && start_m>end_m))
                                                return 0;
                                            if(start_m>12 || start_m<1 || end_m>12 || end_m<1)
                                                return 0;
                                            int inv = 0;
                                            for(auto& obj : investments)
                                            {
                                                if((obj->get_year()>end_y) || (obj->get_year()==end_y && obj->get_mounth()>end_m))
                                                    break;
                                                else if(obj->get_mounth()>=start_m && obj->get_mounth()<=end_m && obj->get_year()>=start_y && obj->get_year()<=end_y)
                                                    inv += obj->get_inv();
                                            }
                                            return inv;
                                        }
                    void Departement::insert_investement(int amount,int m,int y){
                                            int pos=0;
                                            for(int i=0; i<investments.size();i++)
                                            {
                                                if((investments[i]->get_year()>y) || (investments[i]->get_year()==y && investments[i]->get_mounth()>m))
                                                    break;
                                                else if(investments[i]->get_year()==y && investments[i]->get_mounth()==m)
                                                    return;
                                                else
                                                    pos++;
                                            }
                                            investments.insert(investments.begin() + pos,new investment(amount,m,y));
                                        }

//end of departement.CPP
