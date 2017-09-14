//C server for quiz game. A synchronized client/server message exchange(1 to 1).


#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>

char choice[255],playerName[255];
int correctAns;
void child(int sd);
void gameStart(int sd);
void askQue(int sd);
char* getQue(int queNo);
char* getAns(int queNo, char message);

int main(int argc, char *argv[])
{
	int sd, client, portNumber;
	socklen_t len;
	struct sockaddr_in servAdd;

	if(argc != 2)
	{
		printf("Call model: %s <Port #>\n", argv[0]);
		exit(0);
	}

	if ((sd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		fprintf(stderr, "Cannot create socket\n");
		exit(1);
	}

	servAdd.sin_family = AF_INET;
	servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
	sscanf(argv[1], "%d", &portNumber);
	servAdd.sin_port = htons((uint16_t)portNumber);
	bind(sd,(struct sockaddr*)&servAdd,sizeof(servAdd));
	listen(sd, 5);

	while(1)
	{
		client=accept(sd,(struct sockaddr*)NULL,NULL);
		printf("Got a client\n");
		if(!fork())
			gameStart(client);
		close(client);
	}
}
void gameStart(int sd)
{
	char gameOption[]="Please Select Your Option From Above List : ";
	write(sd,gameOption,strlen(gameOption)+1);
	if(!read(sd,choice,255))
	{
		close(sd);
		fprintf(stderr,"Connection Terminated\n");
		exit(0);
	}
	fprintf(stderr,"Selected Option is : %c\n",toupper(choice[0]));
	if(toupper(choice[0])=='S')
	{
		char msgString[]="Please Register Your Name :  ";
		write(sd,msgString,strlen(msgString)+1);
		if(!read(sd,playerName,255))
		{
			close(sd);
			fprintf(stderr,"Does not Find a Player Name\n");
			exit(0);
		}
		fprintf(stderr,"Player Name: %s\n",playerName);
		askQue(sd);
	}
	else
	{
		if(toupper(choice[0])=='H')
		{
	
		}
		else if(toupper(choice[0])=='Q')
		{
		  //if(!read(sd,playerName,255))
 	               	
                        	close(sd);
                        	fprintf(stderr,"Player Exits\n");
                        	exit(0);
                	
			
		}
	}
	
}
char* getQue(int queNo)
{
	char* genQuestion[1];
	switch(queNo)
	{
		//genQuestion[0]=strdup("\tQuestion 1: How many People are in this Room?\n\t\tA.1\tB.2\n\tC.4\tD.3\n\tAns:");
		case 1:
			genQuestion[0]=strdup("Question 1 :\n\nLevel one(G1) driver must keep their alcohol level to zero percent and be accompanied with the class G driver with alcohol level of less than:\n\n\t1. 0.00%\n\t2. 0.05%\n\t3. 0.08%\n\t4. 0.03%\nSelect Option :\n");
		break;
		case 2:
			genQuestion[0]=strdup("Question 2 :\n\nSnow tires are good for:\n\n\t1. summer driving\n\t2. all season driving\n\t3. winter driving\n\t4. spring and fall driving\nSelect Option :\n");
		break;
		case 3:
			genQuestion[0]=strdup("Question 3 :\n\nHighway 407 is:\n\n\t1. Longest highway of Ontario\n\t2. Is a new highway\n\t3. Is an express toll route\n\t4. An expressway to USA\nSelect Option :\n");
		break;
		case 4:
			genQuestion[0]=strdup("Question 4 :\n\nMost automobile skid because of:\n\n\t1. Under inflated tires\n\t2. Over-inflated-tires\n\t3. Snow-ice on the road\n\t4. Driving too fast\nSelect Option :\n");
		break;
		case 5:
			genQuestion[0]=strdup("Question 5 :\n\nIf you become very tired while driving:\n\n\t1. Stop and rest\n\t2. Drink coffee\n\t3. Drive faster to your destination\n\t4. Open window for the fresh air\nSelect Option :\n");
		break;	
		case 6:
			genQuestion[0]=strdup("Question 6:\n\nIf you are convicted for drink and driving for the first time, you will loss the drivers license for:\n\n\t1. 1 month\n\t2. 3 month\n\t3. 6 month\n\t4. 1 year\nSelect Option :\n");
		break;
		case 7:
			genQuestion[0]=strdup("Question 7:\n\nAs a level 2 driver your alcohol level must be:\n\n\t1. 0.00%\n\t2. 0.05%\n\t3. 0.08%\n\t4. 0.03%\nSelect Option :\n");
		break;
		case 8:
			genQuestion[0]=strdup("Question 8:\n\nIn Ontario there is a seat belt law,\n\n\t1. Yes\n\t2. No\n\t3. Only driving on open highway\n\t4. Only when driving in municipality\nSelect Option :\n");
		break;
		case 9:
			genQuestion[0]=strdup("Question 9:\n\nEvery accident must be reported to police where there is personal injury or when the damamge exceeds:\n\n\t1. $100\n\t2. $200\n\t3. $500\n\t4. $1000\nSelect Option :\n");
		break;
		case 10:
			genQuestion[0]=strdup("Question 10:\n\nWhat insurance coverage the owner gets who pays the uninsured motor vehicle fee?\n\n\t1. $10,000\n\t2. $20,000\n\t3. $30,000\n\t4. No insurance protection whatsoever\nSelect Option :\n");
		break;
	}
	return genQuestion[0];
}
char* getAns(int queNo, char message)
{
	int ansFlag=0;
	switch(queNo)
	{
		case 1:
			if(message=='2')
			{
				ansFlag=1;	
			}
		break;
		case 2:
			if(message=='3')
			{
				ansFlag=1;
			}
		break;
		case 3:
			if(message=='3')
			{
				ansFlag=1;
			}
		break;
		case 4:
			if(message=='4')
			{
				ansFlag=1;
			}
		break;
		case 5:
			if(message=='1')
			{
				ansFlag=1;
			}
		break;
		case 6:
			if(message=='4')
			{
				ansFlag=1;
			}
		break;
		case 7:
			if(message=='1')
			{
				ansFlag=1;
			}
		break;
		case 8:
			if(message=='1')
			{
				ansFlag=1;
			}
		break;
		case 9:
			if(message=='4')
			{
				ansFlag=1;
			}
		break;
		case 10:
			if(message=='4')
			{
				ansFlag=1;
			}
		break;
	}
	
	char *varifyAns="Sorry!!! Wrong Answer.\n\n";
	if(ansFlag==1)
	{
		correctAns++;
		varifyAns="Congrats!!! Correct Answer.\n\n";
	}	
	fprintf(stderr,"%s",varifyAns);
	//write(sd,varifyAns,strlen(varifyAns)+1);
	return varifyAns;

}
void askQue(int sd)
{
	correctAns=0;
	//char message[255];
	int questionNo=1;
	int totalQuestion=10;
	int firstQue=0;
	while(1)
	{
		char message[255]={'\0'};
		//int questionNo;
		char *question;
		char *ansResponse;
		question=getQue(questionNo);
		printf("\n");
		fprintf(stderr,"%s",question);
		//printf("\n");

		if(firstQue==0)
		{
			strcat(message,question);
			firstQue=1;
		}
		else
		{
			strcat(message,ansResponse);
			strcat(message,question);
		}

		write(sd,message,strlen(message)+1);
		if(!read(sd,message,255))
		{
			close(sd);
			fprintf(stderr,"Player Quits\n");
			exit(0);
		}
		fprintf(stderr,"Player Selected Option : %s\n",message);
		
		ansResponse=getAns(questionNo,message[0]);
		
		questionNo++;
		if(questionNo>totalQuestion)
		{
			fprintf(stderr,"You Score : %d",correctAns);
			char crtAns[255];
			sprintf(crtAns,"You Score : %d\n",correctAns);
			strcat(crtAns,"Would you like to play agian?(y/n) :");
			char srMsg[255]={'\0'};
			strcat(srMsg,ansResponse);
			strcat(srMsg,crtAns);
			write(sd,srMsg,strlen(srMsg)+1);
			if(!read(sd,srMsg,255))
			{
				close(sd);
                       		fprintf(stderr,"\nPlayer exits.\n");
                        	exit(0);
			}
			if(srMsg[0]=='y' || srMsg[0]=='Y')
			{
				questionNo=1;
				correctAns=0;
				firstQue=0;
			}	
			
		} 
	}
}
