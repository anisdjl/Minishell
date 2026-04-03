# Guide Debug Macros (Minishell)

Ce guide te donne une méthode simple pour:
- activer/désactiver des logs sans supprimer du code,
- isoler une partie précise de l'exécution,
- éviter de te perdre quand il y a fork + pipes + redirections.

---

## 1) Macros de base à copier

Crée un header `debug.h` (ou colle ce bloc dans un header déjà inclus partout):

```c
#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>
# include <unistd.h>

/* Activer avec: make CFLAGS+="-DDEBUG" */
#ifdef DEBUG
# define DBG(fmt, ...) \
	dprintf(2, "[DBG][%d] %s:%d:%s(): " fmt "\n", \
		getpid(), __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
# define DBG(fmt, ...) ((void)0)
#endif

/* Canaux ciblés */
#ifdef DEBUG_AST
# define DBG_AST(fmt, ...) DBG("[AST] " fmt, ##__VA_ARGS__)
#else
# define DBG_AST(fmt, ...) ((void)0)
#endif

#ifdef DEBUG_EXEC
# define DBG_EXEC(fmt, ...) DBG("[EXEC] " fmt, ##__VA_ARGS__)
#else
# define DBG_EXEC(fmt, ...) ((void)0)
#endif

#ifdef DEBUG_PIPE
# define DBG_PIPE(fmt, ...) DBG("[PIPE] " fmt, ##__VA_ARGS__)
#else
# define DBG_PIPE(fmt, ...) ((void)0)
#endif

#endif
```

### Build exemples

```bash
make clean && make CFLAGS+="-DDEBUG -DDEBUG_PIPE"
make clean && make CFLAGS+="-DDEBUG -DDEBUG_EXEC -DDEBUG_AST"
```

---

## 2) Où mettre les logs (stratégie efficace)

### AST

- juste après création d'un nœud (`type`, présence de `left/right`),
- quand tu attaches une redirection (`type`, `value`),
- quand tu détectes un subshell avec suffixe redirection.

Exemple:

```c
DBG_AST("node type=%d left=%p right=%p redirs=%p", node->type, node->left, node->right, node->redirs);
```

### EXEC

- entrée de `exec(...)` avec `ast->type`,
- dans `subshell(...)` avant/après `redir_function(node)`,
- juste avant `exec(node->left, ...)`.

Exemple:

```c
DBG_EXEC("exec type=%d", ast ? ast->type : -1);
DBG_EXEC("subshell redirs=%p", node->redirs);
```

### PIPES / FD

- dans `handle_pipes`: `fd_in`, `fd_out`, type du nœud,
- avant/après `redir_for_pipes`,
- juste après chaque `dup2` et `close` important.

Exemple:

```c
DBG_PIPE("node=%d fd_in=%d fd_out=%d", node->type, fd_in, fd_out);
DBG_PIPE("after redir_for_pipes fd_in=%d fd_out=%d", fd_in, fd_out);
```

---

## 3) Isoler UNE partie du code (sans casser le reste)

Le but: exécuter seulement une branche (ex: subshell) pendant 5 minutes de debug.

Ajoute des switches temporaires:

```c
/* Activer avec: -DONLY_SUBSHELL ou -DONLY_WORD */
#ifdef ONLY_SUBSHELL
# define RUN_ONLY_SUBSHELL 1
#else
# define RUN_ONLY_SUBSHELL 0
#endif

#ifdef ONLY_WORD
# define RUN_ONLY_WORD 1
#else
# define RUN_ONLY_WORD 0
#endif
```

Puis dans le dispatcher:

```c
if (RUN_ONLY_SUBSHELL && ast->type != L_PARENTHESE)
	return (0);
if (RUN_ONLY_WORD && ast->type != WORD)
	return (0);
```

⚠️ Règle d'or: ces guards sont temporaires. Tu les enlèves dès que le bug est compris.

Build:

```bash
make clean && make CFLAGS+="-DDEBUG -DDEBUG_EXEC -DONLY_SUBSHELL"
```

---

## 4) Debug runtime sans recompiler (optionnel)

Tu peux aussi activer des logs avec variable d'environnement:

```c
static int dbg_enabled(const char *name)
{
	char *v = getenv(name);
	return (v && *v == '1');
}

if (dbg_enabled("MSH_DEBUG_PIPE"))
	DBG_PIPE("fd_in=%d fd_out=%d", fd_in, fd_out);
```

Usage:

```bash
MSH_DEBUG_PIPE=1 ./minishell
```

---

## 5) Recette anti-panique (très courte)

1. Réduis à une commande minimale qui casse.
2. Active un seul canal (`DEBUG_PIPE` ou `DEBUG_EXEC`).
3. Trace seulement: `type`, `fd_in`, `fd_out`, `dup2`, `close`.
4. Corrige un point.
5. Reteste la même commande.
6. Élargis seulement après succès.

---

## 6) Cas de test utiles pour ton projet

```bash
(echo hello > outfile) > outfile2
(echo hello) | cat
(echo hello) | (cat)
(cat < infile) | (grep x > out)
```

Attendu:
- redirection interne plus proche de la commande,
- pas de blocage sur les pipes,
- fermeture propre des FDs non utilisés.
