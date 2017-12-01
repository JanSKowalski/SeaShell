#include "seashell.h"

//For readability of code
#define WAITING 1


static void sig_handler(int signo){
	if (signo == SIGINT){
		char message[] = "\n --And thus ends SeaShell. Enjoy your day!-- \n";
		printf("%s", message);
		exit(SIGINT);
	}
}


int main(){

	//Output for Interrupt
	signal(SIGINT, sig_handler);

	char input[1024];

	while(WAITING){
		//Input from terminal, halts loop
		fgets(input, sizeof(input), stdin);
		record_in_log(input);


		//Splits input by ';'
		char **commands = parse_args(input, ";");


		int i = 0;
		char *line;
		//Runs every command provided
		while((line = commands[i++]) != NULL){
        
            printf("%c\n", line[0]);

            while(line[0] == ' '){
                line = line++; 
            } 
            
            printf("%c\n", line[0]);

			/* Special Conditions */

			//Exit condition
			if (strcmp(line, "exit\n") == 0){
				exit(0);
            }

			char **command = parse_args(line, " ");


			//Cd condition
			//Possibility that a command ending in cd triggers
			//if (strstr(line, "cd ") == 0)

			//Strsep by ;, then while loop

			int parent = fork();

			if(parent){
				int status;
				wait(&status);
			}

			if(!parent){
				//execvp automatically releases memory
				execvp(command[0], command);
			}
		}
	}

	return 0;
}
