// Contacts Management System

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int display();
void new_contact();
void del_contact();
int sort();

struct contacts
{
    char name[30];
    char no[15];
} c;

void main()
{
    char ch;
top:
    system("cls");
    printf("\n                Contacts                ");
    printf("\n****************************************\n");
    printf("\n      Press[N]:Create new contact");
    printf("\n      Press[D]:Delete contact");
    printf("\n      Press[S]:Sort");
    printf("\n      Press[E]:Exit\n");
    display();
    printf("\n\n                 ");
    ch = getch();
    switch (ch)
    {
    case 'N':
    case 'n':
        new_contact();
        goto top;
        break;
    case 'D':
    case 'd':
        del_contact();
        goto top;
        break;
    case 'S':
    case 's':
        sort();
        goto top;
        break;
    case 'E':
    case 'e':
        system("cls");
        break;
    default:
        printf("\n\tWrong input press any key...");
        getch();
        goto top;
        break;
    }
}

int display()
{
    int i = 1;
    FILE *fp;
    fp = fopen("Contacts.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\n              No__Contacts ");
        goto end;
    }
    while (fread(&c, sizeof(c), 1, fp) != 0)
    {
        printf("\n %d) %s   :   %s", i, c.no, c.name);
        i++;
    }
    fclose(fp);
    if (i == 1)
    {
        printf("\n\n              No__Contacts ");
    }
end:
    return 0;
}

void new_contact()
{
    FILE *fp;
    system("cls");
    fp = fopen("Contacts.txt", "ab");
    if (fp == NULL)
    {
        printf("\nFile is not found");
        exit(1);
    }
    printf("\n                Contacts                ");
    printf("\n****************************************");
    printf("\n # Create new contact");
    printf("\n        Mobile Number : ");
    fflush(stdin);
    gets(c.no);
    printf("        Name : ");
    fflush(stdin);
    gets(c.name);
    fwrite(&c, sizeof(c), 1, fp);

    fclose(fp);
}

void del_contact()
{
    int flage = 0;
    char number[15];
    FILE *fp, *tptr;
    system("cls");
    printf("\n                Contacts                ");
    printf("\n****************************************");
    display();
    fp = fopen("Contacts.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\n# Press any key to go back...");
        goto end;
    }
    printf("\n\n Enter mobile number,");
    printf("\n         which you want to delete");
    printf("\n    Mobile No.: ");
    fflush(stdin);
    gets(number);
    tptr = fopen("contacts2.txt", "ab");
    if (tptr == NULL)
    {
        printf("\nFile is not found");
        exit(1);
    }
    while (fread(&c, sizeof(c), 1, fp) != 0)
    {
        if (strcmp(number, c.no) != 0)
        {
            fwrite(&c, sizeof(c), 1, tptr);
        }
        else
        {
            flage = 1;
        }
    }
    fclose(fp);
    fclose(tptr);
    remove("Contacts.txt");
    rename("contacts2.txt", "Contacts.txt");
    if (flage == 0)
    {
        printf("\n   *plz check the number");
        printf("\n         in above list and try again");
        printf("\n              press any key...");
    }
    else
    {
        printf("\n *Noumber deleted, press any key...");
    }
end:
    getch();
}

int sort()
{
    FILE *fp, *tmptr;
    int get = 0;
    int A = 65, a = 97;
    while (A <= 90)
    {
        fp = fopen("Contacts.txt", "rb");
        if (fp == NULL)
        {
            goto end;
        }
        tmptr = fopen("contacts2.txt", "ab");
        if (tmptr == NULL)
        {
            printf("\nFile is not found");
            exit(1);
        }
        while (fread(&c, sizeof(c), 1, fp) != 0)
        {
            get = c.name[0];
            if (get == A || get == a)
            {
                fwrite(&c, sizeof(c), 1, tmptr);
            }
        }
        A++;
        a++;

        fclose(fp);
        fclose(tmptr);
    }
    remove("Contacts.txt");
    rename("contacts2.txt", "Contacts.txt");
end:
    return 0;
}