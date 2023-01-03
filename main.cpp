#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
#define republican "republican.txt"
#define democrat "democrat.txt"
#define independent "independent.txt"
#define other "other.txt"

vector<string> responses;

string lower(string toConvert){
    for(int i = 0; i < size(toConvert); i++){
        toConvert[i] = tolower(toConvert[i]);
    }
    return toConvert;
}

string askQuestion(string question, string option1, string option2, string option3, string option4, string qNumber){
    string chosenOption = "";
    string number;
    int choice;
    cout<< "QUESTION "<< qNumber <<": "<< question <<endl;
    cout<< "      1) "<<option1<<endl;
    cout<< "      2) "<<option2<<endl;
    cout<< "      3) "<<option3<<endl;
    cout<< "      4) "<<option4<<endl;
    getline(cin, number);
    choice = stoi(number);
    while(choice < 1 || choice > 4){
        cout<<"Invalid entry, try again.."<<endl;
        getline(cin, number);
        choice = stoi(number);
    }

    switch(choice){
        case 1: 
            chosenOption = option1;
            break;
        case 2: 
            chosenOption = option2;
            break;
        case 3: 
            chosenOption = option3;
            break;
        case 4: 
            chosenOption = option4;
            break;
    }
    return chosenOption;
}

string populateVec(vector<string> name, string party){
    ifstream tFile(party);
    string line;
    while(getline(tFile, line)){
        name.push_back(line);
    }
    tFile.close();
}

int countlines(string party){
    ifstream tFile(party);
    string line;
    int numLines;
    vector<string> name;
    while(getline(tFile, line)){
        name.push_back(line);
    }
    tFile.close();
    //cout<<size(name)<<endl;
    return size(name);
}

float calcProb(string party, string response, int numOfParty){
    ifstream tFile(party);
    string line;
    int numLines;
    vector<string> name;
    while(getline(tFile, line)){
        if(response == line){
            name.push_back(line);
        }
    }
    tFile.close();
    cout<<size(name)<<endl;
    cout<<numOfParty<<endl;
    return (float(size(name)) + 1) / float(numOfParty);
    
}

int main(){
    string party;
    string line;
    string respondents;

    cout<< "When responding to the questions, enter the number that best reflects your answer..\n"<<endl;

    string result1 = askQuestion("What should the government do to help the poor?", 
                        "Make it easier to apply for assistance.", 
                        "Allow parents to use education funds for charter schools.", 
                        "Create welfare to work programs.", 
                        "Nothing.", "1");
    responses.push_back(result1);

    string result2 = askQuestion("What is your stance on guns?", 
                        "Should be eliminated", 
                        "Should have stronger restrictions", 
                        "Should have looser restrictions.", 
                        "Policies are fine as is.", "2");
    responses.push_back(result2);

    string result3 = askQuestion("How should the United States approach foreign policty?", 
                        "We should go back to being neutral", 
                        "We should continue to intervene in conflicts against illegal invasions", 
                        "Foreign Policy should reflect our national interest", 
                        "We should always send aid, but stay out of the war altogether otherwise.", "3");
    responses.push_back(result3);

    string result4 = askQuestion("Government should provide university healthcare for all citizens", 
                        "Strongly Agree", 
                        "Somewhat Agree", 
                        "Somewhat Disagree", 
                        "Strong Disagree", "4");
    responses.push_back(result4);

    string result5 = askQuestion("Which of the following best describes your stance on immigration policy?", 
                        "Strongly support increased border security and stricter enforcement of immigration laws",
                        "Somewhat support increased border security and stricter enforcement of immigration laws",
                        "Strongly support more lenient immigration policies and a pathway to citizenship for undocumented immigrants", 
                        "Somewhat support more lenient immigration policies and a pathway to citizenship for undocumented immigrants", "5");
    responses.push_back(result5);

    ifstream responders("totalrespondents.txt");
    int nNumber;
    if(responders.good()){
        string n;
        getline(responders,n);
        nNumber = stoi(n);
        responders.close();

        nNumber++;
        ofstream nResponders("totalrespondents.txt", ios::out);
        nResponders<<nNumber;
        nResponders.close();
    } 
    //require for there to be at least 30 responses for the program to make an educated guess
    if(nNumber > 30){
        //cout<<"New Number: "<<nNumber<<endl;
        //number of each party for current respondents
        int numRepub = countlines(republican) / 5;
        int numDem = countlines(democrat) / 5;
        int numInd = countlines(independent) / 5;
        int numOther = countlines(other) / 5;
        //initial probabilities for each party
        float probRepub = float(numRepub) / float(nNumber);
        float probDem = float(numDem) / float(nNumber);
        float probInd = float(numInd) / float(nNumber);
        float probOther = float(numOther) / float(nNumber);

        //calculate the number of responses / the number of responders that identify to create some sort of baseline score for each question
        float r1RepubProb, r1DemProb, r1IndProb, r1OthProb;
        r1RepubProb = calcProb(republican, result1, numRepub);
        r1DemProb = calcProb(democrat, result1, numDem);
        r1IndProb = calcProb(independent, result1, numInd);
        r1OthProb = calcProb(other, result1, numOther);

        float r2RepubProb, r2DemProb, r2IndProb, r2OthProb;
        r2RepubProb = calcProb(republican, result2, numRepub);
        r2DemProb = calcProb(democrat, result2, numDem);
        r2IndProb = calcProb(independent, result2, numInd);
        r2OthProb = calcProb(other, result2, numOther);

        float r3RepubProb, r3DemProb, r3IndProb, r3OthProb;
        r3RepubProb = calcProb(republican, result3, numRepub);
        r3DemProb = calcProb(democrat, result3, numDem);
        r3IndProb = calcProb(independent, result3, numInd);
        r3OthProb = calcProb(other, result3, numOther);

        float r4RepubProb, r4DemProb, r4IndProb, r4OthProb;
        r4RepubProb = calcProb(republican, result4, numRepub);
        r4DemProb = calcProb(democrat, result4, numDem);
        r4IndProb = calcProb(independent, result4, numInd);
        r4OthProb = calcProb(other, result4, numOther);

        float r5RepubProb, r5DemProb, r5IndProb, r5OthProb;
        r5RepubProb = calcProb(republican, result5, numRepub);
        r5DemProb = calcProb(democrat, result5, numDem);
        r5IndProb = calcProb(independent, result5, numInd);
        r5OthProb = calcProb(other, result5, numOther);
        
        //naive bayes classifier = initial prob * prob of result1 * prob of result2 * prob of result3 * prob of result4 * prob of result5
        float NBRepProb = probRepub * r1RepubProb * r2RepubProb * r3RepubProb * r4RepubProb * r5RepubProb;
        float NBDemProb = probDem * r1DemProb * r2DemProb * r3DemProb * r4DemProb * r5DemProb;
        float NBIndProb = probInd * r1IndProb * r2IndProb * r3IndProb * r4IndProb * r5IndProb;
        float NBOtherProb = probOther * r1OthProb * r2OthProb * r3OthProb * r4OthProb * r5OthProb;

        map<string, float> parties = {{"Republican", NBRepProb}, {"Democrat", NBDemProb}, {"Independent", NBIndProb}, {"Other", NBOtherProb}};
        auto it = std::max_element(parties.begin(), parties.end(), [](const auto& p1, const auto& p2) { return p1.second < p2.second; });

        cout<<"Based on previous responses in the database, we predict that you are a "<<it->first<<" as a party affiliation.  Please tell us below what party you identify with.."<<endl;
    }
    else{
        cout<<"Not enough responses to give an educated answer!"<<endl;
    }

    string result = askQuestion("What is your political party?", 
                        "Republican",
                        "Democrat", 
                        "Independent",  
                        "Other", "6");

    party = lower(result) + ".txt";
    ofstream tFile(party, ios::binary|ios::app);
    for(int i = 0; i < size(responses); i++){
        tFile<<responses[i]<<endl;
    } 

    return 0;
}
