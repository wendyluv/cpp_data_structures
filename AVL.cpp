#include <iostream>
#include <vector>
using namespace std;



class node{
    private:
        int value;

        int balance = 0;
        int height = 0;


    public:
        node* left = NULL;
        node* right = NULL;
        node* parent = NULL;
        node(int value){
            this->value = value;   
        }
        void add_node(int value){
            if(value >= this->value){
                if(this->right){
                    this->right->add_node(value);
                }
                else{
                    this->right = (node*)malloc(sizeof(node));
                    *(this->right) = node(value);
                    this->right->parent = this;
                }
            }
            else{
                if(this->left){
                    this->left->add_node(value);
                }
                else{
                    this->left = (node*)malloc(sizeof(node));
                    *(this->left) = node(value);
                    this->left->parent = this;
                }
            }
            this->calculate_height();
            this->calculate_balance();
            this->balance_tree();
            
            
            
            
        }

        void balance_tree(void){
            int left_height, right_height;
            if (this->balance > 1){
                
                if(this->left->left){
                    left_height = this->left->left->get_height();
                }
                else{
                    left_height = -1;
                }
                if(this->left->right){
                    right_height = this->left->right->get_height();
                }
                else{
                    right_height = -1;
                }
                if(left_height > right_height){
                    this->rotate_right();
                }
                else{
                    this->rotate_left_right();
                }
            }

            else if(this-> balance < -1)
            {
                if(this->right->left){
                    left_height = this->right->left->get_height();
                }
                else{
                    left_height = -1;
                }
                if(this->right->right){
                    right_height = this->right->right->get_height();
                }
                else{
                    right_height = -1;
                }
                
                if(left_height>right_height){
                        this->rotate_right_left();
                }
                else{
                    this->rotate_left();
                }
                
                
            }
            else
            {   
                
            }
        }

        void rotate_right(void){
            if(this->parent){
                this->left->parent = this->parent;
                if (this->parent->left == this){
                    this->parent->left = this->left;
                }
                else{
                    this->parent->right = this->left;
                }     
            }    
            else{
                this->left->parent = NULL;
            }
            

            this->parent = this->left;
            this->left = this->left->right;
            if (this->left){
                this->left->parent = this;   
            }
            this->parent->right = this;



        }
        void rotate_right_left(void){
            this->right->rotate_right();
            this->rotate_left();
        }
        void rotate_left(void){
            this->right->parent = this->parent;
            if(this->parent){
                if(this->parent->left == this){
                    this->parent->left = this->right;
                }
               else{
                    this->parent->right = this->right;
                }
            }
            this->parent = this->right;
            this->right = this->parent->left;
            this->parent->left = this;
            if(this->right){
                this->right->parent = this;
            }
        }
        void rotate_left_right(void){
            this->left->rotate_left();
            this->rotate_right();
        }

        void calculate_height(void){
            int left, right;

            if(this->left){

                left = this->left->get_height();
            }
            else{
                left = -1;
            }

            if(this->right){
                right = this->right->get_height();

            }
            else{
                right = -1;
            }
            if (right> left){
                this->height = right +1;
            }
            else
            {
                this->height = left + 1;
            }
        }

        void calculate_balance(void){

            int left_val;
            if(this->left){ left_val = this->left->get_height();} 
            else{
                left_val = -1;
            }
            
            int right_val;
            if(this->right){
             right_val= this->right->get_height();
            }
            else
            {
                right_val = -1;
            }
            this->balance = left_val -right_val; 
        }
        int get_value(void){
            return this->value;
        }
        int get_height(void){
            return this->height;
        }



};






class AVL{
    private:
        node* root = NULL;

    public:
        AVL(){ 
        }
        void add(int value){
            if(root){
                root->add_node(value);
                while(root->parent){
                    root = root->parent;
                }
            }
            else{
                this->root = (node*)malloc(sizeof(node));
                *(this->root) = node(value);
            }

        }
        node get_root(void){
            return *(this->root);
        }
        void bfs(void){
            if (this->root){
                cout << this->root->get_value() << endl;
                vector<node> nodes;
                vector<node> next;
                nodes.push_back(*(this->root));
                while(nodes.size()>0){
                    for (int i = 0; i< nodes.size(); i++){
                        if(nodes.at(i).left){
                            next.push_back(*(nodes.at(i).left));
                            cout << nodes.at(i).left->get_value() << "  ";
                            }
                        if(nodes.at(i).right){
                            next.push_back(*(nodes.at(i).right));
                            cout << nodes.at(i).right->get_value() << "  ";
                            }  
                    
                    }
                    nodes = next;
                    next.clear();
                    cout << endl;
                }

            }
        }

};

int main(void){
    AVL tree = AVL();
    tree.add(10);
    tree.add(8);
    tree.add(9);
    tree.add(1);
    tree.add(5);
    tree.add(17);
    tree.add(2);
    tree.add(7);
    tree.add(6);
    tree.add(8);
    tree.add(14);
    tree.add(25);
    tree.bfs(); 
}