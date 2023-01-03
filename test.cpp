#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <iterator>

using namespace std;
#define republican "republican.txt"
#define democrat "democrat.txt"
#define independent "independent.txt"
#define other "other.txt"

int main(){
    ifstream tFile(republican);
    string line;
    int numLines;
    vector<string> name;
    while(getline(tFile, line)){
        if("Make it easier to apply for assistance." == line){
            name.push_back(line);
        }
    }
    cout<<size(name)<<endl;
    /*tFile.close();
    cout<<size(name)<<endl;
    cout<<numOfParty<<endl;*/

}