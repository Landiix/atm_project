#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <nlohmann/json.hpp>
#include <fstream> 

using namespace std;
using namespace nlohmann;

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
    //считать крайнюю строку и вписать в card.number
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

void Createjsonfile()
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

}




void gotoxy(short x, short y)
{
    COORD p = { x,y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

bool LogIn()
{
    system("cls");
    string EnteredNumber;
    cout << "enter your card number" << endl;
    cin >> EnteredNumber;
    string CardNumber = EnteredNumber + ".json";

    ifstream card(CardNumber.c_str());
    if (card.is_open())
        return true;
    else return false;
   
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
    bool exit = false;

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
                if (LogIn()) ShowAccountMenu();
                else system("cls");
                    cout << "Invalid card number";
                    Sleep(10);
            }
            else if (MenuItem == 1) // Create a card
            {
                Createjsonfile();
                
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

