#include "OrgChart.hpp"
#include <stdexcept>
#include <iostream>
using namespace ariel;
using namespace std;

int main(){
    OrgChart org;
    bool first =true;
    cout<<"Hi! Here you can make an OrgChart as you wish\n"
          "Please follow the instructions:\n"
          "First insert the head of the organization:"<<endl;
    while(true){
        if(first){
            cout<<"Please insert head"<<endl;
            string head;
            cin >> head;
            org.add_root(head);
            int choice = -1;
            cout << "Great! now please select:\n";
                    // "0 - for replacing the root\n"
                    // "1 - for add sub (Note:Make sure you insert sub to person who already exist - otherwise - exception\n"
                    // "2 - to continue with the program"<<endl<<endl;
            while(choice != 2){
                cout <<"0 - for replacing the root\n"
                       "1 - for add sub (Note:Make sure you insert sub to person who already exist - otherwise - exception\n"
                       "2 - to continue with the program"<<endl;                
                cin >> choice;
                if(choice == 1){
                    string master;
                    string sub;
                    cout << "Please enter the master first , then the sub"<<endl;
                    cin >> master;
                    cin >> sub;
                    try{
                        org.add_sub(master,sub);
                    }
                    catch(exception& ex){
                        cout << "Please add master that exists in the organization"<<endl;
                    }
                }
                if(choice == 0){
                    cout << "Please enter the new head"<<endl;
                    string master;
                    cin >> master;
                    org.add_root(master);
                }
                if(choice == 2){
                    cout<<"You finished build  the organization!\n"
                    "This is your orgchart"<<endl;
                    cout<<org<<endl;
                    break;
                }
            }
            first = false;
        }
        // cout<<"You finished build  the organization!\n"
        //     "This is your orgchart"<<endl;
        // cout<<org<<endl;
        cout<<"Press 0 to continue"<<endl;
        int con;
        cin >> con;
        cout<<"Now please press:\n"
            "1 - if you want to get all items in chart in levelorder way\n"
            "2 - if you want to get all items in chart in reverse order way\n"
            "3 - if you want to get all items in chart in preorder way\n";
        int pick;
        cin>>pick;
        switch (pick) {
            case 1:
                for (auto element : org)
                { 
                    cout << element << " " ;
                }
                break;
            case 2:
                for (auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it)
                {
                    cout << (*it) << " " ;
                }
                break;
            case 3:
                for (auto it = org.begin_preorder(); it != org.end_preorder(); ++it)
                {
                    cout << (*it) << " " ;
                }
                break;
        }
        cout<<endl;
        int to_break;
        cout << "press 0 to exit, 1 to continue" << endl;
        cin >> to_break;
        if(to_break == 0){
            break;
        }        
    }
    return 0;
    
}