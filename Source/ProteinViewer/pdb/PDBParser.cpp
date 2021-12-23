//
// Created by Konstantin Moskalenko on 23.11.2021.
//

#include "PDBParser.h"
#include "util.h"

#include <fstream>

using namespace pdb;

Atom PDBParser::parseAtom(const std::string &line) {
    Atom atom;
    atom.serial = parseInt(line, 6, 11);
    atom.name = parseString(line, 12, 16);
    atom.altLoc = parseString(line, 16, 17);
    atom.resName = parseString(line, 17, 20);
    atom.chainID = parseString(line, 21, 22);
    atom.resSeq = parseInt(line, 22, 26);
    atom.iCode = parseString(line, 26, 27);
    atom.element = parseString(line, 76, 78);
    atom.x = parseFloat(line, 30, 38);
    atom.y = parseFloat(line, 38, 46);
    atom.z = parseFloat(line, 46, 54);
    atom.occupancy = parseFloat(line, 54, 60);
    atom.tempFactor = parseFloat(line, 60, 66);
    atom.charge = parseString(line, 78, 80);
    return atom;
}

std::vector <Connection> PDBParser::parseConnections(const std::string &line) {
    std::vector <Connection> connections;

    const int a = parseInt(line, 6, 11);
    for (const int i : {11, 16, 21, 26}) {
        try {
            const int b = parseInt(line, i, i + 5);
            connections.push_back(Connection{
                    .serial1 = a, .serial2 = b
            });
        } catch (const std::invalid_argument) {
            // There may be less than 4 connections
            break;
        }
    }

    return connections;
}

Helix PDBParser::parseHelix(const std::string &line) {
    Helix helix;
    helix.serial = parseInt(line, 7, 10);
    helix.helixID = parseString(line, 11, 14);
    helix.initResName = parseString(line, 15, 18);
    helix.initChainID = parseString(line, 19, 20);
    helix.initSeqNum = parseInt(line, 21, 25);
    helix.initICode = parseString(line, 25, 26);
    helix.endResName = parseString(line, 27, 30);
    helix.endChainID = parseString(line, 31, 32);
    helix.endSeqNum = parseInt(line, 33, 37);
    helix.endICode = parseString(line, 37, 38);
    helix.helixClass = parseInt(line, 38, 40);
    helix.length = parseInt(line, 71, 76);
    return helix;
}

Strand PDBParser::parseStrand(const std::string &line) {
    Strand strand;
    strand.strand = parseInt(line, 7, 10);
    strand.sheetID = parseString(line, 11, 14);
    strand.numStrands = parseInt(line, 14, 16);
    strand.initResName = parseString(line, 17, 20);
    strand.initChainID = parseString(line, 21, 22);
    strand.initSeqNum = parseInt(line, 22, 26);
    strand.initICode = parseString(line, 26, 27);
    strand.endResName = parseString(line, 28, 31);
    strand.endChainID = parseString(line, 32, 33);
    strand.endSeqNum = parseInt(line, 33, 37);
    strand.endICode = parseString(line, 37, 38);
    strand.sense = parseInt(line, 38, 40);
    strand.curAtom = parseString(line, 41, 45);
    strand.curResName = parseString(line, 45, 48);
    strand.curChainId = parseString(line, 49, 50);
    strand.curResSeq = parseInt(line, 50, 54);
    strand.curICode = parseString(line, 54, 55);
    strand.prevAtom = parseString(line, 56, 60);
    strand.prevResName = parseString(line, 60, 63);
    strand.prevChainId = parseString(line, 64, 65);
    strand.prevResSeq = parseInt(line, 65, 69);
    strand.prevICode = parseString(line, 69, 70);
    return strand;
}

Model PDBParser::read(const char *filename) {
    std::ifstream inputFile(filename);
    std::string line;

    std::vector <Atom> atoms;
    std::vector <Atom> hetAtoms;
    std::vector <Connection> connections;
    std::vector <Helix> helices;
    std::vector <Strand> strands;
    std::vector <Matrix> bioMatrices;
    std::vector <Matrix> symMatrices;
    Matrix m = identity();

    while (std::getline(inputFile, line)) {
        if (line.rfind("ENDMDL", 0) == 0) {
            break;
        }

        if (line.rfind("ATOM  ", 0) == 0) {
            auto atom = parseAtom(line);
            atoms.push_back(atom);
        }

        if (line.rfind("HETATM", 0) == 0) {
            auto atom = parseAtom(line);
            hetAtoms.push_back(atom);
        }

        if (line.rfind("CONECT", 0) == 0) {
            auto cs = parseConnections(line);
            connections.insert(connections.end(), cs.begin(), cs.end());
        }

        if (line.rfind("HELIX ", 0) == 0) {
            auto helix = parseHelix(line);
            helices.push_back(helix);
        }

        if (line.rfind("SHEET ", 0) == 0) {
            auto strand = parseStrand(line);
            strands.push_back(strand);
        }

        if (line.rfind("REMARK 350   BIOMT", 0) == 0) {
            int row = parseInt(line, 18, 19) - 1;
            m.value[row][0] = parseFloat(line, 23, 33);
            m.value[row][1] = parseFloat(line, 33, 43);
            m.value[row][2] = parseFloat(line, 43, 53);
            m.value[row][3] = parseFloat(line, 53, 68);
            if (row == 2) {
                bioMatrices.push_back(m);
                m = identity();
            }
        }

        if (line.rfind("REMARK 290   SMTRY", 0) == 0) {
            int row = parseInt(line, 18, 19) - 1;
            m.value[row][0] = parseFloat(line, 23, 33);
            m.value[row][1] = parseFloat(line, 33, 43);
            m.value[row][2] = parseFloat(line, 43, 53);
            m.value[row][3] = parseFloat(line, 53, 68);
            if (row == 2) {
                symMatrices.push_back(m);
                m = identity();
            }
        }
    }

    auto residues = Residue::residuesForAtoms(atoms, helices, strands);
    auto chains = Chain::chainsForResidues(residues);

    return Model{
            .atoms = atoms,
            .hetAtoms = hetAtoms,
            .connections = connections,
            .helices = helices,
            .strands = strands,
            .bioMatrices = bioMatrices,
            .symMatrices = symMatrices,
            .residues = residues,
            .chains = chains
    };
}
