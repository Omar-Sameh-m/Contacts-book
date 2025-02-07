#include <bits/stdc++.h>
using namespace std;

template <typename T>
class DynamicArray
{
private:
    T *data;
    int capacity;
    int size;

public:
    DynamicArray() : size(0), capacity(10)
    {
        data = new T[capacity];
    }

    ~DynamicArray()
    {
        delete[] data;
    }

    void add(const T &element) // append
    {
        if (size == capacity)
        {
            capacity *= 2;
            T *newData = new T[capacity];
            for (int i = 0; i < size; ++i)
            {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = element;
    }

    T &operator[](int index) // opertator oveloading
    {
        return data[index];
    }

    const T &operator[](int index) const // opertator oveloading
    {
        return data[index];
    }

    int getSize() const
    {
        return size;
    }

    void reverse()
    {
        for (int i = 0; i < size / 2; ++i)
        {
            swap(data[i], data[size - i - 1]);
        }
    }

    void remove(int index)
    {
        if (index >= 0 && index < size)
        {
            for (int i = index; i < size - 1; ++i)
            {
                data[i] = data[i + 1];
            }
            size--;
        }
    }

    void clear()
    {
        size = 0;
    }
};

class Person
{
private:
    string firstName;
    string lastName;
    string phone;
    bool isFavorite;

public:
    Person() : firstName(""), lastName(""), phone(""), isFavorite(false) {}

    Person(string fName, string lName, string phoneNum, bool fav = false)
        : firstName(fName), lastName(lName), phone(phoneNum), isFavorite(fav) {}

    string getLastName() const
    {
        return lastName;
    }

    friend ostream &operator<<(ostream &os, const Person &p) // print
    {
        os << setw(8) << left << p.firstName << " "
           << setw(8) << left << p.lastName
           << " | Phone: " << setw(8) << left << p.phone;
        return os;
    }
};

class Address
{
private:
    string street;
    string city;
    string zipCode;

public:
    Address(string s = "", string c = "", string z = "")
        : street(s), city(c), zipCode(z) {}

    friend ostream &operator<<(ostream &os, const Address &a)
    {
        os << setw(8) << left << a.street << ", "
           << setw(8) << left << a.city << ", "
           << setw(8) << left << a.zipCode;
        return os;
    }
};

class Contact
{
private:
    Person person;
    Address address;
    string classification;

public:
    Contact(const Person &p = Person(), const Address &a = Address(), string classif = "")
        : person(p), address(a), classification(classif) {}

    string getClassification() const
    {
        return classification;
    }

    Person getPerson() const
    {
        return person;
    }

    friend ostream &operator<<(ostream &os, const Contact &c)
    {
        os << c.person << " | " << setw(8) << left << c.address
           << " | Classification: " << setw(8) << left << c.classification;
        return os;
    }
};

void displayMenu()
{
    cout << "\n================ Contacts Book Menu: ================\n";
    cout << "1. Add a new Contact\n";
    cout << "2. Search by Last Name\n";
    cout << "3. Search by Classification\n";
    cout << "4. Print All Contacts\n";
    cout << "5. Print Favorite Contacts\n";
    cout << "6. Save to File\n";
    cout << "7. Load from File\n";
    cout << "8. Delete Contact\n";
    cout << "9. Update Contact Information\n";
    cout << "10. Share contact with other\n";
    cout << "11. Reverse contacts book\n";
    cout << "12. Exit\n";
    cout << "=====================================================\n";
}

void saveToFile(const DynamicArray<Contact> &contacts, const string &filename)
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cerr << "Error opening file for writing.\n";
        return;
    }
    for (int i = 0; i < contacts.getSize(); ++i)
    {
        outFile << contacts[i] << "\n";
    }
    cout << "Contacts saved to " << filename << "\n";
}

// Load contacts from a file (basic)
void loadFromFile(DynamicArray<Contact> &contacts, const string &filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cerr << "Error opening file for reading.\n";
        return;
    }

    contacts.clear();
    string firstName, lastName, phone, street, city, zipCode, classification;
    while (inFile >> firstName >> lastName >> phone >> street >> city >> zipCode >> classification)
    {
        Person p(firstName, lastName, phone);
        Address a(street, city, zipCode);
        contacts.add(Contact(p, a, classification));
    }
    cout << "Contacts loaded from " << filename << "\n";
}

void searchByLastName(const DynamicArray<Contact> &contacts, const string &lastName) // key
{
    bool found = false; // flag
    for (int i = 0; i < contacts.getSize(); ++i)
    {
        if (contacts[i].getPerson().getLastName() == lastName)
        {
            cout << contacts[i] << "\n";
            found = true;
        }
    }
    if (!found)
    {
        cout << "No contacts found with the last name " << lastName << "\n";
    }
}

int main()
{
    DynamicArray<Contact> contacts;
    bool running = true;

    while (running)
    {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Add new contact
            string fName, lName, phone, street, city, zip, classification;
            cout << "Enter First Name: ";
            cin >> fName;
            cout << "Enter Last Name: ";
            cin >> lName;
            cout << "Enter Phone: ";
            cin >> phone;
            cout << "Enter Street: ";
            cin >> street;
            cout << "Enter City: ";
            cin >> city;
            cout << "Enter Zip Code: ";
            cin >> zip;
            cout << "Enter Classification (friend/work/family/other): ";
            cin >> classification;
            contacts.add(Contact(Person(fName, lName, phone), Address(street, city, zip), classification));
            break;
        }
        case 2:
        {
            // Search by Last Name
            string lName;
            cout << "Enter Last Name: ";
            cin >> lName;
            searchByLastName(contacts, lName);
            break;
        }
        case 4:
        {
            // Print all contacts
            for (int i = 0; i < contacts.getSize(); ++i)
            {
                cout << contacts[i] << "\n";
            }
            break;
        }
        case 6:
        {

            saveToFile(contacts, "contacts.txt");
            break;
        }
        case 7:
        {

            loadFromFile(contacts, "contacts.txt");
            break;
        }
        case 11:
        {
            // Reverse contacts
            contacts.reverse();
            cout << "Contacts reversed.\n";
            break;
        }
        case 12:
            running = false;
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
