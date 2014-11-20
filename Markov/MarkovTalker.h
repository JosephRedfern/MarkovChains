//
//  MarkovTalker.h
//  Markov
//
//  Created by Joseph Redfern on 20/11/2014.
//  Copyright (c) 2014 Joseph Redfern. All rights reserved.
//

#ifndef __Markov__MarkovTalker__
#define __Markov__MarkovTalker__

#include <stdio.h>
#include <string>
#include "MarkovChain.h"

class MarkovTalker{
public:
    MarkovTalker(MarkovChain);
    std::string generateString(std::string, int);
private:
    MarkovChain chain;
};

#endif /* defined(__Markov__MarkovTalker__) */
