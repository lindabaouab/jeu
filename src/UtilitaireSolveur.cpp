#include "UtilitaireSolveur.h"
#include "Case.h"
#include <set>
#include "Grille.h"

void trouverCasesVides(Grille* g, std::vector<Coord>& vides) {
    for (int i = 0; i < g->getLignes(); ++i) {
        for (int j = 0; j < g->getColonnes(); ++j) {
            Case* c = g->getCase(i, j);
            if (c && c->estModifiable()) {
                vides.push_back({i, j});
            }
        }
    }
}

bool verifierBlocParCombi(std::vector<Case*> bloc, int sommeCible, int i, int j, int val) {
    std::set<int> valeurs;
    int somme = 0;
    for (Case* c : bloc) {
        int v = 0;
        if (CaseVide* cv = dynamic_cast<CaseVide*>(c)) {
            v = cv->getValeur();
        } else if (CaseFixe* cf = dynamic_cast<CaseFixe*>(c)) {
            v = cf->getValeur();
        }

        if (c == bloc[i - i]) v = val; // force valeur testée

        if (v != 0) {
            if (valeurs.count(v)) return false;
            valeurs.insert(v);
            somme += v;
        }
    }

    return somme <= sommeCible;
}
