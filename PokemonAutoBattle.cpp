// Créé par Walid Madad et Rayane Benchokroun
// Date de création: 2024-12-25
// Dernière modification: 2025-01-25
// Le Français est la langue principale du code

// Nom du programme: Pokémon Auto-Battle
/* Description: Ce programme simule un combat Pokémon entre deux équipes de trois Pokémon chacune.
   Chaque Pokémon a un type (Feu, Eau, Plante, Électrique, Roche) qui influence les dégâts infligés.
   Les dégâts sont calculés en fonction de l'attaque, de la défense, de la vitesse et du type des Pokémon.
   Les Pokémon peuvent également activer une attaque spéciale avec une probabilité de 30% pour infliger des dégâts supplémentaires.
   Le programme affiche les statistiques des Pokémon, les dégâts infligés et le résultat du combat.
   Les Pokémon KO sont restaurés après chaque combat.
*/

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

#include <algorithm> // Pour std::find
#include <iostream>  // Pour std::cout
#include <vector>    // Pour std::vector
#include <string>    // Pour std::string
#include <cstdlib>   // Pour std::rand et std::srand
#include <ctime>     // Pour std::time
#include <memory>    // Pour std::unique_ptr et std::make_unique

using namespace std;

// Classe de base Pokemon
class Pokemon
{
    // Attributs nom, points de vie, attaque, défense, vitesse, points de vie initiaux et attaque spéciale activée
protected:
    string nom;
    int pointsDeVie;
    int attaque;
    int defense;
    int vitesse;
    int pointsDeVieInitiaux;
    bool attaqueSpecialeActivee = false; // Attribut pour suivre l'activation de l'attaque spéciale
    bool attaqueSpecialeDejaActivee = false;

public:
    // Constructeur avec initialisation des attributs
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

    // Méthode pour réduire les points de vie du Pokémon
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

    // Méthode pour obtenir la vitesse du Pokémon
    int getVitesse() const
    {
        return vitesse;
    }

    // Méthode pour activer l'attaque spéciale du Pokémon
    void activerAttaqueSpeciale()
    {
        if (!attaqueSpecialeDejaActivee) // Ne pas réactiver si déjà activée
        {
            // Activation de l'attaque spéciale avec une probabilité de 30%
            double chanceActivation = static_cast<double>(rand()) / RAND_MAX;

            if (chanceActivation < 0.3) // 30% de chance d'activation
            {
                attaqueSpecialeActivee = true;                       // Activer l'attaque spéciale
                attaqueSpecialeDejaActivee = true;                   // Assurer que l'attaque spéciale est activée une seule fois
                cout << nom << " a activé son attaque spéciale !\n"; // Affichage du message
            }
        }
    }

    // Méthode pour attaquer un autre Pokémon
    void attaquer(Pokemon &cible) // references pour modifer l'objet directement sans creer une copie
    {

        // Activer l'attaque spéciale avant de commencer l'attaque
        if (!attaqueSpecialeActivee)
        {
            activerAttaqueSpeciale();
        }

        // Le multiplicateur peut être modifié en fonction du type de Pokémon
        double multiplicateurType = calculerMultiplicateur(cible);
        double multiplicateurSpecial = 1.0;

        if (attaqueSpecialeActivee)
        {
            multiplicateurSpecial = 2.0;
        }
        attaqueSpecialeActivee = false; // Réinitialiser l'attaque spéciale

        // Facteur aléatoire (entre 0.85 et 1.0)
        double facteurAleatoire = 0.85 + static_cast<double>(rand() % 16) / 100.0;

        // Calcul des dégâts infligés à la cible
        int degats = static_cast<int>((attaque * 20 / cible.defense) * multiplicateurType * multiplicateurSpecial * facteurAleatoire);

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

// Classes dérivées pour les pokémons de type Feu
class FirePokemon : public Pokemon
{
public:
    FirePokemon(string nom, int pv, int atk, int def, int vit)
        : Pokemon(nom, pv, atk, def, vit) {}

    // Destructeur de FirePokemon
    ~FirePokemon() override
    {
    }
    // Méthode pour obtenir le type du Pokémon
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

// Classe dérivée pour les Pokémon de type Eau
class WaterPokemon : public Pokemon
{
public:
    WaterPokemon(string nom, int pv, int atk, int def, int vit)
        : Pokemon(nom, pv, atk, def, vit) {}

    // Destructeur de la classe WaterPokemon
    ~WaterPokemon() override
    {
    }
    // Méthode pour obtenir le type du Pokémon
    int getType() const override
    {
        return 2; // Eau
    }

protected:
    // Méthode pour calculer le multiplicateur de dégâts en fonction du type de Pokémon cible
    double calculerMultiplicateur(const Pokemon &cible) const override
    {
        if (cible.getType() == 1)
            return 2.0; // Feu
        if (cible.getType() == 3)
            return 0.5; // Plante
        return 1.0;
    }
};

// Classe dérivée pour les Pokémon de type Plante
class GrassPokemon : public Pokemon
{
public:
    GrassPokemon(string nom, int pv, int atk, int def, int vit)
        : Pokemon(nom, pv, atk, def, vit) {}

    // Destructeur de la classe GrassPokemon
    ~GrassPokemon() override
    {
    }
    // Méthode pour obtenir le type du Pokémon
    int getType() const override
    {
        return 3; // Plante
    }

protected:
    // Méthode pour calculer le multiplicateur de dégâts en fonction du type de Pokémon cible
    double calculerMultiplicateur(const Pokemon &cible) const override
    {
        if (cible.getType() == 1)
            return 0.5; // Feu
        if (cible.getType() == 2)
            return 2.0; // Eau
        return 1.0;
    }
};

// Classe dérivée pour les Pokémon de type Électrique
class ElectricPokemon : public Pokemon
{
public:
    ElectricPokemon(string nom, int pv, int atk, int def, int vit)
        : Pokemon(nom, pv, atk, def, vit) {}

    // Destructeur de la classe ElectricPokemon
    ~ElectricPokemon() override
    {
    }
    // Méthode pour obtenir le type du Pokémon
    int getType() const override
    {
        return 4; // Électrique
    }

protected:
    // Méthode pour calculer le multiplicateur de dégâts en fonction du type de Pokémon cible
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

// Classe dérivée pour les Pokémon de type Roche
class RockPokemon : public Pokemon
{
public:
    RockPokemon(string nom, int pv, int atk, int def, int vit)
        : Pokemon(nom, pv, atk, def, vit) {}

    // Destructeur de la classe RockPokemon
    ~RockPokemon() override
    {
    }
    // Méthode pour obtenir le type du Pokémon
    int getType() const override
    {
        return 5; // Roche
    }

protected:
    // Méthode pour calculer le multiplicateur de dégâts en fonction du type de Pokémon cible
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
unique_ptr<Pokemon> genererPokemonAleatoire() // pointeur unique pour éviter les fuites de mémoire
{
    // Types de Pokémon
    int type = rand() % 5 + 1;                                      // 1: Feu, 2: Eau, 3: Plante, 4: Electrique, 5: Roche
    string nomsFeu[] = {"Salamèche", "Ponyta", "Dracaufeu"};        // Noms de Pokémon feu
    string nomsEau[] = {"Carapuce", "Tentacruel", "Tortank"};       // Noms de Pokémon eau
    string nomsPlante[] = {"Bulbizarre", "Florizarre", "Roserade"}; // Noms de Pokémon plante
    string nomsElectrique[] = {"Pikachu", "Raichu", "Voltali"};     // Noms de Pokémon électrique
    string nomsRoche[] = {"Racaillou", "Gravalanch", "Tyranocif"};  // Noms de Pokémon roche
    int pv = rand() % 31 + 200;                                     // Points de vie aléatoires entre 200 et 230
    int atk = rand() % 21 + 30;                                     // Attaque aléatoire entre 30 et 50
    int def = rand() % 11 + 20;                                     // Défense aléatoire entre 20 et 40
    int vit = rand() % 11 + 20;                                     // Vitesse aléatoire entre 20 et 40

    switch (type) // Sélection du type de Pokémon
    {
    case 1: // Feu
        // Retourne un pointeur unique vers un Pokémon de type Feu
        return make_unique<FirePokemon>(nomsFeu[rand() % 3], pv, atk, def, vit); // make_unique pour éviter les fuites de mémoire
    case 2:                                                                      // Eau
        // Retourne un pointeur unique vers un Pokémon de type Eau
        return make_unique<WaterPokemon>(nomsEau[rand() % 3], pv, atk, def, vit); // make_unique pour éviter les fuites de mémoire
    case 3:                                                                       // Plante
        // Retourne un pointeur unique vers un Pokémon de type Plante
        return make_unique<GrassPokemon>(nomsPlante[rand() % 3], pv, atk, def, vit); // make_unique pour éviter les fuites de mémoire
    case 4:                                                                          // Électrique
        // Retourne un pointeur unique vers un Pokémon de type Électrique
        return make_unique<ElectricPokemon>(nomsElectrique[rand() % 3], pv, atk, def, vit); // make_unique pour éviter les fuites de mémoire
    case 5:                                                                                 // Roche
        // Retourne un pointeur unique vers un Pokémon de type Roche
        return make_unique<RockPokemon>(nomsRoche[rand() % 3], pv, atk, def, vit); // make_unique pour éviter les fuites de mémoire
    default:
        // Retourne un pointeur nul si le type est invalide
        return nullptr;
    }
}

// Classe Joueur
class Joueur
{
    string nom;                         // Nom du joueur
    string nomEquipe;                   // Ajout du nom de l'équipe
    vector<unique_ptr<Pokemon>> equipe; // Utilisation de pointeurs uniques pour stocker les Pokémon

public:
    Joueur()
    {
        nom = "";
        equipe.clear(); // Initialisation de l'équipe
    }
    Joueur(string nom) : nom(nom), nomEquipe("Équipe sans nom") {} // Constructeur avec initialisation du nom du joueur et de l'équipe

    // Méthodes pour définir le nom de l'équipe et ajouter un Pokémon à l'équipe
    void setNomEquipe(const string &nomEquipe)
    {
        this->nomEquipe = nomEquipe;
    }

    // Méthode pour obtenir le nom de l'équipe
    string getNomEquipe() const
    {
        return nomEquipe;
    }

    // Méthode pour ajouter un Pokémon à l'équipe
    void ajouterPokemon(unique_ptr<Pokemon> p) // Ajout de pointeurs uniques
    {
        if (equipe.size() < 6)
        {
            cout << "\nAjout de Pokémon dans l'équipe \"" << nomEquipe << "\" \n";
            cout << p->afficherStat(); // Afficher les stats du Pokémon ajouté
            equipe.push_back(move(p)); // Ajout du Pokémon à l'équipe
        }
        else
        {
            cout << "L'équipe est complète.\n"; // Message si l'équipe est complète
        }
    }

    // Méthode pour sélectionner les trois premiers Pokémon de l'équipe
    vector<Pokemon *> selectionnerEquipe() // Retourne un vecteur de pointeurs de Pokémon
    {
        vector<Pokemon *> selection;                                            // Vecteur de pointeurs de Pokémon
        for (size_t i = 0; i < min(static_cast<size_t>(3), equipe.size()); ++i) // Sélection des trois premiers Pokémon
        {
            selection.push_back(equipe[i].get()); // Ajout du pointeur du Pokémon à la sélection
        }
        return selection;
    }

    // Méthode pour obtenir le nom du joueur
    string getNom() const
    {
        return nom;
    }
};

// Fonction de combat entre deux équipes
string combattreEquipes(vector<Pokemon *> equipe1, vector<Pokemon *> equipe2, const string &nomEquipe1, const string &nomEquipe2)
{
    size_t i = 0, j = 0, x = 0; // Indices pour les équipes

    cout << "\n===== \"" << nomEquipe1 << "\" 🆚 \"" << nomEquipe2 << "\" ! =====\n\n"; // Affichage des noms des équipes
    cout << "Equipe : " + nomEquipe1 << endl;                                           // Affichage des statistiques des Pokémon
    while (x < equipe1.size())
    {
        cout << "\t" << equipe1[x]->afficherStat() << endl;
        x++;
    }
    x = 0;
    cout << "\nEquipe : " + nomEquipe2 << endl; // Affichage des statistiques des Pokémon
    while (x < equipe2.size())
    {
        cout << "\t" << equipe2[x]->afficherStat() << endl;
        x++;
    }
    while (i < equipe1.size() && j < equipe2.size())
    {
        cout << "\n=== " << equipe1[i]->getNom() << " ⚔️ " << equipe2[j]->getNom() << " ! ===\n"; // Affichage des noms des Pokémon

        while (!equipe1[i]->estKO() && !equipe2[j]->estKO())
        {
            if (equipe1[i]->getVitesse() >= equipe2[j]->getVitesse()) // Vérifier la vitesse des Pokémon pour déterminer qui attaque en premier
            {
                // L'équipe 1 attaque d'abord
                equipe1[i]->attaquer(*equipe2[j]); // Attaque du Pokémon de l'équipe 1
                if (equipe2[j]->estKO())           // Vérifier si le Pokémon de l'équipe 2 est KO
                {
                    cout << equipe2[j]->getNom() << " est KO 💀\n";
                    cout << equipe1[i]->getNom() << " Remporte la partie! 🏆\n";
                    break; // Sortie de la boucle si un Pokémon est KO
                }

                // L'équipe 2 répond avec une attaque si elle n'est pas KO
                equipe2[j]->attaquer(*equipe1[i]); // Attaque du Pokémon de l'équipe 2
                if (equipe1[i]->estKO())           // Vérifier si le Pokémon de l'équipe 1 est KO
                {
                    cout << equipe1[i]->getNom() << " est KO 💀\n";
                    cout << equipe2[j]->getNom() << " Remporte la partie! 🏆\n";
                    break; // Sortie de la boucle si un Pokémon est KO
                }
            }
            else // Si la vitesse du Pokémon de l'équipe 2 est supérieure
            {
                // L'équipe 2 attaque d'abord
                equipe2[j]->attaquer(*equipe1[i]); // Attaque du Pokémon de l'équipe 2
                if (equipe1[i]->estKO())           // Vérifier si le Pokémon de l'équipe 1 est KO
                {
                    cout << equipe1[i]->getNom() << " est KO 💀\n";
                    cout << equipe2[j]->getNom() << " Remporte la partie! 🏆\n";
                    break; // Sortie de la boucle si un Pokémon est KO
                }

                // L'équipe 1 répond avec une attaque si elle n'est pas KO
                equipe1[i]->attaquer(*equipe2[j]); // Attaque du Pokémon de l'équipe 1
                if (equipe2[j]->estKO())           // Vérifier si le Pokémon de l'équipe 2 est KO
                {
                    cout << equipe2[j]->getNom() << " est KO 💀\n";
                    cout << equipe1[i]->getNom() << " Remporte la partie! 🏆\n";
                    break; // Sortie de la boucle si un Pokémon est KO
                }
            }
        }

        if (equipe1[i]->estKO()) // Vérifier si le Pokémon de l'équipe 1 est KO
            ++i;
        if (equipe2[j]->estKO()) // Vérifier si le Pokémon de l'équipe 2 est KO
            ++j;
    }
    // Retourner le nom de l'équipe gagnante
    if (i < equipe1.size())
    {
        cout << "\nL'équipe \"" << nomEquipe1 << "\" remporte le match 🏆🎉\n";
        int x = 0;
        while (x < equipe1.size()) // Restaurer les points de vie des Pokémon
        {
            equipe1[x]->restaurerPV();
            x++;
        }
        return nomEquipe1;
    }
    else
    {
        cout << "\nL'équipe \"" << nomEquipe2 << "\" remporte le match🏆🎉\n";
        int x = 0;
        while (x < equipe2.size()) // Restaurer les points de vie des Pokémon
        {
            equipe2[x]->restaurerPV();
            x++;
        }
        return nomEquipe2;
    }
}

// Fonction pour générer un joueur aléatoirement
Joueur genererJoueurAleatoire(vector<string> &nomsDejaUtilises)
{
    // Liste de noms possibles pour les joueurs
    string nomsJoueurs[] = {"Walid", "Rayane", "Mathieu", "Elissa", "Yanis", "Léo", "Lina"};

    // Varibale pour stocker un nom aléatoire pour le joueur
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
        // Ajout d'un Pokémon aléatoire à l'équipe du joueur
        joueur.ajouterPokemon(genererPokemonAleatoire());
    }

    return joueur;
}

// Fonction pour organiser un combat entre deux joueurs
string combattre(Joueur &joueur1, Joueur &joueur2)
{
    // Sélectionner les équipes
    auto equipe1 = joueur1.selectionnerEquipe();
    auto equipe2 = joueur2.selectionnerEquipe();

    // Affichage des informations des joueurs
    cout << "\nMatch entre " << joueur1.getNom() << " et " << joueur2.getNom() << "!\n";

    // Combat entre les deux équipes
    if (combattreEquipes(equipe1, equipe2, joueur1.getNomEquipe(), joueur2.getNomEquipe()) == joueur1.getNomEquipe())
    {
        return joueur1.getNom();
    }
    else
    {
        return joueur2.getNom();
    }
}

// Fonction pour organiser un tournoi entre quatre joueurs
void tournoi(Joueur &joueur1, Joueur &joueur2, Joueur &joueur3, Joueur &joueur4)
{
    // Tournoi à élimination directe
    cout << "\n=== Début du tournoi ===\n";
    // Premier match (joueur1 contre joueur2)
    cout << "\nPremier match : " << joueur1.getNom() << " contre " << joueur2.getNom() << endl;
    string gagnant1 = combattre(joueur1, joueur2);
    if (gagnant1 == joueur1.getNom())
    {
        // Deuxième match (joueur3 contre joueur4)
        cout << "\n=== Demi finale ===" << endl;
        string gagnant2 = combattre(joueur3, joueur4);
        if (gagnant2 == joueur3.getNom())
        {
            // Finale (gagnants des deux premiers matchs)
            cout << "\n===🏆 Finale 🏆===\n";
            string winner = combattre(joueur1, joueur3);
            cout << "The Winner is " << winner << " 🏆🏆🏆";
        }
        else
        {
            // Finale (gagnants des deux premiers matchs)
            cout << "\n===🏆 Finale 🏆===\n";
            string winner = combattre(joueur1, joueur4);
            cout << "The Winner is " << winner << " 🏆🏆🏆";
        }
    }
    else
    {
        // Deuxième match (joueur3 contre joueur4)
        cout << "\n=== Demi finale ===" << endl;
        string gagnant2 = combattre(joueur3, joueur4);
        if (gagnant2 == joueur3.getNom())
        {
            // Finale (gagnants des deux premiers matchs)
            cout << "\n=== 🏆 Finale 🏆===\n";
            string winner = combattre(joueur2, joueur3);
            cout << "The Winner is " << winner << " 🏆🏆🏆";
        }
        else
        {
            // Finale (gagnants des deux premiers matchs)
            cout << "\n===🏆 Finale 🏆===\n";
            string winner = combattre(joueur1, joueur4);
            cout << "The Winner is " << winner << " 🏆🏆🏆";
        }
    }
}

int main()
{
    srand(static_cast<unsigned>(time(0))); // Initialisation de la graine pour la génération aléatoire

    vector<string> nomsDejaUtilises; // Liste pour suivre les noms déjà utilisés

    // Génération de quatre joueurs aléatoires
    Joueur joueur1 = genererJoueurAleatoire(nomsDejaUtilises);
    Joueur joueur2 = genererJoueurAleatoire(nomsDejaUtilises);
    Joueur joueur3 = genererJoueurAleatoire(nomsDejaUtilises);
    Joueur joueur4 = genererJoueurAleatoire(nomsDejaUtilises);

    // Organiser un tournoi entre les quatre joueurs
    tournoi(joueur1, joueur2, joueur3, joueur4);

    return 0;
}