#ifndef MAINTAINBOOKDETAILS_H
#define MAINTAINBOOKDETAILS_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define MAX_RECORDS 50

struct bookdetails {
    int itemID;
    string authors;
    string title;
    string releaseDate;
    string listPrice;
    string publisher;
};

enum attributes {
    ITEMID = 0,
    AUTHORS = 1,
    TITLE = 2,
    RELEASEDATE = 3,
    LISTPRICE = 4,
    PUBLISHER = 5
};

enum FILEOPEN
{
    READ = 0,
    WRITE = 1
};

class MaintainBookDetails
{
    public:
        MaintainBookDetails();
        bool add_item();
        void display_item(int itemID);
        void updateRecord(ofstream& file, int *itemID, bookdetails &bdet);
        bool createRecord(bookdetails &bdet);
        void parsing(bookdetails *bdetails, string line);
        bool readData(string fname);
        void* openfile(char *fname, enum FILEOPEN);
        vector<string> split(string str, char delimiter);
        vector<string> filesnameswithinfolder(string folder);
        string getFileName(int id);
        virtual ~MaintainBookDetails();

        static MaintainBookDetails *instance() {
            if (!MBookDet_instance)
                MBookDet_instance = new MaintainBookDetails;
                return MBookDet_instance;
        }
    protected:
    private:
        static MaintainBookDetails *MBookDet_instance;
};

#endif // MAINTAINBOOKDETAILS_H
