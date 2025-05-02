#include <iostream>
#include <iomanip>
#include "headers/functions.h"
#include "headers/structs.h"

using namespace std;

/*********************************************************************
File name: supermarket_simulator_program_3.cpp
Author: Andrew Voyez
Date: 12/2/2024

Purpose:
    Create a simulation of a supermarket.
Command Parameters:
    -
Input:
    Path to supermarket text files.
    Various user input menu choices and market purchases.
Results:
    Simulates supermarket operations.
Notes:
    -
*********************************************************************/
int main()
{
    cout << fixed << setprecision(2);
    fstream fileSupermarketInput;
    fstream fileDataIO;
    string szAdminPassword = "minimart";
    string szTemp;
    int iAttempts = 0; 

    string szDefaultMenuChoicesArr[6] = {
        "Display supermarket information",
        "Display aisle information",
        "Display aisle items",
        "Checkout",
        "Employee Menu",
        "Exit program"
    };

    string szAdminMenuChoicesArr[6] = {
        "Update supermarket information",
        "Display total funds",
        "Display total sales",
        "Pay employees",
        "Update employee password",
        "Exit admin menu"
    };

    cout << "Starting supermarket simulation\n" << endl;

    Supermarket marketA;
    processSupermarketInformation(fileSupermarketInput, marketA);

    int iChoice, iAdminChoice, iAisleChoice;
    do
    {
        displayMenu("\nMenu", szDefaultMenuChoicesArr, 6);
        
        if(cout << "\nEnter choice: " && !(cin >> iChoice)) 
        {
            cout << "Killing program due to bad input" << endl;
            return -1;
        }
        
        switch(iChoice)
        {
            case 1:
            {
                displaySupermarketInfo(marketA);
                break;
            }
            case 2:
            {
                displayAisles(marketA);
                break;
            }
            case 3:
            {
                displayAisles(marketA);
                cout << "Enter an aisle index you would like to view: ";
                cin >> iAisleChoice;
                displayItems(marketA, iAisleChoice);
                break;
            }
            case 4:
            {
                marketA.customersArr[marketA.iCurrentCustomers] = checkout(marketA);
                if(marketA.customersArr[marketA.iCurrentCustomers].szName != "")
                    marketA.iCurrentCustomers += 1;
                break;
            }
            case 5:
            {
                cout << "Enter employee password: ";
                cin.ignore();
                cin >> szTemp;

                if(szTemp == szAdminPassword)
                {
                    cout << "Employee access granted" << endl;
                    iAttempts = 0;
                    do
                    {
                        displayMenu("\nEmployee Menu", szAdminMenuChoicesArr, 6);
                        
                        if(cout << "\nEnter choice: " && !(cin >> iAdminChoice)) 
                        {
                            cout << "Killing program due to bad input" << endl;
                            return -1;
                        }
                        
                        switch(iAdminChoice)
                        {
                            case 1:
                            {
                                cin.ignore();
                                processSupermarketInformation(fileSupermarketInput, marketA);
                                break;
                            }
                            case 2:
                            {
                                displayTotalFunds(marketA);
                                break;
                            }
                            case 3:
                            {
                                cout << "Today's total sales is $" << calculateTotalSales(marketA) << endl;
                                break;
                            }
                            case 4:
                            {
                                bool bPayedEmployees = payEmployees(marketA);
                                if(bPayedEmployees)
                                    cout << "Payed employees successfully" << endl;
                                else
                                    cout << "Insufficient funds" << endl;
                                break;
                            }
                            case 5:
                            {
                                cout << "Please enter new admin password: ";
                                cin.ignore();
                                getline(cin, szAdminPassword);
                                cout << "Password has been updated" << endl;
                            } 
                            case -1:
                            {
                                cout << "Exiting admin menu" << endl;
                                iAdminChoice = -1;
                                break;
                            }
                            default:
                                cout << "Please choose a valid menu choice" << endl;
                            
                        }
                    }while(iAdminChoice != -1);
                }
                else
                {
                    cout << "Incorrect password." << endl;
                    iAttempts += 1;
                    
                    if(iAttempts > 3)
                    {
                        cout << "Closing program due to excess password attempts." << endl;
                        return -1;
                    }
                    
                }
                break;
            }
            // Exit the program
            case -1:
            {
                cout << "Exiting program" << endl;
                break;
            }
            // Default case handling
            default:
            {
                cout << "Please choose a valid menu choice" << endl;
            }
        }
        
    }while(iChoice != -1);

    return 0;
}