/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprieur <eprieur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:31:26 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/12 14:20:35 by eprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include "header/parsing.h"
#include "header/utils.h"

void  history(char *line);

#endif


/*

============================ gestion de la ligme de commande et du prompt ========================================================

readline -> affiche un prompt et lit une ligne tappe par le user (elle doit etre free)

rl_clear_history -> vide completement l'historique des commandes stocke par readline

rl_on_new_line -> Indique à readline que l'on est passé à une nouvelle ligne (utile après un signal pour réinitialiser l'affichage).

rl_replace_line : Remplace le contenu de la ligne actuelle par un nouveau texte (souvent utilisé pour effacer la ligne lors d'un Ctrl-C).

rl_redisplay : Force readline à mettre à jour l'affichage du prompt et du texte à l'écran.

add_history : Enregistre la ligne que l'utilisateur vient de taper dans l'historique (pour pouvoir naviguer avec les flèches du haut/bas)


============================= I/O ================================================================================================

isatty : Vérifie si un descripteur de fichier correspond à un terminal.

ttyname : Renvoie le nom du terminal associé à un descripteur de fichier.

ttyslot : Donne l'indice du terminal actuel dans un fichier système (rarement utilisé en Minishell).

ioctl : Contrôle les paramètres des périphériques (souvent pour récupérer la taille de la fenêtre du terminal).

============================= memoire et environnement =============================================================================

getenv : Cherche et renvoie la valeur d'une variable d'environnement (ex: getenv("PATH")).

getcwd : Récupère le chemin absolu du répertoire de travail actuel.

chdir : Change le répertoire actuel (utilisé pour le built-in cd).

============================= process ===============================================================================================

fork : Crée un processus enfant qui est une copie conforme du parent.

wait : Suspend le parent jusqu'à ce qu'un de ses enfants se termine.

waitpid : Attend la fin d'un processus spécifique (plus précis que wait).

**wait3 / wait4 : Variantes de waitpid qui permettent de récupérer en plus des statistiques sur les ressources utilisées (CPU, mémoire).

execve : Remplace le processus actuel par un nouveau programme (ex: lance /bin/ls). C'est la fonction qui exécute les commandes.

exit : Termine le processus actuel avec un code de retour.

============================= signaux ================================================================================================

signal : Définit une fonction à appeler quand un signal arrive (ex: SIGINT pour Ctrl-C).

sigaction : Version plus moderne et précise de signal.

sigemptyset : Initialise un ensemble de signaux à vide.

sigaddset : Ajoute un signal spécifique à un ensemble.

kill : Envoie un signal à un processus (pas forcément pour le "tuer", mais pour communiquer)

============================= files et repo ===========================================================================================

stat / lstat / fstat : Récupèrent des informations détaillées sur un fichier (taille, type, droits). lstat ne suit pas les liens symboliques.

unlink : Supprime un nom de fichier du système (supprime le fichier si c'est le dernier lien).

opendir / readdir / closedir : Permettent d'ouvrir, de lire le contenu (la liste des fichiers) et de fermer un dossier.

============================= terminal =================================================================================================

Ces fonctions servent à configurer le comportement du clavier et de l'affichage du terminal (utilisées surtout pour la gestion du mode "raw" ou des touches spéciales).

    tcsetattr / tcgetattr : Modifient ou récupèrent les paramètres du terminal (ex: désactiver l'écho des touches).

    tgetent / tgetflag / tgetnum / tgetstr : Récupèrent les capacités du terminal depuis la base de données termcap.

    tgoto / tputs : Utilisées pour déplacer le curseur ou envoyer des commandes de formatage au terminal.

    
*/