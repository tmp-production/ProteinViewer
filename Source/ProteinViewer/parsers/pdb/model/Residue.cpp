//
// Created by Konstantin Moskalenko on 26.11.2021.
//

#include "Residue.h"

using namespace pdb;

Residue::Residue(const std::vector <Atom> &atoms) {
    for (const auto &atom : atoms) {
        this->atomsByName[atom.name] = atom;
    }

    this->resName = atoms[0].resName;
    this->chainID = atoms[0].chainID;
    this->resSeq = atoms[0].resSeq;
    this->atoms = atoms;
    this->type = ResidueTypeCoil;
}

std::vector <Residue> Residue::residuesForAtoms(
        const std::vector <Atom> &atoms,
        const std::vector <Helix> &helices,
        const std::vector <Strand> &strands
) {
    std::vector <Residue> residues;
    std::vector <Atom> *group = nullptr;
    int previous = -1;

    for (const auto &atom : atoms) {
        int value = atom.resSeq;

        if (value != previous && group != nullptr) {
            residues.emplace_back(*group);

            delete group;
            group = nullptr;
        }

        if (group == nullptr) {
            group = new std::vector<Atom>();
        }

        group->push_back(atom);
        previous = value;
    }

    if (group != nullptr) {
        residues.emplace_back(*group);
    }

    for (auto &r : residues) {
        for (const auto &h : helices) {
            if (r.chainID == h.initChainID && r.resSeq >= h.initSeqNum && r.resSeq <= h.endSeqNum) {
                r.type = ResidueTypeHelix;
            }
        }
        for (const auto &s : strands) {
            if (r.chainID == s.initChainID && r.resSeq >= s.initSeqNum && r.resSeq <= s.endSeqNum) {
                r.type = ResidueTypeStrand;
            }
        }
    }

    return residues;
}