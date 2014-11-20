//
//  MarkovChain.h
//  Markov
//
//  Created by Joseph Redfern on 20/11/2014.
//  Copyright (c) 2014 Joseph Redfern. All rights reserved.
//
#include <map>
#include <vector>
#include <string>

#ifndef Markov_MarkovChain_h
#define Markov_MarkovChain_h

class MarkovChain
{
private:
    std::vector<std::string> words;
    std::map<std::string, double> histogram;
    std::map<std::string, std::multimap<double, std::string> > firstOrder;
    
public:
    void populate(std::string);
    void printDictionary();
    void generateHistogram();
    void printHistogram();
    void generateFirstOrder();
    bool chainContains(std::string);
    std::string getMostProbableWord(std::string);
};

#endif
