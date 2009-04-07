/* SIMPLE HR MANAGEMENT PROGRAM */
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>



/* LOCAL VARIABLES*/



		long noe;                 //total number of employees
		FILE *rf;
		struct employee {
			long ID;
			char Name[10];    //first name
			char Sname[10];   //second name
			char Function[10];
			long Salary;
			struct employee *next; // link to next employee
		} ;




///////////////////////////////////////////////////////////////////



/* ORDERED LINKED LIST FUNCTIONS   */

struct employee *search(const struct employee **start, char n[],char n2[])
		{
		struct employee *temp;
		temp = *start;
		while(temp) {
			if(((!strcmp(n,temp->Name))&&(!strcmp(n2,temp->Sname)))) return temp;
			temp = temp->next;
			}
		return NULL; /* no match */
}


////////////////////////////////////////////////

void store(long id,char *name,char *sname, char*function,
		long salary, struct employee **start,struct employee **last) {
		struct employee *old, *p,*i;
		++noe;
		i = malloc(sizeof(struct employee));
		i->ID=id;
		strcpy(i->Name,name);
		strcpy(i->Sname,sname);
		strcpy(i->Function,function);
		i->Salary=salary;
		p = *start;
		if(!*last) { /* first element in list */
				i->next = NULL;
			*last = i;
			*start = i;
			return;
		}
		old = NULL;
		while(p) {
			if((strcmp(p->Name,i->Name)<0)||((strcmp(p->Name,i->Name)==0)&&(strcmp(p->Sname,i->Sname)<0))) {
				old = p;
				p = p->next;
			}
		else {
			if(old) { /* goes in middle */
				old->next = i;
				i->next = p;
				return;
			}
			i->next = p; /* new first element */
			*start = i;
			return;
		}
		}
	(*last)->next = i; /* put on end */
	i->next = NULL;
	*last = i;
}

////////////////////////////////////////////


void deletes(char *s,char *s2,struct employee **start,struct employee **last)
{
	struct employee *p,*i;
	if ((!search(start,s,s2))) printf("\nemployee not found!\n\n");
	else {
	--noe;
	p->next=i;
	i = *start;
	while (i!=search(start,s,s2))
		{
		p = i;
		i = i->next;
		}
	if(p) p->next = i->next;
		else *start = i->next;
		if(i==*last && p) *last = p;
		free(i);
	}
}
///////////////////////////////////



void display(struct employee *start)
{
	struct employee *temp;
	temp= start;
	while(temp->next) {
	printf("%5ld; %10s , %15s ; %15s ; %10ld\n",temp->ID,temp->Name,
			  temp->Sname,temp->Function,temp->Salary);
	temp = temp->next;
	}
}

////////////////////////////////////


void savelist(struct employee **start)   // TO employee.txt
{
	struct employee *temp;
	temp = *start;
	while(temp->next) {
	fprintf(rf,"%5ld; %15s, %15s; %15s; %10ld\n",temp->ID,temp->Name,
			  temp->Sname,temp->Function,temp->Salary);
	temp = temp->next;
	}

}


//////////////////////////////



void loadlist(struct employee **start,struct employee **last)
{
	char ids[5],salarys[5],name[10],sname[10],function[10],c;
	long id,salary;         int i,j,k,m,n,b,v;
			strset(name,'\0');
			strset(sname,'\0');
			strset(function,'\0');
			strcpy(ids,"     ");
			strset(salarys,'\0');
	i=0;j=0;k=0;m=0;n=0;b=0;v=0;
	while (!feof(rf)) {
		c = fgetc(rf);
		if (c=='\n') {

			// after facing a lot of problems
			// this method gave superior results

			strncat("0",salarys,5);
			strncpy(name,name,10);
			strncpy(sname,sname,10);
			strncpy(function,function,10);
			id = atoi(ids); salary = atoi(salarys);
			i=0;j=0;k=0;m=0;n=0;b=0;v=0;

			store(id,name,sname,function,salary,start,last);
			strset(name,'\0');
			strset(sname,'\0');
			strset(function,'\0');
			strset(ids,'\0');
			strset(salarys,'\0');

		}
		else if (c==' ') continue;
		else if ((c==';')||(c==',')) {++j; continue;}
		else if ((j==0)&&(isdigit(c))&&(i<5)) ids[i++] = c;
		else if ((j==4)&&(isdigit(c))&&(v<5)) salarys[v++] =c;
		else if ((j==1)&&(isalpha(c))){if(m>=10)continue;else name[m++]=c;  }
		else if ((j==2)&&(isalpha(c))){if(n>=10)continue;else sname[n++]=c; }
		else if ((j==3)&&(isalpha(c))){if(b>=10)continue;else function[b++]=c; }
		else continue;

	}
	}

/////////////////////////////////////


float avgsalary  (struct employee **start) {
	long sum = 0;
	struct employee *temp;
	temp = *start;
	while (temp) {
		sum += temp->Salary;
		temp = temp->next;
	}
	if (noe==0) {printf("You Don't have employees");    return 0;}
	else return (int)(sum/noe);
}




/////////////////////////////////////////////////////////////||
//                                                         //||
//                                                         //||
//               MAIN PROGRAM                              //||
//                                                         //||
//                                                         //||
//                                                         //||
//                                                         //||
/////////////////////////////////////////////////////////////||


int main()
{
int i=0;    char select,  _name[10],_sname[10],_function[10]; long _id,_salary;
struct employee **Last = NULL;
struct employee **Start= NULL;
struct employee *temp;
clrscr();

//  To avoid errors of first and last employees we
//      store these two arbitary employees.
//  They will not be displayed to screen nor
//      saved to the file employee.txt.
//  Also they are not considered in the number of employees.

store(0000,"aaaaa","aaaa","aaaaa",0000,Start,Last);
store(0000,"zzzzz","zzzz","zzzzz",0000,Start,Last);



while(1) {
	clrscr();
	printf("\n\n\n\n\n\n\n\
	You have %d employees! \
	press 'a' to add an employee,\n\
	or    'm' to modify an employee's information,\n\
	or    'x' to delete an employee,\n\
	or    'd' to display your employees information,\n\
	or    'n' to display number of employees,\n\
	or    's' to display average salary,\n\
	or    'l' to save list to employees.txt\n\
	or    'r' to load list from employees.txt\n\
	or    'e' to exit program.",noe-2);
	select = getch();
	clrscr();


	switch (select) {



	case 'a':             // ADD
		clrscr();
		printf("\n\n\n\nenter ID\t"); scanf("%ld",&_id);
		printf("enter first name\t"); scanf("%s",&_name);
		printf("enter second name\t"); scanf("%s",&_sname);
		printf("enter function\t"); scanf("%s",&_function);
		printf("enter salary\t"); scanf("%ld",&_salary);
		store(_id,_name,_sname,_function,_salary,Start,Last);
		clrscr();
		break;


	case 'x':           // DELETE
		clrscr();
		printf("enter first name to delete\t");
		scanf("%s",&_name);
		printf("enter second name\t");
		scanf("%s",&_sname);
		deletes(_name,_sname,Start,Last);
		clrscr();
		break;


	case 'd':          // DISPLAY
		clrscr();
		printf("\n\n\n");
		display(*Start);
		printf("\n\n\t\tPress Any Key:");
		getch();
		clrscr();
		break;


	case 'm':    //modify
		clrscr();
		printf("\nenter the first name of employee you want to modify\t");
		scanf("%s",&_name);
		printf("\nenter the second name of employee you want to modify\t");
		scanf("%s",&_sname);

		temp = search(Start,_name,_sname);

		printf("\n\nOf course you can not change employees names! So\n\
		press 'i' to change ID,\n\
		or    'f' to change function,\n\
		or    's' to change salary,\n\
		or    'c' to cancel.\t");

		switch(getch()) {
			case 'i':
				printf("\nenter new ID\t");
				scanf("%d",&_id);
				temp->ID=_id;
				break;
			case 'f':
				printf("\nenter new function\t");
				scanf("%s",&_function);
				strcpy(temp->Function,_function);
				break;
			case 's':
				printf("\nenter new salary\t");
				scanf("%d",&_salary);
				temp->Salary=_salary;
				break;
			case 'c':
				break;
			default :
				break;
		}


	case 'n':         // NUMBER OF EMPLOYEES
		clrscr();
		printf("\n\n\nYou have %ld employees!\n\
		\n\n\n\n\t\tPress Any Key:",noe-2);

		getch();
		clrscr();
		break;



	case 's':       // AVERAGE SALARY
		clrscr();
		printf("\n\n\nAverage salary is %f Pounds.\n\
		\n\n\n\n\t\tPress Any Key:",avgsalary(Start));
		getch();
		clrscr();
		break;



	case 'l':      // SAVE LIST
		clrscr();
		rf = fopen("C:\\employee.txt","wt");
		savelist(Start);
		fclose(rf);
		printf("\nList Saved to C:\\employee.txt\n\n");
		printf("\n\n\n\n\n\n\n\n\n\t\tPress Any Key:");
		getch();
		clrscr();
		break;




	case 'r':     // LOAD LIST
		clrscr();
		rf = fopen("C:\\employee.txt","rt");
		loadlist(Start,Last);
		fclose(rf);
		printf("\n\n\nLoaded\n\n\n\n\t\tPress Any Key:");
		getch();
		clrscr();
		break;





	case 'e':        // EXIT
		exit(1);
		break;



	default :
		clrscr(); printf("\n\n\n\n\n\n\n\
	press 'a' to add an employee,\n\
	or    'm' to modify an employee's information,\n\
	or    'x' to delete an employee,\n\
	or    'd' to display your employees information,\n\
	or    'n' to display number of employees,\n\
	or    's' to display average salary,\n\
	or    'l' to save list to employees.txt\n\
	or    'r' to load list from employees.txt\n\
	or    'e' to exit program.");
		getch();
		clrscr();
		break;
}{}}}
