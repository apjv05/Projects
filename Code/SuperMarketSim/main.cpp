/*
How to make a supermarket file:

Supermarket Name
Hours
Starting Funds
Membership fee
*Aisle Information* to tell the computer to start looking for aisles
Aisle Name
Product Wholesale Regular Member
############################ to make a new aisle then repeat Aisle informatiom
*Employee Information* to tell the computer to start looking for employee information
Name ID Salary

Examples:
File 1:
CS Mart 3.0
8:00 am to 10:00 pm
10000.00
5.00
*Aisle Information*
Aisle 0: Produce
Apples 0.80 1.29 1.09
Oranges 0.75 1.19 0.99
Bananas 0.60 0.99 0.89
############################
Aisle 1: Dairy
Milk 2.50 3.49 3.19
Cheese 4.00 5.99 5.49
Yogurt 1.20 1.79 1.59
############################
Aisle 2: Snacks
Chips 2.00 2.99 2.69
Candy_Bars 1.50 2.29 2.09
############################
Aisle 3: Personal Care
Shampoo 5.00 7.99 7.19
Toothpaste 2.00 2.99 2.69
Deodorant 2.50 3.99 3.59
Vitamins 10.00 14.99 13.49
############################
*Employee Information*
John_Doe J4567 100.00
Jane_Smith S9012 90.00
Michael_Johnson M3456 120.00
Emily_Williams E8901 80.00
David_Brown D2345 110.00
Olivia_Wilson O7890 85.00
Daniel_Taylor D1234 115.00
Emma_Jones E6789 82.00
Jacob_Miller J3456 125.00
Sophia_Davis S8901 75.00

File 2:
Tech Store
9:00 am to 9:00 pm
50000.00
10.00
*Aisle Information*
Aisle 0: Laptops
Dell_XPS_13 1200.00 1599.99 1499.99
HP_Spectre_x360 1000.00 1399.99 1299.99
MacBook_Air 1500.00 1799.99 1699.99
############################
Aisle 1: Desktops
Dell_XPS_Desktop 800.00 1099.99 999.99
HP_Envy_Desktop 600.00 899.99 799.99
Mac_Studio 1500.00 1999.99 1899.99
############################
Aisle 2: Peripherals
Logitech_Mouse 10.00 19.99 17.99
Razer_Keyboard 30.00 49.99 44.99
Samsung_Monitor 150.00 249.99 229.99
############################
Aisle 3: Gaming
RTX_3080 500.00 799.99 749.99
PS5 400.00 549.99 499.99
Xbox_Series_X 350.00 499.99 449.99
############################
Aisle 4: Accessories
iPhone_Case 5.00 9.99 8.99
Apple_Watch_Band 10.00 19.99 17.99
Headphones 20.00 39.99 34.99
############################
Aisle 5: Networking
Router 50.00 79.99 74.99
Switch 100.00 149.99 139.99
Ethernet_Cable 5.00 9.99 8.99
############################
Aisle 6: Software
Windows_10 50.00 99.99 89.99
Office_365 70.00 119.99 109.99
Antivirus 30.00 49.99 44.99
############################
*Employee Information*
Alex_Smith S1234 1500.00
Emily_Johnson J5678 1200.00
David_Brown B9012 1800.00
Chris_Lee L3456 1400.00
Sarah_Kim K7890 1600.00
Michael_Davis D2345 1300.00
Olivia_Chen C9012 1700.00
Ethan_Lee L1234 1450.00
Ava_Kim K5678 1350.00
Noah_Brown B9012 1650.00
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

string szBreakMessage = "*****************************\n";
double dSALES_TAX = 0.08;
const int MAX_AISLES = 40, MAX_MEMBERS = 200,MAX_EMPLOYEES = 50, MAX_CUSTOMERS = 200, MAX_ITEMS = 100;

struct Item
{
    string szName;          // Name of the item
    int iQuantity = 30;     // Number of items left in stock
    double dWholesale;      // Supermarket's cost
    double dRegularPrice;   // Price for regular customers
    double dMembersPrice;   // Price for store members
};

struct Aisle
{
    string szName = "";          // Name of store aisle
    Item itemArr[100];      // Array of items on that aisle
};

struct CustomerPurchase
{
    string szName = "";             // Name of person who made purchase
    bool bBoughtMembership = false; // Bought membership on the purchase
    int iNumberItems = 0;           // Number of items they purchased 
    double dPurchaseCost = 0.0;     // How much did the purchase cost including tax
    
};

struct Member
{
    string szName = "";         // Name of person who bought membership
};

struct Employee
{
    string szID;                // ID of the employee
    string szName;              // Name of the employee
    double dSalary;             // Salary of the employee
};

struct Supermarket
{
    string szName;                      // Name of the supermarket
    string szStoreHours;                // Hold store hours info
    int iCurrentCustomers = 0;          // Current number of customers
    int iCurrentMembers = 0;            // Current number of members
    int iCurrentEmployees = 0;          // Current number of employees
    double dMembershipFee;              // Fee to become a store member
    double dTotalFunds;                 // Total funds of the store
    Aisle aislesArr[40];                // Array of supermarket aisles
    Employee employeesArr[50];          // Array of employees
    CustomerPurchase customersArr[200]; // Array of customers
    Member membersArr[200];             // Array of members
};

/*********************************************************************
string promptForFilename()
Purpose:
    Helper function ask the user for a valid file path
Parameters:
    -
Return Value:
    Valid filepath string
Notes:
    -
*********************************************************************/
string promptForFilename()
{
	string szFileName;
	bool bFileCheck = false;
    ifstream fin;
    
    do {
		cout << "Please enter file path: ";
        getline(cin, szFileName);
        fin.open(szFileName);
        
	    if(szFileName == "exit") //lets the user exit if needed
        { 
            cout << "Exiting function due to early exiting of file prompt" << endl;
            bFileCheck = true;
        }
        else
        {
            if(!fin)
            {
                cerr << "Please enter a valid file path\n\n";
            }
            else
            {
                bFileCheck = true
            }
        }
    } while (bFileCheck == false);
    fin.close();
	return szFileName;
}

/*********************************************************************
void processSupermarketInformation(fstream& fileInput, Supermarket& myStore)
Purpose:
    Function to read supermarket text file and process the information
    into a supermarket structure
Parameters:
    I/O fstream& fileInput       File stream to read supermarket info
    I/O Supermarket& myStore     Supermarket structure to populate
Return Value:
    -
Notes:
    This function does not validate the file structure it is provided
*********************************************************************/
void processSupermarketInformation(fstream& fileInput, Supermarket& myStore)
{
	int iItemIndex = 0, iEmpIndex = 0, iAisleIndex = 0;
    string szCurrentLine, szTrash;
    bool bAisle = false, bEmp = false, bAisleName = false, bItem = false;
	bool bHasUnderscore = (szCurrentLine.find('_') == string::npos);

	fileInput.open(promptForFilename(), ios::in); // calls function to prompt for file then opens

	getline(fileInput, myStore.szName);
    getline(fileInput, myStore.szStoreHours);
    fileInput >> myStore.dTotalFunds;
    fileInput >> myStore.dMembershipFee;

    while(getline(fileInput, szCurrentLine))
    {
        if (szCurrentLine == "*Aisle Information*")
        {
            bAisle = true;
            bAisleName = true;
            bEmp = false;
        }
        else if (szCurrentLine == "*Employee Information*")
        {
            bAisle = false;
            bAisleName = false;
            bEmp = true;
        }
        else if (szCurrentLine == "############################")
        {
            iAisleIndex++;     // Move to the next aisle
        	bAisleName = true; // Prepare to read the next aisle name
        	bItem = false;     // Stop item reading for now
        	iItemIndex = 0;    // Reset item index for the next aisle
        }
        else if (bAisle == true)
        {
            if (bAisleName == true)
            {
                myStore.aislesArr[iAisleIndex].szName = szCurrentLine;
                bAisleName = false; // Switch to reading items
                bItem = true;
            }
            else if (bItem == true)
            {
                // Process items in the aisle
                istringstream stream(szCurrentLine);
                stream >> myStore.aislesArr[iAisleIndex].itemArr[iItemIndex].szName;
                stream >> myStore.aislesArr[iAisleIndex].itemArr[iItemIndex].dWholesale;
                stream >> myStore.aislesArr[iAisleIndex].itemArr[iItemIndex].dRegularPrice;
                stream >> myStore.aislesArr[iAisleIndex].itemArr[iItemIndex].dMembersPrice;

				for (char& c : myStore.aislesArr[iAisleIndex].itemArr[iItemIndex].szName)
                {
                    if (c == '_')
                    {
                        c = ' ';
                    }
                }
				
                iItemIndex++; // Increment item index
            }
        }
        else if (bEmp == true)
        {
            // Process employee information
            istringstream stream(szCurrentLine);
            stream >> myStore.employeesArr[iEmpIndex].szName;
            stream >> myStore.employeesArr[iEmpIndex].szID;
            stream >> myStore.employeesArr[iEmpIndex].dSalary;

			for (char& c : myStore.employeesArr[iEmpIndex].szName)
            {
                if (c == '_')
                {
                    c = ' ';
                }
            }

            myStore.iCurrentEmployees++;
            iEmpIndex++;
        }
    }
    fileInput.close();
}

/*********************************************************************
void displayMenu(string szMenuName, string szChoicesArr[], int iChoices)
Purpose:
    Function to display the menu choices of a provided menu
Parameters:
    I   string szMenuName       Title of the displayed menu
    I   string szChoicesArr     Menu choices to be displayed
    I   int iChoices            Number of menu choices    
Return Value:
    -
Notes:
    Menu options are displayed starting at 1
    The last menu option should always be displayed as -1
*********************************************************************/
void displayMenu(string szMenuName, string szChoicesArr[], int iChoices)
{
    cout << szMenuName << endl;
	cout << szBreakMessage;
	for(int i = 0; i < iChoices; i++)
	{
		if(i == iChoices-1)
		{
			cout << "-1. " << szChoicesArr[i] << endl;
		}
		else
		{
			cout << i+1 << ". " << szChoicesArr[i] << endl;
		}
	}
	cout << szBreakMessage;
}

/*********************************************************************
void displaySupermarketInfo(const Supermarket myStore)
Purpose:
    Function to display basic supermarket information
Parameters:
    I   Supermarket myStore   Populated Supermarket info   
Return Value:
    -
Notes:
    -
*********************************************************************/
void displaySupermarketInfo(const Supermarket myStore)
{
    cout << myStore.szName << "'s Information" << endl;
	cout << szBreakMessage;
	cout << "Hours: " << myStore.szStoreHours << endl;
	cout << "Membership fee: $" << myStore.dMembershipFee << endl;
	cout << "Total employees: " << myStore.iCurrentEmployees << endl;
	cout << szBreakMessage;
}

/*********************************************************************
void displayAisles(const Supermarket myStore)
Purpose:
    Function to display all aisles in the supermarket
Parameters:
    I   Supermarket myStore   Populated Supermarket info   
Return Value:
    -
Notes:
    Movies are displayed starting at 0
*********************************************************************/
void displayAisles(const Supermarket myStore)
{
    cout << myStore.szName << "'s Aisles" << endl;
	cout << szBreakMessage;
	for(int i = 0; i < MAX_AISLES; i++)
	{
		if(myStore.aislesArr[i].szName != "")
		{
			cout << myStore.aislesArr[i].szName << endl;
		}
	}
	cout << szBreakMessage;
}

/*********************************************************************
void displayItems(const Supermarket myStore, int iAisleIndex)
Purpose:
    Function to display all aisles in the supermarket
Parameters:
    I   Supermarket myStore     Populated Supermarket info   
    I   int iAisleIndex         Index of the aisle to display items
Return Value:
    -
Notes:
    Movies are displayed starting at 0
*********************************************************************/
void displayItems(const Supermarket myStore, int iAisleIndex)
{
    cout << myStore.aislesArr[iAisleIndex].szName << endl;
	cout << szBreakMessage;
	for(int i = 0; i < MAX_AISLES; i++)
	{
		if(myStore.aislesArr[iAisleIndex].itemArr[i].szName != "")
		{
			cout << endl << myStore.aislesArr[iAisleIndex].itemArr[i].szName << endl;
			cout << "Item Quantity: " << myStore.aislesArr[iAisleIndex].itemArr[i].iQuantity << endl;
			cout << "Regular Price: " << myStore.aislesArr[iAisleIndex].itemArr[i].dRegularPrice << endl;
			cout << "Member  Price: " << myStore.aislesArr[iAisleIndex].itemArr[i].dMembersPrice << endl;
		}
	}
	cout << szBreakMessage;
}

/***************************************************************
bool CheckIfReal(string filename, string search)
Purpose:
    To check if the customer is a member
Parameters:
    string szTargetName			Check name that is being looked for
Return Value:
    true or false if the customer is a member
Notes:
    -
***************************************************************/
bool CheckIfReal(Supermarket myStore, string szTargetName)
{
    for(int i = 0; i <= MAX_MEMBERS; i++)
	{
		if(myStore.membersArr[i].szName == szTargetName)
		{
			return true;
		}
	}
	return false;
}

/*********************************************************************
CustomerPurchase checkout(Supermarket& myStore)
Purpose:
    Function to handle customer buying store items
Parameters:
    I/O Supermarket& myStore   Populated Supermarket info 
Return Value:
    Populated CustomerPurchase if transaction was successful
    Empty CustomerPurchase if transaction was unsuccessful
Notes:
    -
*********************************************************************/
CustomerPurchase checkout(Supermarket& myStore)
{
    CustomerPurchase tempCust;
	double dSubCheckTotal = 0.0;
	int iQuantityBought, iTempAisles = 0, iAisleIndex;
	bool bCheckOut = false, bMember = false;
	string szItemIndex;

	/****************************************/

    cout << "Please enter your name: ";
    cin.ignore();
    getline(cin, tempCust.szName);

    //checks if customer is a member
    if(CheckIfReal(myStore, tempCust.szName) == true)
    {
        cout << "Welcome back " << tempCust.szName << endl << endl;
        bMember = true;
    }
    else
    {
        //if customer is not a member, they are prompted to become one
        char cMember;
        cout << "Would you like to become a member (y/n)? ";
        cin >> cMember;
        if(cMember == 'y' || cMember == 'Y')
        {
            //customer gets charged to become a member
            dSubCheckTotal += myStore.dMembershipFee;
			myStore.dTotalFunds += myStore.dMembershipFee;
			tempCust.bBoughtMembership = true;
            bMember = true;
			for(int i = 0; i <= MAX_MEMBERS; i++)
			{
				if(myStore.membersArr[i].szName == "")
				{
					myStore.membersArr[i].szName = tempCust.szName;
					break;
				}
			}
        }
        cout << endl;
    }

	/***************************************************************/

	do
	{
		//displays checkout menu
		cout << "Current cart total: " << dSubCheckTotal << endl;
		cout << endl;
		cout << myStore.szName << "'s Aisles" << endl;
		cout << szBreakMessage;
		for(int i = 0; i < MAX_AISLES; i++) 
		{
			if(myStore.aislesArr[i].szName != "")
			{
				cout << myStore.aislesArr[i].szName << endl;
				iTempAisles++;
			}
		}
		cout << szBreakMessage;
		cout << "Please enter aisle index (-1 to exit): ";
		cin >> iAisleIndex;
		cout << endl;

		/*******************************************************/

		if(iAisleIndex >= 0 && iAisleIndex <= iTempAisles) // checks if inputted number is a valid aisle
		{
			cout << myStore.aislesArr[iAisleIndex].szName << endl;
			cout << szBreakMessage;
			for(int k = 0; k < MAX_ITEMS; k++) // Displays all items
			{
				if(myStore.aislesArr[iAisleIndex].itemArr[k].szName != "") //checks the whole aisle, if there is something there, it prints it
				{
					cout << endl << myStore.aislesArr[iAisleIndex].itemArr[k].szName << endl;
					cout << "Item Quantity: " << myStore.aislesArr[iAisleIndex].itemArr[k].iQuantity << endl;
					cout << "Regular Price: " << myStore.aislesArr[iAisleIndex].itemArr[k].dRegularPrice << endl;
					cout << "Member  Price: " << myStore.aislesArr[iAisleIndex].itemArr[k].dMembersPrice << endl;
				}
			}
			cout << szBreakMessage;

			cout << "Enter item to buy: ";
			cin.ignore();
			getline(cin, szItemIndex);
			for (int i = 0; i <= MAX_AISLES; i++) // checks aisle for item
			{
				// checks for the item
    			if (myStore.aislesArr[iAisleIndex].itemArr[i].szName == szItemIndex)
    			{
					//checks if there is more than 0
					if(myStore.aislesArr[iAisleIndex].itemArr[i].iQuantity > 0)
					{
						cout << "Please enter valid quantity: ";
						cin >> iQuantityBought;
						myStore.aislesArr[iAisleIndex].itemArr[i].iQuantity -= iQuantityBought;
						if(bMember == true) //if user is a member, member price is used
						{
							dSubCheckTotal += (iQuantityBought * myStore.aislesArr[iAisleIndex].itemArr[i].dMembersPrice);
							myStore.dTotalFunds += ((iQuantityBought * myStore.aislesArr[iAisleIndex].itemArr[i].dMembersPrice) - (iQuantityBought * myStore.aislesArr[iAisleIndex].itemArr[i].dWholesale));
						}
						else //else, regular price is used
						{
							dSubCheckTotal += (iQuantityBought * myStore.aislesArr[iAisleIndex].itemArr[i].dRegularPrice);
							myStore.dTotalFunds += ((iQuantityBought * myStore.aislesArr[iAisleIndex].itemArr[i].dRegularPrice) - (iQuantityBought * myStore.aislesArr[iAisleIndex].itemArr[i].dWholesale));
						}
						tempCust.iNumberItems += iQuantityBought;
						break;
					}
					else //else the item is out of stock
					{
						cout << szItemIndex << " out of stock\n" << endl;
						break;
					}
				}
				else if (i >= MAX_AISLES) //once all aisles are checked, it shows if item is valid
				{
					cout << "No item " << szItemIndex << " found" << endl;
				}
			}
		}
		else if(iAisleIndex == -1) //adds tax to total and adds total to tempCust then exits
		{
			cout << "Your total is $" << dSubCheckTotal * (1 + dSALES_TAX) << endl;
			tempCust.dPurchaseCost = dSubCheckTotal;
			bCheckOut = true;
		}
		else
		{
			cout << "Please choose a valid aisle." << endl;
		}
	}while(bCheckOut == false);
	
    return tempCust;
}

/*********************************************************************
void displayTotalFunds(const Supermarket& myStore)
Purpose:
    Function to display the total funds of the store
Parameters:
    I   Supermarket myStore   Populated Supermarket info   
Return Value:
    -
Notes:
    This function should only be called by an employee
*********************************************************************/
void displayTotalFunds(const Supermarket& myStore)
{
	//displays total funds
    cout << myStore.szName << "'s Total Funds" << endl;
	cout << szBreakMessage;
	cout << "Funds: $" << myStore.dTotalFunds << endl;
	cout << szBreakMessage;
}

/*********************************************************************
double calculateTotalSales(const Supermarket& myStore)
Purpose:
    Function to calculate the total sales of the supermarket
Parameters:
    I   Supermarket myStore   Populated Supermarket info   
Return Value:
    Total sales
Notes:
    This function should only be called by an employee
*********************************************************************/
double calculateTotalSales(const Supermarket& myStore)
{
	double dTotalSales = 0;

	for(int i = 0; i < MAX_CUSTOMERS; i++)
	{
		dTotalSales += myStore.customersArr[i].dPurchaseCost;
	}
    return dTotalSales;
}

/*********************************************************************
bool payEmployees(Supermarket& myStore)
Purpose:
    Function to pay all employees
Parameters:
    I/O   Supermarket myStore   Populated Supermarket info   
Return Value:
    True if funds were successfully subtracted, else false. 
Notes:
    This function should only be called by an employee
*********************************************************************/
bool payEmployees(Supermarket& myStore)
{
	//Varible to store total pay
	double dSumPay = 0;

	//finds total pay of all employees
    for(int i = 0; i < MAX_EMPLOYEES; i++)
	{
		if(myStore.employeesArr[i].szName != "")
		{
			dSumPay += myStore.employeesArr[i].dSalary;
		}
	}

	//checks to make sure store has enough funds, if there are enough funds, employees are payed
	if(dSumPay >= myStore.dTotalFunds)
	{
		return false;
	}
	else
	{
		myStore.dTotalFunds -= dSumPay;
		return true;
	}
}

/*********************************************************************
void clearMembers(Supermarket& myStore);
Purpose:
    Function to clear the members from the supermarket
Parameters:
    I/O   Supermarket myStore   Populated Supermarket info   
Return Value:
    -
Notes:
    A cleared member should set back to a default state.
    This function should only be called by an employee.
    This does not clear the stored text file.
*********************************************************************/
void clearMembers(Supermarket& myStore)
{
	//finds and clears every member, skipping over already cleard members
	for(int i = 0; i <= MAX_MEMBERS; i++)
	{
		if(myStore.membersArr[i].szName != "")
		{
			myStore.membersArr[i].szName = "";
		}
	}
	
	//Informs the user members have been cleared
	cout << "Members Cleard" << endl;
}

/*********************************************************************
File name: supermarket_simulator_program_3.cpp
Author: 
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