# Pokémon Auto-Battle

## Description

Ce programme simule un combat Pokémon entre deux équipes de trois Pokémon chacune. Chaque Pokémon a un type (Feu, Eau, Plante, Électrique, Roche) qui influence les dégâts infligés. Les dégâts sont calculés en fonction de l'attaque, de la défense, de la vitesse et du type des Pokémon. Les Pokémon peuvent également activer une attaque spéciale avec une probabilité de 30% pour infliger des dégâts supplémentaires. Le programme affiche les statistiques des Pokémon, les dégâts infligés et le résultat du combat.

## Fonctionnalités

- **Génération aléatoire de Pokémon**: Chaque Pokémon est généré avec des statistiques variées (points de vie, attaque, défense, vitesse) et un type aléatoire. Les types disponibles sont Feu, Eau, Plante, Électrique et Roche.
- **Simulation de combats**: Les combats prennent en compte les types de Pokémon et les attaques spéciales pour déterminer les dégâts infligés. Les attaques spéciales ont une probabilité de 30% de se déclencher et infligent des dégâts supplémentaires.
- **Organisation de tournois**: Le programme permet d'organiser des tournois entre plusieurs joueurs, avec des matchs à élimination directe. Chaque joueur peut avoir une équipe de six Pokémon, et les matchs se déroulent jusqu'à ce qu'un gagnant soit déterminé.

## Compilation

Pour compiler et exécuter le programme, utilisez la commande suivante :

```sh
g++ Pokemon.cpp -o Pokemon -std=c++11 && ./Pokemon
```

## Exemple de sortie

```
===== "Les Flammes Ardentes (Walid)" 🆚 "Les Vagues Infernales (Rayane)" ! =====
Equipe : Les Flammes Ardentes (Walid)
    Nom: Dracaufeu, PV: 150, Attaque: 80, Défense: 60, Vitesse: 80
    Nom: Salamèche, PV: 120, Attaque: 50, Défense: 40, Vitesse: 50
    Nom: Dracaufeu, PV: 150, Attaque: 80, Défense: 60, Vitesse: 80
Equipe : Les Vagues Infernales (Rayane)
    Nom: Voltali, PV: 150, Attaque: 80, Défense: 60, Vitesse: 80
    Nom: Pikachu, PV: 120, Attaque: 50, Défense: 40, Vitesse: 50
    Nom: Voltali, PV: 150, Attaque: 80, Défense: 60, Vitesse: 80
=== Dracaufeu ⚔️ Voltali ! ===
Dracaufeu a activé son attaque spéciale !
Dracaufeu attaque 💥 Voltali et inflige 100 dégâts
Voltali attaque 💥 Dracaufeu et inflige 50 dégât
Dracaufeu attaque 💥 Voltali et inflige 100 dégâts
Voltali est KO 💀
Les Flammes Ardentes (Walid) remporte le match 🏆🎉
```

## Classes Principales

- **`Pokemon`**: Classe de base pour tous les Pokémon, contenant les attributs et méthodes communs. Les attributs incluent les points de vie, l'attaque, la défense, la vitesse et le type.
- **`FirePokemon`**, **`WaterPokemon`**, **`GrassPokemon`**, **`ElectricPokemon`**, **`RockPokemon`**: Classes dérivées représentant les différents types de Pokémon, avec des méthodes spécifiques pour calculer les multiplicateurs de dégâts en fonction des types.
- **`Joueur`**: Classe représentant un joueur avec une équipe de Pokémon. Permet de gérer l'ajout de Pokémon, la sélection de l'équipe pour les combats et le suivi des victoires et des défaites.

## Utilisation

1. **Génération de joueurs**: Le programme génère quatre joueurs avec des équipes de six Pokémon chacun. Chaque joueur reçoit des Pokémon avec des statistiques et des types aléatoires.
2. **Organisation de combats**: Les joueurs s'affrontent dans des matchs à élimination directe. Les combats sont simulés en tenant compte des statistiques et des types des Pokémon, ainsi que des attaques spéciales.
3. **Affichage des résultats**: Le programme affiche les statistiques des Pokémon, les dégâts infligés et le résultat des combats. Les résultats des matchs sont affichés jusqu'à ce qu'un gagnant du tournoi soit déterminé.

## Auteur

- Walid Madad
- Rayane Benchokroun

## Date de création

- 2024-12-25

## Dernière modification

- 2025-01-25

## Langue principale

- Français
