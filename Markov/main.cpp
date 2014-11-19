//
//  main.cpp
//  Markov
//
//  Created by Joseph Redfern on 18/11/2014.
//  Copyright (c) 2014 Joseph Redfern. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

class MarkovChain
{
private:
    std::vector<std::string> words;
    std::map<std::string, double> histogram;
    std::map<std::string, std::map<std::string, double> > firstOrder;
    
public:
    void populate(string);
    void printDictionary();
    void generateHistogram();
    void generateSecondOrder();
};


int main(int argc, const char * argv[]) {
    if(argc < 2){
        cerr << printf("Usage: %s [data] [order] [length]\n", argv[0]);
        return 1;
    }
    
    string path;
    cout << "Path to file: ";
    cin >> path;
    
    MarkovChain* markov = new MarkovChain();
    markov->populate(path);
//    markov->printDictionary();
    markov->generateHistogram();
    
    
    return 0;
}

void MarkovChain::populate(string filename)
{
    ifstream inputFile;
    inputFile.open(filename, ios::in);
    
    string line;
    if(inputFile.is_open()){
        while(getline(inputFile, line)){
            stringstream ss(line);
            string word;
            while(getline(ss, word, ' ')){
                if(!word.empty()){
                    this->words.push_back(word);
                }
            }
        }
    }
    
    cout << "OK, read file.\n";
    cout << "Words: " << this->words.size() << "\n";
}

void MarkovChain::generateHistogram(){
    for(auto i = this->words.begin(); i != this->words.end(); ++i){
        this->histogram[*i]++;
    }
    
}

void MarkovChain::generateSecondOrder(){
    
}

void MarkovChain::printDictionary(){
    for(auto i = this->words.begin(); i != this->words.end(); ++i){
        cout << *i << "\n";
    }
}

