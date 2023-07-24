#ifndef MAIN_H
#define MAIN_H

#define BUFFER_SIZE 1024
#define EXIT_COMMAND "exit"

extern char **environ;

void display_prompt(void);
char *read_command(void);
void execute_command(char *command);
char *find_command(char *command);
pid_t create_child_process(void);
void run_command(char *command);
void print_environment(void);
void free_tokens(char **argv, int count);
void execute_piped_commands(char *first_command, char *second_command);
void trim_whitespace(char *str);

#endif
