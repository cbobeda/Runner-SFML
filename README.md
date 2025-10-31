# 🏃 Neon Runner

Un petit jeu de **plateforme / runner** développé en **C++** avec **SFML 3.0**.  
Le joueur doit courir, sauter et dasher pour éviter les obstacles et collecter des pièces dans un univers néon coloré et dynamique.

---

## 🎮 Aperçu

Le jeu génère des plateformes de manière procédurale et simule une course infinie.  
Inspiré de jeux comme *Geometry Dash*, il met l’accent sur la **fluidité du gameplay**, un **dash rapide** et un **saut réactif**.

---

## 👥 Équipe et contributions

| Développeur | Rôle principal |
|--------------|----------------|
| **Clément** | Génération procédurale de la map, création des menus, gestion du son, ajout du score et système de sauvegarde entre les parties |
| **Téo** | Conception du joueur (gravité, collisions, contrôles, saut fixe et dash fluide) |

---

## ✨ Fonctionnalités principales

- Mouvement fluide basé sur un système de **vélocité**
- **Saut fixe** (hauteur déterminée, inspiré des platformers rétro)
- **Dash horizontal** progressif avec cooldown
- **Collisions précises** avec les plateformes
- **Collecte de pièces** et suppression dynamique après contact
- **Recyclage des tuiles** pour un défilement infini
- **Système de score** persistant entre les parties
- **Menu principal** et **pause**
- **Ambiance sonore** et **effets de couleur dynamiques**

---

## 🕹️ Contrôles

| Action | Touche / Souris |
|--------|-----------------|
| **Sauter** | Clic gauche |
| **Dash** | Clic droit |
| **Pause / Reprendre** | A |
| **Quitter** | Échap |

---

## 🛠️ Installation

### Prérequis
- **C++20** ou supérieur  
- **SFML 3.0** (modules Graphics, Audio, System, Window)
