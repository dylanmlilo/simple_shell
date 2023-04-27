#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define END_OF_FILE -2
#define EXIT -3

	void prompt(char **av, char **env);
	int proc_file_commands(char *file_path, int *exe_ret);
	extern char **environ;
	char *name;
	int hist;

/**
 * struct builtin_s - New struct type defining builtin commands
 *
 * @name: name of the builtin command
 * @f: function pointer to the builtin command's function
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct list_s - New struct type defining a linked list
 *
 * @dir: directory path
 * @next: pointer to another struct list_s
 */

typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct alias_s - New struct defining aliases
 *
 * @name: name of the alias
 * @value: value of the alias
 * @next: pointer to another struct alias_s
 */

typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

	/* Main function helpers */
	ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
	void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
	list_t *get_path_dir(char *path);
	int execute(char **args, char **front);
	void free_list(list_t *head);
	char **_strtok(char *line, char *delim);
	char *get_location(char *command);
	char *_itoa(int num);

	alias_t *aliases;

	/* Input helpers */
	int call_args(char **args, char **front, int *exe_ret);
	int run_args(char **args, char **front, int *exe_ret);
	int handle_args(int *exe_ret);
	int check_args(char **args);
	void handle_line(char **line, ssize_t read);
	void variable_replacement(char **args, int *exe_ret);
	void free_args(char **args, char **front);
	char **replace_aliases(char **args);
	char *get_args(char *line, int *exe_ret);

	/* Builtins */
	int (*get_builtin(char *command))(char **args, char **front);
	int shellby_alias(char **args, char __attribute__((__unused__)) **front);
	int shellby_help(char **args, char __attribute__((__unused__)) **front);
	int shellby_exit(char **args, char **front);
	int shellby_env(char **args, char __attribute__((__unused__)) **front);
	int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
	int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
	int shellby_cd(char **args, char __attribute__((__unused__)) **front);
	char **_copyenv(void);
	char **_getenv(const char *var);
	void free_env(void);

	/* String functions */
	int _strlen(const char *str);
	char *_strchr(char *str, char c);
	int _strspn(char *str, char *accept);
	char *_strcpy(char *dest, const char *src);
	char *_strcat(char *dest, const char *src);
	char *_strncat(char *dest, const char *src, size_t n);
	int _strcmp(char *str1, char *str2);
	int _strncmp(const char *str1, const char *str2, size_t n);

	/* Error handlers */
	int create_error(char **args, int err);
	char *error_env(char **args);
	char *error_1(char **args);
	char *error_2_exit(char **args);
	char *error_2_cd(char **args);
	char *error_2_syntax(char **args);
	char *error_126(char **args);
	char *error_127(char **args);

	/* Linked_list helpers */
	alias_t *add_alias_end(alias_t **head, char *name, char *value);
	list_t *add_node_end(list_t **head, char *dir);
	void free_alias_list(alias_t *head);
	void free_list(list_t *head);
	void help_all(void);
	void help_alias(void);
	void help_cd(void);
	void help_exit(void);
	void help_help(void);
	void help_history(void);
	void help_env(void);
	void help_setenv(void);
	void help_unsetenv(void);

#endif
