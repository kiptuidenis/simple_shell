#ifndef MAIN_H
#define MAIN_H

#define BUFFER_SIZE 1024

void display_prompt(void);
char *read_command(void);
void execute_command(char *command);
char *find_command(char *command);

#endif
