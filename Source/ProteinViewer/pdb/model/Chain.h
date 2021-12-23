//
// Created by Konstantin Moskalenko on 23.11.2021.
//

#ifndef RIBBON_CHAIN_H
#define RIBBON_CHAIN_H

#include <vector>
#include "Residue.h"


namespace pdb {
    struct Chain {
        std::string chainID;
        std::vector <Residue> residues;

        explicit Chain(const std::vector <Residue> &residues);

        static std::vector <Chain> chainsForResidues(
                const std::vector <Residue> &residues
        );
    };
}


#endif //RIBBON_CHAIN_H
