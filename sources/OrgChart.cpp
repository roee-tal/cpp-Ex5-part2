// #include "OrgChart.hpp"
// using namespace std;
// // #include "Node.cpp"
// namespace ariel{
//         // iterator OrgChart::(Node *ptr):pointer_to_current_node(ptr){}

//         // bool OrgChart::operator==(const iterator&it)const{
//         //         return pointer_to_current_node == it.pointer_to_current_node;
//         //     }
//         // bool OrgChart::operator!=(const iterator&it)const{
//         //         return pointer_to_current_node == it.pointer_to_current_node;
//         //     }
//         // std::string& OrgChart::operator*()const{
//         //         return pointer_to_current_node->data;
//         //     }
//         OrgChart::OrgChart(){ this->head= nullptr;}
//         OrgChart& OrgChart::add_root(const std::string &job){
//             if(head == nullptr){
//                 this->head = new Node(job);
//             }
//             else{
//                 Node *newN = new Node(job);
//                 newN->childs.push_back(head);
//                 head = newN;
//             }
//             return *this;

//         }
//         OrgChart& OrgChart::add_sub(const std::string &bos,const std::string &sub){
//             // Node *dad = find_node(bos);
//             // if(dad == nullptr){
//             //     throw std::runtime_error("The boss name doesn't exist");
//             // }
//             // Node *newN = new Node(bos);
//             // dad->childs.push_back(newN);
//             // return *this;
//             if(head == nullptr){
//                 // return nullptr;
//                 throw std::runtime_error("The boss name doesn't exist");
//             }
//             std::deque<Node*> list_to_find;
//             list_to_find.push_back(head);
//             while(!list_to_find.empty()){
//                 Node *temp = list_to_find.front();
//                 if(temp->data == bos){
//                     Node* newN = new Node(sub);
//                     temp->childs.push_back(newN);
//                     return *this;
//                 }
//                 list_to_find.pop_front();
//                 for(unsigned long i = 0;i<temp->childs.size();i++){
//                     list_to_find.push_back(temp->childs[i]);
//                 }
//             }
//             throw std::runtime_error("The boss name doesn't exist");
//             // return nullptr;
//         }

//         // Node* OrgChart::find_node(const std::string &name){
//         //     if(head == nullptr){
//         //         return nullptr;
//         //         // throw std::runtime_error("The boss name doesn't exist");
//         //     }
//         //     std::deque<Node*> list_to_find;
//         //     list_to_find.push_back(head);
//         //     while(!list_to_find.empty()){
//         //         Node *temp = list_to_find.front();
//         //         if(temp->data == name){
//         //             // Node* newN = new Node(name);
//         //             // temp->childs.push_back(newN);
//         //             // return *this;
//         //             return temp;    
//         //         }
//         //         list_to_find.pop_front();
//         //         for(unsigned long i = 0;i<temp->childs.size();i++){
//         //             list_to_find.push_back(temp->childs[i]);
//         //         }
//         //     }
//         //     return nullptr;
//         // }

//         // void OrgChart::fill_level_order(Node *head){
            
//         //     for(size_t i=0;i<head->childs.size();i++){
//         //         this->traverse.push_back(head->childs[i]->data);
//         //     }
//         //     for(size_t i=0;i<head->childs.size();i++){
//         //         fill_level_order(head->childs[i]);
//         //     }
//         // }

//         // void OrgChart::fill_rev_order(Node *head){
//         //     for(size_t i=head->childs.size();i>0;i--){
//         //         this->traverse.push_front(head->childs[i-1]->data);
//         //     }
//         //     for(size_t i=head->childs.size();i>0;i--){
//         //         fill_rev_order(head->childs[i-1]);
//         //     } 
//         // }

//         // void OrgChart::fill_preorder(Node *head){
//         //      for(size_t i=0;i<head->childs.size();i++){
//         //         this->traverse.push_back(head->childs[i]->data);
//         //         fill_preorder(head->childs[i]);
//         //     }
//         // }
    

//         // deque<string>::iterator OrgChart::begin_level_order(){
//         //     this->traverse.clear();
//         //     this->traverse.push_back(head->data);
//         //     fill_level_order(head);
//         //     return this->traverse.begin();
//         // }
        
//         // deque<string>::iterator OrgChart:: begin_reverse_order(){
//         //     this->traverse.clear();
//         //     this->traverse.push_front(head->data);
//         //     fill_rev_order(head);
//         //     return this->traverse.begin();
//         // }
//         // deque<string>::iterator OrgChart::begin_preorder(){
//         //     this->traverse.clear();
//         //     this->traverse.push_back(head->data);
//         //     fill_preorder(head);
//         //     return this->traverse.begin();
//         // }
//         // deque<string>::iterator OrgChart::end_level_order(){
//         //     return this->traverse.end();
//         // }
//         // deque<string>::iterator OrgChart::reverse_order(){
//         //     return this->traverse.end();
//         // }
//         // deque<string>::iterator OrgChart::end_preorder(){
//         //     return this->traverse.end();
//         // }


//         	// iterator OrgChart::begin(){
// 			// 	return begin_level_order();
// 			// }
// 			// iterator OrgChart:: end(){
// 			// 	return end_level_order();
// 			// }
//         ostream &operator<<(ostream &out, OrgChart &org)
//             {
//             for (auto it=org.begin_preorder(); it!=org.end_preorder(); ++it) {
//                 out << (*it) << " " ;
//                 }
//             return out;
//             }

//         // deque<string>::iterator OrgChart::begin(){
//         //     return begin_level_order();
//         // }
//         // deque<string>::iterator OrgChart::end(){
//         //     return end_level_order();
//         // }
// }