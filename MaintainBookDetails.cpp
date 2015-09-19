#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;
#include "MaintainBookDetails.h"


MaintainBookDetails::MaintainBookDetails()
{
    //ctor

}

bool MaintainBookDetails::add_item(bookdetails *bdetails) {
    if (bdetails == NULL)
        return false;

    ofstream basefile("D:/pushdata.csv");
    if (basefile.is_open()) {
        basefile <<bdetails->itemID<<","<<bdetails->authors<<","<<bdetails->releaseDate<<","<<bdetails->listPrice<<","<<bdetails->publisher;
        basefile.close();
    }
    return true;
}

/* bool MaintainBookDetails::openfile(FILE *fname) {
    if(fname == NULL)
        return false;
    fstream myfile("D:/pushdata.txt");
    return true;
} */

bool MaintainBookDetails::readData(char *fname) {
  string line;
  bookdetails bdetails;
  if(fname == NULL)
    return false;

  ifstream csvfile(fname, ifstream::in);
  if (csvfile.is_open()) {
    while (getline(csvfile,line)) {
        char *parsedata;
        char *attribute;
        int i = 0;
        int index = 0;
        parsedata = strtok ((char *)line.c_str(),",");
        while (parsedata != NULL) {
            if(i == 0) {
                stringstream itID;
                itID << parsedata;
                itID >> bdetails.itemID;
               // string::size_type sz;   // alias of size_t
                //bdetails.itemID = stoi (parsedata,&sz);
            } else if (i == 1) {
                attribute = parsedata;
                if(strcmp(attribute, "authors") == 0) {
                    index = AUTHORS;
                } else if(strcmp(attribute, "releaseDate") == 0) {
                    index = RELEASEDATE;
                } else if(strcmp(attribute, "listPrice") == 0) {
                    index = LISTPRICE;
                } else if(strcmp(attribute, "publisher") == 0) {
                    index = PUBLISHER;
                }
            } else if (i == 2) {
                switch(index) {
                case AUTHORS: {
                    bdetails.authors = parsedata;
                    break;
                }
                case RELEASEDATE: {
                    bdetails.releaseDate = parsedata;
                    break;
                }
                case LISTPRICE: {
                    bdetails.listPrice = parsedata;
                    break;
                }
                case PUBLISHER: {
                    bdetails.publisher = parsedata;
                    break;
                }
                default:
                    break;
            }
            parsedata = strtok (NULL, " ,.-");
        }
    }
    csvfile.close();
    if(MaintainBookDetails::add_item(&bdetails))
        cout<<"Successfully updated";
    else
        cout<<"Failed to update the record";
   }
  }
  else
    cout << "Unable to open file";
}

MaintainBookDetails::~MaintainBookDetails()
{
    //dtor
}
