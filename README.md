*This project has been created as part of the 42 curriculum by adjelili, eprieur.*

---

# 🐚 Minishell

> A fully functional Unix shell written in C, built from scratch as part of the 42 School curriculum.

---

## 📋 Table of Contents

- [Description](#description)
- [Features](#features)
- [Architecture](#architecture)
- [Instructions](#instructions)
- [Usage Examples](#usage-examples)
- [Testing & Memory](#testing--memory)
- [Resources](#resources)

---

## Description

**Minishell** is a project from the 42 School curriculum that challenges students to implement a simplified but fully functional Unix shell in C, inspired by `bash`. The goal is to understand how a shell works internally — from reading user input to executing commands — by implementing each layer from scratch: lexing, parsing, expanding, and executing.

This project covers a wide range of low-level systems programming concepts including process management, file descriptors, pipes, signals, environment variables, memory management, and more.

---

## Features

### 🔤 Lexer (adjelili)
The lexer is the first stage of the pipeline. It takes the raw string received from `readline` and breaks it into a **linked list of tokens** using a **Finite State Machine (FSM)**. The FSM transitions between states (default, in single quote, in double quote, in word, etc.) and only splits the input when it encounters a whitespace or a separator token — making it far more precise and efficient than a naive string split approach.

### 🌿 Parser & AST (eprieur)
The parser consumes the token list produced by the lexer and builds an **Abstract Syntax Tree (AST)**. Each node of the tree represents a logical unit of the command line (a command, a pipe, a logical operator, a subshell, etc.). The parser is written using **recursive descent parsing**, inspired by the grammar-based approach from *Crafting Interpreters*.

```
Example AST for: ls -la | grep foo && echo done

        &&
       /  \
      |    echo done
     / \
   ls   grep foo
  -la
```

Each AST node contains:
- A **linked list of redirections** (if any): `>`, `>>`, `<`, `<<`
- A **linked list of command arguments**

The parser also handles **syntax error detection**: unclosed parentheses, unclosed quotes, unexpected tokens, etc.

### 🔁 Expand (eprieur)
Before execution, every AST node goes through an **expansion phase**. This step:
- Removes single and double quotes
- Searches for `$VARIABLE` patterns and replaces them with their value from the environment

Expansion is done **just before each command executes**, which allows constructs like:
```bash
export a=42 && echo $a   # correctly prints 42
```
To avoid memory issues (conditional jumps, invalid reads), the expander uses a **pre-computation function** that predicts the exact size of the resulting string before `malloc`-ing it.

### ⚙️ Execution (adjelili)

#### Built-in Commands
Built-in commands are commands that are handled directly by the shell process itself, without forking a child process. They are necessary because they need to modify the shell's own state (e.g. changing the current directory or modifying environment variables). The following built-ins are implemented:

| Command | Description |
|---------|-------------|
| `echo` | Print arguments to stdout, supports `-n` flag |
| `cd` | Change the current working directory |
| `pwd` | Print the current working directory |
| `env` | Display all environment variables |
| `export` | Set or add environment variables |
| `unset` | Remove environment variables |
| `exit` | Exit the shell with an optional status code |

#### External Commands (`execve`)
Any command that is not a built-in is executed via `execve`. The shell searches for the binary in the directories listed in the `PATH` environment variable, forks a child process, and replaces it with the target program.

#### Pipes
A **pipe** (`|`) is a mechanism that connects the standard output (`stdout`) of one command to the standard input (`stdin`) of the next, using the `pipe()` system call. This creates a communication channel between two processes. Minishell supports chaining multiple commands with pipes, carefully managing all file descriptors to avoid leaks.

#### Redirections
Redirections allow commands to read from or write to file descriptors other than the standard ones (`stdin=0`, `stdout=1`, `stderr=2`). The following redirections are supported:

| Operator | Description |
|----------|-------------|
| `<` | Redirect stdin from a file |
| `>` | Redirect stdout to a file (truncate) |
| `>>` | Redirect stdout to a file (append) |
| `<<` | Heredoc (see below) |

#### Heredoc (`<<`)
A **heredoc** is a form of redirection that lets the user type multi-line input directly in the terminal until a delimiter word is reached. In Minishell, `readline` is used to read each line of the heredoc, which is written to a **temporary file**. The file descriptor of that temp file is stored in the command's AST node. The temporary file is then `unlink`-ed immediately after opening, so it cannot be accessed by other processes or interfere with other shell instances, while the file descriptor remains valid for the current command.

#### Subshells & Logical Operators
- **Subshells** (`(...)`) execute a group of commands in a forked child process, isolating changes to the environment or directory.
- **`&&`** executes the right-hand command only if the left-hand command succeeded (exit code 0).
- **`||`** executes the right-hand command only if the left-hand command failed (non-zero exit code).

### 🌍 Environment
The shell copies the initial `envp` array into an internal **linked list** at startup. This allows dynamic updates to environment variables (`export`, `unset`) throughout the shell session without modifying the original environment.

### 🛑 Signals
The shell handles Unix signals to mimic `bash` behavior:

| Signal | Key combo | Behavior |
|--------|-----------|----------|
| `SIGINT` | `Ctrl+C` | Interrupts current command, shows new prompt |
| `SIGQUIT` | `Ctrl+\` | Ignored in interactive mode |
| `EOF` | `Ctrl+D` | Exits the shell |

Signal handling is adapted depending on context (interactive prompt vs. child process execution).

### 🗑️ Garbage Collector
To guarantee **zero memory leaks** between commands and at program exit, Minishell uses a custom **garbage collector**: a global linked list where every dynamically allocated pointer is registered. This allows freeing all memory at once on error or exit.

The only known remaining leaks are internal to the **`readline` library** itself, which are suppressed using a Valgrind suppression file (`.readline.supp`).

---

## Architecture

```
Minishell/
├── src/
│   ├── lexer/          # FSM-based tokenizer → linked list of tokens
│   ├── parser/         # Recursive descent parser → AST
│   ├── expand/         # Variable expansion & quote removal
│   ├── execution/      # Built-ins, execve, pipes, redirections, heredoc
│   ├── env/            # Environment linked list management
│   ├── signals/        # Signal handlers
│   └── gc/             # Garbage collector
├── includes/           # Header files
├── .readline.supp      # Valgrind suppression file for readline leaks
├── Makefile
└── README.md
```

**Pipeline flow:**

```
readline input
     │
     ▼
  [LEXER]  ──────────────────── FSM → Token linked list
     │
     ▼
  [PARSER] ──────────────────── Recursive descent → AST
     │
     ▼
  [EXPAND] ──────────────────── $VAR substitution, quote removal
     │
     ▼
 [EXECUTE] ──────────────────── Built-ins / execve / pipes / redirections
```

---

## Instructions

### Prerequisites

- A Unix-like system (Linux or macOS)
- `gcc` or `cc`
- `make`
- `readline` library installed
  - On Ubuntu/Debian: `sudo apt install libreadline-dev`
  - On macOS (with Homebrew): `brew install readline`

### Installation & Compilation

```bash
# Clone the repository
git clone git@github.com:anisdjl/Minishell.git
cd Minishell

# Compile
make
```

### Running

```bash
./minishell
```

### Cleanup

```bash
# Remove object files
make clean

# Remove object files and binary
make fclean

# Recompile from scratch
make re
```

---

## Usage Examples

```bash
# Basic command
$ ls -la

# Pipe
$ ls | grep ".c" | wc -l

# Redirections
$ echo "hello" > output.txt
$ cat < output.txt
$ echo "world" >> output.txt

# Heredoc
$ cat << EOF
> Hello
> World
> EOF

# Environment variables
$ export MY_VAR=hello
$ echo $MY_VAR
hello

# Logical operators
$ mkdir test && cd test
$ cat nonexistent || echo "file not found"

# Subshell
$ (cd /tmp && ls)

# Built-ins
$ pwd
$ cd ..
$ env
$ unset MY_VAR
$ exit 0
```

---

## Testing & Memory

### Minishell Tester
The project was tested using community-built minishell testers to compare behavior against `bash`.

### Valgrind
To check for memory leaks and file descriptor leaks, run:

```bash
valgrind -s \
  --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  --suppressions=.readline.supp \
  --track-fds=yes \
  ./minishell
```

The `.readline.supp` suppression file tells Valgrind to ignore leaks internal to `libreadline`, which are outside our control:

```
{
    ignore_libreadline_leaks
    Memcheck:Leak
    ...
    obj:*/libreadline.so.*
}
```

---

## Resources

### Documentation & Articles

- [The Architecture of Open Source Applications — The Bourne-Again Shell (bash)](https://aosabook.org/en/v1/bash.html) — In-depth overview of how bash is structured internally: lexing, parsing, execution.
- [Minishell 42 — L'art de créer un shell performant et maintenable (Medium)](https://medium.com/@gibrat.dylan/minishell-42-lart-de-cr%C3%A9er-un-shell-performant-et-maintenable-53c0aede140e) — Community article from a 42 student covering architecture and design choices.
- [Crafting Interpreters — Parsing Expressions](https://craftinginterpreters.com/parsing-expressions.html) — Used to understand and implement recursive descent parsing for the AST.
- `bash --posix` — Used as the reference for all undefined or ambiguous shell behaviors. Whenever we were unsure how a particular input should be handled, we used `bash --posix` as the ground truth.
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.html) — Official reference for bash behavior and built-in commands.
- [`man` pages](https://man7.org/linux/man-pages/) — `man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`, `man 3 readline`, etc.

### Peer Learning
A significant part of our learning came from testing edge cases directly in the terminal and discussing behaviors with peers. The 42 peer learning community was an important resource for discovering subtle and undocumented behaviors of bash.

### AI Usage

AI (Claude / ChatGPT) was used throughout the project for the following purposes:

- **Learning new concepts**: Understanding Finite State Machines (FSMs) for the lexer, recursive descent parsing for the AST, and Unix signal handling.
- **Debugging**: Helping identify issues with pipes and unclosed file descriptors, as well as memory-related bugs (invalid reads, conditional jumps reported by Valgrind).
- **Understanding AST structure**: Evan used AI to get a clearer grasp on how to build and traverse an Abstract Syntax Tree in C, supplemented by *Crafting Interpreters*.
- AI was **never used to write production code directly** — it was used as a learning and debugging assistant.

---

---

# 🇫🇷 Version Française

---

*Ce projet a été créé dans le cadre du cursus 42 par adjelili, eprieur.*

---

# 🐚 Minishell

> Un shell Unix entièrement fonctionnel écrit en C, construit de zéro dans le cadre du cursus de l'école 42.

---

## 📋 Table des matières

- [Description](#description-1)
- [Fonctionnalités](#fonctionnalités)
- [Architecture](#architecture-1)
- [Instructions](#instructions-1)
- [Exemples d'utilisation](#exemples-dutilisation)
- [Tests & Mémoire](#tests--mémoire)
- [Ressources](#ressources-1)

---

## Description

**Minishell** est un projet du cursus 42 qui demande aux étudiants d'implémenter un shell Unix simplifié mais entièrement fonctionnel en C, inspiré de `bash`. L'objectif est de comprendre le fonctionnement interne d'un shell — de la lecture de l'entrée utilisateur à l'exécution des commandes — en implémentant chaque couche from scratch : le lexer, le parser, l'expansion et l'exécution.

Ce projet couvre un large éventail de concepts de programmation système bas niveau : gestion des processus, descripteurs de fichiers, pipes, signaux, variables d'environnement, gestion mémoire, et bien plus.

---

## Fonctionnalités

### 🔤 Lexer (adjelili)
Le lexer est la première étape du pipeline. Il prend la chaîne brute reçue de `readline` et la découpe en une **liste chaînée de tokens** grâce à une **Finite State Machine (FSM)**. La FSM transite entre différents états (défaut, dans une quote simple, dans une quote double, dans un mot, etc.) et ne découpe l'entrée que lorsqu'elle rencontre un espace ou un séparateur — ce qui est bien plus précis et efficace qu'un simple `split` naïf.

### 🌿 Parser & AST (eprieur)
Le parser consomme la liste de tokens produite par le lexer et construit un **Abstract Syntax Tree (AST)**. Chaque nœud de l'arbre représente une unité logique de la ligne de commande (une commande, un pipe, un opérateur logique, un sous-shell, etc.). Le parser est écrit en **recursive descent parsing**, inspiré de l'approche grammaticale de *Crafting Interpreters*.

```
Exemple d'AST pour : ls -la | grep foo && echo done

        &&
       /  \
      |    echo done
     / \
   ls   grep foo
  -la
```

Chaque nœud de l'AST contient :
- Une **liste chaînée de redirections** (si présentes) : `>`, `>>`, `<`, `<<`
- Une **liste chaînée d'arguments de commande**

Le parser gère également la **détection d'erreurs de syntaxe** : parenthèses non fermées, quotes non fermées, tokens inattendus, etc.

### 🔁 Expand (eprieur)
Avant l'exécution, chaque nœud de l'AST passe par une phase d'**expansion**. Cette étape :
- Supprime les quotes simples et doubles
- Recherche les patterns `$VARIABLE` et les remplace par leur valeur dans l'environnement

L'expansion est effectuée **juste avant chaque exécution de commande**, ce qui permet des constructions comme :
```bash
export a=42 && echo $a   # affiche correctement 42
```
Pour éviter les problèmes mémoire (conditional jumps, invalid reads), l'expander utilise une **fonction de pré-calcul** qui prédit la taille exacte de la chaîne résultante avant le `malloc`.

### ⚙️ Exécution (adjelili)

#### Commandes Built-in
Les commandes built-in sont des commandes gérées directement par le processus shell lui-même, sans forker de processus enfant. Elles sont nécessaires car elles doivent modifier l'état interne du shell (ex. : changer de répertoire ou modifier les variables d'environnement). Les built-ins suivants sont implémentés :

| Commande | Description |
|----------|-------------|
| `echo` | Affiche les arguments sur stdout, supporte le flag `-n` |
| `cd` | Change le répertoire courant |
| `pwd` | Affiche le répertoire courant |
| `env` | Affiche toutes les variables d'environnement |
| `export` | Définit ou ajoute des variables d'environnement |
| `unset` | Supprime des variables d'environnement |
| `exit` | Quitte le shell avec un code de sortie optionnel |

#### Commandes externes (`execve`)
Toute commande qui n'est pas un built-in est exécutée via `execve`. Le shell cherche le binaire dans les répertoires listés dans la variable d'environnement `PATH`, fork un processus enfant et le remplace par le programme cible.

#### Pipes
Un **pipe** (`|`) est un mécanisme qui connecte la sortie standard (`stdout`) d'une commande à l'entrée standard (`stdin`) de la suivante, via l'appel système `pipe()`. Cela crée un canal de communication entre deux processus. Minishell supporte le chaînage de plusieurs commandes avec des pipes, en gérant soigneusement tous les descripteurs de fichiers pour éviter les fuites.

#### Redirections
Les redirections permettent aux commandes de lire depuis ou d'écrire vers des descripteurs de fichiers autres que les standards (`stdin=0`, `stdout=1`, `stderr=2`). Les redirections suivantes sont supportées :

| Opérateur | Description |
|-----------|-------------|
| `<` | Redirige stdin depuis un fichier |
| `>` | Redirige stdout vers un fichier (écrase) |
| `>>` | Redirige stdout vers un fichier (ajoute) |
| `<<` | Heredoc (voir ci-dessous) |

#### Heredoc (`<<`)
Un **heredoc** est une forme de redirection qui permet à l'utilisateur de saisir plusieurs lignes directement dans le terminal jusqu'à atteindre un mot délimiteur. Dans Minishell, `readline` est utilisé pour lire chaque ligne du heredoc, qui est écrite dans un **fichier temporaire**. Le descripteur de ce fichier est stocké dans le nœud AST de la commande. Le fichier temporaire est immédiatement `unlink`-é après ouverture, ce qui empêche tout autre processus d'y accéder et évite toute interférence entre instances de shell, tout en gardant le descripteur valide pour la commande courante.

#### Sous-shells & Opérateurs logiques
- Les **sous-shells** (`(...)`) exécutent un groupe de commandes dans un processus enfant forké, isolant les modifications d'environnement ou de répertoire.
- **`&&`** exécute la commande de droite uniquement si celle de gauche a réussi (code de sortie 0).
- **`||`** exécute la commande de droite uniquement si celle de gauche a échoué (code de sortie non nul).

### 🌍 Environnement
Le shell copie le tableau `envp` initial dans une **liste chaînée interne** au démarrage. Cela permet des mises à jour dynamiques des variables d'environnement (`export`, `unset`) tout au long de la session sans modifier l'environnement d'origine.

### 🛑 Signaux
Le shell gère les signaux Unix pour reproduire le comportement de `bash` :

| Signal | Raccourci | Comportement |
|--------|-----------|--------------|
| `SIGINT` | `Ctrl+C` | Interrompt la commande courante, affiche un nouveau prompt |
| `SIGQUIT` | `Ctrl+\` | Ignoré en mode interactif |
| `EOF` | `Ctrl+D` | Quitte le shell |

La gestion des signaux est adaptée selon le contexte (prompt interactif vs exécution dans un processus enfant).

### 🗑️ Garbage Collector
Pour garantir **zéro fuite mémoire** entre les commandes et à la fermeture du programme, Minishell utilise un **garbage collector** maison : une liste chaînée globale où chaque pointeur alloué dynamiquement est enregistré. Cela permet de tout libérer en une seule passe en cas d'erreur ou à la sortie.

Les seules fuites connues sont internes à la **bibliothèque `readline`** elle-même, supprimées via un fichier de suppression Valgrind (`.readline.supp`).

---

## Architecture

```
Minishell/
├── src/
│   ├── lexer/          # Tokenizer FSM → liste chaînée de tokens
│   ├── parser/         # Parser récursif → AST
│   ├── expand/         # Expansion de variables & suppression des quotes
│   ├── execution/      # Built-ins, execve, pipes, redirections, heredoc
│   ├── env/            # Gestion de la liste chaînée d'environnement
│   ├── signals/        # Gestionnaires de signaux
│   └── gc/             # Garbage collector
├── includes/           # Fichiers d'en-tête
├── .readline.supp      # Fichier de suppression Valgrind pour readline
├── Makefile
└── README.md
```

**Flux du pipeline :**

```
Entrée readline
     │
     ▼
  [LEXER]  ──────────────────── FSM → liste chaînée de tokens
     │
     ▼
  [PARSER] ──────────────────── Descente récursive → AST
     │
     ▼
  [EXPAND] ──────────────────── Substitution $VAR, suppression quotes
     │
     ▼
 [EXECUTE] ──────────────────── Built-ins / execve / pipes / redirections
```

---

## Instructions

### Prérequis

- Un système de type Unix (Linux ou macOS)
- `gcc` ou `cc`
- `make`
- La bibliothèque `readline`
  - Sur Ubuntu/Debian : `sudo apt install libreadline-dev`
  - Sur macOS (avec Homebrew) : `brew install readline`

### Installation & Compilation

```bash
# Cloner le dépôt
git clone git@github.com:anisdjl/Minishell.git
cd Minishell

# Compiler
make
```

### Lancement

```bash
./minishell
```

### Nettoyage

```bash
# Supprimer les fichiers objets
make clean

# Supprimer les fichiers objets et le binaire
make fclean

# Recompiler from scratch
make re
```

---

## Exemples d'utilisation

```bash
# Commande basique
$ ls -la

# Pipe
$ ls | grep ".c" | wc -l

# Redirections
$ echo "hello" > output.txt
$ cat < output.txt
$ echo "world" >> output.txt

# Heredoc
$ cat << EOF
> Hello
> World
> EOF

# Variables d'environnement
$ export MY_VAR=hello
$ echo $MY_VAR
hello

# Opérateurs logiques
$ mkdir test && cd test
$ cat nonexistent || echo "fichier introuvable"

# Sous-shell
$ (cd /tmp && ls)

# Built-ins
$ pwd
$ cd ..
$ env
$ unset MY_VAR
$ exit 0
```

---

## Tests & Mémoire

### Minishell Tester
Le projet a été testé avec des testeurs communautaires pour comparer le comportement avec `bash`.

### Valgrind
Pour vérifier les fuites mémoire et les fuites de descripteurs de fichiers :

```bash
valgrind -s \
  --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  --suppressions=.readline.supp \
  --track-fds=yes \
  ./minishell
```

Le fichier `.readline.supp` indique à Valgrind d'ignorer les fuites internes à `libreadline`, hors de notre contrôle :

```
{
    ignore_libreadline_leaks
    Memcheck:Leak
    ...
    obj:*/libreadline.so.*
}
```

---

## Ressources

### Documentation & Articles

- [The Architecture of Open Source Applications — The Bourne-Again Shell (bash)](https://aosabook.org/en/v1/bash.html) — Vue d'ensemble approfondie de la structure interne de bash : lexing, parsing, exécution.
- [Minishell 42 — L'art de créer un shell performant et maintenable (Medium)](https://medium.com/@gibrat.dylan/minishell-42-lart-de-cr%C3%A9er-un-shell-performant-et-maintenable-53c0aede140e) — Article communautaire d'un étudiant 42 sur l'architecture et les choix techniques.
- [Crafting Interpreters — Parsing Expressions](https://craftinginterpreters.com/parsing-expressions.html) — Utilisé pour comprendre et implémenter le parsing récursif pour l'AST.
- `bash --posix` — Utilisé comme référence pour tous les comportements ambigus ou inconnus. Chaque fois qu'un comportement nous était inconnu, on se basait sur `bash --posix` comme vérité terrain.
- [Manuel GNU Bash](https://www.gnu.org/software/bash/manual/bash.html) — Référence officielle pour le comportement de bash et les commandes built-in.
- [Pages `man`](https://man7.org/linux/man-pages/) — `man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`, `man 3 readline`, etc.

### Peer Learning
Une grande partie de notre apprentissage est venue de tests d'edge cases directement dans le terminal et de discussions sur les comportements avec nos pairs. La communauté de peer learning de 42 a été une ressource importante pour découvrir les comportements subtils et non documentés de bash.

### Utilisation de l'IA

L'IA (Claude / ChatGPT) a été utilisée tout au long du projet pour :

- **Apprendre de nouveaux concepts** : comprendre les FSM pour le lexer, le parsing récursif pour l'AST, et la gestion des signaux Unix.
- **Déboguer** : identifier des problèmes avec les pipes et les descripteurs de fichiers non fermés, ainsi que des bugs mémoire (invalid reads, conditional jumps reportés par Valgrind).
- **Comprendre la structure de l'AST** : Evan a utilisé l'IA pour mieux appréhender la construction et la traversée d'un AST en C, en complément de *Crafting Interpreters*.
- L'IA n'a **jamais été utilisée pour écrire du code de production directement** — elle a servi d'assistant d'apprentissage et de débogage.
