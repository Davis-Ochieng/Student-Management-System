/*
 

Student Information 

    Roll Number 

    Name 

    Email 

    Phone 

    Number of Subjects 


Subject Information 

    Course Code 

    Course Name 



Features 

    Adding a new student 

    Showing All Student's information 

    Editing Student information 

    Searching Student information 

    Deleting Student information 

    Delete All Students data. 

*/


#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

struct StudentInfo
{
    char RollNumber[12];
    char Name[20];
    char Email[30];
    char Phone[20];
    int  NumberOfSubject;
} Students[100];

struct SubjectInfo
{
    char StudentRollNumber[12];
    char Code[10];
    char Name[20];
} Subjects[500];

int i,j;
int TotalNumberOfStudents = 0;
int TotalSubjects = 0;
char StudentRollNumber[12];


void Menu();
void Add_New_Student();
void Show_All_Students();
int  Search_Student(char StudentRollNumber[12]);

void Edit_Student(int StudentFoundIndex);
void Delete_Student(int IndexOfStudent);
void Delete_All_Students();
int  Already_Exist(char LineChecking[30],char informationType, char StudentRollNumber[300]);
void Delete_Subject_by_Index(int SubjectIndex);
void Delete_Student_by_Index(int SubjectIndex);
void GoBack_or_Exit();
void Exit_Project();
void Sample_Data();

int main()
{
    Sample_Data();

    bool IsRunning = true;

    while(IsRunning)
    {
        Menu();
        int Option;
        scanf("%d",&Option);
        switch(Option)
        {
        case 0:
            IsRunning = false;
            Exit_Project();
            break;
        case 1:
            system("clear");
            printf("\n\t\t **** Add A New Student ****\n\n");
            Add_New_Student();
            GoBack_or_Exit();
            break;
        case 2:
            system("clear");
            printf("\n\t\t **** All Students ****\n\n");
            Show_All_Students();
            GoBack_or_Exit();
            break;
        case 3:
        {
            system("clear");
            printf("\n\t\t **** Search Students ****\n\n");
            printf(" Enter The Student RollNumber: ");
            scanf("%s",StudentRollNumber);
            int IsFound = Search_Student(StudentRollNumber);
            if(IsFound < 0)
            {
                printf(" No Student Found\n\n");
            }
            printf("\n");
            GoBack_or_Exit();
            break;
        }
        case 4:
            system("clear");
            printf("\n\t\t **** Edit a Student ****\n\n");
            printf(" Enter The Student RollNumber: ");
            scanf("%s",StudentRollNumber);
            int StudentFoundIndex = Search_Student(StudentRollNumber);

            if(StudentFoundIndex >= 0)
            {
                Edit_Student(StudentFoundIndex);
            }
            else 
            {
                printf(" No Student Found\n\n");
            }
            GoBack_or_Exit();
            break;

        case 5:
            system("clear");
            printf("\n\t\t **** Delete a Student ****\n\n");
            printf(" Enter The Student RollNumber: ");
            scanf("%s",StudentRollNumber);

            int DeleteStudentFoundIndex = Search_Student(StudentRollNumber);

            if(DeleteStudentFoundIndex>=0)
            {
                char Sure = 'N';
                getchar();
                printf("\n\n");
                printf(" Are you sure want to delete this student? (Y/N): ");
                scanf("%c",&Sure);

                Sure = tolower(Sure);
                if (Sure == 'y')
                {
                    Delete_Student(DeleteStudentFoundIndex);
                }
                else
                {
                    printf(" Your Data is Safe.\n\n");
                    GoBack_or_Exit();
                }

            }
            else
            {
                printf(" No Student Found\n\n");
                GoBack_or_Exit();
            }

            break;
        case 6:
        {
            char Sure = 'N';
            getchar();
            system("clear");
            printf("\n\t\t **** Delete ALL Students ****\n\n");

            printf(" Are you sure want to delete all the students? (Y/N): ");
            scanf("%c",&Sure);
            if(Sure == 'Y' || Sure == 'y')
            {
                Delete_All_Students();
            }
            else
            {
                printf(" Your Data is Safe.\n\n");
                GoBack_or_Exit();
            }
            break;
        }

        case 7:
            system("clear");
            break;
        default:
            Exit_Project();
            break;
        }
    }

    return 0;
} 

void Menu()
{
    printf("\t +-----------------------------------+\n");
    printf("\t |     STUDENT MANAGEMENT SYSTEM     |\n");
    printf("\t +-----------------------------------+\n\n");

    printf("\t ====================================\n");
    printf("\t    [ 1 ]. Add A New student.  \n");
    printf("\t    [ 2 ]. Show All students.  \n");
    printf("\t    [ 3 ]. Search A student.   \n");
    printf("\t    [ 4 ]. Edit A student.     \n");
    printf("\t    [ 5 ]. Delete A student.   \n");
    printf("\t    [ 6 ]. Delete All students. \n");
    printf("\t    [ 7 ]. Clear The window.   \n");
    printf("\t    [ 0 ]. Exit the Program.   \n");
    printf("\t ====================================\n");
    printf("\tEnter a Choice from the above Selections : ");
} 

void Add_New_Student()
{
    char StudentRollNumber[300];
    char Name[300];
    char Phone[300];
    char Email[300];
    int NumberOfSubjects;
    char SubjectCode[300];
    char SubjectName[300];

    int IsValidRollNumber = 0;
    while(!IsValidRollNumber)
    {
        printf(" Enter The RollNumber: ");
        scanf("%s", StudentRollNumber);

        if(Already_Exist(StudentRollNumber,'i',StudentRollNumber) > 0)
        {
            printf(" Error: This RollNumber is already exists.\n\n");
            IsValidRollNumber = 0;
        }
        else if(strlen(StudentRollNumber) > 12)
        {
            printf(" Error: RollNumber can not be more than 12 characters.\n\n");
            IsValidRollNumber = 0;
        }
        else if(strlen(StudentRollNumber) <= 0)
        {
            printf(" Error: RollNumber can not be empty.\n\n");
            IsValidRollNumber = 0;
        }
        else
        {
            IsValidRollNumber = 1;
        }
    }

    int IsValidName = 0;
    while(!IsValidName)
    {
        printf(" Enter The Name: ");
        scanf(" %[^\n]s", Name);

        if(strlen(Name) > 20)
        {
            printf(" Error: Name can not be more than 20 characters.\n\n");
            IsValidName = 0;
        }
        if(strlen(Name) <= 0)
        {
            printf(" Error: Name can not be empty.\n\n");
            IsValidName = 0;
        }
        else
        {
            IsValidName = 1;
        }
    }

    int IsValidEmail = 0;
    while(!IsValidEmail)
    {
        printf(" Enter The Email: ");
        scanf("%s", Email);

        if(Already_Exist(Email,'e',StudentRollNumber) > 0)
        {
            printf(" This Email is Already Exists.\n");
            IsValidEmail = 0;
        }
        else if(strlen(Email) > 30)
        {
            printf(" Error: Email can not be more than 30 characters.\n\n");
            IsValidEmail = 0;
        }
        else if(strlen(Email) <= 0)
        {
            printf(" Error: Email can not be empty.\n\n");
            IsValidEmail = 0;
        }
        else
        {
            IsValidEmail = 1;
        }
    }

    int IsValidPhone = 0;
    while(!IsValidPhone)
    {
        printf(" Enter The Phone: ");
        scanf("%s",Phone);

        if(Already_Exist(Phone,'p',StudentRollNumber) > 0)
        {
            printf(" This Phone Number is Already Exists\n");
            IsValidPhone = 0;
        }
        else if(strlen(Phone) > 20)
        {
            printf(" Error: Phone can not be more than 20 characters.\n\n");
            IsValidPhone = 0;
        }
        else if(strlen(Phone) <= 0)
        {
            printf(" Error: Phone can not be empty.\n\n");
            IsValidPhone = 0;
        }
        else
        {
            IsValidPhone = 1;
        }
    }

    int IsValidNumberOfSubject = 0;
    while(!IsValidNumberOfSubject)
    {
        printf(" Number of Subjects: ");
        scanf("%d",&NumberOfSubjects);

        if(NumberOfSubjects <= 0 || NumberOfSubjects > 4)
        {
            printf(" Error: Number of Subjects can not be more than 4 and lees than 1.\n\n");
            IsValidNumberOfSubject = 0;
        }
        else
        {
            IsValidNumberOfSubject = 1;
        }
    }

    strcpy(Students[TotalNumberOfStudents].RollNumber,StudentRollNumber);
    strcpy(Students[TotalNumberOfStudents].Name,Name);
    strcpy(Students[TotalNumberOfStudents].Phone,Phone);
    strcpy(Students[TotalNumberOfStudents].Email,Email);
    Students[TotalNumberOfStudents].NumberOfSubject = NumberOfSubjects;
    TotalNumberOfStudents++;

    for(i = 0; i < NumberOfSubjects; i++)
    {

        printf(" Enter Subject %d Code: ",i+1);
        scanf("%s",SubjectCode);

        printf(" Enter Subject %d Name: ",i+1);
        scanf(" %[^\n]s", SubjectName);

        strcpy(Subjects[TotalSubjects].StudentRollNumber,StudentRollNumber);
        strcpy(Subjects[TotalSubjects].Code,SubjectCode);
        strcpy(Subjects[TotalSubjects].Name,SubjectName);

        TotalSubjects++;
    }

    printf("\n Student Added Successfully.\n\n");
}

void Show_All_Students()
{
    printf("|=============|=====================|===============================|=====================|==============|\n");
    printf("| RollNumber2 |        Name         |            Email              |       Phone         |   NO.Subject |\n");
    printf("|=============|=====================|===============================|=====================|==============|\n");

    for(i = 0; i < TotalNumberOfStudents; i++)
    {
        printf("| ");
        printf("%s",Students[i].RollNumber);
        for(j=0; j < (12-strlen(Students[i].RollNumber)); j++)
        {
            printf(" ");
        }

        printf("| ");
        printf("%s",Students[i].Name);
        for(j=0; j < (20-strlen(Students[i].Name)); j++)
        {
            printf(" ");
        }

        printf("| ");
        printf("%s",Students[i].Email);
        for(j=0; j < (30-strlen(Students[i].Email)); j++)
        {
            printf(" ");
        }

        printf("| ");
        printf("%s",Students[i].Phone);
        for(j=0; j < (20-strlen(Students[i].Phone)); j++)
        {
            printf(" ");
        }

        printf("| ");
        printf("%d",Students[i].NumberOfSubject);
        for(j=0; j < 12; j++)
        {
            printf(" ");
        }
        printf("|\n");
        printf("|-------------|---------------------|-------------------------------|---------------------|--------------|\n");

    }
    printf("\n");
}

/*
int Search_Student(char StudentRollNumber[12])
{
    //system("clear");
    int StudentFoundIndex = -1;


    for(int i = 0; i < TotalNumberOfStudents; i++)
    {
        if(strcmp(StudentRollNumber,Students[i].RollNumber) == 0)
        {
            StudentFoundIndex = i;
            printf("\n One Student Found for RollNumber: %s\n\n",StudentRollNumber);
            printf(" Student Informations\n");
            printf("-------------------------\n");

            printf(" RollNumber:    %s\n",Students[i].RollNumber);
            printf(" Name:  %s\n",Students[i].Name);
            printf(" Email: %s\n",Students[i].Email);
            printf(" Phone: %s\n",Students[i].Phone);
            printf("\n Total Number of Subjects: %d\n",Students[i].NumberOfSubject);
        }
    }
    int SubjectCount = 0;
    
    for(int j = 0; j < TotalSubjects; j++)
    {
        if(strcmp(StudentRollNumber,Subjects[j].StudentRollNumber) == 0)
        {
            SubjectCount++;
            printf(" Subject %d Code: %s\n",SubjectCount,Subjects[j].Code);
            printf(" Subject %d Name: %s\n",SubjectCount,Subjects[j].Name);
        }
    }

    return StudentFoundIndex;
}

*/
int Search_Student(char StudentRollNumber[12])
{
    int StudentFoundIndex = -1;


     for(int i = 0; i < TotalNumberOfStudents; i++)
    {
        if(strcmp(StudentRollNumber,Students[i].RollNumber) == 0)
        {
            StudentFoundIndex = i;
            printf("\n One Student Found for RollNumber: %s\n\n",StudentRollNumber);
            printf("+----------------------------------------+\n");
            printf("|\t         STUDENT INFORMATION          |\n");
            printf("+----------------------------------------+\n");
            printf("| Roll Number : %-30s|\n", Students[i].RollNumber);
            printf("| Name        : %-30s|\n", Students[i].Name);
            printf("| Email       : %-30s|\n", Students[i].Email);
            printf("| Phone       : %-30s|\n", Students[i].Phone);
            printf("+--------------------------------------+\n");
        }
    }   
    

            printf("|\t               SUBJECTS               |\n");
            printf("+-----------------------------------------+\n");
            printf("|Count \t     CODE\t         SUBJECT      |\n");
            printf("|-----------------------------------------|\n");

    int SubjectCount = 0;
    for (int j = 0; j < TotalSubjects; j++)
    {
        if (strcmp(StudentRollNumber, Subjects[j].StudentRollNumber) == 0)
        {
            SubjectCount++;
            printf("| %-6d\t    %-8s     %-14s|\n", SubjectCount, Subjects[j].Code, Subjects[j].Name);
            printf("|--------------------------------------|\n");
        }
    }
}







void Edit_Student(int StudentFoundIndex)
{
    printf("\n\t\t **** Update The New Student ****\n\n");

    char NewName[300];
    char NewPhone[300];
    char NewEmail[300];
    int NewNumberOfSubjects;
    char StudentRollNumber[300];
    strcpy(StudentRollNumber, Students[StudentFoundIndex].RollNumber);
    int OldTotalNumberOfSubject = Students[StudentFoundIndex].NumberOfSubject;

    int IsValidName = 0;
    while(!IsValidName)
    {
        printf(" Enter The New Name (Type 0 to Skip): ");
        scanf(" %[^\n]s", NewName);
        if(strlen(NewName) > 20)
        {
            printf(" Error: Name can not be more than 20 characters.\n\n");
            IsValidName = 0;
        }
        else if(strlen(NewName) <= 0)
        {
            printf(" Error: Name can not be empty.\n\n");
            IsValidName = 0;
        }
        else
        {
            IsValidName = 1;
        }
    }

    int IsValidEmail = 0;
    while(!IsValidEmail)
    {
        printf(" Enter The New Email (Type 0 to Skip): ");
        scanf("%s",NewEmail);

        if(strlen(NewEmail) > 30)
        {
            printf(" Error: Email can not be more than 30 characters.\n\n");
            IsValidEmail = 0;
        }
        else if(strlen(NewEmail) <= 0)
        {
            printf(" Error: Email can not be empty.\n\n");
            IsValidEmail = 0;
        }
        else if(Already_Exist(NewEmail,'e',StudentRollNumber) > 0)
        {
            printf(" Error: This Email Already Exists.\n\n");
            IsValidEmail = 0;
        }
        else
        {
            IsValidEmail = 1;
        }
    }

    int IsValidPhone = 0;
    while(!IsValidPhone)
    {
        printf(" Enter The New Phone (Type 0 to Skip): ");
        scanf("%s",NewPhone);

        if(strlen(NewPhone) > 20)
        {
            printf(" Error: Phone can not be more than 20 characters.\n\n");
            IsValidPhone = 0;
        }
        else if(strlen(NewPhone) <= 0)
        {
            printf(" Error: Phone can not be empty.\n\n");
            IsValidPhone = 0;
        }
        else if(Already_Exist(NewPhone,'p',StudentRollNumber) > 0)
        {
            printf(" Error: This Phone Number is Already Exists.\n\n");
            IsValidPhone = 0;
        }
        else
        {
            IsValidPhone = 1;
        }
    }

    int IsValidNumberOfSubject = 0;
    while(!IsValidNumberOfSubject)
    {
        printf(" Number of New Subjects (Type 0 to Skip): ");
        scanf("%d",&NewNumberOfSubjects);

        if(NewNumberOfSubjects > 7 || NewNumberOfSubjects < 0)
        {
            printf(" Error: A Student can have a Maximum  of 7 and Minimum 0 number of Subjects.\n\n");
            IsValidNumberOfSubject = 0;
        }
        else
        {
            IsValidNumberOfSubject = 1;
        }
    }

    if(strcmp(NewName,"0") != 0)
    {
        strcpy(Students[StudentFoundIndex].Name,NewName);
    }

    if(strcmp(NewEmail,"0") != 0)
    {
        strcpy(Students[StudentFoundIndex].Email,NewEmail);
    }

    if(strcmp(NewPhone,"0") != 0)
    {
        strcpy(Students[StudentFoundIndex].Phone,NewPhone);
    }

    if(NewNumberOfSubjects != 0)
    {
        int OldTotalSubjects = Students[StudentFoundIndex].NumberOfSubject;
        Students[StudentFoundIndex].NumberOfSubject = NewNumberOfSubjects;


        int FirstSubjectIndex;
        int dc;
        for(dc = 0; dc < TotalSubjects; dc++)
        {
            if(strcmp(StudentRollNumber,Subjects[dc].StudentRollNumber) == 0)
            {
                FirstSubjectIndex = dc; // store the index for delete
                break;
            }
        }
        // after every delete array index will update (decrease by one)
        // we store the Subjects sequential
        // so if we know the first Subject index and total number of Subject we can delete all
        for(dc = 1; dc <= OldTotalSubjects; dc++)
        {
            Delete_Subject_by_Index(FirstSubjectIndex);
        }

        char SubjectCode[300];
        char SubjectName[300];
        for(i = 1; i <= NewNumberOfSubjects; i++)
        {
            printf(" Enter New Subject %d Code: ",i);
            scanf("%s",SubjectCode);

            printf(" Enter New Subject %d Name: ",i);
            scanf(" %[^\n]s", SubjectName);

            strcpy(Subjects[TotalSubjects].StudentRollNumber,StudentRollNumber);
            strcpy(Subjects[TotalSubjects].Code,SubjectCode);
            strcpy(Subjects[TotalSubjects].Name,SubjectName);
            TotalSubjects++;
        }
    }

    printf(" Student Updated Successfully.\n\n");

}

void Delete_Student(int IndexOfStudent)
{
    int d;
    int FirstSubjectIndexs;
    struct StudentInfo currentStudent;
    currentStudent = Students[IndexOfStudent];
    for(d=0; d<TotalSubjects; d++)
    {
        if(strcmp(currentStudent.RollNumber,Subjects[d].StudentRollNumber) == 0)
        {
            FirstSubjectIndexs = d;
            break;
        }
    }
    for(d=1; d<=currentStudent.NumberOfSubject; d++)
    {
        Delete_Subject_by_Index(FirstSubjectIndexs);
    }
    Delete_Student_by_Index(IndexOfStudent);
    printf(" Student Deleted Successfully.\n\n");
    GoBack_or_Exit();
}

void Delete_All_Students()
{
    TotalNumberOfStudents = 0;
    TotalSubjects = 0;
    printf(" All Students Deleted Successfully.\n\n");
    GoBack_or_Exit();
}


void Delete_Subject_by_Index(int SubjectIndex)
{

    for(int c = 0; c < TotalSubjects-1; c++)
    {
        if(c >= SubjectIndex)
        {
            Subjects[c] = Subjects[c+1];
        }
    }
    TotalSubjects--;

}

void Delete_Student_by_Index(int SubjectIndex)
{
    int s;
    for(s = 0; s < TotalNumberOfStudents-1; s++)
    {
        if(s >= SubjectIndex)
        {
            Students[s] = Students[s+1];
        }
    }
    TotalNumberOfStudents--;
}


int Already_Exist(char LineChecking[300],char informationType, char StudentRollNumber[300])
{
    int EmailExists = 0;
    int PhoneExists = 0;
    int RollNumberExists = 0;
    int ep;

    for(ep=0; ep < TotalNumberOfStudents; ep++)
    {
        if(strcmp(LineChecking,Students[ep].RollNumber) == 0)
        {
            RollNumberExists++;
        }
        if(strcmp(LineChecking,Students[ep].Email) == 0 && strcmp(StudentRollNumber,Students[ep].RollNumber) != 0 )
        {
            EmailExists++;
        }
        if(strcmp(LineChecking,Students[ep].Phone) == 0 && strcmp(StudentRollNumber,Students[ep].RollNumber) != 0)
        {
            PhoneExists++;
        }

    }

    if(informationType == 'i')
        return RollNumberExists;

    else if(informationType == 'e')
        return EmailExists;

    else if(informationType == 'p')
        return PhoneExists;

    else
        return 0;

}




void GoBack_or_Exit()
{
    getchar();
    char Option;
    printf(" Go back(b)? or Exit(0)?: ");
    scanf("%c",&Option);
    if(Option == '0')
    {
        Exit_Project();
    }
    else
    {
        system("clear");
    }
}

void Exit_Project()
{
    system("clear");
    sleep(2);

    printf("\nExiting the Project....\n\n");
    sleep(2);
    
    printf("..Exited..\n\n");
    exit(0);
}

void Sample_Data()
{
    //1st Student
    strcpy(Students[0].RollNumber,"Stdnt_1");
    strcpy(Students[0].Name,"John Paul");
    strcpy(Students[0].Phone,"+254 712 345 671");
    strcpy(Students[0].Email,"JohnPaul@gmail.com");
    Students[0].NumberOfSubject=1;

    strcpy(Subjects[0].StudentRollNumber,"Stdnt_1");
    strcpy(Subjects[0].Code,"CSE-1");
    strcpy(Subjects[0].Name,"Subject - 1");

    //2nd Student
    strcpy(Students[1].RollNumber,"Stdnt_2");
    strcpy(Students[1].Name,"Leonard Sam");
    strcpy(Students[1].Phone,"+254 712 345 672");
    strcpy(Students[1].Email,"leoSam@gmail.com");
    Students[1].NumberOfSubject=2;

    strcpy(Subjects[1].StudentRollNumber,"Stdnt_2");
    strcpy(Subjects[1].Code,"CSE-1");
    strcpy(Subjects[1].Name,"Subject - 1");

    strcpy(Subjects[2].StudentRollNumber,"Stdnt_2");
    strcpy(Subjects[2].Code,"CSE-2");
    strcpy(Subjects[2].Name,"Subject - 2");


    //3rd Student
    strcpy(Students[2].RollNumber,"Stdnt_3");
    strcpy(Students[2].Name,"Cynhita Wafula");
    strcpy(Students[2].Phone,"+254 712 345 673");
    strcpy(Students[2].Email,"cynthiaWafula3@gmail.com");
    Students[2].NumberOfSubject=3;

    strcpy(Subjects[3].StudentRollNumber,"Stdnt_3");
    strcpy(Subjects[3].Code,"CSE-1");
    strcpy(Subjects[3].Name,"Subject - 1");

    strcpy(Subjects[4].StudentRollNumber,"Stdnt_3");
    strcpy(Subjects[4].Code,"CSE-2");
    strcpy(Subjects[4].Name,"Subject - 2");

    strcpy(Subjects[5].StudentRollNumber,"Stdnt_3");
    strcpy(Subjects[5].Code,"CSE-3");
    strcpy(Subjects[5].Name,"Subject - 3");

    TotalNumberOfStudents = 3;
    TotalSubjects = 6;
}










/*

+==============================+
|     STUDENT INFORMATION      |
+==============================+
| Roll Number : Stdnt_1        |
| Name  : John Paul            |
| Email : JohnPaul@gmail.com   |
| Phone : (+254) 712-345-671   |
+==============================+
|          SUBJECTS            |
+==============================+
|Count   CODE      SUBJECT     |
|------------------------------|
| 1      CSE-1     Subject - 1 |
|------------------------------|
| 2      CSE-2     Subject - 2 |
|------------------------------|



*/
