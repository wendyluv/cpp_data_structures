#include <iostream>
#include <vector>

using namespace std; 

//I used as reference for the delete operation the following algorithm (not mine but fair use) in support with the book intro to algorithms 2009, ed.MIT press.
//https://github.com/alenachang/red-black-deletion-steps/blob/master/RedBlackDeletionSteps.pdf


template <typename t>
class Node{
    private:
        
        
    public:
        t value;
        Node* parent = NULL;
        Node* left =  NULL;
        Node* right = NULL;
        bool color = true;


        Node(t value){
            this->value  = value; 
        }
        void insert(t value, Node* nil){
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

template<typename t>
class RB_tree{
    private:
        Node<t>* root = NULL;
        Node<t>* nil  =  (Node<t>*) malloc(sizeof(Node<t>));
        
        
        Node<t>* find(t key){
            Node<t>* node = this->root;
            while(node != nil){
                if (key == node->value){
                    return node;
                }
                else if(key >= node->value){
                    node = node->right;
                }
                else{
                    node = node->left;
                }
            }
            return node;
        }

        Node<t>* min(Node<t>* node){
            while (node->left != nil)
            {
                node = node->left;
            }
            return node;
        }

        //r = replacement , d == deleted
        void replace(Node<t>* d, Node<t>* r){
            
            if(this->root ==  d){
                this->root = r;
            }
            //Determine if d is left or right
            if(d->parent->left == d){
                d->parent->left = r;
            }
            else
            {
                d->parent->right = r;
            }
            
            if(d->right == r){
                r->left = d->left;
                r->left->parent = r;
            }
            else if(d->left == r){
                
            }
            else{
                r->right->parent = r->parent;
                r->parent->left = r->right;
                r->right = d->right;
                r->left = d->left;
                r->right->parent = r;
                r->left->parent = r;
            }
            r->parent = d->parent;
            nil->left = nil;
            nil->right = nil;
            nil->parent = nil;
            free(d); 
            return;
        }

        void fixup(Node<t>* x){
            this->get_case(x);
            nil->left = nil;
            nil->right = nil;
            nil->parent = nil;
            nil->color = false;
        }


        void get_case(Node<t>* x){
            if(x->color){
                this->case_0(x);
                return;
            }
            Node<t>* w = this->get_sibling(x);
            if(w->color){
                this->case_1(x,w);
                return;
            }
            else if(! w->left->color and ! w->right->color){
                this->case_2(x,w);
                return;
            }
            else if((x== x->parent->left and w->left->color and !w->right->color) or (x== x->parent->right and w->right->color and !w->left->color) ){
                this->case_3(x,w);
                return;
            }
            else{
                this->case_4(x,w);
                return;
            }
        }

        Node<t>* get_sibling(Node<t>* x){
            Node<t>* w;
            if (x->parent->left == x){
                w = x->parent->right;
            }
            else{
                w= x->parent->left;
            }
            return w;
        }

        bool is_left_child(Node<t>* x){
            return (x->parent->left == x);
        }


        void case_0(Node<t>* x){
            x->color = false;
            return;
        }
        void case_1(Node<t>* x , Node<t>* w){
            w->color = false;
            x->parent->color =true;
            if(this->is_left_child(x)){
                x->parent->shift_left(x->parent);
            }
            else{
                x->parent->shift_right(x->parent);
            }
            this->get_case(x);
            return;
        }
        void case_2(Node<t>* x, Node<t>* w){
            w->color =true;
            x = x->parent;
            if(x->color){
                x->color =false;
                return;
            }
            this->get_case(x);
            return;

        }
        void case_3(Node<t>* x, Node<t>* w){
            if(this->is_left_child(x)){
                w->left->color = false;
            }
            w->color = true;
            if(this->is_left_child(x)){
                w->shift_right(w);
            }
            else{
                w->shift_left(w);
            }
            w = this->get_sibling(x);
            this->case_4(x,w);
            return;
        }
        void case_4(Node<t>* x, Node<t>* w){
            w->color = x->parent->color;
            x->parent->color = false;
            if(this->is_left_child(x)){
                w->right->color = false;
                x->parent->shift_left(x->parent);
            }
            else{
                w->left->color =false;
                x->parent->shift_right(x->parent);
            }
            return;
        }
        


    
    
    public:
        RB_tree(){
            *(this->nil) = Node<t>(0);
            this->nil->color =false;
            this->nil->right =this->nil;
            this->nil->left =this->nil;
            this->nil->parent =this->nil;
            this->root = this->nil;
        }


        void insert(t value){
            if(this->root != nil){

                this->root->insert(value, this->nil);
            }
            else{
                this->root = (Node<t>*)malloc(sizeof(Node<t>));
                *(this->root) = Node<t>(value);
                this->root->parent = this->nil;
                this->root->left = this->nil;
                this->root->right = this->nil;
            }
            while(this->root->parent != nil){
                this->root =this->root->parent;
            }
            this->root->color = false;
        }




        void delete_node(t key){
            Node<t>* node_to_delete = find(key);
            Node<t>* replacement;
            Node<t>* x;
            if(node_to_delete == nil){
                return;
            }
            
            //1 Determine replacement
            if(node_to_delete->left == nil){
                replacement = node_to_delete->right;
                x  = replacement;
            }
            else if(node_to_delete->right == nil){
                replacement = node_to_delete->left;
                x = replacement; 
            }
            else{
                replacement = this->min(node_to_delete->right);
                x= replacement->right;
            }


            //2 determine fixing needed
            if(node_to_delete->color and (replacement->color or replacement == nil)){
                replace(node_to_delete, replacement);
                return;
            }
            else if(node_to_delete->color and !replacement->color){
                replacement->color = true;
                //proceed to case
            }
            else if(!node_to_delete->color and replacement->color){
                
                replace(node_to_delete, replacement);
                replacement->color = false;

                return;
            }
            else{
                //proceed to case
            }
            
            replace(node_to_delete, replacement);
            this->fixup(x);
            return;
        }

        



        void inlevel(void){
            if (this->root != nil){
                vector<Node<t>> nodes, next;
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
    RB_tree<int> tree = RB_tree<int>();
    tree.insert(13);
    tree.insert(8);
    tree.insert(17);
    tree.insert(1);
    tree.insert(11);
    tree.insert(15);
    tree.insert(25);
    tree.insert(6);
    tree.insert(22);
    tree.insert(27);
    tree.delete_node(4);
    tree.inlevel();   

    RB_tree<float> tree_float= RB_tree<float>();
    tree_float.insert(5.8);
    tree_float.insert(13);
    tree_float.insert(8.8);
    tree_float.insert(17);
    tree_float.insert(1);
    tree_float.insert(11);
    tree_float.insert(15);
    tree_float.insert(25);
    tree_float.insert(6.7);
    tree_float.insert(22.56);
    tree_float.insert(27.02);
    tree_float.delete_node(8.8);
    tree_float.inlevel();


    //tree.inlevel();
    //tree.delete_node(8);
    /*
    tree.insert(19);
    tree.insert(23);
    tree.insert(9);
    tree.insert(13);
    tree.insert(10);
    tree.inlevel();
    */
}


