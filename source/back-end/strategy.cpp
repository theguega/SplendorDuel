#include "strategy.hpp"

/*Privilege StrategyHumain::utiliserPrivilege(const EspaceJeux& espaceJeux) {
    // voir si le joueur a un jeton
    // voir si le plateau a des jetons
    // le déplacer du joueur vers le plateau
    // le déplacer du plateau vers le joueur

}*/

const Jeton& StrategyHumain::choisirJeton(Plateau& plateau){
    int i, j;
    std::cout << "Entrez la valeur de i : ";
    std::cin >> i;
    std::cout << "Entrez la valeur de j : ";
    std::cin >> j;

    return plateau.recupererJeton(i, j);
}

void StrategyHumain::remplirPlateauStrat(Plateau& plateau, Sac& sac){
    plateau.remplirPlateau(sac);
}