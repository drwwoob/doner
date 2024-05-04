// coded in c++ 
#include <string>
#include <__algorithm/max.h>
#include <set>

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

    // wait I thought i have to do all of 'em haha ;)

    //Design an algorithm to find the kth number such that the only prime factors are 3, 5, and 7. [7.7 p.102]
    int m1(int k){
        // as we all know, 3 < 5 < 7
        // for the prime factors with only 3, 5 and 7
        // it turns into 3^x, 5^y, 7^z
        // but how do i determine if 3^x is bigger or 5^y is bigger(
        // first, I think x + y + z <= k, x <= k, y <= k, z <= k
        // eh, maybe we can make a table?
        //tries|   1 | 2 | 3 | 4 | 5 | 6 | 7 |
        // ------------------------------------
        //  3 |    1 | 0 | 0 | 2 | 1 | 1 | 3
        //  5 |    0 | 1 | 0 | 0 | 1 | 0 | 0
        //  7 |    0 | 0 | 1 | 0 | 0 | 1 | 0
        // well this is endless
        // but this might follows the pattern x + y + z < sqrt(k + 2)? (idk im just guessing)
        // ohh wait maybe limited the number of x + y + z to get it as low as possible? but nah
        //then writing the algorithm in this way

        if(k = 1){
            return 1;
        }

        int x = 3, y = 5, z = 7;
        std::set<int> values;
        values.emplace(1);
        int i = 0;
        while(i++ < k && values.size() < k){
            for(auto element : values){
                values.emplace(element * x);
                values.emplace(element * y);
                values.emplace(element * z);
            }
        }

        return *std::next(values.begin(), k);
    }

    // You are given the source to an application which crashes when it is run. 
    // After running it ten times in a debugger, you find it never crashes in the same place. 
    // The application is single-threaded, and uses only the C standard library. 
    // What programming errors could be causing this crash? How would you test each one?

    // m2
    // According to my own experience (sadly) with using C++ on Doner, I think there is a memory leak,
    // and throughout the loop memory leaks so much that there becomes a out of memory exception.
    // Since it is a runtime bug, it mostly likely could now get debugged by setting breakpoints.
    // What I did when I encounter this is that I first checked all the possible memory leaking part, then
    // seperate the code block by block to find the leaking point.

    // You have two very large binary trees: T1 with millions of nodes,
    // and T2 with hundreds of nodes. Create an algorithm to decide if T2 is a subtree of T1. 
    // A tree T2 is a subtree of T1 if there exists a node n in T1 such that the subtree of n is identical to T2.
    // That is, if you cut off the tree at node n, the two trees would be indentical. [4.8 p. 86]

    bool h1(Tree* T1, Tree* T2){
        if(T1 == nullptr || T2 == nullptr){
            return false;
        }

        // find the equal value
        while(T1->value != T2->value){
            if(T1->value < T2->value){
                T1 = T1->right;
            }
            else{
                T1 = T1->left;
            }
            if(T1 == nullptr){
                return false;
            }
        }

        // see if they have totally identical branches
        return sameTree(T1, T2);
    } 

    bool sameTree(Tree* T1, Tree* T2){
        if(T1 == nullptr || T2 == nullptr) 
            return(T1 == T2);
        return (T1->value == T2->value)
                    &&(sameTree(T1->left, T2->left))
                    &&(sameTree(T1->right, T2->right));
    }

    //Write a method to count the number of 2's that appear in all the number between 0 and n [inclusive]. [18.4 p.167]
    //EXAMPLE:
    //Input: 25
    //Output: 9 [2, 12, 20, 21, 22, 23, 24, and 25] Note that 22 counts for two 2's.

    int h2(std::vector<int> numbers){
        int count = 0;
        int pow = 10;
        for(auto num : numbers){
            auto num_str = std::to_string(num);
            for(auto digit : num_str){
                if(digit == '2'){
                    count++;
                }
            }
        }
        return count;
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