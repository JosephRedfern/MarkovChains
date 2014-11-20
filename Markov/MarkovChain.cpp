//
//  main.cpp
//  Markov
//
//  Created by Joseph Redfern on 18/11/2014.
//  Copyright (c) 2014 Joseph Redfern. All rights reserved.
//

#include "MarkovChain.h"
#include "MarkovTalker.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

int main(int argc, const char * argv[]) {
    string path;
    if(argc < 2){
        cout << "Path to file: ";
        cin >> path;
    }else{
        path = argv[1];
    }
    
    MarkovChain* markov = new MarkovChain();
    markov->populate(path);
    markov->generateHistogram();
    markov->generateFirstOrder();
    
    MarkovTalker* talker = new MarkovTalker(*markov);
    
    while(true){
    cout << "Enter seed word: ";
    string seed;
    cin >> seed;
    cout << "\nEnter desired string length: ";
    int stringLength;
    cin >> stringLength;
    
    cout << talker->generateString(seed, stringLength);
    }
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
        cout << "OK, read file.\n";
    }else{
        cerr << "Unable to open file.\n";
        exit(1);
    }
}

void MarkovChain::generateHistogram(){
    for(auto i = this->words.begin(); i != this->words.end(); ++i){
        this->histogram[*i]++;
    }
    
}

void MarkovChain::printHistogram(){
    if(this->words.size()==0){
        cerr << "No Histogram data";
        return;
    }
    
    for(auto i = this->histogram.begin(); i!= this->histogram.end(); ++i){
        cout << "Key:" << i->first << ", Value:" << i->second << "\n";
    }
    
    
}

void MarkovChain::generateFirstOrder(){
    std::map<string, std::map<string, int> > firstOrderHist;
    for(int i = 0; i < this->words.size()-1; i++){
        firstOrderHist[this->words.at(i)][this->words.at(i+1)] += 1;
    }
    
    for(auto i = firstOrderHist.begin(); i != firstOrderHist.end(); ++i){ //iterator
        string wordA = i->first;
        
        for(auto j = i->second.begin(); j != i->second.end(); ++j){
            string wordB = j->first;
            int freq = j->second;
            double probability = freq / this->histogram.at(wordA);
            this->firstOrder[wordA].insert(pair<double, string>(probability, wordB));
            //cout << "Given " << wordA << ", " << probability*100 << "% chance of " << wordB << "\n";
        }
    }
    
}

bool MarkovChain::chainContains(std::string word){
    return (this->firstOrder.find(word) != this->firstOrder.end());
}

std::string MarkovChain::getMostProbableWord(std::string input){
    if(!this->chainContains(input)){
        return ".";
    }else{
        std::multimap<double, string> map = this->firstOrder.at(input);
        return map.rbegin()->second;
    }
    return "";
}

void MarkovChain::printDictionary(){
    for(auto i = this->words.begin(); i != this->words.end(); ++i){
        cout << *i << "\n";
    }
}

