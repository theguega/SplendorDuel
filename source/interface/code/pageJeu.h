#ifndef PAGEJEU_H
#define PAGEJEU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScreen>
#include <QSize>
#include <interface/code/vuePlateau.h>
#include "interface/code/vuePlateau.h"
#include "interface/code/pageJoueur.h"
#include "interface/code/popUp.h"
#include "interface/code/vuePyramide.h"
#include "back-end/controller.hpp"
#include "interface/code/popUp.h"
#include "back-end/joueur.hpp"

class pageJeu : public QWidget {
    Q_OBJECT
private:
    Controller* control;
    vuePlateau* vPlateau; //Plateau de jetons
    pageJoueur* joueur1; //Page du joueur1
    pageJoueur* joueur2; //Page du joueur2
    vuePyramide* vPyramide; //Pyramide de carte

    QPushButton* afficherJ1; //Bouton pour afficher la page du joueur1
    QPushButton* afficherJ2; //Bouton pour afficher la page du joueur2

    QHBoxLayout* partieHaute;
    QHBoxLayout* partieMoyenne;  //Partie Haute a ranger (pyramide et plateau)
    QHBoxLayout* partieBasse; //Partie Basse a ranger (boutons)
    QVBoxLayout* layout;//Layout principal
    QVBoxLayout* layoutPrivileges;

    QLabel* labelJC;

    QScreen* ecran; //Recupere l'ecran de l'utilisateur
    QSize tailleEcran; //Recupere la taille de l'ecran

    int tailleLargeur; //Utile pour definir les tailles de sous objets
    int tailleHauteur; //Utile pour definir les tailles de sous objets

    popUpValider* aSauvegarde; //PopUp pour sauvegarder la partie
    bool quitterPage = false; //Utile pour la redefinission de closeEvent
protected:
    void closeEvent(QCloseEvent *event) override { //Redefinition de la methode closeEvent
        aSauvegarde -> hide();
        if(!quitterPage){
            aSauvegarde -> show();
            event -> ignore();
        }
    }
    void quitter(){ //Permet de quitter la page
        quitterPage = true;
        aSauvegarde -> close();
        this -> close();
    }
    void rester(){ //Permet de restetr sur la page
        aSauvegarde -> close();
    }
    void paintEvent(QPaintEvent *event);
public:
    pageJeu(QString statut_partie, QString pseudo_j_1, type type_j_1, QString pseudo_j_2, type type_j_2, QWidget *parent = nullptr);
    ~pageJeu() = default;
    void mousePressEvent(QMouseEvent* event) override { //Permet de cacher tous les elements quand on cique sur la page de Jeu
        joueur1 -> hide();
        joueur2 -> hide();
        vPlateau -> cacherElements();
        aSauvegarde -> hide();
        QWidget::mousePressEvent(event);
    }
    void setLabelJC(){labelJC->setText(QString::fromStdString("C'est au tour de " + control->getJoueurCourant().getPseudo()));}

public slots:
    void validerSelectionCarte(position* p);
private slots:
    void validerSelectionJeton();

    void handleValidationCarte(position* p);
};



class vuePrivilege : public QWidget{
    Q_OBJECT
private:
    int h;
    int l;
protected:
    void paintEvent(QPaintEvent *event);
public:
    vuePrivilege(int hauteur, int largeur) : h(hauteur), l(largeur){setFixedSize(l, h);}
};

#endif // PAGEJEU_H

