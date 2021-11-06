#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
	if(argc == 2) {
		if(strncmp(argv[1], "--help", 7) == 0 || strncmp(argv[1], "-h", 3) == 0) {
			puts("Usage:\ncwdc -d [PATH] -c [COMMAND]");
			
			return 0;
		}

		puts("cwdc: missing operand.\x0ATry 'cwdc -h' or 'cwdc --help' for more information.");
		
		return -1;
	}
	else if(argc < 4) {
		puts("cwdc: missing operand.\x0ATry 'cwdc -h' or 'cwdc --help' for more information.");
	
		return -1;
	}

	int opt;
	char *dir, *command;

	while((opt = getopt(argc, argv, ":d:c:")) != -1) {
		switch(opt) {
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
	
	int n = strlen(getenv("PWD")) + 1;
	char *oldpwd;
	oldpwd = malloc(n);

	strcpy(oldpwd, getenv("PWD"));
	oldpwd[n] = '\0';
	setenv("OLDPWD", oldpwd, 1);

	int cd = chdir(dir);
	setenv("PWD", dir, 1);

	if(cd) {
		perror("cwdc");

		return -1;
	}

	system(command);

	free(dir);
	free(command);
	free(oldpwd);

	return 0;
}
