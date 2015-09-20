#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <list>
#include <cctype>
using namespace std;
#include "MaintainBookDetails.h"

std::map<int,string> bookmap;

MaintainBookDetails *MaintainBookDetails::MBookDet_instance = 0;

MaintainBookDetails::MaintainBookDetails()
{
    //ctor

}


bool MaintainBookDetails::add_item() {
    stringstream fileNameGen;
    for (std::map<int,string>::iterator it=bookmap.begin(); it!=bookmap.end(); ++it) {
        ofstream basefile(MaintainBookDetails::getFileName(it->first).c_str(), std::ios_base::app);
        if (basefile.is_open()) {
            cout<<"file\t"<<it->second<<endl;
           /* bookdetails bdet;
            string line = it->second;
            string update;
            char *parsedata = NULL;
            while(basefile >> line) {
                parsedata = strtok ((char *)line.c_str(),",");
                if (atoi(parsedata) == *itemID)  {
                    MaintainBookDetails::parsing(&bdet, line);
                    update = bdet.itemID + "," + bdet.authors + "," + bdet.title + "," + bdet.releaseDate + "," + bdet.listPrice + "," + bdet.publisher;
                    line == update;
                }
                line += "\n";
                basefile << line;
            }*/
            //MaintainBookDetails::parsing(&bdet, line);
            //MaintainBookDetails::updateRecord(basefile,*it->first,bdet);
            basefile << it->second<<endl;
        } else {
            cout<<it->first;
            cout<<"Unable to do datapush";
        }
        basefile.close();
    }
    return true;
}

bool MaintainBookDetails::readData(string fname) {
    string line;
  if(fname.c_str() == NULL)
    return false;
    cout<<"filename"<<fname.c_str()<<endl;
  ifstream csvfile(fname.c_str());
  if (csvfile.is_open()) {
    while (getline(csvfile,line)) {
        bookdetails bdetails;
        char *parsedata;
        char *attribute;
        int i = 0;
        int index = 0;
        parsedata = strtok ((char *)line.c_str(),",");
        while (parsedata != NULL) {
            if(i == 0) {
                    bdetails.itemID = atoi(parsedata);
            } else if (i == 1) {
                attribute = parsedata;
                if(strcmp(attribute, "authors") == 0) {
                    index = AUTHORS;
                } else if(strcmp(attribute, "title") == 0) {
                    index = TITLE;
                } else if(strcmp(attribute, "release date") == 0) {
                    index = RELEASEDATE;
                } else if(strcmp(attribute, "list price") == 0) {
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
                case TITLE: {
                    bdetails.title = parsedata;
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
            }
            ++i;
            parsedata = strtok (NULL, ",");
        }
        if(MaintainBookDetails::createRecord(bdetails))
            cout<<"Successfully updated itemid \t"<<bdetails.itemID<<endl;
        else
            cout<<"Failed to update the record";
    }
    csvfile.close();
    MaintainBookDetails::add_item();
  }
  else {
    cout << "Unable to open file"<<fname.c_str()<<endl;
    return false;
  }
  return true;
}

vector<string> MaintainBookDetails::filesnameswithinfolder(string folder)
{
    vector<string> fnames;
    char search_path[200];
    sprintf(search_path, "%s/*.*", folder.c_str());
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path, &fd);
    if(hFind != INVALID_HANDLE_VALUE) {
        do {
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
                fnames.push_back(fd.cFileName);
            }
        }while(::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return fnames;
}

/*void MaintainBookDetails::updateRecord(ofstream& file, int *itemID, bookdetails &bdet) {
    string line;
    string update;
    char *parsedata = NULL;
    while(file >> line) {
        parsedata = strtok ((char *)line.c_str(),",");
        if (atoi(parsedata) == *itemID)  {
            update = bdet.itemID + "," + bdet.authors + "," + bdet.title + "," + bdet.releaseDate + "," + bdet.listPrice + "," + bdet.publisher;
            line == update;
        }
        line += "\n";
        file << line;
    }
}*/

bool MaintainBookDetails::createRecord(bookdetails &bdet) {
stringstream update;
std::map<int,string>::iterator it;
 bookdetails tmpbookdetails;
 update.str("");
  update << bdet.itemID << "," << bdet.authors << "," << bdet.title << "," << bdet.releaseDate << "," << bdet.listPrice << "," << bdet.publisher;

  std::pair<std::map<int,string>::iterator,bool> ret;
  ret = bookmap.insert ( std::pair<int,string>(bdet.itemID, update.str()) );
  if (ret.second == false) {
    MaintainBookDetails::parsing(&tmpbookdetails, ret.first->second);
        if(tmpbookdetails.itemID == bdet.itemID) {
            if((tmpbookdetails.authors.size() == 0) || !(strcmp(tmpbookdetails.authors.c_str(), bdet.authors.c_str())))
               tmpbookdetails.authors = bdet.authors;
            else if((tmpbookdetails.title.size() == 0) || !(strcmp(tmpbookdetails.title.c_str(), bdet.title.c_str())))
               tmpbookdetails.title = bdet.title;
            else if ((tmpbookdetails.releaseDate.size() == 0) || !(strcmp(tmpbookdetails.releaseDate.c_str(), bdet.releaseDate.c_str())))
               tmpbookdetails.releaseDate = bdet.releaseDate;
            else if ((tmpbookdetails.listPrice.size() == 0) || !(strcmp(tmpbookdetails.listPrice.c_str(), bdet.listPrice.c_str())))
               tmpbookdetails.listPrice = bdet.listPrice;
            else if ((tmpbookdetails.publisher.size() == 0) || !(strcmp(tmpbookdetails.publisher.c_str(), bdet.publisher.c_str())))
               tmpbookdetails.publisher = bdet.publisher;
        }
        update.str("");
        update << tmpbookdetails.itemID << "," << tmpbookdetails.authors << "," << tmpbookdetails.title << "," << tmpbookdetails.releaseDate << "," << tmpbookdetails.listPrice << "," << tmpbookdetails.publisher;
        cout<<"update"<<update.str()<<endl;
        if (!bookmap.insert (std::make_pair(bdet.itemID, update.str())).second) {
            bookmap[bdet.itemID] = update.str();
        }
  }
  return true;
}

vector<string> MaintainBookDetails::split(string str, char delimiter) {
  vector<string> tmp;
  stringstream ss(str); // Turn the string into a stream.
  string token;

  while(getline(ss, token, delimiter)) {
    tmp.push_back(token);
  }

  return tmp;
}

void MaintainBookDetails::parsing(bookdetails *bdetails, string line) {
   if(line.empty())
        return;

   int i = 0;
    string delimiter = ",";
    vector<string> token = MaintainBookDetails::split(line, ',');

    for(i = 0; i < (signed int)token.size(); ++i)
        switch(i) {
        case ITEMID: {
            bdetails->itemID = atoi(token[i].c_str());;
            break;
        }
        case AUTHORS: {
            bdetails->authors = token[i];
            break;
        }
        case TITLE: {
            bdetails->title = token[i];
            break;
        }
        case RELEASEDATE: {
            bdetails->releaseDate = token[i];
            break;
        }
        case LISTPRICE: {
            bdetails->listPrice = token[i];
            break;
        }
        case PUBLISHER: {
            bdetails->publisher = token[i];
            break;
        }
        default:
            break;
   }
}

string MaintainBookDetails::getFileName(int id) {
    stringstream fileNameGen;
    int range;
    range = id/MAX_RECORDS;
    int start = (range * 50) + 1;
    int endrange = start + 50;
    fileNameGen << "D:/share/pushdata_" << start << "_" << endrange << ".txt";
    return fileNameGen.str().c_str();
}

void MaintainBookDetails::display_item(int getItemID) {
    ifstream csvfile(MaintainBookDetails::getFileName(getItemID).c_str());
    string delimiter = ",";
    string line;
    bool flag = false;
    vector<string> token;
    if (csvfile.is_open()) {
        while (getline(csvfile,line)) {
            token = MaintainBookDetails::split(line, ',');
            if(getItemID == atoi(token[0].c_str())) {
                    flag = true;
            for(int i=0; i<(signed int)token.size(); ++i) {
                    switch(i) {
                    case ITEMID: {
                        cout<<"ItemID:\t"<<token[i]<<endl;
                        break;
                    }
                    case AUTHORS: {
                        cout<<"Author:\t"<<token[i]<<endl;
                        break;
                    }
                    case TITLE: {
                        cout<<"Title:\t"<<token[i]<<endl;
                        break;
                    }
                    case RELEASEDATE: {
                        cout<<"Release Date:"<<token[i]<<endl;
                        break;
                    }
                    case LISTPRICE: {
                        cout<<"List Price:"<<token[i]<<endl;
                        break;
                    }
                    case PUBLISHER: {
                        cout<<"Publisher:"<<token[i]<<endl;
                        break;
                    }
                    default:
                        break;
                    }
                }
            }
        }
        csvfile.close();
        if(flag == false)
            cout<<"No such record\n";
    } else
        cout<<"Unable to open file";;
}

MaintainBookDetails::~MaintainBookDetails()
{
    //dtor
}
