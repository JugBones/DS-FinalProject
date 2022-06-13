#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class book
{
    public:
    string title;
    string author;
    string publisher;
    int year;
    string binusid;
    book* next;
    book(string, string, string, int, string, book*);
};

book::book(string tempTitle, string tempAuthor, string tempPublisher, int tempYear, string tempBinusid, book* tempNext)
{
    title=tempTitle;
    author=tempAuthor;
    publisher=tempPublisher;
    year=tempYear;
    binusid=tempBinusid;
    next=tempNext;
}

typedef book* bookPtr;

void getline(istream &stream, string &str, char delimiter)
{    char temp[500];

    stream.get(temp, 500, delimiter);
    stream.ignore(500, delimiter);
    str = temp;
}

void getline(istream &stream, int &num, char delimiter)
{    int temp;

    stream >> temp;
    stream.ignore(500, delimiter);
    num= temp;
}

void readFile(bookPtr &root);
void insert (bookPtr &root);
void delTitle(bookPtr &root);
bookPtr locateNode(bookPtr temp, string titl);
void delBinusid(bookPtr &root);
bookPtr locateNodeBinusid(bookPtr temp, string isb);
void searchBnusid(bookPtr temp);
void printList(bookPtr temp);
void printAuthor(bookPtr temp);
void saveFile(bookPtr temp);
int countNodes(bookPtr temp);


void readFile(bookPtr &root)
{
    int numBooks, yea;
    string titl, aut, pub, bin_id;
    ifstream infile ("books.txt", ios::in);
    infile >> numBooks;
    infile.ignore(500,'\n');
    for (int count = 0; count < numBooks; count++)
    {
        getline(infile, titl, '\n');
        getline(infile, aut, '\n');
        getline(infile, pub, '\n');
        getline(infile,yea, '\n');
        getline(infile, bin_id, '\n');

        root = new book (titl, aut, pub, yea, bin_id, root);
    }
}

void insert (bookPtr &root)
{
    string titl, aut, pub, bin_id;
    int yea;

    cout << "Title:\t\t\t";
    cin.ignore(500,'\n');
    getline(cin, titl, '\n');
    cout << "Author:\t\t\t";
    getline(cin, aut, '\n');
    cout << "Publisher:\t\t";
    getline(cin,pub, '\n');
    cout << "Year:\t\t\t";
    getline(cin,yea, '\n');
    cout << "Binusian ID:\t\t";
    getline(cin, bin_id, '\n');

    root = new book (titl, aut, pub, yea, bin_id, root);
}

void delTitle(bookPtr &root)
{
    string titl;

    cout << "Book Title:\t\t\t";
    cin.ignore(500,'\n');
    getline(cin, titl, '\n');

    bookPtr p = locateNode(root, titl);

    if (p == NULL)
        cout << "\nDeletion cannot be done.\n\n";
    else if (root == p)
        root = p->next;
    else
    {
        bookPtr q = root;
        while (q->next != p)
            q = q->next;
        q->next = p->next;
    }
    delete p;
}

bookPtr locateNode(bookPtr temp, string titl)
{
    while (temp != NULL)
    {
        if (temp->title == titl)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void delBinusid(bookPtr &root)
{
    string bin_id;

    cout << "Binusian ID:\t\t\t";
    cin.ignore(500,'\n');
    getline(cin, bin_id, '\n');

    bookPtr p = locateNodeBinusid(root, bin_id);

    if (p == NULL)
        cout << "\nDeletion cannot be done.\n\n";
    else if (root == p)
        root = p->next;
    else
    {
        bookPtr q = root;
        while (q->next != p)
            q = q->next;
        q->next = p->next;
    }
    delete p;
}

bookPtr locateNodeBinusid(bookPtr temp, string bin_id)
{
    while (temp != NULL)
    {
        if (temp->binusid == bin_id)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void searchBinusid(bookPtr temp)
{
    string bin_id;

    cout << "Binusian ID:\t\t\t";
    cin.ignore(500,'\n');
    getline(cin, bin_id, '\n');

    while (temp != NULL)
    {
        if (bin_id == temp->binusid)
        {
            cout << "Book:" << "\n\n";
            cout << "title : "<<temp->title << "\n";
            cout << "author : "<< temp->author << "\n";
            cout << "publisher : "<< temp->publisher << "\n";
            cout << "year : "<< temp->year << "\n";
            cout << "Binusian ID : "<< temp->binusid << "\n\n";
        }
        temp = temp->next;
    }
    cout << "\n";
}

void printList(bookPtr temp)
{
    while (temp != NULL)
    {
        cout << "Book:" << "\n\n";
        cout << "Title : " << temp->title << "\n";
        cout << "Author : " << temp->author << "\n";
        cout << "Publisher : " << temp->publisher << "\n";
        cout << "Year of book : " << temp->year << "\n";
        cout << "Binusian ID : " << temp->binusid << "\n\n";
        temp = temp->next;
    }
    cout << "\n";
}

void printAuthor(bookPtr temp)
{
    string aut;

    cout << "Author name:\t\t\t";
    cin.ignore(500,'\n');
    getline(cin, aut, '\n');

    while (temp != NULL)
    {
        if (temp->author == aut)
        {
            cout << temp->title << "\n";
            cout << temp->author << "\n";
            cout << temp->publisher << "\n";
            cout << temp->year << "\n";
            cout << temp->binusid << "\n\n";
        }
        temp = temp->next;
    }
    cout << "\n";
}

void saveFile(bookPtr temp)
{
    int count = countNodes(temp);
    ofstream outFile("saved.txt",ios::out);

    outFile << count << "\n";
    while (temp != NULL)
    {
        outFile << temp->title << "\n";
        outFile << temp->author << "\n";
        outFile << temp->publisher << "\n";
        outFile << temp->year << "\n";
        outFile << temp->binusid << "\n";
        temp = temp->next;
    }
    cout << "\n";
}

int countNodes(bookPtr temp)
{
    int countB = 0;
    while (temp != NULL)
    {
        countB++;
        temp = temp->next;
    }
    return countB;
}
int main()
{
    int choice;
    bookPtr root = NULL;
    readFile(root);

    do
    {
        cout << "\t\t<<=========================>>";
        cout << "\n\t\t>>LIBRARY MANAGEMENT SYSTEM<<";
        cout << "\n\t\t<<=========================>>";
        cout << "\n\nMenu: Select your option\n\n";
        cout << "(1) Add a book to the list\n";
        cout << "(2) Delete a book based on Title\n";
        cout << "(3) Delete a book based on Binusian ID\n";
        cout << "(4) Search for a book by Binusian ID.\n";
        cout << "(5) List all books.\n";
        cout << "(6) List all books by an author.\n";
        cout << "(7) Quit.\n\n";
        cout << "Enter your choice ---> ";

        cin >> choice;

        if (1 <= choice && choice <= 6)
        {
            switch (choice)
            {
            case 1:
                insert(root);
                break;
            case 2:
                delTitle(root);
                break;
            case 3:
                delBinusid(root);
                break;
            case 4:
                searchBinusid(root);
                break;
            case 5:
                printList(root);
                break;
            case 6:
                printAuthor(root);
                break;
            default:
                cout << "Invalid choice. Please input the valid number. Enter again.\n\n";
                break;
            }
        }
    }
    while (choice != 7);
    saveFile(root);
    return 0;
}
