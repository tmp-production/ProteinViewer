//
// Created by Konstantin Moskalenko on 23.11.2021.
//

#ifndef RIBBON_HELIX_H
#define RIBBON_HELIX_H


namespace pdb {
    struct Helix {
        int serial;
        std::string helixID;
        std::string initResName;
        std::string initChainID;
        int initSeqNum;
        std::string initICode;
        std::string endResName;
        std::string endChainID;
        int endSeqNum;
        std::string endICode;
        int helixClass;
        int length;
    };
}


#endif //RIBBON_HELIX_H
