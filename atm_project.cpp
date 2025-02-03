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

void Createjsonfile()
{
    ofstream card1("1111.json");
    fstream card;
    card.open("1111.json");
    json card2;
    card2["Name"] =
        card2["Surname"] =
        card2["Balance"] = 0;
    //дописать 
    
}

Card CreateCard(string name, string surname)
{
    system("cls");
    string name, surname;
    cout << "Enter your name" << endl;
    cin >> name;
    cout << endl;
    cout << "Enter your surname" << endl;
    cin >> surname;
    cout << endl;
    Card card(name, surname);
    
    fstream CardData;
    CardData.open("CardData.txt");
    //считать крайнюю строку и вписать в card.number


    return card;
}

void EnterCardholderInfo()
{
    
    fstream CardData;
    CardData.open("CardData.json");
    //вписать в фаил номер карты которая только что сделалась
}

void LogIn()
{
    int CardNum;
    cout << "Enter card number";
    cin >> CardNum;
    cout << endl;
}

void gotoxy(short x, short y)
{
    COORD p = { x,y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void ShowCardMenu()
{
    system("cls");
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

            }
            else if (MenuItem == 1) // Create a card
            {
                
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

