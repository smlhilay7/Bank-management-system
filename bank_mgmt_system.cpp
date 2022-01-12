
/* A bank management system made for customers use.
a user can simply create an account, deposit, transfer and withdraw money at any time
using this simple program.
*/

#include <iostream>
#include <stdlib.h>  
#include <iomanip>    // Manipulators
#include <fstream>    // file handling
#include <ctime>      // time() function
#include <cstdlib>    // for using rand() and srand()
 
using namespace std;

// Global variables in order to access them in every function
string USERNAME,PASSWORD,Confirm,receiver="None";
int receiver_acc=0,account_no;
float amount,deposit,withdraw,transaction;
string usr,p;
int acc;
 
void login();
void create_account();
void recent();
void dashboard();
void save_history();
void save_amnt(int,float);
void transfer();

int main(){
    // Signs [+]: asking for input, >>:asking for choice, **....**: for message, !!....!!:for errors.
    
    // Main menu
    menu:
        int choice;
        cout<<"\n**********************"<<endl;
        cout<<"       Main Menu"<<endl;
        cout<<"**********************"<<endl;
        cout<<"1. Login"<<endl;
        cout<<"2. Create an account"<<endl;
        cout<<"3. Recent activities"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"**********************"<<endl;
        cout<<">> ";
        cin>>choice;
        
        switch(choice){
            case 1:
                login();      // function call 
                break;
            case 2:
                create_account();
                break;
            case 3:
                recent();
                break;
            case 4:
                cout<<"**  GOOD BYE!  **"<<endl;
                exit(1);        //used to exit from the program or terminate the program
                break;
            default:
                cout<<"!! Invalid choice !!"<<endl;
                goto menu;
        }    
    return 0;
}



void login(){
    //function for checking if the specified username and password are correct 
    // then takes the user to the dashbored
    string username,password,usr;
    float am;
    cout<<"\n[+] Username:  ";
    cin>>username;
    cout<<"[+] Password:  ";
    cin>>password;

    ifstream file("data.txt");
    while(!file.eof()){
        file>>USERNAME>>PASSWORD>>account_no;

        if(username == USERNAME && password == PASSWORD){
            cout<<"**  Logged in successfully!  **"<<endl;
            ifstream file("amnt.txt");
            while(!file.eof()){
                file>>acc>>am;
                if(acc == account_no){
                    amount = am;
                }
            }            
            dashboard();
            break;
    }
        else{
            cout<<"!! Access denied !!"<<endl;
            continue;
            }
    }
    login();
}

void create_account(){
    // Function to create a new account for new customers
    cout<<"\n**  You have to provide some information in order to create an account.  **"<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;
    cout<<"[+] Username:  ";
    cin>>USERNAME;    
    p:
        cout<<"[+] Password:  "; 
        cin>>PASSWORD;
        cout<<"[+] Confirm Password:  ";
        cin>>Confirm;
        if (PASSWORD == Confirm){
            string usr,p;
            int acc;
            ifstream check_acc("data.txt",ios::in);
            srand((unsigned)time(NULL));
            int test_acc = rand();
            while(!check_acc.eof()){
                check_acc>>usr>>p>>acc;
                if(acc == test_acc){
                    test_acc = rand();
                }
                else{
                    continue;
                }

            }
            check_acc.close();
            account_no = test_acc;

            cout<<"Your account number is "<<account_no<<endl;

            cout<<"\n**  Your account has been created successfully!  **"<<endl;
            cout<<"\n[+] Enter an amount to deposit:  ";
            cin>>deposit;
            amount = 0;
            amount += deposit;

            ofstream save_acc("data.txt",ios::app);
            save_acc<<"\n"<<USERNAME<<" "<<PASSWORD<<" "<<account_no;
            save_acc.close();
            dashboard();
        }
        else{
            cout<<"\n";
            cout<<"!! The password you entered doesn't match !!"<<endl;
            cout<<"**  Please try again.  **"<<endl;
            cout<<"\n"<<endl;
            goto p;
            }
}

void recent(){
    // Function for cheking history
    float w=0,t=0,d=0;
    string u="None",r="None",ac="None",rac="None";

    ifstream file("history.txt");

    cout<<"Customer    Account no.    Withdrawal    Deposit     Transaction    Receiver    Account no."<<endl;
    cout<<"________    ___________    __________    _______     ___________    ________    ___________"<<endl;

    while(!file.eof()){
        file>>u>>ac>>w>>d>>t>>r>>rac;
        cout<<setfill(' ')<<left<<setw(13)<<u;
        cout<<setfill(' ')<<left<<setw(15)<<ac;
        cout<<setfill(' ')<<left<<setw(13)<<w;
        cout<<setfill(' ')<<left<<setw(13)<<d;
        cout<<setfill(' ')<<left<<setw(14)<<t;
        cout<<setfill(' ')<<left<<setw(13)<<r;
        cout<<setfill(' ')<<left<<setw(13)<<rac<<endl;
    }
    file.close();
    main();   //calling the main function
}

void save_history(){
    // Saves history of the customer recent activities
    // the history will saved in history.txt file 
    ofstream file("history.txt",ios::app);
    file<<"\n"<<USERNAME<<" "<<account_no<<" "<<fixed<<setprecision(2)<<withdraw<<" "<<deposit<<" "<<transaction<<" "<<receiver<<" "<<receiver_acc;
    file.close();
    deposit = 0;
    withdraw =0;
    receiver = "None";
    receiver_acc = 0;
    amount = 0;
}

void dashboard(){
    // The dashbored where the customer is able to do tasks
    dash:
        int choice;

        cout<<"\n+++++++++++++++++++++++++++"<<endl;
        cout<<"        Dashboard"<<endl;
        cout<<"+++++++++++++++++++++++++++"<<endl;
        cout<<" 1. Check account balance"<<endl;
        cout<<" 2. Withdraw"<<endl;
        cout<<" 3. Deposit"<<endl;
        cout<<" 4. Transfer"<<endl;
        cout<<" 5. Main menu"<<endl;
        cout<<" 6. Exit"<<endl;
        cout<<"+++++++++++++++++++++++++++"<<endl;
        cout<<">> ";
        cin>>choice;
        
        switch(choice){
            case 1:
                cout<<"--\tAccount No: "<<account_no<<endl;
                cout<<"--\tCurrent Balance: $"<<fixed<<setprecision(2)<<amount<<"\t--"<<endl;
                goto dash;
                break;
                
            case 2:
                cout<<"[+] Enter the amount to withdraw: ";
                cin>>withdraw;
                if ((amount - withdraw) <= 0){
                    cout<<"**  Your balance is insufficient  **"<<endl;
                    cout<<"--\tCurrent Balance: $"<<fixed<<setprecision(2)<<amount<<"\t--"<<endl;
                }
                else{
                    amount -= withdraw;
                    cout<<"--\tCurrent Balance: $"<<fixed<<setprecision(2)<<amount<<"\t--"<<endl;
                }
                goto dash;
                break;
            case 3:
                cout<<"[+] Enter the amount to deposit: ";
                cin>>deposit;
                amount += deposit;
                cout<<"--\tCurrent Balance: $"<<fixed<<setprecision(2)<<amount<<"\t--"<<endl;
                goto dash;
                break;
            case 4:
                transfer();
                goto dash;
                break;
            case 5:
                save_amnt(account_no,amount);
                save_history();
                main();
                break;
            case 6:
                save_amnt(account_no,amount);
                save_history();
                cout<<"**  GOOD BYE!  **"<<endl;
                exit(1); 
                break;
            default:
                cout<<"!! Invalid choice !!"<<endl;
                goto dash;
        }
}

void save_amnt(int acc,float amnt){
    ofstream file("amnt.txt",ios::app);
    file<<"\n"<<acc<<" "<<amnt;
    file.close();
}

void transfer(){
    cout<<"[+] Enter the receiver's account number: ";
    cin>>receiver_acc;
    ifstream file("data.txt",ios::in);

    while(!file.eof()){
        file>>usr>>p>>acc;
        if(receiver_acc == acc){
            cout<<"The receiver is "<<usr<<endl;
            cout<<"[+] Enter the amount to transfer: ";
            cin>>transaction;
            if((amount - transaction) <= 0){
                cout<<"**  Your balance is insufficient  **"<<endl;
                cout<<"--\tCurrent Balance: $"<<fixed<<setprecision(2)<<amount<<"\t--"<<endl;
            }
            else{
                amount -= transaction;
                int acc=receiver_acc;
                int amnt=0;
                receiver = usr;
                ifstream amntfile("amnt.txt",ios::in);
                while(!amntfile.eof()){
                    amntfile>>acc>>amnt;
                }
                save_amnt(acc,amnt+transaction);
                cout<<"--\tCurrent Balance: $"<<fixed<<setprecision(2)<<amount<<"\t--"<<endl;
                dashboard();
            }
        }    
    }
    file.close();
    cout<<"\n\n!! There is no account with account_no "<<receiver_acc<<" !!"<<endl;
}