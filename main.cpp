#include <iostream>
#include <fstream>
#include <string>
#include "MaintainBookDetails.h"
#include  "basefilecreation.h"
using namespace std;

int main()
{
    MaintainBookDetails *MBookDet = MaintainBookDetails::instance();
    int index;

    do {
    cout<<endl<<"Large Scale Distributed Systems"<<endl;
    cout<<"*******************************"<<endl;
    cout<<"1. Parsing CSV file\n";
    cout<<"2. Get Item Details\n";
    cout<<"Press any key to continue";
    cin>>index;
    if(index > 2)
        cout<<"Invalid Entry!!! Try Again!!!\n";

    switch(index) {
    case 1: {
        cout<<"Parsing Started\n";
        string filePath = "D:/share/";
        vector<string> fileNames = MBookDet->filesnameswithinfolder(filePath);
        for (std::vector<string>::iterator it = fileNames.begin(); it != fileNames.end(); ++it) {
            string appendFilePath = "D:/share/";
            appendFilePath += *it;
            MBookDet->readData(appendFilePath);
        }
        //MBookDet->readData("D:/share/file_1.txt");
        cout<<"Parsing Completed";
        break;
    }
    case 2: {
        int itemid;
        cout<<"Display Items\n";
        cout<<"*************\n";
        cout<<"Enter your itemID:\n";
        cin>>itemid;
        MBookDet->display_item(itemid);
        break;
    }
    default: {
        cout<<endl<<"Large Scale Distributed Systems"<<endl;
        cout<<"*******************************"<<endl;
        cout<<"1. Parsing CSV file\n";
        cout<<"2. Get Item Details\n";
        cout<<"Press any key to continue:";
        cin>>index;
        if(index > 2)
            cout<<"Invalid Entry!!! Try Again!!!\n";
        break;
    }
    }
    } while(index < 2);
    return 0;
}
