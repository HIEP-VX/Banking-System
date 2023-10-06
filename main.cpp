#include<bits/stdc++.h>
using namespace std;

class account{
    private:
        int nAccount;                   // account number
        char name[50];                  // user name
        int deposit;                    // tien gui
        char type;                      // kieu tai khoan
    public:
        void createAccount();           // function to get data from user
        void showAccount() const;       // function to show data on screen
        void modify();                  // function to add new data
        void depositAmount(int);        // function to accept amount and add to balance amount
        void draw(int);                 // function to accept amount and subtract from balance amount
        void report() const;            // function to show data in tabular format
        int returnAccount() const;      // function to return account number
        int returnDeposit() const;      // function to return balance amount
        char returnType() const;        // function to return type of account
};

void account ::createAccount(){
        cout << "\nEnter The account no. : ";
        cin >> nAccount;
        cout << "\nEnter The name of the account holder : ";
        fflush(stdin);
        cin.getline(name, 50);
        cout << "\nEnter Type of the account <C/S>: ";
        cin >> type;
        type = toupper(type);
        cout << "\nEnter The initial amount (>=500 for Saving and >=1000 for current ) : ";
        cin >> deposit;
        cout << "\n\n\tAccount Created..";
}

void account :: showAccount() const{
        cout << "\nAccount No. : " << nAccount
             << "\nAccount Holder Name: " << name
             << "\nType of Account: " << type
             << "\nBalance amount: " << deposit;
}

void account :: modify(){
        cout << "\nAccount No. : " << nAccount;
        cout << "\nModify Account Holder Name : ";
        fflush(stdin);
        cin.getline(name, 50);
        cout << "\nModify Type of Account <C/S>: ";
        cin >> type;
        type = toupper(type);
        cout << "\nModify Balance amount : ";
        cin >> deposit;
}

/**
 * This method is used to deposit money into a bank account, receive 1 integer argument as the amount to be
 * deposited and add this amount to the variable of the account object, helping to update the balance
 * after depositing.
 *
 * @param x the amount to be deposited
 */
void account::depositAmount(int x)
{
    deposit += x;
}

/**
 * The function draw() subtracts the amount of money that the user wants to withdraw from the account
 * balance
 * 
 * @param x the amount of money to be withdrawn
 */
void account::draw(int x)
{
    deposit -= x;
}

void account::report() const
{
    cout << nAccount << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::returnAccount() const
{
    return nAccount;
}

int account::returnDeposit() const
{
    return deposit;
}

char account::returnType() const
{
    return type;
}

//! function declaration

void writeAccount();                // function to write record in binary file
void displayAccount(int);           // function to display account details given by user
void modifyAccount(int);            // function to modify record of file
void deleteAccount(int);            // function to delete record of file
void displayAll();                  // function to display all account details
void depositWithdraw(int, int);     // function to desposit/withdraw amount for given account
void intro();                       // introductory screen function

int main(){
    char ch;
    int num;
    intro();
    do
    {
        system("cls");
        cout << "\n\n\t     - MENU -";
        cout << "\n\t01. NEW ACCOUNT";
        cout << "\n\t02. DEPOSIT AMOUNT";
        cout << "\n\t03. WITHDRAW AMOUNT";
        cout << "\n\t04. BALANCE ENQUIRY";
        cout << "\n\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\t08. EXIT";
        cout << "\nSelect Your Option (1-8) ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            writeAccount();
            break;
        case '2':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            depositWithdraw(num, 1);
            break;
        case '3':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            depositWithdraw(num, 2);
            break;
        case '4':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            displayAccount(num);
            break;
        case '5':
            displayAll();
            break;
        case '6':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            deleteAccount(num);
            break;
        case '7':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            modifyAccount(num);
            break;
        case '8':
            cout << "\n\n\tThanks for using bank managemnt system";
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch != '8');
    return 0;
}

// It creates an account object, opens the file, creates an account, and writes the account to the file
void writeAccount(){
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.createAccount();
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
    outFile.close();
}

void displayAccount(int n){
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile){
        cout << "\n\tFile could not be open !! Press any Key ....";
        return;
    }
    cout << "\n\tBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.returnAccount() == n)
        {
            ac.showAccount();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nAccount number does not exist";
}

/**
 * It opens a file, reads the file, and if the account number matches the account number passed to the
 * function, it modifies the account.
 * 
 * @param n account number
 * 
 * @return the account number.
 */
void modifyAccount(int n)
{
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.returnAccount() == n)
        {
            ac.showAccount();
            cout << "\n\nEnter The New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}

/**
 * It opens the file, reads the file, and if the account number is not equal to the account number
 * passed in, it writes the account to a temporary file. 
 * 
 * If the account number is equal to the account number passed in, it does not write the account to the
 * temporary file. 
 * 
 * Then it closes the files, deletes the original file, and renames the temporary file to the original
 * file name. 
 * 
 * The result is that the account is deleted from the file.
 * 
 * @param n the account number
 * 
 * @return The account number.
 */
void deleteAccount(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.returnAccount() != n)
        {
            outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\n\tRecord Deleted ..";
}

// It reads the data from the file and displays it on the screen
void displayAll()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

/**
 * Hàm này đc sd để ghi d/l vào tệp và update thông tin tk cho hoạt động gửi tiền hoặc rút tiền. Cụ thể, nó sẽ
 * y/c user nhập số tk và lựa chọn hđ. Nếu tk tồn tại, hàm sẽ hiển thị thông tin tk, thực hiện hđ gửi tiền hoặc
 * rút tiền và cập nhật thông tin mới vào tệp. Nếu tk k tồn tại, hàm sẽ thông báo cho user biết.
 *
 * @param n The account number
 * @param option 1 for deposit, 2 for withdraw
 *
 * @return the account number.
 */
void depositWithdraw(int n, int option)
{
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.returnAccount() == n)
        {
            ac.showAccount();
            if (option == 1)
            {
                cout << "\n\n\tTO DEPOSITE AMOUNT ";
                cout << "\n\nEnter The amount to be deposited";
                cin >> amt;
                ac.depositAmount(amt);
            }
            if (option == 2)
            {
                cout << "\n\n\tTO WITHDRAW AMOUNT ";
                cout << "\n\nEnter The amount to be withdraw";
                cin >> amt;
                int bal = ac.returnDeposit() - amt;
                if ((bal < 500 && ac.returnType() == 'S') || (bal < 1000 && ac.returnType() == 'C'))
                    cout << "Insufficience balance";
                else
                    ac.draw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}

void intro()
{
    cout << "\n\t\tBANK MANAGEMENT SYSTEM"
         << "\n\n\tMADE BY : VU XUAN HIEP"
         << "\n\tSCHOOL : UNETI"
         << "\n\nPress any key to continue";
    cin.get();
}