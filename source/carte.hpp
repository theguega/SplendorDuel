#ifndef CARTES_H
#define CARTES_H

#include <iostream>
#include <string>

#include <array>
#include <vector>
#include <unordered_map>
#include <map>

#include <random>
#include <filesystem>

#include "sqlite/sqlite3.h" 
#include <filesystem>
using namespace std;
extern std::filesystem::path projectPath;




class CarteException{
private:
    string info;
public:
    CarteException(const string& i) : info(i) {}
    string getInfo() const { return info; }
};


enum class CouleurCarte {blanc, bleu, vert, noir, rouge, perle, indt}; // ajout de "indetermin�" car certaines carte ont une couleur de Bonus variable

string CouleurCartetoString(CouleurCarte c);
ostream& operator<<(ostream& f, CouleurCarte c);
extern std::initializer_list<CouleurCarte> CouleursCarte;
extern std::map<string, CouleurCarte> stringToCouleurCarteMap;
CouleurCarte StringToCouleurCarte(const string& couleurStr);


enum class TypeCarte { Niv1, Niv2, Niv3, Noble };
string TypeCartetoString(TypeCarte t);
ostream& operator<<(ostream& f, TypeCarte t);
extern std::initializer_list<TypeCarte> TypesCarte;


enum class Capacite { NewTurn, TakePrivilege, TakeJetonFromBonus, TakeJetonToAdv, AssociationBonus, None };
extern std::map<std::string, Capacite> stringToCapaciteMap;
string CapacitetoString(Capacite c);
ostream& operator<<(ostream& f, Capacite c);
Capacite StringToCapacite(const string& capaciteStr);



class Prix { // on l'encapsule dans la classe carte ? ou bien il y'a d'autres elements qui ont un cout ?
private:
    unsigned int blanc, bleu, vert, noir, rouge, perle;
public:
    Prix(unsigned int bla, unsigned int ble, unsigned int v, unsigned int n, unsigned int r, unsigned int p) : blanc(bla), bleu(ble), vert(v), noir(n), rouge(r), perle(p) {}
    unsigned int getBlanc() const { return blanc; }
    unsigned int getBleu() const { return bleu; }
    unsigned int getVert() const { return vert; }
    unsigned int getNoir() const { return noir; }
    unsigned int getRouge() const { return rouge; }
    unsigned int getPerle() const { return perle; }
};
ostream& operator<<(ostream& f, const Prix& p);


class Bonus {
private:
    CouleurCarte couleur;
    unsigned int nbBonus;
public:
    Bonus(CouleurCarte c = CouleurCarte::indt, int n = 0) : couleur(c), nbBonus(n) {}
    void setCouleur(CouleurCarte c) { couleur = c; };
    CouleurCarte getCouleur() const { return couleur; }
    unsigned int getNbBonus() const { return nbBonus; }
};
ostream& operator<<(ostream& f, const Bonus& b);


class Carte {
private:
    // eventuel ajout d'un champ ID, peut �tre util pour les cartes nobles par exemple, savoir qui est qui
    TypeCarte type;
    Prix prix;
    Capacite capacite1;
    Capacite capacite2;
    Bonus bonus;
    unsigned int nbCouronnes;
    unsigned int nbPtsPrivilege;
    unsigned int id;
public:
    Carte(TypeCarte t, Prix& p, Capacite c1, Capacite c2, Bonus& b, unsigned int nbC, unsigned int nbP, unsigned int id); // constructeur classique
    Carte(TypeCarte t, Capacite c, unsigned int nbP, unsigned int id); // constructeur carte noble
    ~Carte() = default;
    TypeCarte getType() const { return type; }
    Prix getPrix() const { return prix; }
    Capacite getCapacite1() const { return capacite1; }
    Capacite getCapacite2() const { return capacite2; }
    Bonus getBonus() const { return bonus; }
    unsigned int getId() const { return id; }
    unsigned int getNbCouronnes() const { return nbCouronnes; }
    unsigned int getNbPtsPrivilege() const { return nbPtsPrivilege; }
};
ostream& operator<<(ostream& f, const Carte& c);

class JeuCarte {
private:
    // appliquer le design pattern singleton plus tard
    vector<const Carte*> cartes_nv1; 
    vector<const Carte*> cartes_nv2;
    vector<const Carte*> cartes_nv3;
    vector<const Carte*> cartes_nobles;
public:
    JeuCarte();
    ~JeuCarte();
    size_t getNbCartes_nv1() const { return cartes_nv1.size(); }
    size_t getNbCartes_nv2() const { return cartes_nv2.size(); }
    size_t getNbCartes_nv3() const { return cartes_nv3.size(); }
    size_t getNbCartes_nobles() const { return cartes_nobles.size(); }
    const Carte& getCarteNiv1(size_t i) const;
    const Carte& getCarteNiv2(size_t i) const;
    const Carte& getCarteNiv3(size_t i) const;
    const Carte& getCarteNoble(size_t i) const;
    JeuCarte(const JeuCarte& j) = delete;
    JeuCarte& operator=(const JeuCarte& j) = delete;
};

class Pioche{
private:
    TypeCarte type_carte;
    vector<const Carte*> cartes;
public:
    explicit Pioche(const JeuCarte& j, TypeCarte t); // j'ai pris ca depuis le td mais a t on besoin du explicit ?
    ~Pioche();
    bool estVide() const { return getNbCartes() == 0; }
    size_t getNbCartes() const { return cartes.size(); }
    const Carte& piocher();
    Pioche(const Pioche& p) = delete;
    Pioche& operator=(const Pioche& p) = delete;
};

#endif
