#include <iostream>                 //for regular C++ functions like for example cin and cout
#include <iomanip>                  //for setprecision function

using namespace std;


#define RESET "\033[0m"                  //defining colors used in the project
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"
#define BOLD "\033[1m"

int accountIds[100];                      //where account ids are stored in
long double accountBalances[100];         //where account balances are stored in
int accountPins[100];                     //where account PINS are stored in
int accountCount = 0;                     //counter for created accounts (Max is 100 accounts)
bool acclogin = false;                    //login state checker
int logedin_id;                           //declaring login id variable (helps to know the index of the logged in account in the other arrays)

void createAccount() {                    //function for account creation
    if (accountCount >= 100) {
        cout <<RED << "Maximum number of accounts reached!\n" << RESET;
        return;
    }

    int id;
    long double balance;
    int pin;

    cout << "Enter Account ID (3 digits only): ";
    cin >> id;
    if (id > 999 || id < 100){
        cout << RED << "ID Must be 3 digits only\n" <<RESET;
        return;
    }
    for (int i = 0; i < accountCount; i++) {
        if (accountIds[i] == id) {
            cout << RED << "Account ID already exists!\n" << RESET;
            return;
        }
    }
    cout << "Enter Initial Balance: ";
    cin >> balance;
    if (balance < 0){
        cout << RED << "Invalid amount\n"<< RESET;
        return;
    }
    cout << "Set a 4-digit PIN: ";
    cin >> pin;
    if (pin <=999 || pin >9999){
        cout << RED << "PIN Must be 4 digits\n"<< RESET;
        return;
    }

    accountIds[accountCount] = id;                      //Stores the id of the newly created account
    accountBalances[accountCount] = balance;            //Stores the initial Balance of the newly created account
    accountPins[accountCount] = pin;                    //Stores the PIN of the newly created account
    accountCount++;                                     //increments the Accounts counter due to the newly created account
    cout << GREEN << "Account created successfully!\n" << RESET;
}

bool verifyPin(int id) {                                //function for PIN verification
    for (int i = 0; i < accountCount; i++) {
        if (accountIds[i] == id) {
            int inputPin;
            cout << "Enter your 4-digit PIN: ";
            cin >> inputPin;
            if (inputPin == accountPins[i]){
                return true;
            }
        }
    }
    return false;
}

void login(){                                          //Login function
    int id;
    if(!acclogin){
        cout << "Enter account id: ";
        cin >> id;
        if (!verifyPin(id)){
            cout << RED << "Invalid Id/PIN!\n" << RESET;
            return;
        }
        cout << GREEN << "Login done\n"<< RESET;
        logedin_id = id;
        acclogin = true;
        return;
    }
    cout << RED << "Logout first!\n" << RESET;
}

void checkBalance() {                                 //Check Balance function
    if(acclogin){
        for (int i = 0; i < accountCount; i++) {
            if (accountIds[i] == logedin_id) {
                cout << GREEN << "Account Balance: " << fixed << setprecision(2) << accountBalances[i] << "$\n" << RESET;
                return;
            }
        }
    }
    cout << RED << "Login first!\n" << RESET;
}

void depositMoney() {                                 //Depositing money function
    long double amount;
    if (acclogin){
        if(!verifyPin(logedin_id)){
            cout << "Incorrect PIN\n";
            return;
        }
        for (int i = 0; i < accountCount; i++) {
            if (accountIds[i] == logedin_id) {
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                if (amount > 0) {
                    accountBalances[i] += amount;
                    cout <<GREEN << "Deposit successful!\n"<<RESET;
                    cout << GREEN << "Your new Balance is " << fixed << setprecision(2) << accountBalances[i] << "$\n"<< RESET;
                        return;
                }
                cout << RED << "Enter valid number!\n" << RESET;
                return;
            }
        }
    }
    cout << RED << "Login first!\n" << RESET;
}


void withdrawMoney() {                                //Money withdrawal function
    long double amount;
    if (acclogin){
        if(!verifyPin(logedin_id)){
            cout << "Incorrect PIN\n";
            return;
        }
        for (int i = 0; i < accountCount; i++) {
            if (accountIds[i] == logedin_id) {
                cout << "Enter the amount you want to withdraw: ";
                cin >> amount;
                if (amount > 0 && accountBalances[i] >= amount) {
                    accountBalances[i] -= amount;
                    cout << GREEN << "Withdrawal successful!\n" << RESET;
                    cout << GREEN << "Your new Balance is " << fixed << setprecision(2) << accountBalances[i] << "$\n"<< RESET;
                } else {
                    cout << RED <<"Enta ka7yaaan yasta :( \n" << RESET;             //يا فقير
                }
                return;
            }
        }
    }
    cout << RED << "Login first!\n" <<RESET;
}

void closeAccount() {                                 //Function for Account closure (Deletes the account currently logged in)
    if (acclogin){
        if(!verifyPin(logedin_id)){
            cout << "Incorrect PIN\n";
            return;
        }
        char sure;
        while(1){
            cout << RED << "Are You sure ??(Y,N): " << RESET;
            cin >> sure;
            if (sure == 'Y' || sure == 'y'){
                for (int i = 0; i < accountCount; i++) {
                    if (accountIds[i] == logedin_id) {
                        for (int j = i; j < accountCount - 1; j++) {                // Shifting the registered accounts back therefore reducing the array size after account deletion
                            accountIds[j] = accountIds[j + 1];
                            accountBalances[j] = accountBalances[j + 1];
                            for (int k = 0; k < 5; k++) {
                                accountPins[j] = accountPins[j + 1];
                            }
                        }
                        accountCount--;
                        cout << GREEN << "Account Deleted successfully\n" << RESET;
                        acclogin = false;
                        return;
                    }
                }
            }
            else if (sure == 'N' || sure == 'n'){                                  //executes if the user doesn't want to proceed with account deletion
                cout << "Delete Canceled!\n";
                return;
            }
        }
    }
    cout << RED <<"Login first!\n" << RESET;
}


bool idfound(int id){                                //Function for finding if the id is found in accounts id array or not
    for (int i = 0; i < accountCount ; i++){
        if (accountIds[i] == id){
            return true;
        }
    }
    return false;
}

void transfer (){                                    //Function for transferring money  between accounts
    long double amount;
    int second_id ,account1_index,account2_index;
    if (acclogin){
        if(!verifyPin(logedin_id)){
            cout << "Incorrect PIN\n";
            return;
        }
        cout << "Enter the account id you want to transfer to: ";
        cin >> second_id;

        if (!idfound(second_id)){
            cout << RED << "Invalid ID\n";
            return;
        }

        if (logedin_id == second_id){
            cout << RED <<"You can't transfer to the same account.\n" << RESET;
            return;
        }

        for (int i = 0; i < accountCount; i++) {
            if (accountIds[i] == logedin_id) {
                account1_index = i;
            }
            if (accountIds[i] == second_id) {
                account2_index = i;
            }
        }
        cout << "Enter the amount: ";
        cin >> amount;
        if (amount <=0 || amount > accountBalances[account1_index] ){
            cout << RED << "Invalid amount\n" << RESET;
            return;
        }
        accountBalances[account1_index] -= amount;
        accountBalances[account2_index] += amount;
        cout << CYAN << "Transfer Done.\n" << RESET;
        return;
    }

    cout << RED << "Login first!\n" << RESET;

}


void logout(){                                       //Logging out function
    if (acclogin){
        if(!verifyPin(logedin_id)){
            cout << "Incorrect PIN\n";
            return;
        }
        cout << GREEN << "Done Logging out.\n" << RESET;
        acclogin = false;
        return;
    }
    cout << RED <<"Login first!\n" << RESET;


}

void currency_calculator(){                        //Curency calculator function
    long double amount;
    int choice;
    while(1){
        cout << "1-Egyption Pound (EGP) -> United States Dollar (USD)\n" << "2-United States Dollar (USD) -> Egyption Pound (EGP)\n" << "3-Egyption Pound (EGP) -> Euro (EUR) \n" << "4-Euro (EUR) -> Egyption Pound (EGP)\n" << "5-Egyption Pound (EGP) -> United Arab Emirates Dirham (AED)\n" << "6-United Arab Emirates Dirham (AED) -> Egyption Pound (EGP)\n" << "7-Egyption Pound (EGP) -> Kuwaiti Dinar (KWD)\n" << "8-Kuwaiti Dinar (KWD) -> Egyption Pound (EGP)\n" << "9-Egyption Pound (EGP) -> Saudi Riyal (SAR)\n" << "10-Saudi Riyal (SAR) -> Egyption Pound (EGP)\n" << "11-Exit to main menu\n";
        cout << MAGENTA <<  "Enter your choice: " << RESET;
        cin >> choice;
        if (choice > 11 || choice <1){
            cout << RED << "Invalid number! Try Again...\n" << RESET;
        }
        else if (choice == 11){
            return;
        }
        else{
            cout << "Enter the amount: ";
            cin >> amount;
            switch(choice){
                case 1: cout << GREEN << amount << " EGP = " << amount / 50.59 << " USD\n" << RESET;
                    break;
                case 2: cout << GREEN << amount << " USD = "  << amount * 50.59 << " EGP\n" << RESET;
                    break;
                case 3: cout << GREEN << amount << " EGP = " << amount / 53.09 << " EUR\n" << RESET;
                    break;
                case 4: cout << GREEN << amount << " EUR = " << amount * 53.09 << " EGP\n" << RESET;
                    break;
                case 5: cout << GREEN << amount << " EGP = " << amount / 13.77 << " AED\n" << RESET;
                    break;
                case 6: cout << GREEN << amount << " AED = " << amount * 13.77 << " EGP\n" << RESET;
                    break;
                case 7: cout << GREEN << amount << " EGP = " << amount / 163.98 << " KWD\n" << RESET;
                    break;
                case 8: cout << GREEN << amount << " KWD = " << amount * 163.98 << " EGP\n" << RESET;
                    break;
                case 9: cout << GREEN << amount << " EGP = " << amount / 13.49 << " SAR\n" << RESET;
                    break;
                case 10: cout << GREEN << amount << " SAR = " << amount * 13.49 << " EGP\n" << RESET;
                    break;
            }
        }
    }
}

void menu() {                                        //Main menu Function
    int choice;
    while (true) {
        cout << YELLOW << "\n======================\n" << RESET;
        cout << CYAN << BOLD << " Bank Masr Elghalaba\n" << RESET;
        cout << YELLOW << "======================\n" << RESET;
        cout << "1-Create Account\n" << "2-Login\n"<< "3-Deposit Money\n" << "4-Withdraw Money\n" << "5-Check Balance\n" << "6-Transfer Money\n" << "7-Logout\n" << "8-Delete Account\n" << "9-Currency Calculator\n" << "10-Exit\n";
        cout << MAGENTA << "Enter your choice: " << RESET;
        cin >> choice;


        switch (choice) {                            //Switch for choosing between bank functions
            case 1: createAccount();
                    break;
            case 2: login();
                    break;
            case 3: depositMoney();
                    break;
            case 4: withdrawMoney();
                    break;
            case 5: checkBalance();
                    break;
            case 6: transfer();
                    break;
            case 7: logout();
                    break;
            case 8: closeAccount();
                    break;
            case 9: currency_calculator();
                    break;
            case 10: cout << BLUE << BOLD << "ONTOR ABLAKASH :)" << RESET ;     // "الجيار قال "الكويس منها بديله التحيه والوحش منها بقوله برا انطر ابلكاش
                    return;
            default: cout <<RED << "Invalid number.\n"<< RESET;
        }
    }
}

int main() {                                         //Program execution begins here
    menu();
    return 0;
}
