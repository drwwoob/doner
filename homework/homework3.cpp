// coded in c++ 
#include <string>
#include <__algorithm/max.h>

class test{
    // Implement an algorithm to determine if a string has all unique characters. 
    //What if you cannot use additional data structures? [1.1 p.73]
    bool l1(std::string str){
        for(auto letter : str){
            if(str.find(letter) != str.rfind(letter))
                return false;
        }
        return true;
    }

    //Implement a method to perform basic string compression using the counts of repeated characters. 
    //For example, the string aabcccccaaa would become a2b1c5a3.
    // If the compressed string would not become smaller than the original string, 
    //your method should return the original string. [1.5 p.73]
    std::string l2(std::string str){
        if(str.size() < 2){
            return str;
        }
        std::string comp = "";
        int pos = 1;
        char letter = str.at(0);
        int count = 1;

        while(comp.size() < str.size()){
            if(pos == str.size()){
                return comp;
            }
            if(str.at(pos) == letter){
                count++;
            }
            else{
                comp += letter;
                comp += count;
                letter = str.at(pos);
                count = 1;
            }
            pos++;
        }
        return str;
    }

    //Write code to remove duplicates from an unsorted linked list. 
    //A follow-on question: how would you solve this problem if a temporary buffer is not allowed? [2.1 p.77]
    Node l3(Node* head){         // node are set in the very back of this file
        std::vector<int> values;
        values.emplace_back(head->value);
        Node* clear_head = head;

        while(head->next != nullptr){
            if(std::find(values.begin(), values.end(), head->next->value) == values.end()){
                values.emplace_back(head->next->value);
                head = head->next;
            }
            else{
                head->next = head->next->next;
            }
        }

        return *clear_head;


    // if a temporary buffer is not allowed, I think I would just go throught the list from head to search for value
    // while(head.next != nullptr){
    //      int n_v = head->next->value;
    //      Node* search = clear_head;
    //      while(search !=  head->next && search->value != head->next->value){
    //          search = head->next;
    //      }
    //      if(search == head->next){
                // values.emplace_back(head->next->value);
                // head = head->next;
    //       }
    //        else{
    //             head->next = head->next->next;
    //       }
    //}
    }

    //Implement a function to determine if a linked list is a palindrome [2.7 p.78]
    bool l4(Node* head){
        if(head == nullptr){
            return true;
        }
        std::vector<int> values;

        do{
            values.emplace_back(head->value);
            head = head->next;
        }
        while(head != nullptr);
    
        auto v_begin = 0;
        auto v_end = values.size() - 1;
        while(v_begin < v_end){
            if(values.at(v_begin) != values.at(v_end)){
                return false;
            }
        }
        return true;
    }
    
    //Implement a function to check if a binary tree is balanced. 
    // For the purposes of this question, 
    // a balanced tree is defined to be a tree such that the heights of the two subtrees 
    // of any node never differ by more than one. [4.1 p.86]
    bool l5(Tree* root){ // btree struct is decleared in the end of this file
        if (root == NULL)
            return true;
    
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        
        if (abs(leftHeight - rightHeight) <= 1 && l5(root->left) && l5(root->right))
            return true;
        
        return false;
    }

    int height(Tree* root) {
        if (root == NULL){
            return 0;
        }
        return 1 + std::max(height(root->left), height(root->right));
    }
};

// setting up for linked list
struct Node{
    int value;
    struct Node* next;
};

// setting up for binary tree
struct Tree{
    int value;
    Tree *left;
    Tree *right;
};