//
// Created by Konstantin Moskalenko on 23.11.2021.
//

#ifndef RIBBON_MODEL_H
#define RIBBON_MODEL_H

#include "Atom.h"
#include "Chain.h"
#include "Connection.h"
#include "Helix.h"
#include "Strand.h"
#include "Matrix.h"
#include "Residue.h"


namespace pdb {
    struct Model {
        std::vector <Atom> atoms;
        std::vector <Atom> hetAtoms;
        std::vector <Connection> connections;
        std::vector <Helix> helices;
        std::vector <Strand> strands;
        std::vector <Matrix> bioMatrices;
        std::vector <Matrix> symMatrices;
        std::vector <Residue> residues;
        std::vector <Chain> chains;
    };
}


#endif //RIBBON_MODEL_H
