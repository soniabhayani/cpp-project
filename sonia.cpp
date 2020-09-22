#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

/*This is abstract class for making a shuffler*/
class Shuffler{
public:
    virtual void shuffle(string& str)=0;
};

/*cut first portion of the string and appends to last*/
class Cut:public Shuffler{
    int n;
public:
    Cut(int n){
        this->n = n;
    }
    void shuffle(string& str){
        string firstN="",lastN="";
        int i=0;
        for(i=0; i<n && i<str.size(); i++){
            firstN+=str[i];
        }

        for( ; i<str.size(); i++){
            lastN+=str[i];
        }
        str = lastN + firstN;
    }
};

/* reverses a string */
class Rev:public Shuffler{
public:
    void shuffle(string& str){
        string temp="";
        for(int i=str.size()-1; i>=0; i--){
            temp+=str[i];
        }
        str=temp;
    }
};

/* reads the steps file and save the steps in a vector of Shuffler class */
vector<Shuffler*> readSteps(){
    ifstream in("steps.txt");
    string line="";
    vector<Shuffler*> vect;
    while(getline(in, line)){
        istringstream iss(line);
        string command;
        iss>>command;
        if(command=="cut"){
            int n;
            iss>>n;
            vect.push_back(new Cut(n));
        } else {
            vect.push_back(new Rev());
        }
    }
    return vect;
}

int main(){
    vector<Shuffler*> vect = readSteps();
    ifstream in("input.txt");
    string str="";
    while (getline(in, str)) //reading the input strings line by line
    {
        for(int i=0; i<vect.size(); i++){ //operating all steps on the current string
            Shuffler *operation = vect[i];
            operation->shuffle(str);
        }
        cout<<str<<endl; //printing out the final string
    }
    return 0;
}
