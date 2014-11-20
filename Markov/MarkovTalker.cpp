//
//  MarkovTalker.cpp
//  Markov
//
//  Created by Joseph Redfern on 20/11/2014.
//  Copyright (c) 2014 Joseph Redfern. All rights reserved.
//

#include "MarkovTalker.h"
#include "MarkovChain.h"
#include <string>

using namespace std;


MarkovTalker::MarkovTalker(MarkovChain chain){
    this->chain = chain;
}

string MarkovTalker::generateString(std::string seed, int length){
    string output = seed;
    output.append(" ");
    string currentWord = seed;
    if(this->chain.chainContains(seed)) {
        for(int i = 0; i < length; i++){
            string mostProbable = this->chain.getMostProbableWord(currentWord);
            output.append(mostProbable);
            output.append(" ");
            currentWord = mostProbable;
        }
    }else{
        output = "Nope.";
    }
    return output;
}