# 🌊 OceanDepths — Aventure Textuelle Sous-Marine (2025)

OceanDepths est un jeu d’exploration et de combat entièrement codé en C en 2025, dans le cadre d’un projet académique.  
Le but du programme : plonger dans les profondeurs marines, survivre aux créatures redoutables, gérer ses ressources vitales et découvrir des trésors perdus des abysses.

Ce projet met en œuvre :
- de la génération procédurale (créatures, zones…)
- un système de combat tour par tour
- une gestion de ressources (PV, oxygène, fatigue)
- un inventaire complet (objets, équipements)
- une carte océanique multi-zones

---

## 🐚 Sommaire
- Fonctionnalités
- Structure du projet
- Compilation & exécution
- Mécaniques principales
- Système de combat
- Inventaire & récompenses
- Sauvegarde
- Éléments techniques
- Améliorations possibles
- Auteur

---

## 🌊 Fonctionnalités
- Génération aléatoire de **1 à 4 créatures marines** selon la profondeur.
- Combats tour par tour incluant fatigue, gestion d’oxygène, effets spéciaux.
- Exploration d’une **carte océanique** multi-zones.
- Inventaire complet et récompenses évolutives.
- Interface textuelle immersive.

---

## 📂 Structure du projet

```
oceandepths/
├── src/
│   └── .c
├── include/
│   └── .h
├── saves/
├── main.c
├── Makefile
├── config.txt (optionnel)
└── README.md
```

---

## ⚙️ Compilation & exécution

### Compiler
```bash
make
```

### Exécuter
```bash
./oceandepths
```

### Nettoyer
```bash
make clean
```

### Vérification mémoire
```bash
valgrind --leak-check=full ./oceandepths
```

---

## ⚔️ Système de combat

### Tour de combat
1. Affichage  
2. Actions joueur  
3. Consommation oxygène  
4. Attaque des créatures  
5. Récupération fatigue  
6. Vérification fin  

---

## 🎁 Inventaire & récompenses

- Harpons  
- Combinaisons  
- Objets (soins, armes...)  
- Perles  

---

## 💾 Sauvegarde

Format texte structuré :

```
OCEANDEPTHS_SAVE_V1
PLONGEUR:87:100:58:100:3:127
INVENTAIRE:Capsule_O2:3;Trousse_Soin:1
EQUIPEMENT:Harpon_Rouille:Neoprene_Basic
POSITION:247:Recif_Corallien
CREATURES:Kraken:124:156;Requin:89:89;Meduse:23:34
```

---

## 🚀 Améliorations possibles
- Système d'expérience  
- Boutique  
- Nouvelles zones  
- Événements aléatoires  
- Interface ASCII avancée  

---

## ✍️ Auteur
Projet développé en 2025 par **ZreY27 & antoineeeeeeeee**.
