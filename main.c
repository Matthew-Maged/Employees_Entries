#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Enter 0x0D
#define Esc 0x1B
#define Space 0x20
#define Tab 0x09

#define Up 0x48
#define Down 0x50
#define Home 0x47
#define End 0x4F
#define BackSpace 0x08

#define Right 0x4D
#define Left 0x4B
#define Delete 0x53

#define A_VALUE 0x41
#define Z_VALUE 0x5A
#define a_VALUE 0x61
#define z_VALUE 0x7A
#define ZERO_VALUE 0x30
#define NINE_VALUE 0x39

#define IDNum 4
#define AgeNum 2
#define GenderNum 1
#define FirstNameNum 10
#define SecondNameNum 10
#define SalaryNum 4
#define OvertimeNum 4
#define DeductionNum 4
#define AddressNum 30
#define PhoneNumberNum 11
#define DeptNameNumber 3

#define CHARS 1
#define NUMS 2

#define NUM_OF_LINES 11

struct Employee
{
    short int ID, age;
    char Gender;
    char FirstName[FirstNameNum + 1];
    char SecondName[SecondNameNum + 1];
    double Salary, Overtime, Deduction;
    char Address[AddressNum + 1];
    char PhoneNumber[PhoneNumberNum + 1];
    char DeptName[PhoneNumberNum + 1];
};

char *LineEditor(int Copy_xPosition, int Copy_yPosition, int Copy_Size, short int CharsOrNums);
char **MultiLineEditor(int *Copy_xPosition, int *Copy_yPosition, int *Copy_Size, int NumberOfLines, int *CharsOrNums);
void gotoxy1(int x, int y);
void textattr(int i);
void SelectActionLine(char Copy_Character, int *Copy_ExitFlag, int *Copy_CurrentPosition, char *Copy_Data, int Copy_Size, int Copy_xPosition, int Copy_yPosition);
void SelectAction(char Copy_Character, int *Copy_ExitFlag, int *Copy_CurrentPosition, char **Copy_Data, int *Copy_Size, int *Copy_xPosition, int *Copy_yPosition, int *Copy_CurrentLine);
void PrintNonExtendedKeysLine(char Copy_Character, char *Copy_Data, int *Copy_CurrentPosition, int Copy_Size, int Copy_xPosition, int Copy_yPosition, short int CharsOrNums);
void PrintNonExtendedKeys(char Copy_Character, char **Copy_Data, int *Copy_CurrentPosition, int *Copy_Size, int *Copy_xPosition, int *Copy_yPosition, int *Copy_CurrentLine, int *CharsOrNums);
void MainMenu();
void SelectActionMenu(char Copy_Character, struct Employee *Employees, int *ExistingEmployees, int *NumberOfEmployees);
void PressedEnter(int Copy_Current, struct Employee *Employees, int *ExistingEmployees, int *NumberOfEmployees);
void DoAction(int Copy_Number, struct Employee *Employees, int *ExistingEmployees, int *NumberOfEmployees);
void DataMenu();
void NewEmployeeMenu(int Copy_Employee_Index, struct Employee *Employees);
void DisplayEmployee(struct Employee Copy_Employee);

char Menu[3][25] = {"New Employee", "Display Employee", "Display All Employees"};
int Global_ExitFlag = 0;
int Global_Current = 0;
int MaxCurrentPosition [11] = {0};


int main()
{
    char Local_Character = 0;
    int Local_Counter;

    printf("Enter number of Employees");
    char *DataNumbers = LineEditor(0, 1, 2, NUMS);
    int NumberOfEmployees = atoi(DataNumbers);
    free(DataNumbers);
    int *ExistingEmployees = (int *)malloc(NumberOfEmployees * sizeof(int));
    for (Local_Counter = 0; Local_Counter < NumberOfEmployees; Local_Counter++)
    {
        ExistingEmployees[Local_Counter] = 0;
    }
    struct Employee *Employees = (struct Employee *)malloc(NumberOfEmployees * sizeof(struct Employee));

    textattr(0x0F);
    system("cls");

    do
    {
        MainMenu();
        Local_Character = getch();
        SelectActionMenu(Local_Character, Employees, ExistingEmployees, &NumberOfEmployees);
    } while (!Global_ExitFlag);

    free(ExistingEmployees);
    free(Employees);
    return 0;
}

char *LineEditor(int Copy_xPosition, int Copy_yPosition, int Copy_Size, short int CharsOrNums)
{
    int Local_Counter;
    char Local_Character = 0;
    char *Data = (char *)malloc((Copy_Size + 1) * sizeof(char));
    Data[0] = '\0';
    Data[Copy_Size] = '\0';
    int Local_CurrentPosition = Copy_xPosition;
    int Local_ExitFlag = 0;

    gotoxy1(Copy_xPosition, Copy_yPosition);
    textattr(0x40);
    for (Local_Counter = 0; Local_Counter < Copy_Size; Local_Counter++)
    {
        _cprintf(" ");
        Data[Local_Counter] = ' ';
    }
    gotoxy1(Copy_xPosition, Copy_yPosition);
    textattr(0x40);

    do
    {
        Local_Character = getch();
        SelectActionLine(Local_Character, &Local_ExitFlag, &Local_CurrentPosition, Data, Copy_Size, Copy_xPosition, Copy_yPosition);
        PrintNonExtendedKeysLine(Local_Character, Data, &Local_CurrentPosition, Copy_Size, Copy_xPosition, Copy_yPosition, CharsOrNums);
    } while (!Local_ExitFlag);

    return Data;
}

char **MultiLineEditor(int *Copy_xPosition, int *Copy_yPosition, int *Copy_Size, int NumberOfLines, int *CharsOrNums)
{
    int Local_Counter;
    int Local_Counter2;
    char Local_Character = 0;
    int Local_ExitFlag = 0;
    int Local_CurrentLine = 0;

    char **Data = (char **)malloc(NumberOfLines * sizeof(char *));
    for (Local_Counter = 0; Local_Counter < NumberOfLines; Local_Counter++)
    {
        Data[Local_Counter] = (char *)malloc((Copy_Size[Local_Counter] + 1) * sizeof(char));
        Data[Local_Counter][Copy_Size[Local_Counter]] = '\0';
    }

    int *Local_CurrentPosition = (int *)malloc(NumberOfLines * sizeof(int));

    for (Local_Counter = 0; Local_Counter < NumberOfLines; Local_Counter++)
    {
        Local_CurrentPosition[Local_Counter] = Copy_xPosition[Local_Counter];
    }

    for (Local_Counter = 0; Local_Counter < NumberOfLines; Local_Counter++)
    {
        gotoxy1(Copy_xPosition[Local_Counter], Copy_yPosition[Local_Counter]);
        for (Local_Counter2 = 0; Local_Counter2 < Copy_Size[Local_Counter]; Local_Counter2++)
        {
            textattr(0x40);
            _cprintf(" ");
            Data[Local_Counter][Local_Counter2] = ' ';
        }
    }
    gotoxy1(Copy_xPosition[0], Copy_yPosition[0]);
    textattr(0x40);

    do
    {
        Local_Character = getch();
        SelectAction(Local_Character, &Local_ExitFlag, Local_CurrentPosition, Data, Copy_Size, Copy_xPosition, Copy_yPosition, &Local_CurrentLine);
        PrintNonExtendedKeys(Local_Character, Data, Local_CurrentPosition, Copy_Size, Copy_xPosition, Copy_yPosition, &Local_CurrentLine, CharsOrNums);
    } while (!Local_ExitFlag);

    return Data;
}

void gotoxy1(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

void SelectActionLine(char Copy_Character, int *Copy_ExitFlag, int *Copy_CurrentPosition, char *Copy_Data, int Copy_Size, int Copy_xPosition, int Copy_yPosition)
{
    char Local_Character = 0;
    switch (Copy_Character)
    {
    case -32:
        Local_Character = getch();
        switch (Local_Character)
        {
        case Left:
            if (*Copy_CurrentPosition > Copy_xPosition)
            {
                (*Copy_CurrentPosition)--;
                gotoxy1(*Copy_CurrentPosition, Copy_yPosition);
            }
            break;
        case Right:
            if (*Copy_CurrentPosition < (Copy_xPosition + Copy_Size) - 1)
            {
                (*Copy_CurrentPosition)++;
                gotoxy1(*Copy_CurrentPosition, Copy_yPosition);
            }
            break;
        case Home:
            *Copy_CurrentPosition = Copy_xPosition;
            gotoxy1(*Copy_CurrentPosition, Copy_yPosition);
            break;
        case End:
            *Copy_CurrentPosition = Copy_xPosition + Copy_Size - 1;
            gotoxy1(*Copy_CurrentPosition, Copy_yPosition);
            break;
        }
        break;
    case BackSpace:
        if (*Copy_CurrentPosition > Copy_xPosition)
        {
            _cprintf(" ");
            Copy_Data[*Copy_CurrentPosition - Copy_xPosition] = ' ';
            (*Copy_CurrentPosition)--;
            gotoxy1(*Copy_CurrentPosition, Copy_yPosition);
        }
        else if (*Copy_CurrentPosition == Copy_xPosition && Copy_Data[0] != ' ')
        {
            _cprintf(" ");
            gotoxy1(*Copy_CurrentPosition, Copy_yPosition);
            Copy_Data[*Copy_CurrentPosition - Copy_xPosition] = ' ';
        }
        break;
    case Space:
        if (*Copy_CurrentPosition < (Copy_xPosition + Copy_Size) - 1)
        {
            _cprintf(" ");
            Copy_Data[*Copy_CurrentPosition - Copy_xPosition] = ' ';
            (*Copy_CurrentPosition)++;
            gotoxy1(*Copy_CurrentPosition, Copy_yPosition);
        }
        break;

    case Enter:
        if (Copy_Data[0] != '\0' && Copy_Data[0] != ' ')
        {
            *Copy_ExitFlag = 1;
            if ((*Copy_CurrentPosition - Copy_xPosition) < Copy_Size)
            {
                Copy_Data[*Copy_CurrentPosition - Copy_xPosition + 1] = '\0';
            }
        }
        break;

    case Esc:
        *Copy_ExitFlag = 1;
        if ((*Copy_CurrentPosition - Copy_xPosition) < Copy_Size)
        {
            Copy_Data[*Copy_CurrentPosition - Copy_xPosition + 1] = '\0';
        }
        break;
    }
}

void SelectAction(char Copy_Character, int *Copy_ExitFlag, int *Copy_CurrentPosition, char **Copy_Data, int *Copy_Size, int *Copy_xPosition, int *Copy_yPosition, int *Copy_CurrentLine)
{
    char Local_Character = 0;
    int Local_Counter = 0;



    switch (Copy_Character)
    {
    case -32:
        Local_Character = getch();
        switch (Local_Character)
        {
        case Left:
            if (Copy_CurrentPosition[*Copy_CurrentLine] > Copy_xPosition[*Copy_CurrentLine])
            {
                (Copy_CurrentPosition[*Copy_CurrentLine])--;
                gotoxy1(Copy_CurrentPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
            }
            break;
        case Right:
            if (Copy_CurrentPosition[*Copy_CurrentLine] < (Copy_xPosition[*Copy_CurrentLine] + Copy_Size[*Copy_CurrentLine]) - 1)
            {
                Copy_CurrentPosition[*Copy_CurrentLine]++;
                gotoxy1(Copy_CurrentPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
            }
            break;
        case Up:
            if ((*Copy_CurrentLine) == 0)
            {
                *Copy_CurrentLine = 10;
            }
            else
            {
                (*Copy_CurrentLine)--;
            }
            gotoxy1(Copy_CurrentPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
            break;
        case Down:
            if ((*Copy_CurrentLine) == 10)
            {
                *Copy_CurrentLine = 0;
            }
            else
            {
                (*Copy_CurrentLine)++;
            }
            gotoxy1(Copy_CurrentPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
            break;
        case Home:
            Copy_CurrentPosition[*Copy_CurrentLine] = Copy_xPosition[*Copy_CurrentLine];
            gotoxy1(Copy_CurrentPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
            break;
        case End:
            Copy_CurrentPosition[*Copy_CurrentLine] = Copy_xPosition[*Copy_CurrentLine] + Copy_Size[*Copy_CurrentLine] - 1;
            gotoxy1(Copy_CurrentPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
            break;
        }
        break;
    case BackSpace:
        if (Copy_CurrentPosition[*Copy_CurrentLine] > Copy_xPosition[*Copy_CurrentLine])
        {
            _cprintf(" ");
            Copy_Data[*Copy_CurrentLine][Copy_CurrentPosition[*Copy_CurrentLine] - Copy_xPosition[*Copy_CurrentLine]] = ' ';
            Copy_CurrentPosition[*Copy_CurrentLine]--;
            gotoxy1(Copy_CurrentPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
        }
        else if (Copy_CurrentPosition[*Copy_CurrentLine] == Copy_xPosition[*Copy_CurrentLine])
        {
            _cprintf(" ");
            gotoxy1(Copy_CurrentPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
            Copy_Data[*Copy_CurrentLine][Copy_CurrentPosition[*Copy_CurrentLine] - Copy_xPosition[*Copy_CurrentLine]] = ' ';
        }
        break;
    case Space:
        if (Copy_CurrentPosition[*Copy_CurrentLine] < (Copy_xPosition[*Copy_CurrentLine] + Copy_Size[*Copy_CurrentLine]) - 1)
        {
            _cprintf(" ");
            Copy_Data[*Copy_CurrentLine][Copy_CurrentPosition[*Copy_CurrentLine] - Copy_xPosition[*Copy_CurrentLine]] = ' ';
            Copy_CurrentPosition[*Copy_CurrentLine]++;
            gotoxy1(Copy_CurrentPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
        }
        break;
    case Enter:
        *Copy_ExitFlag = 1;
        for (Local_Counter = 0; Local_Counter < NUM_OF_LINES; Local_Counter++)
        {
            if (Copy_Data[Local_Counter][0] == '\0' || Copy_Data[Local_Counter][0] == ' ')
            {
                *Copy_ExitFlag = 0;
                break;
            }
        }
        break;
    case Tab:

        if (Copy_Data[*Copy_CurrentLine][0] != '\0' && Copy_Data[*Copy_CurrentLine][0] != ' ')
        {
            //Copy_Data[*Copy_CurrentLine][Copy_CurrentPosition[*Copy_CurrentLine] - Copy_xPosition[*Copy_CurrentLine] + 1] = '\0';
            Copy_Data[*Copy_CurrentLine][MaxCurrentPosition[*Copy_CurrentLine] - Copy_xPosition[*Copy_CurrentLine] + 1] = '\0';

            if (*Copy_CurrentLine == NUM_OF_LINES - 1)
            {
                (*Copy_CurrentLine) = 0;
            }
            else
            {
                (*Copy_CurrentLine)++;
            }

            gotoxy1(Copy_xPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
        }
        break;
    case Esc:
        *Copy_ExitFlag = 1;
        if ((Copy_CurrentPosition[*Copy_CurrentLine] - Copy_xPosition[*Copy_CurrentLine]) < Copy_Size[*Copy_CurrentLine])
        {
            Copy_Data[*Copy_CurrentLine][Copy_CurrentPosition[*Copy_CurrentLine] - Copy_xPosition[*Copy_CurrentLine] + 1] = '\0';
        }
        break;
    }
}

void PrintNonExtendedKeysLine(char Copy_Character, char *Copy_Data, int *Copy_CurrentPosition, int Copy_Size, int Copy_xPosition, int Copy_yPosition, short int CharsOrNums)
{
    if (CharsOrNums == 1) // Chars Only
    {
        if (((Copy_Character >= A_VALUE && Copy_Character <= Z_VALUE) || (Copy_Character >= a_VALUE && Copy_Character <= z_VALUE)) && (*Copy_CurrentPosition != (Copy_xPosition + Copy_Size)))
        {
            if (*Copy_CurrentPosition < (Copy_xPosition + Copy_Size) - 1)
            {
                _cprintf("%c", Copy_Character);
                Copy_Data[*Copy_CurrentPosition - Copy_xPosition] = Copy_Character;
                (*Copy_CurrentPosition)++;
                gotoxy1(*Copy_CurrentPosition, Copy_yPosition);
            }
            else
            {
                _cprintf("%c", Copy_Character);
                Copy_Data[*Copy_CurrentPosition - Copy_xPosition] = Copy_Character;
                gotoxy1(*Copy_CurrentPosition, Copy_yPosition);
            }
        }
    }
    else if (CharsOrNums == 2)
    {
        if ((Copy_Character >= ZERO_VALUE && Copy_Character <= NINE_VALUE) && *Copy_CurrentPosition != (Copy_xPosition + Copy_Size))
        {
            if (*Copy_CurrentPosition < (Copy_xPosition + Copy_Size) - 1)
            {
                _cprintf("%c", Copy_Character);
                Copy_Data[*Copy_CurrentPosition - Copy_xPosition] = Copy_Character;
                (*Copy_CurrentPosition)++;
                gotoxy1(*Copy_CurrentPosition, Copy_yPosition);
            }
            else
            {
                _cprintf("%c", Copy_Character);
                Copy_Data[*Copy_CurrentPosition - Copy_xPosition] = Copy_Character;
                gotoxy1(*Copy_CurrentPosition, Copy_yPosition);
            }
        }
    }
}

void PrintNonExtendedKeys(char Copy_Character, char **Copy_Data, int *Copy_CurrentPosition, int *Copy_Size, int *Copy_xPosition, int *Copy_yPosition, int *Copy_CurrentLine, int *CharsOrNums)
{
    if (CharsOrNums[*Copy_CurrentLine] == CHARS)
    {
        if (((Copy_Character >= A_VALUE && Copy_Character <= Z_VALUE) || (Copy_Character >= a_VALUE && Copy_Character <= z_VALUE)) && (Copy_CurrentPosition[*Copy_CurrentLine] != (Copy_xPosition[*Copy_CurrentLine] + Copy_Size[*Copy_CurrentLine])))
        {
            if (Copy_CurrentPosition[*Copy_CurrentLine] < (Copy_xPosition[*Copy_CurrentLine] + Copy_Size[*Copy_CurrentLine] - 1))
            {
                _cprintf("%c", Copy_Character);
                Copy_Data[*Copy_CurrentLine][Copy_CurrentPosition[*Copy_CurrentLine] - Copy_xPosition[*Copy_CurrentLine]] = Copy_Character;
                Copy_CurrentPosition[*Copy_CurrentLine]++;
                if(MaxCurrentPosition[*Copy_CurrentLine] < Copy_CurrentPosition[*Copy_CurrentLine])
                {
                    MaxCurrentPosition[*Copy_CurrentLine] = Copy_CurrentPosition[*Copy_CurrentLine];
                }
                gotoxy1(Copy_CurrentPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
            }
            else
            {
                _cprintf("%c", Copy_Character);
                Copy_Data[*Copy_CurrentLine][Copy_CurrentPosition[*Copy_CurrentLine] - Copy_xPosition[*Copy_CurrentLine]] = Copy_Character;
                if(MaxCurrentPosition[*Copy_CurrentLine] < Copy_CurrentPosition[*Copy_CurrentLine])
                {
                    MaxCurrentPosition[*Copy_CurrentLine] = Copy_CurrentPosition[*Copy_CurrentLine];
                }
                gotoxy1(Copy_CurrentPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
            }
        }
    }
    else if (CharsOrNums[*Copy_CurrentLine] == NUMS)
    {
        if ((Copy_Character >= ZERO_VALUE && Copy_Character <= NINE_VALUE) && (Copy_CurrentPosition[*Copy_CurrentLine] != (Copy_xPosition[*Copy_CurrentLine] + Copy_Size[*Copy_CurrentLine])))
        {
            if (Copy_CurrentPosition[*Copy_CurrentLine] < (Copy_xPosition[*Copy_CurrentLine] + Copy_Size[*Copy_CurrentLine] - 1))
            {
                _cprintf("%c", Copy_Character);
                Copy_Data[*Copy_CurrentLine][Copy_CurrentPosition[*Copy_CurrentLine] - Copy_xPosition[*Copy_CurrentLine]] = Copy_Character;
                Copy_CurrentPosition[*Copy_CurrentLine]++;
                if(MaxCurrentPosition[*Copy_CurrentLine] < Copy_CurrentPosition[*Copy_CurrentLine])
                {
                    MaxCurrentPosition[*Copy_CurrentLine] = Copy_CurrentPosition[*Copy_CurrentLine];
                }
                gotoxy1(Copy_CurrentPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
            }
            else
            {
                _cprintf("%c", Copy_Character);
                Copy_Data[*Copy_CurrentLine][Copy_CurrentPosition[*Copy_CurrentLine] - Copy_xPosition[*Copy_CurrentLine]] = Copy_Character;
                if(MaxCurrentPosition[*Copy_CurrentLine] < Copy_CurrentPosition[*Copy_CurrentLine])
                {
                    MaxCurrentPosition[*Copy_CurrentLine] = Copy_CurrentPosition[*Copy_CurrentLine];
                }
                gotoxy1(Copy_CurrentPosition[*Copy_CurrentLine], Copy_yPosition[*Copy_CurrentLine]);
            }
        }
    }
}

void MainMenu()
{
    short int Local_Counter = 0;
    for (Local_Counter = 0; Local_Counter < 3; Local_Counter++)
    {
        gotoxy1(10, 8 + 3 * Local_Counter);
        if (Global_Current == Local_Counter)
        {
            textattr(0x03);
        }
        else
        {
            textattr(0x0F);
        }
        _cprintf("%s", Menu[Local_Counter]);
    }
}

void SelectActionMenu(char Copy_Character, struct Employee *Employees, int *ExistingEmployees, int *NumberOfEmployees)
{
    char Local_Character = 0;
    switch (Copy_Character)
    {
    case -32:
        Local_Character = getch();
        switch (Local_Character)
        {
        case Up:
            if (Global_Current == 0)
                Global_Current = 2;
            else
                Global_Current--;
            break;
        case Down:
            if (Global_Current == 2)
                Global_Current = 0;
            else
                Global_Current++;
            break;
        case Home:
            Global_Current = 0;
            break;
        case End:
            Global_Current = 2;
            break;
        }
        break;
    case Enter:
        PressedEnter(Global_Current, Employees, ExistingEmployees, NumberOfEmployees);
        break;
    case Esc:
        Global_ExitFlag = 1;
        break;
    }
}

void PressedEnter(int Copy_Current, struct Employee *Employees, int *ExistingEmployees, int *NumberOfEmployees)
{
    char Local_Character;
    textattr(0x0F);
    system("cls");
    DoAction(Copy_Current, Employees, ExistingEmployees, NumberOfEmployees);
    textattr(0x0C);
    printf("\n\n\n\n\n\n\n\n\n.........Press Escape key to return to the main menu.........\n");
    Local_Character = getch();
    while (Local_Character != Esc)
    {
        Local_Character = getch();
    }
    textattr(0x0F);
    system("cls");
}

void DoAction(int Copy_Number, struct Employee *Employees, int *ExistingEmployees, int *NumberOfEmployees)
{
    int Local_Employee_Index;
    char *DataNumbers;

    switch (Copy_Number)
    {
    case 0:
        printf("Enter Employee Index: \n");
        DataNumbers = LineEditor(0, 1, 2, NUMS);
        Local_Employee_Index = atoi(DataNumbers);
        free(DataNumbers);
        if ((Local_Employee_Index >= 1) && (Local_Employee_Index <= *NumberOfEmployees))
        {
            DataMenu();
            NewEmployeeMenu(Local_Employee_Index - 1, Employees);
            ExistingEmployees[Local_Employee_Index - 1] = 1;
        }
        else
        {
            textattr(0x0C);
            printf("\n\n\nWrong Employee Index");
        }

        break;

    case 1:
        printf("Enter Employee Index: \n");
        DataNumbers = LineEditor(0, 1, 2, NUMS);
        Local_Employee_Index = atoi(DataNumbers);
        free(DataNumbers);
        if ((Local_Employee_Index >= 1) && (Local_Employee_Index <= *NumberOfEmployees) && (ExistingEmployees[Local_Employee_Index - 1] == 1))
        {
            DisplayEmployee(Employees[Local_Employee_Index - 1]);
            printf("\n");
        }
        else
        {
            textattr(0x0C);
            printf("\n\n\nWrong Employee Index or the data isn't available. \n");
        }
        break;

    case 2:
        printf("\n\n");
        for (int Local_Counter = 0; Local_Counter < *NumberOfEmployees; Local_Counter++)
        {
            if (ExistingEmployees[Local_Counter] == 1)
            {
                printf("\n........Employee with index %d: ........", Local_Counter + 1);
                DisplayEmployee(Employees[Local_Counter]);
                printf("\n\n");
            }
        }
        break;
    }
}

void DataMenu()
{
    textattr(0x03);
    char Menu[11][20] = {"ID: ", "Age: ", "Gender(M/F): ", "First Name: ", "Second Name: ", "Salary: ", "OverTime: ", "Deduction: ", "Address: ", "Phone Number: ", "Department: "};
    char Local_Counter = 0;
    for (Local_Counter = 0; Local_Counter < 7; Local_Counter++)
    {
        gotoxy1(10, 8 + 2 * Local_Counter);
        _cprintf("%s", Menu[Local_Counter]);
    }
    for (Local_Counter = 0; Local_Counter < 4; Local_Counter++)
    {
        gotoxy1(40, 8 + 2 * Local_Counter);
        _cprintf("%s", Menu[Local_Counter + 7]);
    }
}

void NewEmployeeMenu(int Copy_Employee_Index, struct Employee *Employees)
{
    char Local_Character = 0;
    short int Local_Counter = 0;
    char **DataChars;
    int *X_Positions = (int *)malloc(NUM_OF_LINES * sizeof(int));
    int *Y_Positions = (int *)malloc(NUM_OF_LINES * sizeof(int));
    int *Copy_Size = (int *)malloc(NUM_OF_LINES * sizeof(int));
    int *CharsOrNums = (int *)malloc(NUM_OF_LINES * sizeof(int));

    X_Positions[0] = 15;
    X_Positions[1] = 20;
    X_Positions[2] = 25;
    X_Positions[3] = 25;
    X_Positions[4] = 25;
    X_Positions[5] = 25;
    X_Positions[6] = 25;
    X_Positions[7] = 55;
    X_Positions[8] = 55;
    X_Positions[9] = 55;
    X_Positions[10] = 55;

    Y_Positions[0] = 8;
    Y_Positions[1] = 10;
    Y_Positions[2] = 12;
    Y_Positions[3] = 14;
    Y_Positions[4] = 16;
    Y_Positions[5] = 18;
    Y_Positions[6] = 20;
    Y_Positions[7] = 8;
    Y_Positions[8] = 10;
    Y_Positions[9] = 12;
    Y_Positions[10] = 14;

    Copy_Size[0] = IDNum;
    Copy_Size[1] = AgeNum;
    Copy_Size[2] = GenderNum;
    Copy_Size[3] = FirstNameNum;
    Copy_Size[4] = SecondNameNum;
    Copy_Size[5] = SalaryNum;
    Copy_Size[6] = OvertimeNum;
    Copy_Size[7] = DeductionNum;
    Copy_Size[8] = AddressNum;
    Copy_Size[9] = PhoneNumberNum;
    Copy_Size[10] = DeptNameNumber;

    CharsOrNums[0] = NUMS;
    CharsOrNums[1] = NUMS;
    CharsOrNums[2] = CHARS;
    CharsOrNums[3] = CHARS;
    CharsOrNums[4] = CHARS;
    CharsOrNums[5] = NUMS;
    CharsOrNums[6] = NUMS;
    CharsOrNums[7] = NUMS;
    CharsOrNums[8] = CHARS;
    CharsOrNums[9] = NUMS;
    CharsOrNums[10] = CHARS;

    DataChars = MultiLineEditor(X_Positions, Y_Positions, Copy_Size, NUM_OF_LINES, CharsOrNums);

    Employees[Copy_Employee_Index].ID = atoi(DataChars[0]);

    Employees[Copy_Employee_Index].age = atoi(DataChars[1]);

    Employees[Copy_Employee_Index].Gender = DataChars[2][0];

    for (Local_Counter = 0; Local_Counter < FirstNameNum + 1; Local_Counter++)
    {
        Employees[Copy_Employee_Index].FirstName[Local_Counter] = DataChars[3][Local_Counter];
    }

    for (Local_Counter = 0; Local_Counter < SecondNameNum + 1; Local_Counter++)
    {
        Employees[Copy_Employee_Index].SecondName[Local_Counter] = DataChars[4][Local_Counter];
    }

    Employees[Copy_Employee_Index].Salary = atof(DataChars[5]);

    Employees[Copy_Employee_Index].Overtime = atof(DataChars[6]);

    Employees[Copy_Employee_Index].Deduction = atof(DataChars[7]);

    for (Local_Counter = 0; Local_Counter < AddressNum + 1; Local_Counter++)
    {
        Employees[Copy_Employee_Index].Address[Local_Counter] = DataChars[8][Local_Counter];
    }

    for (Local_Counter = 0; Local_Counter < PhoneNumberNum + 1; Local_Counter++)
    {
        Employees[Copy_Employee_Index].PhoneNumber[Local_Counter] = DataChars[9][Local_Counter];
    }

    for (Local_Counter = 0; Local_Counter < DeptNameNumber + 1; Local_Counter++)
    {
        Employees[Copy_Employee_Index].DeptName[Local_Counter] = DataChars[10][Local_Counter];
    }

    free(X_Positions);
    free(Y_Positions);
    free(Copy_Size);
    free(CharsOrNums);
    for (Local_Counter = 0; Local_Counter < NUM_OF_LINES; Local_Counter++)
    {
        free(DataChars[Local_Counter]);
    }
    free(DataChars);
}

void DisplayEmployee(struct Employee Copy_Employee)
{
    printf("\n\n\n");
    textattr(0x0F);
    char FullName[20] = {0};
    strcat(FullName, Copy_Employee.FirstName);
    strcat(FullName, Copy_Employee.SecondName);
    printf("Employee Code: %d\n", Copy_Employee.ID);
    printf("Employee Name: %s\n", FullName);
    printf("Employee Age: %d\n", Copy_Employee.age);
    printf("Employee Gender: %c\n", Copy_Employee.Gender);
    printf("Employee Salary: %.2f\n", Copy_Employee.Salary);
    printf("Employee Overtime: %.2f\n", Copy_Employee.Overtime);
    printf("Employee Deduction: %.2f\n", Copy_Employee.Deduction);
    printf("Employee Net Salary: %.2f\n", Copy_Employee.Salary + Copy_Employee.Overtime - Copy_Employee.Deduction);
    printf("Employee Address: %s\n", Copy_Employee.Address);
    printf("Employee Phone Number: %s\n", Copy_Employee.PhoneNumber);
    printf("Employee Department Name: %s\n", Copy_Employee.DeptName);
}
