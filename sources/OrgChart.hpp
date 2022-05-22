#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <deque>
#include <fstream>
#include <sstream>
namespace ariel{
    template <class T> class Iterator;
    template<class T=std::string>
    class OrgChart{
        struct Node{
            T data;
            std::vector<Node*>childs;

            Node(T &data):data(data) {                
            }
        };

        public:
            Node *head;
            std::deque<Node*>to_del;


        OrgChart(){
             this->head= nullptr;
        }

        OrgChart(OrgChart &other);
        // {
        //     this->head = other.head;
        // }
        OrgChart(OrgChart &&other)noexcept;
        // {
        //     this->head = other.head;
        //     other.head = nullptr;
        // }
        OrgChart &operator=(OrgChart other);
        // {
        //     // if(other.head == nullptr){
        //     //     std::cout<<"dsa";
        //     // }
        //     this->head = other.head;
        //     return *this;
        // }
        OrgChart &operator=(OrgChart &&other) noexcept;
        // {
        //     this->head = other.head;
        //     other.head = nullptr;
        //     return *this;
        // }
        ~OrgChart(){
            del_nodes(head);
        }



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

        //Add root - if there is no root - create new node to be the root, else - replace the root 
        OrgChart& add_root(T job){
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


    friend std::ostream &operator<<(std::ostream &out, const OrgChart &org)
    {
        std::deque<OrgChart::Node *> q;
        if (!org.head)
        {
            throw std::out_of_range("OrgChart is empty");
        }
        q.push_back(org.head);
        while (!q.empty())
        {
            size_t len = q.size();
            for (size_t i = 0; i < len; i++)
            {
                OrgChart::Node *tmp = q.front();
                out << tmp->data << "   ";
                if (!tmp->childs.empty())
                {
                    for (OrgChart::Node *child : tmp->childs)
                    {
                        q.push_back(child);
                    }
                }
                q.pop_front();
            }
            out << "\n";
        }

        return out;
    }

        

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
