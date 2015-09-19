#include <iostream>
#include "MaintainBookDetails.h"
#include  "basefilecreation.h"
using namespace std;

int main()
{
    MaintainBookDetails *MBookDet = new MaintainBookDetails;
    MBookDet->readData("file_1.csv");
    return 0;
}
