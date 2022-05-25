#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <deque>
#include <fstream>
#include <sstream>
namespace ariel{
    template<class T=std::string>

    class OrgChart{
                        /*----------Node-----------*/

        struct Node{
            T data;
            std::vector<Node*>childs;

            Node(T &data):data(data) {                
            }
        };
                        /*-----OrgChart operations-----*/
        
        Node *head;
        std::deque<Node*>to_del;

        //Destructor - first fill the deque to delete - then delete each node
        void del_nodes(Node *head){
            this->to_del.push_back(head);
            fill_to_del(head);		 

        for(unsigned int i=0;i<to_del.size();i++){
            delete to_del.at(i);
        }
    }

        void fill_to_del(Node* head){
            if(head!=nullptr){
             for(size_t i=0;i<head->childs.size();i++){
                this->to_del.push_back(head->childs[i]);
                fill_to_del(head->childs[i]);
            }
        }
    }

        static std::string print( Node *node, std::string space,bool first) {
            std::string s;
            if(first){
                s+="root: ";
            }
            s+= space + "$ " + node->data +"\n";
            if(first){
                space+="         ";
            }
            else{
                space+="   ";
            }
            for (size_t i = 0; i < node->childs.size(); i++) {
                s+=print(node->childs[i],space,false);
            }
            return s;
        }

       void empty_word(T word){
            if(word == ""){
                throw std::runtime_error("The cannot enter empty name");
            }
        }

    public:

        OrgChart(){
             this->head= nullptr;
        }
        //copy constructor
        OrgChart(OrgChart &other)
        {
            this->head = other.head;
        }
        
        //Move constructor - copy the object and nulling out the pointer to the temporary data
        OrgChart(OrgChart &&other)noexcept
        {
            this->head = other.head;
            other.head = nullptr;
        }

        //Copy assigment operator - create a new object from an existing one by initialization
        OrgChart &operator=(OrgChart other)
        {
        if (other != this)
        {
            this->head = other.head;
        }

        return *this;
        }

        OrgChart &operator=(OrgChart &&other) noexcept
        {
        if (other != this){
            this->head = other.head;
            other.head = nullptr;
            return *this;
            }
        }

        //Destructor
        ~OrgChart(){
            del_nodes(head);
        }



        //Add root - if there is no root - create new node to be the root, else - replace the root 
        OrgChart& add_root(T job){
            empty_word(job); //Check no empty root name
            if(head == nullptr){
                this->head = new Node(job);
            }
            else{
                this->head->data = job;
            }
            return *this;

        }

        // Add sub - Insert each node to deque and check if the bos name is equal to the curr node
        // If isnt exist - exception
        OrgChart & add_sub(T bos,T sub){
            empty_word(sub);//Check no empty sub name
            if(head == nullptr){
                throw std::runtime_error("The boss name doesn't exist");
            }
            std::deque<Node*> list_to_find;
            list_to_find.push_back(head); // Push the root
            while(!list_to_find.empty()){
                Node *temp = list_to_find.front(); //Check if the curr node is the chosen one
                if(temp->data == bos){
                    Node* newN = new Node(sub);
                    temp->childs.push_back(newN);
                    return *this;
                }
                for(unsigned long i = 0;i<temp->childs.size();i++){
                    list_to_find.push_back(temp->childs[i]);
                }
                list_to_find.pop_front(); // Pop the curr node
            }
            throw std::runtime_error("The boss name doesn't exist"); //If bos name doesnt exist
        }

 

        friend std::ostream &operator<<(std::ostream &output, const OrgChart &org) {
            output<<print(org.head, "",true);
            return output;
        }



                    /*------Iterator inner class-------*/

		class iterator{
            //L - level order
            //R - reverse order
            //P -preorder

			Node *curr;
			std::deque<Node*> traverse2;
            std::deque<Node*> traverse_help;
		public:

            // Constructor - the iterator gets also char (flag) to know what order we need to iterate over the nodes
			iterator(Node* ptr,const char& c)
			{
				this->curr = ptr;
				
				if(c == 'L'){
					if (ptr != nullptr) {
                    	this->traverse2.push_back(ptr);
                }
					fill_level_order(ptr,0);
				}
				else if(c == 'R'){
					if (ptr != nullptr) {
                    	this->traverse2.push_front(ptr);
                }
					fill_rev_order(ptr,0);
					curr = traverse2[0]; // So we dont start from the head (that last)
				}
				else if(c == 'P'){
                    if (ptr != nullptr) {
                    	this->traverse2.push_back(ptr);
                }
					fill_preorder(ptr);
				}
                
				this->traverse2.push_back(nullptr); // Null in the end of the iterator
			}

        // Use recursion to fill the iterator in level order
		void fill_level_order(Node *head,unsigned int index){
            if(head==nullptr){
               throw std::runtime_error("The boss name doesn't exist");
            }
            // If there is no place to move on
            if((index)== (traverse2.size()-1) && (traverse2.at(index)->childs.empty())){
                return;
            }
            index++;
            for(size_t i=0;i<head->childs.size();++i){
                this->traverse2.push_back(head->childs.at(i));
            }
            fill_level_order(traverse2.at(index),index);
        // }
        }

        // Fill reverse iterative
		 void fill_rev_order(Node *head, unsigned int index){
            if(head==nullptr){
               throw std::runtime_error("The boss name doesn't exist");
            }
            traverse_help.push_back(head);
            while(!traverse_help.empty()){
                Node *temp = traverse_help.front();
                for(size_t i=temp->childs.size();i>0;i--){
                    traverse_help.push_back(temp->childs[i-1]);
                }
                for(size_t i=temp->childs.size();i>0;i--){
                    traverse2.push_front(temp->childs[i-1]);
                }
                traverse_help.pop_front();
            }
            
        }
                
        // Use recursion for preorder
		void fill_preorder(Node *head){
        if(head!=nullptr){
             for(size_t i=0;i<head->childs.size();i++){
                this->traverse2.push_back(head->childs[i]);
                fill_preorder(head->childs[i]);
            }
        }
        if(head==nullptr){
               throw std::runtime_error("The boss name doesn't exist");
            }
         }
         
		bool operator==(const iterator&it)const{
                return this->curr == it.curr;
            }

        // Use the prev func
        bool operator!=(const iterator&it)const{
                return !(*this==it);
            }
        
        // * operator to return the value of the node 
        T& operator*()const{
                return curr->data;
        }

        // * operator to return the address value of the node 
		T* operator->() const {
                return &(curr->data);
        }

        //++i
		iterator &operator++() {
            if (!traverse2.empty()) {
                traverse2.erase(traverse2.begin());
                curr = traverse2.front();
            }
            return *this;
        }

        //i++
        iterator operator++(int) {
            iterator t = *this;
            ++*this;
            return t;
            }
		};

                    /*---Done iterator class - begin the iterator---*/

			iterator begin_level_order(){
				return iterator{head,'L'};
			}
			iterator end_level_order(){
                 return end_it();
			}
			iterator begin_reverse_order(){
				return iterator{head,'R'};
			}
			iterator reverse_order(){
                 return end_it();
			}
            iterator begin_preorder(){
				return iterator{head,'P'};
			}
            iterator end_preorder(){
                return end_it();
			}

            //Help function for all 'end' iterators
            iterator end_it(){
                 if (this->head == nullptr) {
                        throw std::runtime_error("Chart is empty!");
                    }
                return iterator{nullptr,'K'};
            }
            
            //forecach style
			iterator begin(){
				return begin_level_order();
			}
			 iterator end(){
				return end_level_order();
			}
    };
}
