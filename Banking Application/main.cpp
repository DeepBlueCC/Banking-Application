#include <iostream>
#include <iomanip>
#include "tinyxml2.h"
#include <string>

using namespace tinyxml2;
using namespace std;

void parser() 
{
	XMLDocument xmlDoc;
	char amountText[100];

	string bar;
	bar.assign(62, '-');
	bar += "\n";
	cout << '|' << setw(7) << "Acc No." << '|' << setw(12) << "Account Type" << '|' << setw(15)
		<< "Customer Name" << '|' << setw(10) << "Balance" << '|' << setw(12) << "Open Date" << endl;
	cout << bar;

	// Load the XML file into the xmlDoc instance
	xmlDoc.LoadFile("Accounts.xml");
	// Get root element
	XMLElement* pRootElement = xmlDoc.RootElement();

	if (pRootElement != NULL)
	{
		// Get 'Accounts' child
		XMLElement* pAccounts = pRootElement->FirstChildElement("Accounts");
		if (pAccounts != NULL)
		{	// Get 'Account' element
			XMLElement* pAccount = pAccounts->FirstChildElement("Account");
			while (pAccount)
			{	// Get 'Account no' 
				XMLElement* pAccountNo = pAccount->FirstChildElement("AccountNo");
					if (pAccountNo != NULL)
					{
						cout << '|' << setw(7) << pAccountNo->GetText();
					}
					// Get 'type'
					XMLElement* pType = pAccount->FirstChildElement("type");
					if (pType != NULL)
					{
						cout << '|' << setw(12) << pType->GetText();
					}
					// Get 'customer'
					XMLElement* name = pAccount->FirstChildElement("customer");
					if (name != NULL)
					{
						cout << '|' << setw(15) << name->GetText();
					}
					// Get 'balance'
					XMLElement* balance = pAccount->FirstChildElement("balance");
					if (balance != NULL)
					{
						strcpy_s(amountText, "$");
						strcat_s(amountText, balance->GetText());
						cout << '|' << setw(10) << amountText;
					}
					// Get 'openDate'
					XMLElement* openDate = pAccount->FirstChildElement("openDate");
					if (openDate != NULL)
					{
						cout << '|' << setw(12) << openDate->GetText() << '|';
					}
					cout << endl << bar;
					// Next account
					pAccount = pAccount->NextSiblingElement("Account");
			}
			cout << "\n";
		}

	}


}


void writer()
{
	XMLDocument xmlDoc;
	char amountText[100];
		char typeChar[100];

	// Load the XML file into the xmlDoc instance
	xmlDoc.LoadFile("Accounts.xml");
	// Get root element
	XMLElement* pRootElement = xmlDoc.RootElement();
	XMLElement* pAccounts = pRootElement->FirstChildElement("Accounts");
	// Create new element
	XMLNode* pRoot = xmlDoc.NewElement("Account");

	// Insert new element
	pAccounts->InsertEndChild(pRoot);
	XMLElement* pElement = xmlDoc.NewElement("AccountNo");
	pElement->SetText("3"); // Account no. 3

	pRoot->InsertEndChild(pElement);
	pElement = xmlDoc.NewElement("type");
	pElement->SetText("Checking");	// type checking

	pRoot->InsertEndChild(pElement);
	pElement = xmlDoc.NewElement("customer");
	pElement->SetText("Craig");		// customer Craig

	pRoot->InsertEndChild(pElement);
	pElement = xmlDoc.NewElement("balance");
	pElement->SetText("3000");		// balance 3000

	pRoot->InsertEndChild(pElement);
	pElement = xmlDoc.NewElement("openDate");
	pElement->SetText("27/01/2023"); // open date 27/01/2023

	pRoot->InsertEndChild(pElement);
	xmlDoc.SaveFile("Accounts.xml");

}


int main()
{
	parser();
	writer();	// Write Craig's new account
	return 0;
}


