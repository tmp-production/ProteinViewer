//
// Created by Konstantin Moskalenko on 23.11.2021.
//

#ifndef RIBBON_STRAND_H
#define RIBBON_STRAND_H


namespace pdb {
    struct Strand {
        int strand;
        std::string sheetID;
        int numStrands;
        std::string initResName;
        std::string initChainID;
        int initSeqNum;
        std::string initICode;
        std::string endResName;
        std::string endChainID;
        int endSeqNum;
        std::string endICode;
        int sense;
        std::string curAtom;
        std::string curResName;
        std::string curChainId;
        int curResSeq;
        std::string curICode;
        std::string prevAtom;
        std::string prevResName;
        std::string prevChainId;
        int prevResSeq;
        std::string prevICode;
    };
}


#endif //RIBBON_STRAND_H
