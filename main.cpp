#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

// global variables

int numOfAcc = 0;
bool gameOver = false;

struct CurrentAcc // this stuct holds all information related to accounts
{

    string accType; // basic and advanced
    int sortCode = 886804; // same for each account
    int accNo; // random 8 digit number
    string accHolder;
    string monthOpen;
    string yearOpen;
    string password;
    char status; // Active, inactive, dormant, suspended, under investigation
    double initDeposit; // $10 minimum
    double availBalance;
    double latestTxn;
    char overdraftStatus;
    double overdraftLimit;

};

// prototypes

int menu();
int randomNum();
string getMonth();
string getYear();
void printRecord(CurrentAcc);
void storeRecord(CurrentAcc[],CurrentAcc);
void newAccount(CurrentAcc[],CurrentAcc);

void withdraw(CurrentAcc[]);
void deposit(CurrentAcc[]);

void writeRecord(CurrentAcc[]); // to file
void readRecord(CurrentAcc[]); // to file

void logout();

// functions

string getYear()
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t); // tm structure pointing to local time, passed t

    int y = (timePtr->tm_year)+1900; // retrieves current year, adding the century

    string year = to_string(y); // converts year integer to string
    return year;
}
string getMonth()
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);

    string month;
    int m = (timePtr->tm_mon)+1; // returns month in integer form, if statements convert number to date

    if (m ==1)
    {
        month = "January";
    }
    else if(m ==2)
    {
        month = "February";
    }
    else if(m ==3)
    {
        month = "March";
    }
    else if(m ==4)
    {
        month = "April";
    }
    else if(m ==5)
    {
        month = "May";
    }
    else if(m ==6)
    {
        month = "June";
    }
    else if(m ==7)
    {
        month = "July";
    }
    else if(m ==8)
    {
        month = "August";
    }
    else if(m ==9)
    {
        month = "September";
    }
    else if(m ==10)
    {
        month = "October";
    }
    else if(m ==11)
    {
        month = "November";
    }
    else if(m ==12)
    {
        month = "December";
    }

    return month;



}

int randomNum() // generates random number
{
    srand((int)time(0));
    int number;
    number = rand() % 100001;
    number *= number;
    return number;
}

void newAccount(CurrentAcc account, CurrentAcc aa[])
{

    system("CLS"); // clears screen

    short int deposit; // short integer to hold deposit amount
    string fName, sName; // strings to hold first and second names

    cout << "\n\t::::Welcome to Account Creation!::::\n";
    cout << "\nWould you like to open a basic or advanced account?: \t";
    cin >> account.accType; // stores to struct variable Basic or Advanced
    account.accNo = randomNum(); // returns random 8 digit number
    cout << "\nWhat is the account holders name?: \t";
    cin >> fName >> sName; // first and second namd stored as strings
    account.accHolder = fName + " " + sName; // assigns variable from strings
    account.monthOpen = getMonth(); // gets month
    account.yearOpen = getYear(); // gets year
    account.status = 'A';

    // work on this                                     !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    cout << "Enter Your new password:\t";
        cin >> account.password;
    cout << "Please re-enter your password";
        string tempPass;
        cin >> tempPass;

    if (tempPass == account.password)
    {
        cout << "Passwords verified";
    } else {
    // work on this                                     !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }


    cout << "\nPlease make an initial deposit of more than 10: \t";
    cin >> deposit;

    if (deposit < 10)
    {
        cin.clear();
        cin.ignore();
        cout << "\nPlease make an initial deposit of more than 10: \t";
        cin >> deposit;
    }

    account.availBalance += deposit;

    storeRecord(aa,account);
    writeRecord(aa);
    system("CLS");





}


void storeRecord(CurrentAcc a[], CurrentAcc acc) // places information held by account into array
{
    a[numOfAcc] = acc; // index of array is equal to the account passed
    numOfAcc++; // increment number of accounts

}

void printRecord(CurrentAcc a[])
{

    system("CLS");
    cout << "\n";
    cout << "======================================";
    cout << "\n\tAll accounts\n";
    cout << "======================================\n";

    for (int i = 0; i < numOfAcc; i++)
    {
        cout <<"Account Holder:\t" << a[i].accHolder << "\n";
        cout <<"Account Type:\t" << a[i].accType << "\n";
        cout <<"Account Number:\t" << a[i].accNo << "\n";
        cout <<"Account Sort Code:" << a[i].sortCode << "\n";
        cout <<"Month Opened:\t" << a[i].monthOpen << "\n";
        cout <<"Year Opened:\t" << a[i].yearOpen << "\n";
        cout <<"Account Status:\t" << a[i].status << "\n";
        cout <<"Account Balance:" << a[i].availBalance << "\n";
        cout << "\n";


    }
    cout << "======================================\n";
    cout << "======================================\n";

    system("PAUSE");
    system("CLS");

}

void writeRecord(CurrentAcc a[]) // to file
{
    ofstream fout; // output stream
    fout.open("data.txt", ios::app); // ios out replaces all info in document, app (append) to += info
    if (fout.fail())
    {
        cout << "\nERROR opening file";
    }
    else
    {

        for (int i = 0; i < numOfAcc; i++)
        {
            fout <<"Account Type:\t" << a[i].accType << "\n";
            fout <<"Account Number:\t" << a[i].accNo << "\n";
            fout <<"Account Holder:\t" << a[i].accHolder << "\n";
            fout <<"Month Opened:\t" << a[i].monthOpen << "\n";
            fout <<"Year Opened:\t" << a[i].yearOpen << "\n";
            fout <<"Account Status:\t" << a[i].status << "\n\n";

        }

    }
}

void readRecord(CurrentAcc a[]) // to file
{
    ifstream fin ("data.txt"); //input stream
    if(fin.fail())
    {
        cout << "\n Error opening file!";
    }
    else
    {
        string fileContents; // string to hold imported file info
        while(fin)
        {

            getline(fin,a[0].accType);
            cout << a[0].accType << endl;

        }

    }


}


void withdraw(CurrentAcc a[])
{
    system("CLS");

    int number;
    short int accnum;
    double withNum;
    cout << "What is your account number?: \t";
    cin >> number;

    for(int i = 0; i < numOfAcc; i++)
    {
        if (number == a[i].accNo)
        {
            cout << "\nAccount found!\n\n";
            accnum = i;

            cout <<"Account Holder:\t" << a[accnum].accHolder << "\n";
            cout <<"Account Type:\t" << a[accnum].accType << "\n";
            cout <<"Account Number:\t" << a[accnum].accNo << "\n";
            cout <<"Account Sort Code:" << a[accnum].sortCode << "\n";
            cout <<"Month Opened:\t" << a[accnum].monthOpen << "\n";
            cout <<"Year Opened:\t" << a[accnum].yearOpen << "\n";
            cout <<"Account Status:\t" << a[accnum].status << "\n";
            cout <<"Account Balance:" << a[accnum].availBalance << "\n";
            cout << "\n";
        }
    }

    cout << "Your available balance is: \t" << a[accnum].availBalance;
    cout << "\n How much would you like to withdraw?: \t";
    cin >> withNum;

    double checkNum = a[accnum].availBalance - withNum;

    if (checkNum < 0)
    {
        cout << "\nInsufficient funds!\n";

    }
    else
    {

        cout << "\nYour withdrawal of " << withNum << " has been successful\n";
        a[accnum].availBalance -= withNum;
        system("PAUSE");

    }



    system("CLS");
}

void deposit(CurrentAcc a[])
{
    system("CLS");

    int number;
    short int accnum;
    double depNum;
    cout << "What is your account number?: \t";
    cin >> number;

    for(int i = 0; i < numOfAcc; i++)
    {
        if (number == a[i].accNo)
        {
            cout << "\nAccount found!\n\n";
            accnum = i;

            cout <<"Account Holder:\t" << a[accnum].accHolder << "\n";
            cout <<"Account Type:\t" << a[accnum].accType << "\n";
            cout <<"Account Number:\t" << a[accnum].accNo << "\n";
            cout <<"Account Sort Code:" << a[accnum].sortCode << "\n";
            cout <<"Month Opened:\t" << a[accnum].monthOpen << "\n";
            cout <<"Year Opened:\t" << a[accnum].yearOpen << "\n";
            cout <<"Account Status:\t" << a[accnum].status << "\n";
            cout <<"Account Balance:" << a[accnum].availBalance << "\n";
            cout << "\n";
        }
    }

    cout << "Your available balance is: \t" << a[accnum].availBalance;
    cout << "\nHow much would you like to deposit: \t";
    cin >> depNum;

    a[accnum].availBalance += depNum;

    cout << "\nYour deposit of " << depNum  << " was successful\n\n";


    system("PAUSE");
    system("CLS");

}
void logout()
{
    cout << "\n\nLogging out...\n";
    cout << "see you next time!\n\n";
    gameOver = true;
}
int menu()
{

    short int choice;

    CurrentAcc account;
    CurrentAcc aa[10];


    while (gameOver == false)
    {
        //system("CLS");
        cout << "\t::::Welcome to Hogan Banking!::::\n\n";
        cout << "\tSelect from the menu below\n";
        cout << "\t-==========================-\n";
        cout <<"\t1: Create a new account\n";
        cout <<"\t2: View current account holders\n";
        cout <<"\t3: Withdraw\n";
        cout <<"\t4: Deposit\n";
        cout <<"\t5: Account Balance\n";
        cout <<"\t6: Logout\n";
        cout << "\t-==========================-\n";
        cout << "\tEnter your choice: \t";
        cin >> choice;

        if(cin.fail())
        {
            system("CLS"); // clears console
            cin.clear(); // clears error flags
            cin.ignore(); // ignores last character in stream
            cout << "\t-=======================================-";
            cout << "\n\t Please choose a number between 1 - 6";
            cout << "\n\t-=======================================-\n\n";
        }

        switch(choice)
        {
        case 1:
            newAccount(account, aa);
            break;
        case 2:
            printRecord(aa);

            break;
        case 3:
            withdraw(aa);

            break;
        case 4:
            deposit(aa);

            break;
        case 5:

            break;
        case 6:
            logout();

            break;
        }


    }
    return 0;
}


int main()
{
    menu();






}
