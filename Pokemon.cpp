// Créé par Walid et Rayane
// Date de création: 2025-01-05
// Dernière modification: 2025-01-25

// Nom du programme: Pokemon
// Description: Un jeu de combat Pokémon simplifié avec des classes et des pointeurs uniques
// Compilation: g++ Pokemon.cpp -o Pokemon -std=c++11 && ./Pokemon

// Entrée: Aucune
// Exemple de sortie:
// ===== "Les Flammes Ardentes (Walid)" 🆚 "Les Vagues Infernales (Rayane)" ! =====
// Equipe : Les Flammes Ardentes (Walid)
// 	Nom: Dracaufeu, PV: 150, Attaque: 80, Défense: 60, Vitesse: 80
// 	Nom: Salamèche, PV: 120, Attaque: 50, Défense: 40, Vitesse: 50
// 	Nom: Dracaufeu, PV: 150, Attaque: 80, Défense: 60, Vitesse: 80
// Equipe : Les Vagues Infernales (Rayane)
// 	Nom: Voltali, PV: 150, Attaque: 80, Défense: 60, Vitesse: 80
// 	Nom: Pikachu, PV: 120, Attaque: 50, Défense: 40, Vitesse: 50
// 	Nom: Voltali, PV: 150, Attaque: 80, Défense: 60, Vitesse: 80
// === Dracaufeu ⚔️ Voltali ! ===
// Dracaufeu a activé son attaque spéciale !
// Dracaufeu attaque 💥 Voltali et inflige 100 dégâts
// Voltali attaque 💥 Dracaufeu et inflige 50 dégât
// Dracaufeu attaque 💥 Voltali et inflige 100 dégâts
// Voltali est KO 💀
// Les Flammes Ardentes (Walid) remporte le match 🏆🎉

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

// Classe de base Pokemon
class Pokemon
{
protected:
    string nom;
    int pointsDeVie;
    int attaque;
    int defense;
    int vitesse;
    int pointsDeVieInitiaux;
    bool attaqueSpecialeActivee = false; // Attribut pour suivre l'activation de l'attaque spéciale

public:
    Pokemon(string nom, int pv, int atk, int def, int vit)
        : nom(nom), pointsDeVie(pv), attaque(atk), defense(def), vitesse(vit), pointsDeVieInitiaux(pv) {}

    // Destructeur virtuel
    // Permet de s'assurer que le destructeur de la classe dérivée sera appelé
    virtual ~Pokemon() = default;

    // Méthode virtuelle pure pour obtenir le type du Pokémon
    virtual int getType() const = 0;

    // Méthode pour afficher les statistiques du Pokémon
    string afficherStat() const
    {
        return "Nom: " + nom + ", PV: " + to_string(pointsDeVie) + ", Attaque: " + to_string(attaque) + ", Défense: " + to_string(defense) + ", Vitesse: " + to_string(vitesse);
    }

    // Méthodes pour obtenir le nom et les points de vie du Pokémon
    string getNom()
    {
        return nom;
    }

    void perdrePV(int montant)
    {
        pointsDeVie = max(0, pointsDeVie - montant);
    }

    // Méthode pour restaurer les points de vie du Pokémon
    void restaurerPV()
    {
        pointsDeVie = pointsDeVieInitiaux;
    }

    // Méthode pour vérifier si le Pokémon est KO
    bool estKO() const
    {
        return pointsDeVie <= 0;
    }

    int getVitesse() const
    {
        return vitesse;
    }

    // Méthode pour activer l'attaque spéciale du Pokémon
    void activerAttaqueSpeciale()
    {
        // Activation de l'attaque spéciale avec une probabilité de 30%
        double chanceActivation = static_cast<double>(rand()) / RAND_MAX;

        // Affichage du message si l'attaque spéciale est activée
        if (chanceActivation < 0.3)
        {
            attaqueSpecialeActivee = true;
            cout << nom << " a activé son attaque spéciale !\n";
        }
    }

    // Méthode pour attaquer un autre Pokémon
    void attaquer(Pokemon &cible)
    {

        // Activer l'attaque spéciale avant de commencer l'attaque
        if (!attaqueSpecialeActivee)
        {
            activerAttaqueSpeciale();
        }

        // Le multiplicateur peut être modifié en fonction du type de Pokémon
        double multiplicateurType = calculerMultiplicateur(cible);

        double multiplicateurSpecial = attaqueSpecialeActivee ? 2.0 : 1.0;

        // Facteur aléatoire (entre 0.85 et 1.0)
        double facteurAleatoire = 0.85 + static_cast<double>(rand() % 16) / 100.0;

        // Calcul des dégâts infligés à la cible
        int degats = static_cast<int>((attaque * 50 / cible.defense) * multiplicateurType * multiplicateurSpecial * facteurAleatoire);

        cible.perdrePV(degats); // Réduction des points de vie de la cible

        // Affichage des dégâts infligés
        cout << nom << " attaque 💥 " << cible.nom << " et inflige " << degats << " dégâts.\n";
    }

protected:
    // Méthode virtuelle pour calculer le multiplicateur de dégâts
    virtual double calculerMultiplicateur(const Pokemon &cible) const
    {
        return 1.0; // Neutre par défaut
    }
};

// Classes dérivées pour chaque type de Pokémon
class FirePokemon : public Pokemon
{
public:
    FirePokemon(string nom, int pv, int atk, int def, int vit)
        : Pokemon(nom, pv, atk, def, vit) {}

    int getType() const override
    {
        return 1; // Feu
    }

protected:
    // Méthode pour calculer le multiplicateur de dégâts en fonction du type de Pokémon cible
    double calculerMultiplicateur(const Pokemon &cible) const override
    {
        if (cible.getType() == 2)
            return 0.5; // Eau
        if (cible.getType() == 3)
            return 2.0; // Plante
        return 1.0;
    }
};

class WaterPokemon : public Pokemon
{
public:
    WaterPokemon(string nom, int pv, int atk, int def, int vit)
        : Pokemon(nom, pv, atk, def, vit) {}

    int getType() const override
    {
        return 2; // Eau
    }
    // Méthode pour calculer le multiplicateur de dégâts en fonction du type de Pokémon cible
protected:
    double calculerMultiplicateur(const Pokemon &cible) const override
    {
        if (cible.getType() == 1)
            return 2.0; // Feu
        if (cible.getType() == 3)
            return 0.5; // Plante
        return 1.0;
    }
};

class GrassPokemon : public Pokemon
{
public:
    GrassPokemon(string nom, int pv, int atk, int def, int vit)
        : Pokemon(nom, pv, atk, def, vit) {}

    int getType() const override
    {
        return 3; // Plante
    }

protected:
    double calculerMultiplicateur(const Pokemon &cible) const override
    {
        if (cible.getType() == 1)
            return 0.5; // Feu
        if (cible.getType() == 2)
            return 2.0; // Eau
        return 1.0;
    }
};

class ElectricPokemon : public Pokemon
{
public:
    ElectricPokemon(string nom, int pv, int atk, int def, int vit)
        : Pokemon(nom, pv, atk, def, vit) {}

    int getType() const override
    {
        return 4; // Électrique
    }

protected:
    double calculerMultiplicateur(const Pokemon &cible) const override
    {
        if (cible.getType() == 2)
            return 2.0; // Eau
        if (cible.getType() == 3)
            return 1.5; // Plante
        if (cible.getType() == 4)
            return 0.5; // Électrique
        return 1.0;
    }
};

class RockPokemon : public Pokemon
{
public:
    RockPokemon(string nom, int pv, int atk, int def, int vit)
        : Pokemon(nom, pv, atk, def, vit) {}

    int getType() const override
    {
        return 5; // Roche
    }

protected:
    double calculerMultiplicateur(const Pokemon &cible) const override
    {
        if (cible.getType() == 1)
            return 0.5; // Feu
        if (cible.getType() == 3)
            return 2.0; // Plante
        if (cible.getType() == 5)
            return 0.5; // Roche
        return 1.0;
    }
};

// Génération aléatoire de Pokémon
// Retourne un pointeur unique vers un Pokémon
unique_ptr<Pokemon> genererPokemonAleatoire()
{
    // Types de Pokémon
    int type = rand() % 5 + 1; // 1: Feu, 2: Eau, 3: Plante, 4: Electrique, 5: Roche
    string nomsFeu[] = {"Salamèche", "Ponyta", "Dracaufeu"};
    string nomsEau[] = {"Carapuce", "Tentacruel", "Tortank"};
    string nomsPlante[] = {"Bulbizarre", "Florizarre", "Roserade"};
    string nomsElectrique[] = {"Pikachu", "Raichu", "Voltali"};
    string nomsRoche[] = {"Racaillou", "Gravalanch", "Tyranocif"};
    int pv = rand() % 31 + 120; // PV aléatoires entre 120 et 150
    int atk = rand() % 31 + 50; // Attaque aléatoire entre 50 et 80
    int def = rand() % 21 + 40; // Défense aléatoire entre 40 et 60
    int vit = rand() % 31 + 50; // Vitesse aléatoire entre 50 et 80

    switch (type)
    {
    case 1: // Feu
        // Retourne un pointeur unique vers un Pokémon de type Feu
        return make_unique<FirePokemon>(nomsFeu[rand() % 3], pv, atk, def, vit);
    case 2: // Eau
        // Retourne un pointeur unique vers un Pokémon de type Eau
        return make_unique<WaterPokemon>(nomsEau[rand() % 3], pv, atk, def, vit);
    case 3: // Plante
        // Retourne un pointeur unique vers un Pokémon de type Plante
        return make_unique<GrassPokemon>(nomsPlante[rand() % 3], pv, atk, def, vit);
    case 4: // Électrique
        // Retourne un pointeur unique vers un Pokémon de type Électrique
        return make_unique<ElectricPokemon>(nomsElectrique[rand() % 3], pv, atk, def, vit);
    case 5: // Roche
        // Retourne un pointeur unique vers un Pokémon de type Roche
        return make_unique<RockPokemon>(nomsRoche[rand() % 3], pv, atk, def, vit);
    default:
        // Retourne un pointeur nul si le type est invalide
        return nullptr;
    }
}

// Classe Joueur
class Joueur
{
    string nom;
    string nomEquipe;                   // Ajout du nom de l'équipe
    vector<unique_ptr<Pokemon>> equipe; // Utilisation de pointeurs uniques pour stocker les Pokémon

public:
    Joueur(string nom) : nom(nom), nomEquipe("Équipe sans nom") {}

    // Méthodes pour définir le nom de l'équipe et ajouter un Pokémon à l'équipe
    void setNomEquipe(const string &nomEquipe)
    {
        this->nomEquipe = nomEquipe;
    }

    string getNomEquipe() const
    {
        return nomEquipe;
    }

    void ajouterPokemon(unique_ptr<Pokemon> p)
    {
        if (equipe.size() < 6)
        {
            cout << "\nAjout de Pokémon dans l'équipe \"" << nomEquipe << "\" \n";
            cout << p->afficherStat(); // Afficher les stats du Pokémon ajouté
            equipe.push_back(move(p)); // Ajout du Pokémon à l'équipe
        }
        else
        {
            cout << "L'équipe est complète.\n";
        }
    }

    // Méthode pour sélectionner les trois premiers Pokémon de l'équipe
    vector<Pokemon *> selectionnerEquipe()
    {
        vector<Pokemon *> selection;
        for (size_t i = 0; i < min(static_cast<size_t>(3), equipe.size()); ++i)
        {
            selection.push_back(equipe[i].get());
        }
        return selection;
    }

    string getNom() const
    {
        return nom;
    }
};

// Fonction de combat entre deux équipes
void combattreEquipes(vector<Pokemon *> equipe1, vector<Pokemon *> equipe2, const string &nomEquipe1, const string &nomEquipe2)
{
    size_t i = 0, j = 0, x = 0;

    cout << "\n===== \"" << nomEquipe1 << "\" 🆚 \"" << nomEquipe2 << "\" ! =====\n\n";
    cout << "Equipe : " + nomEquipe1 << endl;
    while (x < equipe1.size())
    {
        cout << "\t" << equipe1[x]->afficherStat() << endl;
        x++;
    }
    x = 0;
    cout << "\nEquipe : " + nomEquipe2 << endl;
    while (x < equipe2.size())
    {
        cout << "\t" << equipe2[x]->afficherStat() << endl;
        x++;
    }
    while (i < equipe1.size() && j < equipe2.size())
    {
        cout << "\n=== " << equipe1[i]->getNom() << " ⚔️ " << equipe2[j]->getNom() << " ! ===\n";

        while (!equipe1[i]->estKO() && !equipe2[j]->estKO())
        {
            if (equipe1[i]->getVitesse() >= equipe2[j]->getVitesse())
            {
                // L'équipe 1 attaque d'abord
                equipe1[i]->attaquer(*equipe2[j]);
                if (equipe2[j]->estKO())
                {
                    cout << equipe2[j]->getNom() << " est KO 💀\n";
                    cout << equipe1[i]->getNom() << " Remporte la partie! 🏆\n";
                    break; // Sortie de la boucle si un Pokémon est KO
                }

                // L'équipe 2 répond avec une attaque si elle n'est pas KO
                equipe2[j]->attaquer(*equipe1[i]);
                if (equipe1[i]->estKO())
                {
                    cout << equipe1[i]->getNom() << " est KO 💀\n";
                    cout << equipe2[j]->getNom() << " Remporte la partie! 🏆\n";
                    break; // Sortie de la boucle si un Pokémon est KO
                }
            }
            else
            {
                // L'équipe 2 attaque d'abord
                equipe2[j]->attaquer(*equipe1[i]);
                if (equipe1[i]->estKO())
                {
                    cout << equipe1[i]->getNom() << " est KO 💀\n";
                    cout << equipe2[j]->getNom() << " Remporte la partie! 🏆\n";
                    break; // Sortie de la boucle si un Pokémon est KO
                }

                // L'équipe 1 répond avec une attaque si elle n'est pas KO
                equipe1[i]->attaquer(*equipe2[j]);
                if (equipe2[j]->estKO())
                {
                    cout << equipe2[j]->getNom() << " est KO 💀\n";
                    cout << equipe1[i]->getNom() << " Remporte la partie! 🏆\n";
                    break; // Sortie de la boucle si un Pokémon est KO
                }
            }
        }

        if (equipe1[i]->estKO())
            ++i;
        if (equipe2[j]->estKO())
            ++j;
    }

    if (i < equipe1.size())
    {
        cout << "\nL'équipe \"" << nomEquipe1 << "\" remporte le match 🏆🎉\n";
    }
    else
    {
        cout << "\nL'équipe \"" << nomEquipe2 << "\" remporte le match🏆🎉\n";
    }
}

// Fonction pour générer un joueur aléatoirement
Joueur genererJoueurAleatoire(vector<string> &nomsDejaUtilises)
{
    // Liste de noms possibles pour les joueurs
    string nomsJoueurs[] = {"Walid", "Rayane", "Léo", "Alex", "Mélissa"};
    string nomJoueur;

    // Recherche d'un nom non utilisé
    do
    {
        nomJoueur = nomsJoueurs[rand() % 5];
    } while (find(nomsDejaUtilises.begin(), nomsDejaUtilises.end(), nomJoueur) != nomsDejaUtilises.end());

    // Ajout du nom à la liste des noms déjà utilisés
    nomsDejaUtilises.push_back(nomJoueur);

    // Création du joueur avec un nom aléatoire
    Joueur joueur(nomJoueur);

    // Nom de l'équipe (aléatoire également)
    string nomsEquipes[] = {"Les Flammes Ardentes", "Les Vagues Infernales", "Les Tornades Mystiques", "Les Guerriers de la Nuit"};
    joueur.setNomEquipe(nomsEquipes[rand() % 4] + " (" + nomJoueur + ")");

    // Génération d'une équipe de 6 Pokémon
    for (int i = 0; i < 6; ++i)
    {
        joueur.ajouterPokemon(genererPokemonAleatoire());
    }

    return joueur;
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    vector<string> nomsDejaUtilises; // Liste pour suivre les noms déjà utilisés

    // Génération de deux joueurs aléatoires
    Joueur joueur1 = genererJoueurAleatoire(nomsDejaUtilises);
    Joueur joueur2 = genererJoueurAleatoire(nomsDejaUtilises);

    // Affichage des informations des joueurs
    cout << "\nNom de l'équipe de " << joueur1.getNom() << ": " << joueur1.getNomEquipe() << endl;
    cout << "Nom de l'équipe de " << joueur2.getNom() << ": " << joueur2.getNomEquipe() << endl;

    // Sélection des équipes
    auto equipe1 = joueur1.selectionnerEquipe();
    auto equipe2 = joueur2.selectionnerEquipe();

    // Combat entre les deux équipes
    combattreEquipes(equipe1, equipe2, joueur1.getNomEquipe(), joueur2.getNomEquipe());

    return 0;
}