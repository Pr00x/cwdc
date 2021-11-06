#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<termios.h>

int main(int argc, char *argv[]) {
	int opt;
	char *dir, *command;

	while((opt = getopt(argc, argv, ":hd:c:")) != -1) {
		switch(opt) {
			case 'h':
				puts("Usage:\ncwdc -d [PATH] -c [COMMAND]");

				return 0;
			case 'd':
				dir = malloc(strlen(optarg) + 1);
				strcpy(dir, optarg);
				*(dir + (strlen(optarg))) = '\0';
				break;
			case 'c':
				command = malloc(strlen(optarg) + 1);
				strcpy(command, optarg);
				*(command + (strlen(optarg))) = '\0';
				break;
			case ':':
				puts("cwdc: option needs a value");

				return -1;
			case '?':
				printf("cwdc: unknown option '%c'.\x0A", optopt);

				return -1;
		}
	}
	
	if(dir == NULL || command == NULL) {
		puts("cwdc: missing operand.\x0ATry 'cwdc -h' for more information.");

		return -1;
	}

	struct termios orig;
	char *pwd = getenv("PWD");
	size_t n = strlen(pwd) + 1;
	char *oldpwd;
	oldpwd = malloc(n);

	strcpy(oldpwd, pwd);
	oldpwd[n] = '\0';
	setenv("OLDPWD", oldpwd, 1);

	int cd = chdir(dir);
	setenv("PWD", dir, 1);

	if(cd) {
		perror("cwdc");

		return -1;
	}

	tcgetattr(STDIN_FILENO, &orig);

	system(command);

	tcsetattr(STDIN_FILENO, TCSANOW, &orig);

	free(dir);
	free(command);
	free(oldpwd);

	return 0;
}
