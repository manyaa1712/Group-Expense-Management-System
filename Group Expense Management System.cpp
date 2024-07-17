#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <string>
#include <array>




using namespace std;

//variables used
// variables used
int number_of_persons;
string group;


string personWhoPaid;
string personWhoTransfered;

float expense;
float eachPersonExpense;
float transferMoney;

void line(int n){
    while(n--) cout<<"-";
}




//group class


class Group{
    string groupName;
    float graph[51][51];    //graph[i][j] means how much person i owes person j
    map<string,int> peopleArr;
    map<string,int> peopleIncludedInExpenseArr;

    public:
    Group(string, map<string, int>);
    int get_Minimum(float array[]);
    int get_Maximum(float array[]);
    float minimum_of_two(float number1, float number2);
    string findNameForIndex(int index);
    void minCashFlowRecursion(float amount[]);
    void minCashFlow();
    void settle();
    void transfer();
    void addExpense();


};

Group::Group(string s, map<string, int> m){
        groupName = s;
        peopleArr = m;

        //SET graph values to 0;
        for (int i = 0; i < number_of_persons; i++)
            for (int j = 0; j < number_of_persons; j++)
                graph[i][j] = 0;
}


int Group::get_Minimum(float array[])
    {
        int min_Index = 0;
        for(int i = 1; i < number_of_persons; i++)
        {
            if(array[i] < array[min_Index])
                min_Index = i;
        }

        //returns the index of the minimum value
        return min_Index;
    }

    //A utility function that returns index of maximum value in array[]
int Group::get_Maximum(float array[])
    {
        int max_Index = 0;
        for(int i = 1; i < number_of_persons; i++)
        {
            if(array[i] > array[max_Index])
                max_Index = i;
        }


        return max_Index;
    }


float Group::minimum_of_two(float number1, float number2)
    {
        if(number1 < number2)
            return number1;
        else
            return number2;
    }


string Group::findNameForIndex(int index)
    {
        for(auto it_type = peopleArr.begin(); it_type != peopleArr.end(); it_type++) {
            if(it_type->second == index)
            {
                return it_type->first;
            }
        }
        return "";
    }

void Group::minCashFlowRecursion(float amount[])
    {


        int maxCredit = get_Maximum(amount), maxDebit = get_Minimum(amount);


        if(amount[maxCredit] <= 0.01 && amount[maxDebit] <= 0.01)
            return;

        float minimum = minimum_of_two(-amount[maxDebit], amount[maxCredit]);
        amount[maxCredit] -= minimum;
        amount[maxDebit] += minimum;


        cout<<findNameForIndex(maxDebit)<<" pays "<<minimum<<" to "<<findNameForIndex(maxCredit)<<"."<<endl;


        minCashFlowRecursion(amount);
    }


void Group::minCashFlow()
    {

        float amount[number_of_persons] = {0};

        for(int p = 0; p < number_of_persons; p++)
        {
            for(int i = 0; i < number_of_persons; i++)
            {
                amount[p] += (graph[i][p] - graph[p][i]);
            }
        }

        minCashFlowRecursion(amount);
    }




void Group::settle()
    {

        line(64);
        cout<<endl<<endl;
        minCashFlow();
        cout<<endl<<endl;
        line(64);
        cout<<endl<<endl;
    }

// method to transfer money in group
void Group::transfer()
    {
        cout << "Who transfered : ";
        cin >> personWhoTransfered;

        string transferedTo;
        cout<<"Transfered to: ";
        cin>>transferedTo;
        cout << "How much transfered : ";
        cin >> transferMoney;

        // set values to the graph
        graph[peopleArr[transferedTo]][peopleArr[personWhoTransfered]] += transferMoney;
    }

    // method to add expense to group
void Group::addExpense()
    {
        cout <<"Enter expense amount to group " << group << " : ";
        cin >> expense;

        do{
            cout << "Who paid : ";
            cin >> personWhoPaid;

            if(peopleArr.find(personWhoPaid)==peopleArr.end()){
                cout<<"\nWrong name entered. Enter again. \n";
            }
        }while(peopleArr.find(personWhoPaid)==peopleArr.end());


        char temp;
        string peop;
        do{
            cout << "Enter the number of people paid for : ";
            cin >> temp;
            if(!isdigit(temp)){
                cout<<"Enter a numeric value.\n";
            }
        }while(!isdigit(temp));
        int n = temp - '0';
        for (int i = 0; i < n; i++) {
             do{
                cout << "Enter " << i+1 << " person : ";
                cin >> peop;
                if(peopleArr.find(peop)==peopleArr.end()){
                    cout<<"Wrong name entered. Enter again.\n\n";
                }
            }while(peopleArr.find(peop)==peopleArr.end());
            peopleIncludedInExpenseArr[peop] = 1;
        }

        eachPersonExpense = expense / peopleIncludedInExpenseArr.size();

        // set values to the graph
        for(auto it_type = peopleIncludedInExpenseArr.begin(); it_type != peopleIncludedInExpenseArr.end(); it_type++) {
            graph[peopleArr[it_type->first]][peopleArr[personWhoPaid]] += eachPersonExpense;
        }
    }




// data structures used


map<string, Group*> groups;



void displayMenu(string group){

    Group *g1 = groups[group];
    int option = 0;
    do {
        cout << "\n\n******** MAIN MENU ********";
        cout << "\n\n 1. Add expense to " << group;
        cout << "\n 2. Transfer in " << group;
        cout << "\n 3. Settle up " << group;
        cout << "\n 4. Exit \n";
        line(64);
        cout << "\nEnter your option : ";
        cin >> option;

        switch (option) {
            case 1:
                g1->addExpense();
                break;

            case 2:
                g1->transfer();
                break;

            case 3:
                g1->settle();
                break;

            default:
                break;
        }

    } while (option != 4);
    cout<<"\n\n\n\n";

}
void formNewGroup(){
    string group;
    do{
        cout<<"Enter name of the group: ";
        cin>>group;

        if(groups.find(group)!=groups.end()){
            cout<<"Group already exists. Enter a new group: ";
        }
    }while(groups.find(group)!=groups.end());

      cout << "Enter the number of people in group " << group << " : ";
      cin >> number_of_persons;

      string name;
      map<string, int> people;
      cout << "Enter the names of people in group " << group<< " : ";
      for (int i = 0; i < number_of_persons; i++) {
            cin >> name;
            people[name] = i;
        }


    Group *g = new Group(group,people);
    groups[group] = g;

    displayMenu(group);
}

void enterOldGroup(){
    if(groups.size()==0){
        cout<<"\n\n\No groups formed. Form a new group first.\n";
        return;
    }

    string name;

    do{
        cout<<"\n\nEnter group name: ";
        cin>>name;
        if(groups.find(name)==groups.end()){
            cout<<"No such group exists. Enter again : ";
        }
    }while(groups.find(name)==groups.end());
    displayMenu(name);
}


void initialDisplayMenu(){
  int choice;
    do{
        line(64);
        cout<<"\n WELCOME TO SPLITTER \n";
        line(64);

        cout<<"\n\n1. Add a new group";
        cout << "\n2. Enter in old group";
        cout<<"\n3. Exit\n";
        line(64);
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice){
            case 1: formNewGroup();
            break;
            case 2: enterOldGroup();
            break;
            default: break;
        }

    }while(choice !=3);
}


int main()
{
    initialDisplayMenu();

    return 0;
}

