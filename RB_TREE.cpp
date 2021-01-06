#include <iostream>
#include <vector>

using namespace std; 


class Node{
    private:
        
        
    public:
        int value;
        Node* parent = NULL;
        Node* left =  NULL;
        Node* right = NULL;
        bool color = true;


        Node(int value){
            this->value  = value; 
        }
        void insert(int value, Node* nil){
            if (value >= this->value){
                if(this->right != nil){
                    this->right->insert(value, nil);
                    
                }
                else{
                    this->right = (Node*) malloc(sizeof(Node));
                    *(this->right) = Node(value);
                    this->right->parent = this;
                    this->right->left = nil;
                    this->right->right = nil;
                    
                }
                this->right->balance(nil);
            } 
            else{
                if (this->left != nil){
                    this->left->insert(value, nil);
                    
                }
                else{
                    this->left = (Node*)malloc(sizeof(Node));
                    *(this->left) = Node(value);
                    this->left->parent = this;
                    this->left->left = nil;
                    this->left->right = nil;
                }
                this->left->balance(nil);
                
            }
            
        }

        ///Hacer , corregir para nil
        void balance(Node* nil){
            Node* uncle; //left True / right False    
            Node* g = this->parent->parent;
            Node* p = this->parent;
            
            
            
            if(!this->color or !this->parent->color){
                return;
            }
            //rotations
            cout<<"****************************"<<endl;
            //left from parent
            if (this->parent->left == this){
                
                
                if (this->parent->parent->left == this->parent){

                    uncle = this->parent->parent->right;
                    if(! uncle->color){
                        
                        this->parent->parent->shift_right(nil);
                        g->color = true;
                        p->color = false;
                        return;
                        //cout << this->parent->value;

                    }
                }
                else{
                    uncle = this->parent->parent->left;
                    if(! uncle->color){
                        this->parent->shift_right(nil);
                        this->parent->color =true;
                        this->color = false;
                        this->parent->shift_left(nil);
                        return;
                    }
                }
            }
            //right from parent
            else{
                if (this->parent->parent->left == this->parent){
                    uncle = this->parent->parent->right;
                    if(! uncle->color){
                        this->parent->shift_left(nil);
                        this->parent->color =true;
                        this->color = false;
                        this->parent->shift_right(nil);
                        return;
                    }
                }
                else{
                    uncle = this->parent->parent->left;
                    if(! uncle->color){
                        
                        this->parent->parent->shift_left(nil);
                        g->color = true;
                        p->color = false;
                        return;
                    }
                }
            }

            //color
                                    
            if(p->color and uncle->color){
                g->color = true;
                p->color = false;
                uncle->color = false;    
                return;
            }
            
            
            
                
            return;
            
        }
        
        void shift_left(Node* nil){
            this->right->parent = this->parent;
            
            if(this->parent->left ==this){
                this->parent->left = this->right;
            }
            else{
                this->parent->right = this->right;
            }
            
            this->parent = this->right;
            this->right = this->right->left;
            this->right->parent = this;
            this->parent->left = this;
            nil->left =nil;
            nil->right =nil;
            nil->parent = nil;
        }
        void shift_right(Node* nil){
            this->left->parent =  this->parent;
            
            if(this->parent->left == this){
                this->parent->left = this->left;
            }           
            else{
                this->parent->right = this->left;
            }
            this->parent = this->left;
            this->left = this->left->right;
            this->left->parent = this;
            this->parent->right = this;
            
            nil->left = nil;
            nil->right = nil;
            nil->parent = nil;
            
        }
};


class RB_tree{
    private:
        Node* root = NULL;
        Node* nil  =  (Node*) malloc(sizeof(Node));
    public:
        RB_tree(){
            *(this->nil) = Node(0);
            this->nil->color =false;
            this->nil->right =this->nil;
            this->nil->left =this->nil;
            this->nil->parent =this->nil;

            
            this->root = this->nil;
        }
        void insert(int value){
            if(this->root != nil){

                this->root->insert(value, this->nil);
            }
            else{
                this->root = (Node*)malloc(sizeof(Node));
                *(this->root) = Node(value);
                this->root->parent = this->nil;
                this->root->left = this->nil;
                this->root->right = this->nil;
            }
            while(this->root->parent != nil){
                this->root =this->root->parent;
            }
            this->root->color = false;
        }
        void inlevel(void){
            if (this->root != nil){
                vector<Node> nodes, next;
                nodes.push_back(*(this->root));
                while(nodes.size() > 0){
                    for(int i = 0; i < nodes.size(); i++){
                        if(nodes.at(i).left != nil){
                            next.push_back(*(nodes.at(i).left));
                        }
                        if(nodes.at(i).right != nil){
                            next.push_back(*(nodes.at(i).right));
                        }
                        cout << nodes.at(i).value << "-" << nodes.at(i).color << "  ";
                    }
                    cout << endl;
                    nodes = next;
                    next.clear();
                }


                
            }
        }

        
};


int main(void){
    RB_tree tree = RB_tree();
    tree.insert(8);
    tree.insert(15);
    tree.insert(5);
    tree.insert(12);
    tree.inlevel();
    tree.insert(19);
    tree.insert(23);
    tree.insert(9);
    tree.insert(13);
    tree.insert(10);
    tree.inlevel();
}


