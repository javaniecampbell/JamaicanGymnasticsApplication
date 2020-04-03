// JamaicanGymnasticsApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <float.h>

#define SIZE 100
#define STRINGLENGTH 100
 //typedef enum { false, true} bool;
typedef enum Genders {
	MALE,
	FEMALE
} Gender;

typedef enum CompetitionTypes
{
	INDIVIDUAL = 1,
	ALLROUND
} CompetitionType;

typedef struct Countries {
	int id;
	char name[STRINGLENGTH];
} Country;

typedef struct Schools {
	int id;
	char name[STRINGLENGTH];
	Country country;
} School;

typedef struct DateOfBirth {
	int day;
	int month;
	int year;
} DOB;
typedef struct Events {
	int id;
	char eventName[STRINGLENGTH];
} Event;

typedef struct JudgeScores {
	int id;
	int eventId;
	float score;
} JudgeScore;

typedef struct Participants
{
	int id;
	char firstName[STRINGLENGTH];
	char lastName[STRINGLENGTH];
	DOB dateOfBirth;
	char age[STRINGLENGTH];
	Gender *gender;
	School school;
	JudgeScore scores[5];
	float averageScore;
	CompetitionType competitionType;
	Event registeredEvents[6];
} Participant;





void Menu();
struct tm* currentDateTime();
void RegisterParticipant(Participant participants[]);
Participant* ViewParticipant(const int id);
void DisplayParticipant(Participant * participant);
void DisplayIndividualEventWinners(Participant participants[],int eventId);
void DisplayAllRoundEventWinners(Participant participants[]);
void DisplayOverallWinners(Participant participants[]);
float AverageScores(Participant *participant);
void AcceptJudgesScore(Participant *participant, JudgeScore score, int judgeId, int eventId);
char* FormatDateOfBirth(DOB dateOfBirth);
void CreateAndSaveCSV(const char* filename, Participant *participant);
bool file_exists(const char *filename);
void SelectCompetitionType(Participant * participants, int i);
void SaveAll(Participant *participants);
int currentlyRegistered = 0;
Participant participants[SIZE];

Event MaleEvents[6] = {
	{1,"floor exercise"},
	{2,"parallel bars"},
	{3,"pommel horse"},
	{4,"still rings"},
	{5,"vault"},
	{6, "uneven bars" }
};

Event FemaleEvents[4] = {
	{1,"vault"},
	{2, "uneven bars" },
	{3,"balance beam"},
	{4,"floor exercise"}
};

int main()
{
	Participant participant = {
		0,
		"",
		"",
	{0,0,0},
		"",
		NULL,
	{0,"",{0, ""} },
	{{0,0,0.0f},{0,0,0.0f},{0,0,0.0f},{0,0,0.0f},{0,0,0.0f}},
		0.0f,
		ALLROUND,
	{{0, ""},{0, ""},{0, ""},{0, ""},{0, ""},{0, ""}},
	};
	//CreateCSV("Participants.csv"//, participant
	//);

	for (int i = 0; i < SIZE; i++)
	{
		participants[i] = participant;
	}

	Menu();
	return 0;
}

struct tm* currentDateTime()
{
	time_t timer;
	struct tm* tm_info;
	//char day[3];
	//char month[3];
	//char year[5];
	time(&timer);
	tm_info = localtime(&timer);
	return tm_info;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

void Menu()
{

	int option = 0, participantID = 0;

	printf("Welcome to Jamaican Gynastics Application\n");
	printf("\n(1) Register Participant");
	printf("\n(2) Add Judges Score for Individual Event");
	printf("\n(3) Add Judges Score for All-Round Event");
	printf("\n(4) View Participant Details");
	printf("\n(5) View Individual Event Winners");
	printf("\n(6) View All-Round Event Winners");

	printf("\n(7) View Overall Report");
	printf("\n(8) Save All");
	printf("\n(0) Exit");
	printf("\n\nEnter Your Selection Here: ");
	scanf("%d", &option);
	Participant *participant = NULL;
	while (option != 0)
	{
		switch (option)
		{
		case 1:
			fflush(stdin);
			RegisterParticipant(participants);
			break;
		case 2:
			fflush(stdin);
			participantID = 0;
			float judgeScore = 0.0f;
			system("cls");
			printf("(2) Add Judges Score for Individual Event\n");
			printf("\nEntering Score for Participant Number: \n> ");
			scanf("%d", &participantID);
			participant = ViewParticipant(participantID);
		
			
			for (int i = 1; i < 6; i++)
			{
				printf("\nEntering Judge #%d Score : \n> ", i);
				scanf("%f", &judgeScore);
				JudgeScore score = { i,participant->registeredEvents[0].id, judgeScore };
				AcceptJudgesScore(participant, score , i, participant->registeredEvents[0].id);
			}

			DisplayParticipant(participant);

			system("pause");
			break;
		case 3:
			fflush(stdin);
			participantID = 0;
			int eventId = 0;
			system("cls");
			printf("(3) Add Judges Score for All-Round Event\n");
			printf("\nEntering Score for Participant Number: \n> ");
			scanf("%d", &participantID);
			participant = ViewParticipant(participantID);
			printf("\nEntering Score for Event Number: \n> ");
			scanf("%d", &eventId);
			

			for (int i = 0; i < 5; i++)
			{
				AcceptJudgesScore(participant, participant->scores[i], i, eventId);
			}

			//participant->averageScore = AverageScores(participant);

			DisplayParticipant(participant);
			system("pause");
			break;
		case 4:
			fflush(stdin);
			participantID = 0;
			system("cls");
			printf("(4) View Participant Details\n");
			printf("\nEntering Score for Participant Number: \n> ");
			scanf("%d", &participantID);
			participant = ViewParticipant(participantID);
			DisplayParticipant(participant);
			system("pause");
			break;
		case 5:
			fflush(stdin);
			system("cls");
			printf("(5) View Individual Event Winners\n");

			system("pause");
			break;
		case 6:
			fflush(stdin);
			system("cls");
			printf("(6) View All-Round Event Winners\n");

			system("pause");
			break;

		case 7:
			system("cls");
			printf("(7) View Overall Report\n");
			system("pause");
			break;
		case 8:
			SaveAll(participants);
			break;
		default:
			system("cls");
			printf("\nInvalid Option\n");
			system("pause");
			exit(1);
			break;

		}


		system("cls");
		printf("Welcome to Jamaican Gynastics Application\n");
		printf("\n(1) Register Participant");
		printf("\n(2) Add Judges Score for Individual Event");
		printf("\n(3) Add Judges Score for All-Round Event");
		printf("\n(4) View Participant Details");
		printf("\n(5) View Individual Event Winners");
		printf("\n(6) View All-Round Event Winners");

		printf("\n(7) View Overall Report");
		printf("\n(8) Save All");
		printf("\n(0) Exit");

		printf("\n\nEnter Your Selection Here: ");
		scanf("%d", &option);
		participant = NULL;

	}
}


void RegisterParticipant(Participant participants[])
{
	int records = 0;

	system("cls");
	printf("\n(1) Register Participant\n");

	printf("\nHow many participants will be entered?\n> ");
	scanf("%d", &records);
	if (records < SIZE) {
		for (int i = 0; i < records; i++)
		{

			/*int id;
			char *name;
			DOB dateOfBirth; day month year
			char *age;
			School school; id name
			JudgeScore scores[5]; eventId, score
			float averageScore;*/

			printf("\nEnter Participant's First Name:\n");
			scanf("%s", participants[i].firstName);
			printf("\nEnter Participant's Last Name:\n");
			scanf("%s", participants[i].lastName);
			printf("\nEnter Participant's Gender: \n> (m) Male | (f) Female : ");
			char gender[6];
			scanf("%s", gender);

			participants[i].gender = ((strcmp(gender, "m") == 0) || (strcmp(gender, "male") == 0) || (strcmp(gender, "MALE") == 0)) ? (Gender*)MALE : ((strcmp(gender, "f") == 0) || (strcmp(gender, "female") == 0) || (strcmp(gender, "FEMALE") == 0)) ? (Gender*)FEMALE : NULL;

			printf("\nEnter Participant's Day of Birth:\n");
			scanf("%d", &participants[i].dateOfBirth.day);
			printf("\nEnter Participant's Month of Birth:\n");
			scanf("%d", &participants[i].dateOfBirth.month);
			printf("\nEnter Participant's Year of Birth:\n");
			scanf("%d", &participants[i].dateOfBirth.year);
			printf("\nEnter Participant's Country :\n");
			scanf("%s", participants[i].school.country.name);
			printf("\nEnter Participant's School:\n");
			scanf("%s", participants[i].school.name);

			SelectCompetitionType(participants, i);


			currentlyRegistered += 1;
			participants[i].id = currentlyRegistered;

			printf("\nParticipant ID : %d - %s %s was successfully registered.\n", participants[i].id, participants[i].firstName, participants[i].lastName);

			
		}
	}
	else {
		// Saved to csv and reset with a plus 10
	}



	system("pause");
}

void SelectCompetitionType(Participant * participants, int i)
{
	printf("\nEnter Participant's Competition Type:\n Select (1) Individual  OR (2) All-Round: \n> ");
	int competitionType = 0;
	scanf("%d", &competitionType);


	if (competitionType == -1) { return; }

	switch (competitionType)
	{
	case INDIVIDUAL:
		participants[i].competitionType = INDIVIDUAL;
		break;
	case ALLROUND:
		participants[i].competitionType = ALLROUND;
		break;
	default:
		printf("\n Invalid Choice \n Please Try Again!");
		SelectCompetitionType(participants, i);
		break;
	}
}

void SaveAll(Participant * participants)
{
	Participant * participant = NULL;
	for (int i = 0; i < currentlyRegistered; i++)
	{
		
			participant = &participants[i];

			CreateAndSaveCSV("Participants.csv", participant);
	}

	participant = NULL;
}




Participant* ViewParticipant(const int id)
{
	bool found = false;

	Participant *participant = NULL;
	for (int i = 0; i < currentlyRegistered; i++)
	{
		if (participants[i].id == id) {
			found = true;
			participant = &participants[i];
		}
		else {
			found = false;
			participant = NULL;
		}

	}

	if (!found) {
		printf("\nNo Participant found with ID: %d\n", id);
	}

	return participant;

}

void DisplayParticipant(Participant * participant)
{
	if (participant == NULL) return;

	printf("ID:\t\t%d\nFull Name:%-20.20s %s\nSchool:%-20.20s\nCountry:%-20.20s\n,DOB:\t\t%d-%d-%d\nGender:%-20.20s\nEvent:%-20.20s\nJudge 1 Score:\t%f\nJudge 2 Score:\t%f\nJudge 3 Score:\t%f\nJudge 4 Score:\t%f\nJudge 5 Score:\t%f\nAverage Score:\t%f\n\n",
		participant->id,
		participant->firstName,
		participant->lastName,
		participant->school.name,
		participant->school.country.name,
		participant->dateOfBirth.day,
		participant->dateOfBirth.month,
		participant->dateOfBirth.year,
		*participant->gender == MALE ? "Male" : "Female",
		participant->competitionType == INDIVIDUAL ? strcat("INDIVIDUAL: ", participant->registeredEvents[0].eventName) : "",
		participant->scores[0].score,
		participant->scores[1].score,
		participant->scores[2].score,
		participant->scores[3].score,
		participant->scores[4].score,
		participant->averageScore);
}

void DisplayIndividualEventWinners(Participant participants[], int eventId)
{
	float first, second, third;
	Participant * p1, * p2, *p3;
	Participant initial = {
	0,
	"",
	"",
{0,0,0},
	"",
	NULL,
{0,"",{0, ""} },
{{0,0,0.0f},{0,0,0.0f},{0,0,0.0f},{0,0,0.0f},{0,0,0.0f}},
	0.0f,
	ALLROUND,
{{0, ""},{0, ""},{0, ""},{0, ""},{0, ""},{0, ""}},
	};

	if (currentlyRegistered < 3)
	{
		printf("\n Not enough registered participants");
		return;
	}
	
	first = second = third = FLT_MIN;
	p1 = p2 = p3 = &initial;

	for (int i = 0; i < currentlyRegistered; i++)
	{
		// if current element is greater than first 

		if (participants[i].averageScore > first 
			//&& participants[i].registeredEvents[0].id == eventId
			)
		{
			third = second;
			second = first;
			first = participants[i].averageScore;

			p3 = p2;
			p2 = p1;
			p1 = &participants[i];

		}
		else if (participants[i].averageScore > second 
			// && participants[i].registeredEvents[0].id == eventId
			) {
			// if arr[i] is in between first and second then update second
			third = second;
			second = participants[i].averageScore;

			p3 = p2;
			p2 = &participants[i];
		}
		else if (participants[i].registeredEvents[0].id == eventId)
		{
			third = participants[i].averageScore;
			p3 = &participants[i];
		}

		printf("\nIndividual Winners For Event ");

	}
	
}

void DisplayAllRoundEventWinners(Participant participants[])
{

}

void DisplayOverallWinners(Participant participants[])
{

}

float AverageScores(Participant *participant)
{
	float sum = 0;
	int length = 5;
	for (int i = 0; i < length; i++)
	{
		sum += participant->scores[i].score;
	}

	return (float)(sum / length);
}

void AcceptJudgesScore(Participant *participant, JudgeScore score, int judgeId, int eventId)
{
	if (score.score < 0.0f && score.score > 10.0f) {
		return;
	}

	if (judgeId <= 0) {
		printf("\n Judge ID cannot be less than 1");
		return;
	}

	if (judgeId > 5) {
		printf("\n Judge ID cannot be greater than 5");
		return;
	}
	// Accept score for specific event & Judge

	int length = 5;

	for (int i = 0; i < length; i++)
	{
		int index = (judgeId - 1);
		if (i == index) {
			participant->scores[i].id = judgeId;
			participant->scores[i].eventId = eventId;
			participant->scores[i].score = score.score;
		}
	}
}



char * FormatDateOfBirth(DOB dateOfBirth)
{


	return NULL;
}

void CreateAndSaveCSV(const char *filename, Participant *participant)
{
	FILE* file;
	printf("\nCreating %s file", filename);
	//filename = strcat(filename, ".csv");

	if (!file_exists(filename)) {
		file = fopen(filename, "w+");

		fprintf(file, "Participant ID, First Name, Last Name, School, Country,DOB Day, DOB Month, DOB Year, Gender, Event Type, Judge #1 Score, Judge #2 Score, Judge #3 Score, Judge #4 Score, Judge #5 Score, Average Score\n");
		fprintf(file, "%d, %s, %s ,%s, %s,%d, %d, %d, %d, %s, %f, %f, %f, %f, %f, %f\n",
			participant->id,
			participant->firstName,
			participant->lastName,
			participant->school.name,
			participant->school.country.name,
			participant->dateOfBirth.day,
			participant->dateOfBirth.month,
			participant->dateOfBirth.year,
			(int)participant->gender,
			participant->competitionType == INDIVIDUAL ? strcat("INDIVIDUAL: ", participant->registeredEvents[0].eventName) : "",
			participant->scores[0].score,
			participant->scores[1].score,
			participant->scores[2].score,
			participant->scores[3].score,
			participant->scores[4].score,
			participant->averageScore);
	}
	else {
		file = fopen(filename, "a");
		// "Participant ID, First Name, Last Name, School, Country,DOB Day, DOB Month, DOB Year, Gender, Event Type, Judge #1 Score, Judge #2 Score, Judge #3 Score, Judge #4 Score, Judge #5 Score, Average Score\n"
		fprintf(file, "%d, %s, %s ,%s, %s,%d, %d, %d, %d, %s, %f, %f, %f, %f, %f, %f\n",
			participant->id,
			participant->firstName,
			participant->lastName,
			participant->school.name,
			participant->school.country.name,
			participant->dateOfBirth.day,
			participant->dateOfBirth.month,
			participant->dateOfBirth.year,
			(int)participant->gender,
			participant->competitionType == INDIVIDUAL ? strcat("INDIVIDUAL: ", participant->registeredEvents[0].eventName) : "",
			participant->scores[0].score,
			participant->scores[1].score,
			participant->scores[2].score,
			participant->scores[3].score,
			participant->scores[4].score,
			participant->averageScore);

		// 
	}


	fclose(file);

	printf("\n %s save file successfully created!\n", filename);

}

bool file_exists(const char * filename)
{
	FILE *file;
	if ((file = fopen(filename, "r"))) {
		fclose(file);
		return true;
	}
	return false;
}
