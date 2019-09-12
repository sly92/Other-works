#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

#define TOTAL_USER 10     /* how many pending connections queue will hold */


const char	*CMD[] =
{
	"NICK", "USER", "QUIT", "JOIN",
	"NAMES", "LIST", "TOPIC", "PRIVMSG", "PING"
};

typedef struct user
{
	int	socket;
	char nick[TOTAL_USER];
	struct user *next;

} users;

typedef struct room
{
	users *users;
	struct room *next;

} rooms;

int max(int a, int b)
{
	if(a>b)
		return a;
	return b;
}

int getSize(char** tab)
{
	int i = 0;
	while(tab[i]!=NULL)
		i++;

	return i;
}

void launchAction(char *cmd, char *user, char *arg)
{
	const char	*CMD[] = [
		"NICK", "USER", "QUIT", "JOIN",
		"NAMES", "LIST", "PRIVMSG", "PING"
		];
		switch(cmd) {
			case CMD[0] :
			acceptUser(socket, u, a);
			break;
			case CMD[1] :
			getChannel(socket, u, a);
			break;

			default :{
				 char * msg =  "UNKNOWN COMMAND\r\n";
				write(socket, msg, strlen(msg));
			}
		}
}

void handleCmd( int fd )
{
	char *cmd;
	int i = 0;
	int j = 0;
	int k = 0;
	int n;
	char *token;

	memset(&cmd, 0, sizeof(cmd));
	while(1){

		if(read( fd, &cmd, strlen(cmd)) < 0){
			printf("Error in read");
		}

		printf("cmd: %s\n", cmd);

		char **str;
		token = strtok(cmd, " ");

		while( token != NULL ) {
			for(j=0;strlen(token);j++){
				str[i][j]=token;
			}

				token = strtok(NULL, " ");
				i++;
		}
	}

		launchAction(str[0],str[1],str[2]);
	}

	close(fd);
}

void
sendMessage(int socket, const char * user, const char * room, const char * mess)
{
    bool check = false;
    bool exist = false;
    int index = 0;

    for (int i = 0; i < getTotal(rooms); i++) {
        if (strcmp(rooms[i].name, room) == 0) {
            check = true;
            index = i;
            break;
        }
    }
    if(check) {
        for (int i = 0; i <getTotal(rooms[index].users); i++) {
            if(strcmp(rooms[index].users[i], user) == 0) {
                exist = true;
                break;
            }
        }}
        if (exist) {
            rooms[index].count ++;


            if(getTotal(rooms[index].messages) ==100)
                rooms[index].messages.erase(rooms[index].users[0]);
	            strcpy(temp,user);
	            strcat(temp," ");
	            strcat(temp, mess);
	            rooms[index].messages.push_back(strdup(temp));
	            const char * msg = "OK\r\n";
	            write(socket,msg,strlen(msg));
	            free(temp);

            return;
        }


    }

void acceptUser(int socket,  char * user,  char * args)
{
	servers s;
	int total_users;
	char *pseudo;

    printf("entrez votre pseudo :\n");
    scanf("%s", &pseudo);

	total_users = getSize(s->users);
	s->users[total_users+1]=pseudo;

	printf("%s",s->users[total_users+1])
}



void
getChannel(int socket, char * user, char * args) {
	for (int i = 0; i < getSize(rooms); i++) {
		write(socket, rooms[i].name, strlen(rooms[i].name));
		write(socket, "\r\n", strlen("\r\n"));
	}
}


int main(int argc,char *argv[])
{

	char buffer[256];
	int listen_fd, accepted_fd,new_fd, n, sock, conn;
	struct sockaddr_in server_addr;
	fd_set rdfs;
	int i=0,j=0,k=0,actif=0;
	int max_fd=0;
	int conn_tab[TOTAL_USER];
	int port;
	char *host;

	if(argc < 2) {
		printf("\nUsage: ./server [port]\n\n");
		exit(1);
	}
	host = argv[1];
	port = atoi(argv[2]);


	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("Error : socket creation");
           // exit(1);
	}
	printf("Bienvenue dans mon serveur IRC !\n");

	memset(&server_addr, 0, sizeof(server_addr));

	// = memset de 0 (plus utilisé)
	server_addr.sin_family = AF_INET;
	// human to numeric (1025 en binaire)
	server_addr.sin_port = htons(port);
	// INADDR_ANY ecoute de n'importe quel adresse
	server_addr.sin_addr.s_addr = INADDR_ANY;

	inet_pton(AF_INET,"127.0.0.1", &server_addr.sin_addr);

	// il attend un sockaddr * donc on caste en ça
	if (bind(listen_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {

		printf("Error : bind file descriptor");
            //exit(1);
	}


	// 10 est le nombre de co max

	if (listen(listen_fd, TOTAL_USER) != 0) {
		printf("Error : listen file descriptor");
           // exit(1);
	}
	printf("Listening on %s:%d\n !", host, port);
	// NULL car on ne veut pas des information des clients entrant dans le serveur


	max_fd = listen_fd;
	conn_tab[0] = listen_fd;
	actif++;

	while(1)
	{
		FD_ZERO(&rdfs);
		for(i=0;i<actif;i++)
			FD_SET(conn_tab[i], &rdfs);

		if( sock = select(max_fd, &rdfs, NULL, NULL, NULL) < 0)
		{
			printf("Error : select file descriptor");
               	//exit(1);
		}

 	// Gestion connexion client
		if(FD_ISSET(listen_fd, &rdfs))
		{
			if((conn = accept(listen_fd, (struct sockaddr*) NULL, NULL)) < 0){
				printf("Error accepting new socket");
				continue;
			}
			else{

				max_fd = max(max_fd, conn_tab[actif])+1;
				conn_tab[actif]=conn;
				actif++;
			}
		}
		for(j=0;j<actif;j++)
		{
			if(FD_ISSET(conn_tab[j],&rdfs)){
				memset(&buffer, 0, sizeof(buffer));
				handleCmd(conn_tab[j]);
				read(conn_tab[j], &buffer, 256);
				printf("%s", buffer);
				for(k=0;k<actif;k++)
					write(conn_tab[k], buffer, sizeof(buffer));
			}

		}

	}



	close(accepted_fd);
	close(listen_fd);

	return 0;
}
