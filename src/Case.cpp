#include "Case.h"
#include <set>         // Pour std::set
#include <vector>      // Pour std::vector
#include <functional>  // Pour std::function
#include <algorithm>   // Pour std::sort ou autres fonctions utiles

void CaseIndication::genererCombinaisons() {
    auto generer = [&](int sommeCible, const std::vector<Case*>& cases) {
        int nbCases = cases.size();
        std::vector<std::set<int>> combinaisons;

        std::vector<int> chiffres {1,2,3,4,5,6,7,8,9};
        std::vector<bool> selection(chiffres.size(), false);

        std::function<void(int, int, std::set<int>&)> backtrack = [&](int index, int sommeActuelle, std::set<int>& courant) {
            if (courant.size() == nbCases) {
                if (sommeActuelle == sommeCible)
                    combinaisons.push_back(courant);
                return;
            }

            for (int i = index; i < 9; ++i) {
                int val = chiffres[i];
                if (courant.count(val)) continue;
                if (sommeActuelle + val > sommeCible) break;

                courant.insert(val);
                backtrack(i + 1, sommeActuelle + val, courant);
                courant.erase(val);
            }
        };

        std::set<int> enCours;
        backtrack(0, 0, enCours);

        // Enregistre dans la bonne direction
        if (cases == casesDroite) combinaisonsValidées = combinaisons;
        else if (cases == casesBas) combinaisonsValidées.insert(combinaisonsValidées.end(), combinaisons.begin(), combinaisons.end());
    };

    if (!casesDroite.empty()) generer(sommeDroite, casesDroite);
    if (!casesBas.empty())    generer(sommeBas, casesBas);
}
