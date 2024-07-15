#include <iostream>


using namespace std;

class Address
{
    public:
        string location;
        string city;
        long phone;

        Address() 
        {

        }

        Address(string location, string city, long phone)
        {
            this->location = location;
            this->city = city;
            this->phone = phone;
        }
};

class Contact
{
    public:
        int id;
        string name;
        string email;
        long phone;
        Address address;

        Contact()
        {

        }
        Contact(string name, string email, long phone, Address address)
        {
            this->name = name;
            this->email = email;
            this->phone = phone;
            this->address = address;
        }
};

class Directory
{
    public:
        virtual int add(Contact contact) = 0;
        virtual void update(Contact contact) = 0;
        virtual Contact get(int id) = 0;
        virtual int* search(string name) = 0;
        virtual int search(long phone) = 0;
};

class SimpleDirectory: public Directory
{
    private:
        Contact entries[10];
    public:
        SimpleDirectory()
        {

        }

        int add(Contact contact) {
            return 0;
        }
        void update(Contact contact) {

        }
        Contact get(int id) {
            return Contact();
        }
        int* search(string name) {
            return NULL;
        }
        int search(long phone) {
            return -1;
        }
};

class DirectoryFactory
{
    public:
        static Directory* getDirectory(){
            return new SimpleDirectory();
        }
};
int main()
{
    Directory* directory = DirectoryFactory::getDirectory();
    Address address = Address("X", "ABC", 560016);
    Contact contact = Contact("PQR", "def@ghi.com", 855864587, address);
    int id = directory->add(contact);
    cout << "added contact with id: " << id << endl;
}