//
// Created by Konstantin Moskalenko on 26.11.2021.
//

#include "Chain.h"

using namespace pdb;

Chain::Chain(const std::vector <Residue> &residues) {
    this->chainID = residues[0].chainID;
    this->residues = residues;
}

std::vector <Chain> Chain::chainsForResidues(const std::vector <Residue> &residues) {
    std::vector <Chain> chains;
    std::vector <Residue> *group = nullptr;

    std::string previous;

    for (const auto &residue : residues) {
        std::string value = residue.chainID;

        if (value != previous && group != nullptr) {
            chains.emplace_back(*group);

            delete group;
            group = nullptr;
        }

        if (group == nullptr) {
            group = new std::vector<Residue>();
        }

        group->push_back(residue);
        previous = value;
    }

    if (group != nullptr) {
        chains.emplace_back(*group);
    }

    return chains;
}
