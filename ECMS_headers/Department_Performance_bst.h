#ifndef DEPARTMENT_PERFORMANCE_BST_H
#define DEPARTMENT_PERFORMANCE_BST_H

#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <limits>
#include <utility>
#include <sstream>
using namespace std;

class Departement_Performence{
private:

            class performence{
            public:
                    int ID;
                    string name;
                    int dep_performence;
                    performence* left;
                    performence* right;

                    performence(int dep_id,string n,int per):ID(dep_id),name(n),dep_performence(per),left(nullptr),right(nullptr){}
            };
            performence* root;
public:

            Departement_Performence():root(nullptr){}

            ~Departement_Performence()
            {
                erase(root);
            }

            void insert(int dep_id,string n,int per){
                                insert(root,dep_id,n,per);
                                 }
            void insert(performence* &ptr,int dep_id,string n,int per){
                                if(ptr == nullptr)
                                    ptr = new performence(dep_id,n,per);
                                else if(ptr->dep_performence > per)
                                    insert(ptr->left,dep_id,n,per);
                                else
                                    insert(ptr->right,dep_id,n,per);
                                }
            void in_order_traversal(){
                                    int rank = 1;
                                    in_order_traversal(root,rank);
                                    }
            void in_order_traversal(performence* ptr,int &rank) {
                                    if(ptr != nullptr)
                                    {   in_order_traversal(ptr->right,rank);
                                        cout<<"the departement in rank "<<rank<<" is :"<<ptr->name<<", ID : "<<ptr->ID<<std::endl;
                                        in_order_traversal(ptr->left,++rank);
                                    }}

            void erase(performence* &ptr)
            {
                if(ptr!=nullptr)
                {
                    erase(ptr->left);
                    erase(ptr->right);
                    delete ptr;
                    ptr = nullptr;
                }
            }

};


#endif // DEPARTMENT_PERFORMANCE_BST_H
