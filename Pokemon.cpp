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

    // Méthode pour attaquer un autre Pokémon
    void attaquer(Pokemon &cible)
    {
        // Multiplicateur par défaut : neutre (1.0)
        // Le multiplicateur peut être modifié en fonction du type de Pokémon
        double multiplicateurType = calculerMultiplicateur(cible);

        // Facteur aléatoire (entre 0.85 et 1.0)
        double facteurAleatoire = 0.85 + static_cast<double>(rand() % 16) / 100.0;

        int degats = static_cast<int>((attaque * 50 / cible.defense) * multiplicateurType * facteurAleatoire);
        cible.perdrePV(degats);

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
unique_ptr<Pokemon> genererPokemonAleatoire()
{
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
        return make_unique<FirePokemon>(nomsFeu[rand() % 3], pv, atk, def, vit);
    case 2: // Eau
        return make_unique<WaterPokemon>(nomsEau[rand() % 3], pv, atk, def, vit);
    case 3: // Plante
        return make_unique<GrassPokemon>(nomsPlante[rand() % 3], pv, atk, def, vit);
    case 4: // Électrique
        return make_unique<ElectricPokemon>(nomsElectrique[rand() % 3], pv, atk, def, vit);
    case 5: // Roche
        return make_unique<RockPokemon>(nomsRoche[rand() % 3], pv, atk, def, vit);
    default:
        return nullptr;
    }
}

// Classe Joueur
class Joueur
{
    string nom;
    string nomEquipe; // Ajout du nom de l'équipe
    vector<unique_ptr<Pokemon>> equipe;

public:
    Joueur(string nom) : nom(nom), nomEquipe("Équipe sans nom") {}

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
            equipe.push_back(move(p));
        }
        else
        {
            cout << "L'équipe est complète.\n";
        }
    }

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

int main()
{
    srand(static_cast<unsigned>(time(0)));

    // Création des joueurs
    string nomJoueur1 = "Walid";
    string nomJoueur2 = "Rayane";

    Joueur joueur1(nomJoueur1);
    Joueur joueur2(nomJoueur2);

    // Définir les noms des équipes
    string nomEquipe1 = "Les Flammes Ardentes";
    string nomEquipe2 = "Les Vagues Infernales";
    joueur1.setNomEquipe(nomEquipe1 + " (" + nomJoueur1 + ")");
    joueur2.setNomEquipe(nomEquipe2 + " (" + nomJoueur2 + ")");

    // Ajout de Pokémon aux équipes
    for (int i = 0; i < 4; ++i)
    {
        joueur1.ajouterPokemon(genererPokemonAleatoire());
        joueur2.ajouterPokemon(genererPokemonAleatoire());
    }

    // Sélection des équipes
    auto equipe1 = joueur1.selectionnerEquipe();
    auto equipe2 = joueur2.selectionnerEquipe();

    // Combat entre les deux équipes
    combattreEquipes(equipe1, equipe2, joueur1.getNomEquipe(), joueur2.getNomEquipe());
    return 0;
}
