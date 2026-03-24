#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient
{
    int id;
    char name[50];
    int age;
    char phone[15];
};

struct Visit
{
    int patientID;
    char date[20];
    char diagnosis[100];
    char prescription[100];
};

int patientExists(int id);
void registerPatient();
void addVisit();
void searchPatient();
void showVisitHistory();
void frequentVisitors();
void visitorLeaderboard();
void displayPatients();

int patientExists(int id)
{
    FILE *fp;
    struct Patient p;

    fp = fopen("patients.txt","r");

    if(fp == NULL)
        return 0;

    while(fscanf(fp,"%d|%[^|]|%d|%s\n",&p.id,p.name,&p.age,p.phone)!=EOF)
    {
        if(p.id == id)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void registerPatient()
{
    struct Patient p;
    FILE *fp;

    printf("\nEnter Patient ID: ");
    scanf("%d",&p.id);

    if(patientExists(p.id))
    {
        printf("\n⚠ Patient ID already exists!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]",p.name);

    printf("Enter Age: ");
    scanf("%d",&p.age);

    if(p.age < 0 || p.age > 120)
    {
        printf("Invalid age\n");
        return;
    }

    printf("Enter Phone: ");
    scanf("%s",p.phone);

    fp = fopen("patients.txt","a");

    if(fp == NULL)
    {
        printf("File error\n");
        return;
    }

    fprintf(fp,"%d|%s|%d|%s\n",p.id,p.name,p.age,p.phone);

    fclose(fp);

    printf("\n✔ Patient Registered Successfully\n");
}

void addVisit()
{
    struct Visit v;
    FILE *fp;

    printf("\nEnter Patient ID: ");
    scanf("%d",&v.patientID);

    if(!patientExists(v.patientID))
    {
        printf("\n⚠ Patient does not exist!\n");
        return;
    }

    printf("Enter Date (DD-MM-YYYY): ");
    scanf("%s",v.date);

    printf("Enter Diagnosis: ");
    scanf(" %[^\n]",v.diagnosis);

    printf("Enter Prescription: ");
    scanf(" %[^\n]",v.prescription);

    fp = fopen("visits.txt","a");

    if(fp == NULL)
    {
        printf("File error\n");
        return;
    }

    fprintf(fp,"%d|%s|%s|%s\n",v.patientID,v.date,v.diagnosis,v.prescription);

    fclose(fp);

    printf("\n✔ Visit Recorded Successfully\n");
}

void searchPatient()
{
    FILE *fp;
    struct Patient p;
    int id,found=0;

    printf("\nEnter Patient ID: ");
    scanf("%d",&id);

    fp = fopen("patients.txt","r");

    if(fp == NULL)
    {
        printf("No records found\n");
        return;
    }

    while(fscanf(fp,"%d|%[^|]|%d|%s\n",&p.id,p.name,&p.age,p.phone)!=EOF)
    {
        if(p.id == id)
        {
            printf("\nPatient Found\n");
            printf("ID: %d\n",p.id);
            printf("Name: %s\n",p.name);
            printf("Age: %d\n",p.age);
            printf("Phone: %s\n",p.phone);
            found=1;
            break;
        }
    }

    if(!found)
        printf("Patient not found\n");

    fclose(fp);
}

void showVisitHistory()
{
    FILE *fp;
    struct Visit v;
    int id,found=0;

    printf("\nEnter Patient ID: ");
    scanf("%d",&id);

    fp = fopen("visits.txt","r");

    if(fp == NULL)
    {
        printf("No visit records\n");
        return;
    }

    printf("\n===== VISIT HISTORY =====\n");

    while(fscanf(fp,"%d|%[^|]|%[^|]|%[^\n]\n",&v.patientID,v.date,v.diagnosis,v.prescription)!=EOF)
    {
        if(v.patientID == id)
        {
            printf("\nDate: %s\n",v.date);
            printf("Diagnosis: %s\n",v.diagnosis);
            printf("Prescription: %s\n",v.prescription);
            found=1;
        }
    }

    if(!found)
        printf("No visits found\n");

    fclose(fp);
}

void frequentVisitors()
{
    FILE *fp;
    struct Visit v;
    int id,count=0;

    printf("\nEnter Patient ID: ");
    scanf("%d",&id);

    fp = fopen("visits.txt","r");

    if(fp == NULL)
    {
        printf("No visit records\n");
        return;
    }

    while(fscanf(fp,"%d|%[^|]|%[^|]|%[^\n]\n",&v.patientID,v.date,v.diagnosis,v.prescription)!=EOF)
    {
        if(v.patientID == id)
            count++;
    }

    printf("\nTotal Visits: %d\n",count);

    if(count >= 3)
        printf("⚠ Frequent Visitor\n");

    fclose(fp);
}

void visitorLeaderboard()
{
    FILE *fp;
    struct Visit v;
    int ids[100],count[100];
    int i,size=0,found;

    fp = fopen("visits.txt","r");

    if(fp == NULL)
    {
        printf("No visit records\n");
        return;
    }

    while(fscanf(fp,"%d|%[^|]|%[^|]|%[^\n]\n",&v.patientID,v.date,v.diagnosis,v.prescription)!=EOF)
    {
        found=0;

        for(i=0;i<size;i++)
        {
            if(ids[i]==v.patientID)
            {
                count[i]++;
                found=1;
                break;
            }
        }

        if(!found)
        {
            ids[size]=v.patientID;
            count[size]=1;
            size++;
        }
    }

    printf("\n===== FREQUENT VISITOR LEADERBOARD =====\n");

    for(i=0;i<size;i++)
    {
        if(count[i] >= 3)
            printf("Patient %d -> %d visits\n",ids[i],count[i]);
    }

    fclose(fp);
}

void displayPatients()
{
    FILE *fp;
    struct Patient p;

    fp = fopen("patients.txt","r");

    if(fp == NULL)
    {
        printf("No records found\n");
        return;
    }

    printf("\n===== PATIENT DATABASE =====\n");

    while(fscanf(fp,"%d|%[^|]|%d|%s\n",&p.id,p.name,&p.age,p.phone)!=EOF)
    {
        printf("\nID: %d\n",p.id);
        printf("Name: %s\n",p.name);
        printf("Age: %d\n",p.age);
        printf("Phone: %s\n",p.phone);
    }

    fclose(fp);
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n=====================================\n");
        printf("        SMARTCLINIC TERMINAL\n");
        printf("=====================================\n");

        printf("1. Register Patient\n");
        printf("2. Add Visit Record\n");
        printf("3. Search Patient\n");
        printf("4. Show Visit History\n");
        printf("5. Visit Count (Single Patient)\n");
        printf("6. Display All Patients\n");
        printf("7. Frequent Visitor Leaderboard\n");
        printf("0. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: registerPatient(); break;
            case 2: addVisit(); break;
            case 3: searchPatient(); break;
            case 4: showVisitHistory(); break;
            case 5: frequentVisitors(); break;
            case 6: displayPatients(); break;
            case 7: visitorLeaderboard(); break;
            case 0: exit(0);
            default: printf("Invalid choice\n");
        }
    }
}
