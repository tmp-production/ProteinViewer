//
// Created by Konstantin Moskalenko on 23.11.2021.
//

#ifndef RIBBON_PDBPARSER_H
#define RIBBON_PDBPARSER_H

#include <string>
#include <vector>

#include "model/Atom.h"
#include "model/Connection.h"
#include "model/Helix.h"
#include "model/Strand.h"
#include "model/Model.h"


namespace pdb {
    class PDBParser {
        static Atom parseAtom(const std::string &line);

        static std::vector <Connection> parseConnections(const std::string &line);

        static Helix parseHelix(const std::string &line);

        static Strand parseStrand(const std::string &line);

    public:
        static Model read(const char *filename);
    };
}


#endif //RIBBON_PDBPARSER_H
