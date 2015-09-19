#ifndef MAINTAINBOOKDETAILS_H
#define MAINTAINBOOKDETAILS_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct bookdetails {
    int itemID;
    string authors;
    string releaseDate;
    string listPrice;
    string publisher;
};

enum attributes {
    ITEMID = 0,
    AUTHORS = 1,
    RELEASEDATE = 2,
    LISTPRICE = 3,
    PUBLISHER = 4
};

class MaintainBookDetails
{
    public:
        MaintainBookDetails();
        bool add_item(bookdetails *bdetails);
        void display_item(int itemID);
        bool readData(char *fname);
        virtual ~MaintainBookDetails();
    protected:
    private:
};

#endif // MAINTAINBOOKDETAILS_H
