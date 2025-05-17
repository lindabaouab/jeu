#include "Grille.h"
#include "Case.h"
#include "include/json.hpp"
#include <fstream>
#include <string>

using json = nlohmann::json;

Grille* chargerDepuisJSON(const std::string& chemin) {
    std::ifstream in(chemin);
    json j;
    in >> j;

    int lignes = j["lignes"];
    int colonnes = j["colonnes"];
    auto g = new Grille(lignes, colonnes);

    for (int i = 0; i < lignes; ++i) {
        for (int jCol = 0; jCol < colonnes; ++jCol) {
            std::string val = j["grille"][i][jCol];

            if (val == "#") {
                g->setCase(i, jCol, new CaseNoire());
            } else if (val == ".") {
                g->setCase(i, jCol, new CaseVide());
            } else if (isdigit(val[0])) {
                if (val.find('/') != std::string::npos) {
                    // case indication
                    int sBas = 0, sDroite = 0;
                    size_t pos = val.find('/');
                    std::string droite = val.substr(0, pos);
                    std::string bas = val.substr(pos + 1);
                    sDroite = droite.empty() ? 0 : std::stoi(droite);
                    sBas = bas.empty() ? 0 : std::stoi(bas);
                    g->setCase(i, jCol, new CaseIndication(sDroite, sBas));
                } else {
                    // case fixe
                    g->setCase(i, jCol, new CaseFixe(std::stoi(val)));
                }
            } else {
                std::cerr << "Format inconnu: " << val << "\n";
            }
        }
    }

    return g;
}
