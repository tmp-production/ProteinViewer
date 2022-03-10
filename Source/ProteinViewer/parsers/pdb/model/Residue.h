//
// Created by Konstantin Moskalenko on 23.11.2021.
//

#ifndef RIBBON_RESIDUE_H
#define RIBBON_RESIDUE_H

#include <string>
#include <vector>
#include <map>

#include "Atom.h"
#include "Helix.h"
#include "Strand.h"


namespace pdb {
    enum ResidueType {
        ResidueTypeCoil,
        ResidueTypeHelix,
        ResidueTypeStrand
    };

    struct Residue {
        std::string resName;
        std::string chainID;
        int resSeq;
        std::vector <Atom> atoms;
        std::map <std::string, Atom> atomsByName;
        ResidueType type;

        explicit Residue(const std::vector <Atom> &atoms);

        static std::vector <Residue> residuesForAtoms(
                const std::vector <Atom> &atoms,
                const std::vector <Helix> &helices,
                const std::vector <Strand> &strands
        );
    };
}


#endif //RIBBON_RESIDUE_H
