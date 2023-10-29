#ifndef JETONS_H
#define JETONS_H

#include <iostream>
#include <vector>
#include <string>

//Gestion des jetons splendor duel

/* Il faudra implémenter la classe jetons, ansi que Lot de Jetons qui contiendra tous les jetons.
Il faudra également définir le plateau de Jeu qui est une matrice de jetons.
Les privilèges apparaitront également sur le plateau. Il faudra aussi définir la classe Lot de Privilege.
Les jetons peuvent se situer à trois endroits : dans le sac, sur le plateau ou dans la main d'un joueur.
Les privilèges, à deux endroits : sur le plateau ou dans la main d'un joueur.
La classe joueur implémenter dans le fichier joueur agira comme controleur pour les jetons et les privilèges.
*/

//Gestion des exceptions liées aux jetons
class JetonException
{
public:
    JetonException(const std::string& i) :info(i) {}
    std::string getInfo() const { return info; }
private:
    std::string info;
};

//Enum pour les couleurs : initialiser, to string, affichage.
enum class CouleurJeton { RUBIS, SAPHIR, ÉMERAUDE, ONYX, DIAMANT, OR, PERLE };
std::string toString(CouleurJeton c);
std::ostream& operator<<(std::ostream& f, CouleurJeton c);
extern std::initializer_list<CouleurJeton> CouleursJeton;

//Classe Jetons
class Jeton {
    private :
        CouleurJeton couleur;
    public :
        Jeton(CouleurJeton c) : couleur(c) {}
        CouleurJeton getCouleur() const { return couleur; }
};
std::ostream& operator<< (std::ostream& f, const Jeton& jeton);

class LotDeJetons {
    private :
        std::array<Jeton*, 25> jetons;
    public:
        size_t getNbJetons() const { return jetons.size(); }
        const Jeton& getJetons(size_t i) const;
        LotDeJetons();
        ~LotDeJetons();

        //pas de copie ni d'affectation 
        LotDeJetons(const LotDeJetons&) = delete;
        LotDeJetons& operator=(const LotDeJetons&) = delete;
};

class Privilege {
    //pas d'attribut : les 3 privilèges sont identiques
    public :
        //pas de recopie ni d'affectation
        Privilege() = default;
        Privilege(const Privilege&) = delete;
        Privilege& operator=(const Privilege&) = delete;
};

class LotPrivilege {
    private :
        std::array<Privilege*, 3> privileges;
    public :
        size_t getNbPrivileges() const { return privileges.size(); }
        const Privilege& getPrivilege(size_t i) const;
        LotPrivilege();
        ~LotPrivilege();

        //pas de copie ni d'affectation
        LotPrivilege(const LotPrivilege&) = delete;
        LotPrivilege& operator=(const LotPrivilege&) = delete;
};

class Sac {
    //Le sac de jetons contient tous les jetons qui ne sont ni dans la main des joueurs ni sur le plateau
    //Au debut de la partie, le plateau est pleins, le sac est donc vide au même titre que la main des joueurs
    private :
        std::vector<const Jeton*> jetons;
    public :
        explicit Sac(const LotDeJetons& lot);
        bool estVide() const { return jetons.empty(); }
        size_t getNbJetons() const { return jetons.size(); }
        void ajouterJeton(const Jeton* j);
        const Jeton& piocherJeton();
        ~Sac();

        //pas de duplication et d'affection du sac
        Sac(const Sac&) = delete;
        Sac& operator=(const Sac&) = delete;
};

#endif
