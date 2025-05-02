#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include "structs.h"

using namespace std;

const int MAX_AISLES = 40, MAX_MEMBERS = 200,MAX_EMPLOYEES = 50, MAX_CUSTOMERS = 200, MAX_ITEMS = 100;
string szBreakMessage = "*****************************\n";
double dSALES_TAX = 0.08;

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
    
	cout << "Type exit bypass file input.\n";
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
                bFileCheck = true;
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