#ifndef EDITOR_H_
#define EDITOR_H_

char *LineEditor(int Copy_xPosition, int Copy_yPosition, int Copy_Size, short int CharsOrNums);
char **MultiLineEditor(int *Copy_xPosition, int *Copy_yPosition, int *Copy_Size, int NumberOfLines, int *CharsOrNums);
void SelectActionLine(char Copy_Character, int *Copy_ExitFlag, int *Copy_CurrentPosition, char *Copy_Data, int Copy_Size, int Copy_xPosition, int Copy_yPosition);
void PrintNonExtendedKeysLine(char Copy_Character, char *Copy_Data, int *Copy_CurrentPosition, int Copy_Size, int Copy_xPosition, int Copy_yPosition, short int CharsOrNums);



#endif