#include "doctest.h"
#include "sources/OrgChart.hpp"
#include "string"
using namespace ariel;
using namespace std;

TEST_CASE ("Case 2 Football Team")
{
    //checking string
    OrgChart<string> organization;
            CHECK_NOTHROW(organization.add_root("CEO"));
            CHECK_NOTHROW(organization.add_sub("CEO" , "CTO"));//Owner was replaced
            CHECK_NOTHROW(organization.add_sub("CEO" , "CFO"));//no such value
            CHECK_NOTHROW(organization.add_sub("CEO" , "COO"));
            CHECK_NOTHROW(organization.add_sub("CTO" , "SUB_CTO_1"));
            CHECK_NOTHROW(organization.add_sub("CTO" , "SUB_CTO_2"));
            CHECK_NOTHROW(organization.add_sub("COO" , "SUB_COO_1"));
            CHECK_NOTHROW(organization.add_sub("COO" , "SUB_COO_2"));
            CHECK_NOTHROW(organization.add_sub("CFO" , "SUB_CFO_1"));
            CHECK_NOTHROW(organization.add_sub("CFO" , "SUB_CFO_2"));
            CHECK_NOTHROW(organization.add_sub("SUB_CTO_1" , "EMPLOYEE"));
            CHECK_NOTHROW(organization.add_sub("SUB_CFO_1" , "ENGINEER"));

//                                              CEO
//                  CTO                         CFO                                 COO
//        SUB_CTO_1    SUB_CTO_1       SUB_CFO_1    SUB_CFO_1              SUB_COO_1  SUB_COO_1      
//        EMPLOYEE                      ENGINEER


            // test level order
            vector<string> l_order;
            for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
            {
               l_order.push_back(*it);
            }
            CHECK_EQ(l_order.at(0),"CEO");
            CHECK_EQ(l_order.at(1),"CTO");
            CHECK_EQ(l_order.at(2),"CFO");
            CHECK_EQ(l_order.at(3),"COO");
            CHECK_EQ(l_order.at(4),"SUB_CTO_1");
            CHECK_EQ(l_order.at(5),"SUB_CTO_2");
            CHECK_EQ(l_order.at(6),"SUB_CFO_1");
            CHECK_EQ(l_order.at(7),"SUB_CFO_2");
            CHECK_EQ(l_order.at(8),"SUB_COO_1");
            CHECK_EQ(l_order.at(9),"SUB_COO_2");
            CHECK_EQ(l_order.at(10),"EMPLOYEE");
            CHECK_EQ(l_order.at(11),"ENGINEER");
            l_order.clear();

            //add another field and check that it works
            CHECK_NOTHROW(organization.add_sub("EMPLOYEE" , "SUB_EMPLOYEE"));
            CHECK_NOTHROW(organization.add_root("NEW_CEO"));
             cout << organization << endl;
            //check default iterator
            for (auto name:organization)
            {
                l_order.push_back(name);
            }
            CHECK_EQ(l_order.at(0),"NEW_CEO");
            CHECK_EQ(l_order.at(1),"CTO");
            CHECK_EQ(l_order.at(2),"CFO");
            CHECK_EQ(l_order.at(3),"COO");
            CHECK_EQ(l_order.at(4),"SUB_CTO_1");
            CHECK_EQ(l_order.at(5),"SUB_CTO_2");
            CHECK_EQ(l_order.at(6),"SUB_CFO_1");
            CHECK_EQ(l_order.at(7),"SUB_CFO_2");
            CHECK_EQ(l_order.at(8),"SUB_COO_1");
            CHECK_EQ(l_order.at(9),"SUB_COO_2");
            CHECK_EQ(l_order.at(10),"EMPLOYEE");
            CHECK_EQ(l_order.at(11),"ENGINEER");
            CHECK_EQ(l_order.at(12),"SUB_EMPLOYEE");
            l_order.clear();

            // test reverse level order
            vector<string> r_order;
            for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
            {
                r_order.push_back(*it);
            }
            CHECK_EQ(r_order.at(0),"SUB_EMPLOYEE");
            CHECK_EQ(r_order.at(1),"EMPLOYEE");
            CHECK_EQ(r_order.at(2),"ENGINEER");
            CHECK_EQ(r_order.at(3),"SUB_CTO_1");
            CHECK_EQ(r_order.at(4),"SUB_CTO_2");
            CHECK_EQ(r_order.at(5),"SUB_CFO_1");
            CHECK_EQ(r_order.at(6),"SUB_CFO_2");
            CHECK_EQ(r_order.at(7),"SUB_COO_1");
            CHECK_EQ(r_order.at(8),"SUB_COO_2");
            CHECK_EQ(r_order.at(9),"CTO");
            CHECK_EQ(r_order.at(10),"CFO");
            CHECK_EQ(r_order.at(11),"COO");
            CHECK_EQ(r_order.at(12),"NEW_CEO");

            // Change root check that still works
            

            //test preorder
            vector<string> pre_order;
            for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
            {
                pre_order.push_back(*it);
            }
            CHECK_EQ(pre_order.at(0),"NEW_CEO");
            CHECK_EQ(pre_order.at(1),"CTO");
            CHECK_EQ(pre_order.at(2),"SUB_CTO_1");
            CHECK_EQ(pre_order.at(3),"EMPLOYEE");
            CHECK_EQ(pre_order.at(4),"SUB_EMPLOYEE");
            CHECK_EQ(pre_order.at(5),"SUB_CTO_2");
            CHECK_EQ(pre_order.at(6),"CFO");
            CHECK_EQ(pre_order.at(7),"SUB_CFO_1");
            CHECK_EQ(pre_order.at(8),"ENGINEER");
            CHECK_EQ(pre_order.at(9),"SUB_CFO_2");
            CHECK_EQ(pre_order.at(10),"COO");
            CHECK_EQ(pre_order.at(11),"SUB_COO_1");
            CHECK_EQ(pre_order.at(12),"SUB_COO_2");

}

TEST_CASE ("Case 2 CS Depatrment")
{
    //create object person for this test
    class Person {
    public:
        string name;
        int age;

        Person(string name, int age) : name(name), age(age) {}

        bool operator==(Person &p) {
            return this->name == p.name;
        }
    };
    //instantiate People
    Person Head_Of_Department("Boaz", 50);
    Person Course_manager_algo("Elad", 45);
    Person Course_manager_CPP("Erel", 47);
    Person Lecturer_Algo("Roee", 38);
    Person Lecturer_CPP("Mor", 39);
    Person Excerciser_Algo("Edut", 22);
    Person Excerciser_CPP("Tal", 23);

    OrgChart<Person> Depatrment;
            CHECK_NOTHROW(Depatrment.add_root(Head_Of_Department));
            CHECK_NOTHROW(Depatrment.add_sub(Head_Of_Department, Course_manager_algo));
            CHECK_NOTHROW(Depatrment.add_sub(Head_Of_Department, Course_manager_CPP));
            CHECK_NOTHROW(Depatrment.add_sub(Course_manager_CPP, Lecturer_CPP));
            CHECK_NOTHROW(Depatrment.add_sub(Course_manager_algo, Lecturer_Algo));
            CHECK_NOTHROW(Depatrment.add_sub(Lecturer_Algo, Excerciser_Algo));
            CHECK_NOTHROW(Depatrment.add_sub(Lecturer_CPP, Excerciser_CPP));

    // test level order
    vector<Person> lvl_order;
    for (auto it = Depatrment.begin_level_order(); it != Depatrment.end_level_order(); ++it) {
        lvl_order.push_back(*it);
    }
            CHECK_EQ(lvl_order.at(0).name, Head_Of_Department.name);
            CHECK_EQ(lvl_order.at(1).name, Course_manager_algo.name);
            CHECK_EQ(lvl_order.at(2).name, Course_manager_CPP.name);
            CHECK_EQ(lvl_order.at(3).name, Lecturer_Algo.name);
            CHECK_EQ(lvl_order.at(4).name, Lecturer_CPP.name);
            CHECK_EQ(lvl_order.at(5).name, Excerciser_Algo.name);
            CHECK_EQ(lvl_order.at(6).name, Excerciser_CPP.name);


    lvl_order.clear();
    //add another field and check that it works
    Person Excerciser_Algo2("Nir", 25);
            CHECK_NOTHROW(Depatrment.add_sub(Lecturer_Algo, Excerciser_Algo2));
    // Change root check that still works
    Person New_H_O_D("Yossi", 60);
            CHECK_NOTHROW(Depatrment.add_root(New_H_O_D));

    //check default iterator
    for (auto person: Depatrment) {
        lvl_order.push_back(person);
    }
            CHECK_EQ(lvl_order.at(0).name, New_H_O_D.name);
            CHECK_EQ(lvl_order.at(1).name, Course_manager_algo.name);
            CHECK_EQ(lvl_order.at(2).name, Course_manager_CPP.name);
            CHECK_EQ(lvl_order.at(3).name, Lecturer_Algo.name);
            CHECK_EQ(lvl_order.at(4).name, Lecturer_CPP.name);
            CHECK_EQ(lvl_order.at(5).name, Excerciser_Algo.name);
            CHECK_EQ(lvl_order.at(7).name, Excerciser_CPP.name);
            CHECK_EQ(lvl_order.at(6).name, Excerciser_Algo2.name);



    // test reverse level order
    vector<Person> r_order;
    for (auto it = Depatrment.begin_reverse_order(); it != Depatrment.reverse_order(); ++it) {
        r_order.push_back(*it);
    }
            CHECK_EQ(r_order.at(0).name, Excerciser_Algo.name);
            CHECK_EQ(r_order.at(1).name, Excerciser_Algo2.name);
            CHECK_EQ(r_order.at(2).name, Excerciser_CPP.name);
            CHECK_EQ(r_order.at(3).name, Lecturer_Algo.name);
            CHECK_EQ(r_order.at(4).name, Lecturer_CPP.name);
            CHECK_EQ(r_order.at(5).name, Course_manager_algo.name);
            CHECK_EQ(r_order.at(6).name, Course_manager_CPP.name);
            CHECK_EQ(r_order.at(7).name, New_H_O_D.name);




    //test preorder
    vector<Person> pre_order;
    for (auto it = Depatrment.begin_preorder(); it != Depatrment.end_preorder(); ++it) {
        pre_order.push_back(*it);
    }
            CHECK_EQ(pre_order.at(0).name, New_H_O_D.name);
            CHECK_EQ(pre_order.at(1).name, Course_manager_algo.name);
            CHECK_EQ(pre_order.at(2).name, Lecturer_Algo.name);
            CHECK_EQ(pre_order.at(3).name, Excerciser_Algo.name);
            CHECK_EQ(pre_order.at(4).name, Excerciser_Algo2.name);
            CHECK_EQ(pre_order.at(5).name, Course_manager_CPP.name);
            CHECK_EQ(pre_order.at(6).name, Lecturer_CPP.name);
            CHECK_EQ(pre_order.at(7).name, Excerciser_CPP.name);


}


TEST_CASE("Utilities"){

       OrgChart organization;
       //Adding sub when tree is empty
       CHECK_THROWS(organization.add_sub("CEO", "CTO"));

       organization.add_root("CEO")
      .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
      .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
      .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
      .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
      .add_sub("COO", "VP_BI"); 


    //Changing root name
    CHECK_NOTHROW(organization.add_root("NEW_CEO"));
    CHECK(*(organization.begin_level_order()) == "NEW_CEO");

    //Adding sub to root that replaced
    CHECK_THROWS(organization.add_sub("CEO", "CPO")); 

    //Adding sub to non existsing node
    CHECK_THROWS(organization.add_sub("CPO", "CPPO"));
    CHECK_THROWS(organization.add_sub("CLO", "CL"));

      
      //Check for implementation of begin() and end()
      CHECK_NOTHROW(for(auto str: organization));

      //Check arrow operator
      size_t combinedLen = 0;
      for(auto it = organization.begin(); it != organization.end(); ++it){

          combinedLen += it->length();
      }

      CHECK_EQ(combinedLen, 26);

        //Check for empty tree
         OrgChart org;
        CHECK_THROWS(org.begin_preorder());
        CHECK_THROWS(org.end_preorder());
      
}

