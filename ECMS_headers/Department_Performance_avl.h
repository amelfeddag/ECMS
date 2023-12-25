#ifndef DEPARTMENT_PERFORMANCE_AVL_H
#define DEPARTMENT_PERFORMANCE_AVL_H

#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <limits>
#include <utility>
#include <sstream>
using namespace std;

class Departement_Performence
{

private:
    class performence
    {
        public:

            int ID;
            string name;
            int dep_performence;
            performence* left;
            performence* right;

            int height;

            performence(int dep_id,string n,int per):ID(dep_id),name(n),dep_performence(per),left(nullptr),right(nullptr),height(0){}
    };

    performence* root;

public:

    Departement_Performence():root(nullptr){}

    ~Departement_Performence()
            {
                erase(root);
            }

    void insert(int dep_id,string n,int per)
    {
        insert(root,dep_id,n,per);
    }
    void insert(performence* &ptr,int dep_id,string n,int per)
    {
        if(ptr == nullptr)
            ptr = new performence(dep_id,n,per);
        else if(ptr->dep_performence > per)
            insert(ptr->left,dep_id,n,per);
        else
            insert(ptr->right,dep_id,n,per);

        balence(ptr);
    }

    void in_order_traversal()
    {
        int rank = 1;
        in_order_traversal(root,rank);
    }
    void in_order_traversal(performence* ptr,int &rank)
    {
        if(ptr != nullptr)
        {
            in_order_traversal(ptr->right,rank);

            cout<<"the departement in rank "<<rank<<" is :"<<ptr->name<<", ID : "<<ptr->ID<<std::endl;

            in_order_traversal(ptr->left,++rank);
        } }

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

    void balence(performence* &ptr)
    {

        if(ptr==nullptr)
            return;
        else if(height(ptr->left) - height(ptr->right) >1)
        {
            if(height(ptr->left->left) > height(ptr->left->right))
                rotateR(ptr);
            else if(height(ptr->left->left) < height(ptr->left->right))
                doublerotateLR(ptr);
        }

        else if(height(ptr->right) - height(ptr->left) >1)
        {
            if(height(ptr->right->right) > height(ptr->right->left))
                rotateL(ptr);
            else if(height(ptr->right->right) < height(ptr->right->left))
                doublerotateRL(ptr);
        }

        ptr->height = max(height(ptr->left),height(ptr->right)) + 1;
    }

    void rotateR(performence* &ptr)
    {
        performence * temp = ptr->left;

        ptr->left = temp->right;
        temp->right = ptr;

        temp->height = max(height(temp->left),height(temp->right)) + 1;

        ptr->height = max(height(ptr->left),height(ptr->right)) + 1;

        ptr = temp;

    }

    void rotateL(performence* &ptr)
    {
        performence * temp = ptr->right;

        ptr->right = temp->left;
        temp->left = ptr;

        temp->height = max(height(temp->left),height(temp->right)) + 1;

        ptr->height = max(height(ptr->left),height(ptr->right)) + 1;

        ptr = temp;
    }

    void doublerotateLR(performence* &ptr)
    {
        rotateL(ptr->left);
        rotateR(ptr);
    }

    void doublerotateRL(performence* &ptr)
    {
        rotateR(ptr->right);
        rotateL(ptr);
    }

    int height(performence* t){
        if(t==nullptr) return -1;
        return t->height;
    }


};

#endif // DEPARTMENT_PERFORMANCE_AVL_H
