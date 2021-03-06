/* Homework 4
 * Scott Gavin
 * 12343703
 * sggtgb
 * Section D */

#include <stdio.h>
#include <stdlib.h>
//structure data to hold student information
typedef struct{
		int id;
		char name[10];
		int hw;
		int quiz;
		int midterm;
		char grade;
	      }data;
//function prototypes
void print_info(data *student[], int n);
data* read_info(int size);
void calculate_grades(data *student,int size);
void update_score(data *student[], int size);
void compute_stats(data *student[], int size);
int search(data* student[], int id, int size);
void sort(data *student[], int size);

//function main
int main(int argc, char** argv)
{//start main
	system("clear"); //clear the system screen
	if (argc < 2 || atoi(argv[1]) > 10 || atoi(argv[1]) < 0) //if statement to check the validity of inputs
	{//start if
		printf("USAGE: %s SIZE 0 < 10\n"); //error statement
		return 0; //end function
	}//end if
	data *ptrarray[10];//data ptrarray to hold data
	int i;//counter
	int size = atoi(argv[1]); //accept size from user input
	for (i = 0; i < size; i++) //for statement to write pointers to an array
	{//start for
		ptrarray[i] = read_info(size); //call function read info
	}//finish for
	print_info(ptrarray,size);//call function print info
	update_score(ptrarray, size);//call function update score
	print_info(ptrarray,size);//call function print info
	compute_stats(ptrarray, size);//call function compute stats
	return 0;//end function
}//end main

data* read_info(int size)//function read_info to read info into a data struct 
{//start read info
	data *ptr = malloc(sizeof(data) );//malloc the memory for a data struct
	int i;
	//prompt for information
	printf("Please enter student ID: ");
	scanf("%d", &(*ptr).id);
	printf("Student name: ");
	scanf("%s", (*ptr).name);
	printf("Homework score: ");	
	scanf("%d", &(*ptr).hw);
	printf("Quiz score: ");
	scanf("%d", &(*ptr).quiz);
	printf("Midterm score: ");
	scanf("%d", &(*ptr).midterm);
	printf("\n");
	calculate_grades(ptr, size); //finish filling each struct by calculating the grade
	return ptr;//return the pointer to the memory point
}//end read info

void print_info(data *student[], int size) //function print info to print the sructs to the screen
{//start function
	int i;
	printf("ID:\tName:\tHomework\tQuiz\tMidterm\t\tGrade\n-----------------------------------------------------\n");
	for (i = 0; i < size; i++) //for loop to run through the pointer
	{//start for
		printf("%d\t%s\t%d\t\t%d\t%d\t\t%c\n", (*student[i]).id,(*student[i]).name,(*student[i]).hw,(*student[i]).quiz,(*student[i]).midterm,(*student[i]).grade);
	}//end for
}//end function

void update_score(data *student[], int size) //function update score to accept user input modifying original inputs
{//start function
	//printf("\n\nHi\n\n");	
	int l, x = 0,id, change, q = 0, truth = 0;
	char n[7], check[3]; //character arrays to accept user strings
	while (l != 0) //while loop to run until user is done inputting
	{//start while
	x=0;q=0;truth=0;//reset variable for each loop through
		while (x != 1) //while loop to insure user inputs a valid id
		{//start while
			printf("Please input ID to update: "); //prompt for id to edit
			scanf("%d", &id);
			truth = search(student,id,size);//call function search to determine if id is in the data given
			if (truth == 0) printf("ERROR: ID not present\n");//error statement
			if (truth != 0) x = 1; //break out of while loop
			
		}//end while
		truth--;//set truth back so as not to segfault
		printf("."); //No idea why but putting a printf here prevents a seg fault.
		while (q != 1)//while loop to run until user inputs a valid selection
		{//start while
			printf("Enter the score you want to edit: ");
			scanf("%s", &n);
			//check which of the grades user wishes to edit and apply change
			if (strcmp(n,"hw") == 0)
			{
				printf("Please enter the change in grade: ");
				scanf("%d", &change);
				(*student[truth]).hw += change;
				q++;
			}
			if (strcmp(n,"quiz") == 0)
		        {
		                printf("Please enter the change in grade: ");
		                scanf("%d", &change);
		                (*student[truth]).quiz += change;
				q++;
		        }
			if (strcmp(n,"midterm") == 0)
		        {
		                printf("Please enter the change in grade: ");
		                scanf("%d", &change);
		                (*student[truth]).midterm += change;
				q++;
		        }
			if (q == 0)//error statement
			{
				printf("ERROR: Please enter a valid input\n");
			}
		}//end while
		printf("Would you like to update more scores? (type yes or no): "); //check if user intends to edit more information
		scanf("%s", check);
		l = strcmp(check, "no");//process user input
		calculate_grades(student[truth],size); //call calculate grades to update grades
	 }//end user controlled while
}//end function
	
int search(data* student[], int id, int size) //function search to determine if an id is in the array
{//start function
	int i;
	for (i = 0;i < size; i++)
	{//start for loop to search through array
		if (id == (*student[i]).id) return (i+1);
	}//end for loop
	return 0;
}//end function

void calculate_grades(data *student, int size) //function calculate grades to determine the letter grade of each averaged number grade
{//start function
	int total = 300;
	int grade = (*student).hw+(*student).quiz+(*student).midterm;
	float perc = (float) grade/total;
	if (perc >= .9) (*student).grade = 'A';
	if (perc >= .8 && perc < .9) (*student).grade = 'B';
	if (perc >= .7 && perc < .8) (*student).grade = 'C';
	if (perc >= .6 && perc < .7) (*student).grade = 'D';
	if (perc < .6) (*student).grade = 'F';
}//end function

void compute_stats(data *student[], int size) //function compute stats to determine and print the class statistics
{//begin function
	float avg,avg1,avg2;
	int i, high, low, sum = 0, array[5] = {0};
	for (i = 0; i < size; i++)//for loop to gather values for the histogram and sum the total grades of classes
	{//begin for loop
		sum += (*student[i]).hw+(*student[i]).quiz+(*student[i]).midterm;
		if ((*student[i]).grade == 'A') array[0]++;
		if ((*student[i]).grade == 'B') array[1]++;
		if ((*student[i]).grade == 'C') array[2]++;
		if ((*student[i]).grade == 'D') array[3]++;
		if ((*student[i]).grade == 'F') array[4]++;
	}//end for loop
	sort(student,size);//call function sort
	avg1 = (float) ((*student[0]).hw+(*student[0]).quiz+(*student[0]).midterm)/3;
	avg2 = (float) ((*student[size-1]).hw+(*student[size-1]).quiz+(*student[size-1]).midterm)/3;
	//print the class high, low, and average
	printf("\n\nStudent with highest marks\n%d %s with the total of %.2f%%\n\n", (*student[0]).id, (*student[0]).name, avg1);
	printf("Student with lowest marks\n%d %s with the total of %.2f%%\n\n", (*student[size-1]).id, (*student[size-1]).name, avg2);	
	avg = (float) sum / (size*3);
	printf("Class average is %.2f%%\n\n", avg);
	//print the grade distro histogram
	printf("Grade Distribution:\n\nA:");
	for (i = 0; i < array[0]; i++) printf("*");
	printf("\nB:");
	for (i = 0; i < array[1]; i++) printf("*");
        printf("\nC:");
	for (i = 0; i < array[2]; i++) printf("*");
        printf("\nD:");
	for (i = 0; i < array[3]; i++) printf("*");
        printf("\nF:");
	for (i = 0; i < array[4]; i++) printf("*");
	printf("\n");
}//end function

void sort(data *student[], int size) //function sort to sort data in the array
{//start sort
	int i, count;
	data *temp;
	while (count != 0)//while loo[ to run until no changes are made
	{//start while
		count = 0;
		for(i = 0; i < size-1; i++)
		{
			if ((((*student[i]).hw+(*student[i]).quiz+(*student[i]).midterm))/3 < ((*student[i+1]).hw+(*student[i+1]).quiz+(*student[i+1]).midterm)/3)
			{
				temp = student[i];
				student[i] = student[i+1];
				student[i+1] = temp;
				count++;
			}
		}
	}//end while
}//end sort		
