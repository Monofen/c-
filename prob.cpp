#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class top
{
public:
    void color(int color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void gotoxy(int x, int y)
    {
        COORD c;
        c.X = x;
        c.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }
};

class file
{
public:
    fstream user_password;
    fstream item;
};

class login : virtual public top, virtual public file
{
public:
    int i = 0,found=0;
    int Set[5] = {7, 7, 7, 7, 7};
    int def[2] = {7,7};
    int counter = 1;
    char key;
    string input_user,input_password, username, password, fname, lname,test;
    int consoleWidth = 100;
    int menuWidth = 40; // Width of the menu
    int padding = (consoleWidth - menuWidth) / 2; // Calculate left padding


    void clear()
    {
        system("cls");
    }

    void displayMenu()
    {
        counter=1;
        clear();
        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        top::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tMenu \tWelcome, "<<fname<<" "<<lname << endl;
        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        while (1)
        {
            top::gotoxy(padding + 2, 4);
            top::color(Set[0]);
            cout << "1. Create Invoice" << endl;

            top::gotoxy(padding + 2, 5);
            top::color(Set[1]);
            cout << "2. Create Costumer Membership" << endl;

            top::gotoxy(padding + 2, 6);
            top::color(Set[2]);
            cout << "3. Edit Shoplist / Edit Moderators" << endl;

            top::gotoxy(padding + 2, 7);
            top::color(Set[3]);
            cout << "4. Exit" << endl;

            if (counter != 4)
            {
                top::color(def[0]);
                cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
            }
            key = _getch();

            if (key == 72 && (counter >= 2 && counter <= 4))
                counter--;
            if (key == 80 && (counter >= 1 && counter <= 3))
                counter++;
            if (key == '\r')
            {
                switch (counter)
                {
                case 1:
                    Set[0] = 7;
                    cout << "Menu 1 is Open" << endl;
                    break;
                case 2:
                    Set[1] = 7;
                    cout << "Menu 2 is Open" << endl;
                    break;
                case 3:
                    clear();
                    Set[2] = 7;
                    EditMenu();
                    break;
                case 4:
                    Set[3] = 7;
                    clear();
                    displayLogin();

                    break;
                }
            }

            Set[0] = 7;
            Set[1] = 7;
            Set[2] = 7;
            Set[3] = 7;

            if (counter == 1)
                Set[0] = 12;
            if (counter == 2)
                Set[1] = 12;
            if (counter == 3)
                Set[2] = 12;
            if (counter == 4)
                Set[3] = 12;
        }
    }

    void read_user_pass()
{
    ifstream user_password("user_name_and_password.txt", ios::in | ios::binary);

    cout << "Enter username:" << endl;
    cin >> input_user;
    cout << "Enter password:" << endl;
    cin >> input_password;

    found = 0;

    while (user_password >> username >> password>>fname>>lname)
    {
        if (username == input_user && password == input_password)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        clear();
        displayMenu();
    }
    else
    {
        cout << "Invalid username or password. Please try again." << endl;
        cout<<"Press enter key to continue."<<endl;
        key=_getch();
        if (key == '\r')
        {
        clear();
        displayLogin();
        }
    }
}

    void deleteRecord()
    {
        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        top::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tRemove" <<endl;
        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        ifstream user_password("user_name_and_password.txt", ios::binary | ios::in|ios::out);
        ofstream data_clear("temp.txt",ios::binary|ios::out);
        top::gotoxy(padding, 4);
        cout << "Firstname" << setw(15) << "Lastname" << setw(15) << "Username" << endl;
        i=5;
        int b=0;
        bool found=false;
        while (user_password >> username >> password >> fname >> lname)
        {
            top::gotoxy(padding, i);
            cout << fname << setw(18) << lname << setw(15) << username << endl;
            i++;
        }
        user_password.close();
        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        cout<<"Enter username of the user you want to delete"<<endl;
        cin>>input_user;
        ifstream check("user_name_and_password.txt", ios::binary|ios::in );

string tempUsername, tempPassword, tempFname, tempLname;


    while (check >> tempUsername >> tempPassword >> tempFname >> tempLname) {
        if (tempUsername != input_user) {
            data_clear << tempUsername << " " << tempPassword << " " << tempFname << " " << tempLname << std::endl;
        } else {
            found = true;
        }
    }
    getch();
    data_clear.close();
    check.close();
    remove("user_name_and_password.txt");
    rename("temp.txt", "user_name_and_password.txt");
    if (found) {
        cout << "Record deleted!" << endl;
    } else {
        cout << "No such data found." << endl;
        remove("temp.txt");
    }
    cout << "Press enter key to continue." << endl;
    cout << "Else press any other key." << endl;
    key = _getch();
    if (key == '\r') {
        clear();
        deleteRecord();
    } else {
        clear();
        EditModerator();
    }

    }

    void createRecord()
    {
        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        top::color(def[0]);
        cout << setw(padding) << "" << "           Insert" <<endl;
        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        ofstream user_password("user_name_and_password.txt",ios::app|ios::binary);

        top::gotoxy(padding + 2, 4);
        cout << "Enter First Name: ";
        cin.ignore();
        getline(cin, fname);
        cin.ignore();

        top::gotoxy(padding + 2, 5);
        cout << "Enter Last Name: ";
        getline(cin, lname);
        cin.ignore();

        top::gotoxy(padding + 2, 6);
        cout << "Enter Username: ";
        getline(cin, username);
        cin.ignore();

        top::gotoxy(padding + 2, 7);
        cout << "Enter Password: ";
        getline(cin, password);
        cin.ignore();

        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        user_password << username << " " << password << " " << fname << " " << lname << endl;
        user_password.close();
        cout<<"Data successfully added!!"<<endl;
        cout<<"Would you like to continue?"<<endl;
        cout<<"Press enter key to continue"<<endl;
        cout<<"Else press any key"<<endl;
        key=_getch();
        if(key=='\r')
        {
            clear();
            createRecord();
        }
        else
        {
            clear();
            EditModerator();
        }
    }

    void EditModerator()
    {
         counter=1;
        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        top::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tAdd/Remove" <<endl;
        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        while (1)
        {

            top::gotoxy(padding + 2, 4);
            top::color(Set[0]);
            cout << "1. Add moderator" << endl;

            top::gotoxy(padding + 2, 5);
            top::color(Set[1]);
            cout << "2. Remove moderator" << endl;

            top::gotoxy(padding + 2, 6);
            top::color(Set[2]);
            cout << "3. Exit" << endl;

            if (counter != 2)
            {
                top::color(def[0]);
                cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
            }
            key = _getch();
            if (key == 72 && (counter >= 2 && counter <= 3))
            {
                counter--;
            }
            if (key == 80 && (counter >= 1 && counter <= 2))
            {
                counter++;
            }
            if (key == '\r')
            {
                switch (counter)
                {
                case 1:
                    Set[0] = 7;
                    clear();
                    createRecord();
                    break;

                case 2:
                    Set[1] = 7;
                    clear();
                    deleteRecord();
                    break;

                case 3:
                    Set[2] = 7;
                    clear();
                    EditMenu();
                    break;

                default:
                    cout << "Invalid" << endl;
                    continue;
                }
            }

            Set[0] = 7;
            Set[1] = 7;
            Set[2] = 7;

            if (counter == 1)
                Set[0] = 12;

            if (counter == 2)
                Set[1] = 12;

            if (counter == 3)
                Set[2] = 12;
        }
    }

    void EditMenu()
    {

        counter=1;
        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        top::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tChoose Edit" <<endl;
        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        while (1)
        {

            top::gotoxy(padding + 2, 4);
            top::color(Set[0]);
            cout << "1. Edit shoplist" << endl;

            top::gotoxy(padding + 2, 5);
            top::color(Set[1]);
            cout << "2. Edit moderator" << endl;

            top::gotoxy(padding + 2, 6);
            top::color(Set[2]);
            cout << "3. Exit" << endl;

            if (counter != 2)
            {
                top::color(def[0]);
                cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
            }
            key = _getch();
            if (key == 72 && (counter >= 2 && counter <= 3))
            {
                counter--;
            }
            if (key == 80 && (counter >= 1 && counter <= 2))
            {
                counter++;
            }
            if (key == '\r')
            {
                switch (counter)
                {
                case 1:
                    Set[0] = 7;
                    read_user_pass();
                    break;

                case 2:
                    Set[1] = 7;
                    clear();
                    EditModerator();
                    break;

                case 3:
                    Set[2] = 7;
                    clear();
                    displayMenu();
                    break;

                default:
                    cout << "Invalid" << endl;
                    continue;
                }
            }

            Set[0] = 7;
            Set[1] = 7;
            Set[2] = 7;

            if (counter == 1)
                Set[0] = 12;

            if (counter == 2)
                Set[1] = 12;

            if (counter == 3)
                Set[2] = 12;
        }
    }


    void displayLogin()
    {

        counter=1;
        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        top::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tLogin" <<endl;
        top::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        while (1)
        {
            top::gotoxy(padding + 2, 4);
            top::color(Set[0]);
            cout << "1. Login" << endl;

            top::gotoxy(padding + 2, 5);
            top::color(Set[1]);
            cout << "2. Exit" << endl;

            if (counter != 2)
            {
                cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
            }
            key = _getch();
            if (key == 72 && (counter == 2))
            {
                counter--;
            }
            if (key == 80 && (counter == 1))
            {
                counter++;
            }
            if (key == '\r')
            {
                switch (counter)
                {
                case 1:
                    Set[0] = 7;
                    read_user_pass();
                    break;

                case 2:
                    Set[1] = 7;
                    clear();
                    cout << "Closing shop...." << endl;
                    ExitProcess(0);
                    break;

                default:
                    cout << "Invalid" << endl;
                    continue;
                }
            }

            Set[0] = 7;
            Set[1] = 7;
            Set[2] = 7;

            if (counter == 1)
                Set[0] = 12;

            if (counter == 2)
                Set[1] = 12;

            if (counter == 3)
                Set[2] = 12;
        }
    }
};

int main()
{
    login d;
    d.displayLogin();
    return 0;
}
