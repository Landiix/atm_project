#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <nlohmann/json.hpp>
#include <fstream> 

using namespace std;
using namespace nlohmann;


string EnteredNumber;

class Card
{
public:
    string name, surname;
    int nubmer,balance = 0;

    Card() {}

    Card(string name1, string surname1)
    {
        name = name1;
        surname = surname1;
    }

};

Card CreateCard()
{
    system("cls");
    string name, surname;
    cout << "Enter your name" << endl;
    cin >> name;
    cout << endl;
    cout << "Enter your surname" << endl;
    cin >> surname;
    cout << endl;
    system("cls");
    Card card(name, surname);

    fstream CardData;
    CardData.open("CardData.txt");
    string LastNum;
    while (true)
    {
        if (!CardData.eof())
        {
            getline(CardData, LastNum);
        }
        else
            break;
        
    }

    CardData.close();

    card.nubmer = atoi(LastNum.c_str()) + 1;

    string CardNumber = to_string(atoi(LastNum.c_str()) + 1);

    ofstream CardData1;
    CardData1.open("CardData.txt", ios_base::app);
    CardData1 <<endl<< CardNumber;
    CardData1.close();

    return card;
}

int Createjsonfile()
{
    Card cardd = CreateCard();
    string FileName = to_string(cardd.nubmer) + ".json";
    ofstream card1;
    card1.open(FileName.c_str());

    
    json card;
    
    card["name"] = cardd.name;
    card["surname"] = cardd.surname;
    card["balance"] = cardd.balance;
    card["number"] = cardd.nubmer;

    card1 << card << endl;
    card1.close();

    return cardd.nubmer;
}

void Deposit()
{
    system("cls");
    cout << "Enter banknotes (from 100 to 5000)" << endl;
    int EnteredValue, OldValue;
    cin >> EnteredValue;
    Sleep(100);
    cout << ". "; 
    Sleep(100); 
    cout << ". "; 
    Sleep(100); 
    cout << "." << endl;
    
    fstream f(EnteredNumber.c_str());
    json Cardj = json::parse(f);

    OldValue = Cardj["balance"];

    Card card;
    card.name = Cardj["name"];
    card.nubmer = Cardj["number"];
    card.surname = Cardj["surname"];
    card.balance = Cardj["balance"];

    

    card.balance = OldValue + EnteredValue;

    
    remove(EnteredNumber.c_str());
    
    ofstream card1;
    card1.open(EnteredNumber.c_str());

    json CardNew;

    CardNew["name"] = card.name;
    CardNew["surname"] = card.surname;
    CardNew["number"] = card.nubmer;
    CardNew["balance"] = card.balance;

    card1 << CardNew << endl;

    card1.close();

}

void transfer()
{
    system("cls");

    string TransferNumber;
    int TransferValue, OldFromValue,OldToValue;
    system("cls");
    cout << "Enter number of card u want to transfer" << endl;
    cin >> TransferNumber;
    cout << "Enter value" << endl;
    cin >> TransferValue;
    TransferNumber = TransferNumber + ".json";
    fstream f(TransferNumber.c_str());
    json TransferToCard = json::parse(f);

    fstream g(EnteredNumber.c_str());
    json TransferFromCard = json::parse(g);

    if (TransferFromCard["balance"] >= TransferValue)
    {
        OldFromValue = TransferFromCard["balance"];
        TransferFromCard["balance"] = TransferFromCard["balance"] - TransferValue;
        OldToValue = TransferToCard["balance"];
        TransferToCard["balance"] = TransferToCard["balance"] + TransferValue;
    }
    else
    {
        cout << "Not enough balance";
        Sleep(10000);
    }
    f.close();
    g.close();

}

void gotoxy(short x, short y)
{
    COORD p = { x,y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

bool LogIn()
{
    system("cls");
    cout << "enter your card number" << endl;
    cin >> EnteredNumber;
    EnteredNumber = EnteredNumber + ".json";

    ifstream card(EnteredNumber.c_str());
    if (card.is_open())
        return true;
    else return false;
}

void ShowAccountInfo()
{
    system("cls");
    ifstream f(EnteredNumber.c_str());
    json Card = json::parse(f);

    cout << "Name: " << Card["name"] << endl << "Surname: " << Card["surname"] << endl << "Balance: " << Card["balance"] << endl << "Card Number: " << Card["number"] << endl;
    f.close();
}

void ShowAccountMenu()
{
    system("cls");
    cout << " show account info" << endl;
    cout << " deposit" << endl;
    cout << " transfer" << endl;
    cout << " back to main menu" << endl;

}

void ShowMainMenu()
{
    system("cls");
    cout << " Log In" << endl;
    cout << " Create a Card" << endl;
    cout << " Exit" << endl;
}


int main()
{
    

    int ch = 0;
    int MenuItem = 0;
    bool exit = false, exitToMainMenu = false, exitToAccMenu = false;

    ShowMainMenu();

    while (!exit)
    {

        ShowMainMenu();
        gotoxy(0, MenuItem);

        ch = _getch();
        if (ch == 224) 
            ch = _getch();

        switch (ch)
        {
        case 27: exit = true; break;
        case 72: MenuItem--; break;
        case 80: MenuItem++; break;
        case 13:
            if (MenuItem == 0) // Log In
            {
                if (LogIn()) { 
                    ShowAccountMenu();

                    while (!exitToMainMenu)
                    {
                        ShowAccountMenu();
                        gotoxy(0, MenuItem);
                        ch = _getch();
                        if (ch == 224)
                            ch = _getch();
                        switch (ch)
                        {
                        case 27: exitToMainMenu = true; break;
                        case 72: MenuItem--; break;
                        case 80: MenuItem++; break;
                        case 13:
                            if (MenuItem == 0) // show account info
                            {
                                while(!exitToAccMenu)
                                {
                                    ch = _getch();
                                    if (ch == 224)
                                        ch = _getch(); 
                                    ShowAccountInfo();
                                    switch (ch)
                                    {
                                    case 27: exitToAccMenu = true; break;
                                    }
                                }
                                exitToAccMenu = false;
                            }
                            else if (MenuItem == 1) // deposit
                            {
                                Deposit();
                            }
                            else if (MenuItem == 2) // transfer
                            {
                                transfer();
                            }
                            else if (MenuItem == 3) // exit to main menu
                            {
                                exitToMainMenu = true;
                            }
                        }
                        if (MenuItem < 0)
                        {
                            MenuItem = 0;
                        }
                        if (MenuItem > 3)
                        {
                            MenuItem = 3;
                        }
                    }
                }
                else {
                    system("cls");
                    cout << "Invalid card number";
                    Sleep(3000);
                }
            }
            else if (MenuItem == 1) // Create a card
            {
                cout<<"Your card number is: "<<Createjsonfile();
                Sleep(5000);
                
            }
            else if (MenuItem == 2) // Exit
            {
                exit = true;
            }
            break;
        }
        if (MenuItem < 0)
        {
            MenuItem = 0;
        }
        if (MenuItem > 2)
        {
            MenuItem = 2;
        }
    }
}

