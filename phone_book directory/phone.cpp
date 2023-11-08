#include <iostream>
#include <fstream>
#include <string>
#include<windows.h>

using namespace std;

struct node
{
    string name, number, email;
    node* next;
};

node* head = NULL, * newnode, * temp;
int len = 0;

void C_node()
{
    newnode = new node;
    cout << "Enter Name: ";
    cin >> newnode->name;
    cout << "Enter Number: ";
    cin >> newnode->number;
    cout << "Enter Email: ";
    cin >> newnode->email;
    newnode->next = NULL;
    if (head == NULL)
    {
        head = newnode;
        temp = newnode;
    }
    else
    {
        temp->next = newnode;
        temp = newnode;
    }
    len++;
}

void display()
{
    if (head == NULL)
    {
        cout << "Contact list is Empty" << endl;
    }
    else
    {
        node* trav = head;
        while (trav != NULL)
        {
            cout << "\n\t\t\tFull Name: " << trav->name << endl;
            cout << "\t\t\tPhone Number: " << trav->number << endl;
            cout << "\t\t\tEmail id: " <<trav->email << endl;
            trav = trav->next;
        }
        cout << "\nTotal contacts in the list = " << len << endl;
    }
}

void saveContactsToFile()
{
    ofstream file("contacts.txt");
    if (file.is_open())
    {
        node* current = head;
        while (current != NULL)
        {
            file << current->name << " " << current->number << " " << current->email << "\n";
            current = current->next;
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file for saving contacts." << endl;
    }
}

void loadContactsFromFile()
{
    ifstream file("contacts.txt");
    if (file.is_open())
    {
       
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
        len = 0; 

        
        string name, number, email;
        while (file >> name >> number >> email)
        {
            newnode = new node;
            newnode->name = name;
            newnode->number = number;
            newnode->email = email;
            newnode->next = NULL; 
            if (head == NULL)
            {
                head = newnode;
                temp = newnode;
            }
            else
            {
                temp->next = newnode;
                temp = newnode;
            }
            len++;
        }
        file.close();
    }
    else
    {
        cout << "No existing contacts file found." << endl;
    }
}

void displayContactsInAscendingOrder()
{
    if (head == NULL)
    {
        cout << "Contact list is Empty" << endl;
        return;
    }

    // Create an array to store the contacts
    node** contactArray = new node*[len];
    node* current = head;

    
    int index = 0;
    while (current != NULL)
    {
        contactArray[index] = current;
        current = current->next;
        index++;
    }

    // Sort the contacts by name (ascending order)
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (contactArray[j]->name > contactArray[j + 1]->name)
            {
              
                node* temp = contactArray[j];
                contactArray[j] = contactArray[j + 1];
                contactArray[j + 1] = temp;
            }
        }
    }

    // Display sorted contacts
    cout << "Contacts in ascending order by name:" << endl;
    for (int i = 0; i < len; i++)
    {
        cout << "\nFull Name: " << contactArray[i]->name << endl;
        cout << "Phone Number: " << contactArray[i]->number << endl;
        cout << "Email id: " << contactArray[i]->email << endl;
    }

  
    delete[] contactArray;
}

void search_contact_name ()
{
    node *search_node_by_name = head;
    string srch;
    int count = 1;
    cout<<"Enter your desired contact you want to search ";
    cin>>srch;
    bool found = false;
    if(head == NULL)
    {
        cout<<"\nList is Empty "<<endl;
    }
    else
    {
        while (search_node_by_name != NULL)
        {
            if(srch == search_node_by_name->name)
            {
                cout<<"\n\t\tFull name: "<<search_node_by_name->name<<endl;
                cout<<"\t\tPhone number: "<<search_node_by_name->number<<endl;
                cout<<"\t\tEmail id: "<<search_node_by_name->email<<endl;
                found =true;
                break;
            }
            search_node_by_name = search_node_by_name->next;
            count++;
        }
    }
    if(found == true)
    {

        cout<<"\t\tIndex of the Contact = "<<count<<endl;
    }
    else
    {
        cout<<"Desired contact not fount "<<endl;
    }
}

void searchContactByNumber()
{
    if (head == NULL)
    {
        cout << "Contact list is Empty" << endl;
        return;
    }

    string numberToSearch;
    cout << "Enter the phone number you want to search for: ";
    cin >> numberToSearch;

    node* current = head;
    bool found = false;
    int index = 1;

    while (current != NULL)
    {
        if (current->number == numberToSearch)
        {
            cout << "\nFull Name: " << current->name << endl;
            cout << "Phone Number: " << current->number << endl;
            cout << "Email id: " << current->email << endl;
            cout << "Index of the Contact = " << index << endl;
            found = true;
        }

        current = current->next;
        index++;
    }

    if (!found)
    {
        cout << "Contact with phone number '" << numberToSearch << "' not found" << endl;
    }
}


void deleteContactByName()
{
    if (head == NULL)
    {
        cout << "Contact list is Empty" << endl;
        return;
    }

    string nameToDelete;
    cout << "Enter the name of the contact you want to delete: ";
    cin >> nameToDelete;

    if (head->name == nameToDelete)
    {
        // If the contact to delete is the first one
        temp = head;
        head = head->next;
        delete temp;
        cout << "Contact with name '" << nameToDelete << "' has been deleted" << endl;
        len--;
        return;
    }
    else
    {
        node* prev = head;
        temp = head->next;
        while (temp != NULL)
        {
            if (temp->name == nameToDelete)
            {
                prev->next = temp->next;
                delete temp;
                cout << "Contact with name '" << nameToDelete << "' has been deleted" << endl;
                len--;
                return; // Contact found and deleted, exit the function
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Contact with name '" << nameToDelete << "' not found" << endl;
    }
}

void clear_all()
{
    if (head == NULL)
    {
        cout << "List is Empty" << endl;
    }
    else
    {
        temp = head;
        while (head != NULL)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
        len = 0; // Reset the contact count to zero
        cout << "\nALL contact list has been deleted" << endl;
      
        ofstream file("contacts.txt");
        file.close();
    }
}


void menu()
{
    cout << "\n\nEnter 1 to add contact" << endl;
    cout << "Enter 2 to display all contacts" << endl;
    cout << "Enter 3 to save contacts to a file" << endl;
    cout << "Enter 4 to display contacts in ascending order" << endl;
    cout << "Enter 5 to search contact by name" << endl;
    cout << "Enter 6 to search contact by number" << endl;
    cout << "Enter 7 to delete contact by name" << endl;
    cout << "Enter 8 to clear all contacts\n" << endl;
}

int main()
{
    int op;
    loadContactsFromFile(); 
    
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    
	
    
    
    while (true)
    {
        menu();
        cin >> op;
        switch (op)
        {
        case 1:
        	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
            C_node();
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case 2:
        	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
            display();
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case 3:
        	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
            saveContactsToFile();
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case 4:
        	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
            displayContactsInAscendingOrder();
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case 5:
        	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
            search_contact_name();
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case 6:
        	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        	searchContactByNumber();
        	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        	break;
        case 7:
        	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
            deleteContactByName();
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case 8:
        	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
            clear_all();
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        default:
        	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "Invalid Option" << endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        }
    }
    return 0;
}

