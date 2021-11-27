//
// Created by Konstantin Moskalenko on 23.11.2021.
//

#ifndef RIBBON_ATOM_H
#define RIBBON_ATOM_H


namespace pdb {
    struct Atom {
        int serial;
        std::string name;
        std::string altLoc;
        std::string resName;
        std::string chainID;
        int resSeq;
        std::string iCode;
        double x, y, z;
        double occupancy;
        double tempFactor;
        std::string element;
        std::string charge;
    };
}


#endif //RIBBON_ATOM_H
