#define TOTAL_CHARACTER_PER_LINE 80


typedef struct node {
    int idLine;
    int startCharCollumn;
    int endCharCollumn;
    char character[TOTAL_CHARACTER_PER_LINE];
    int flagCurrentLine;
    struct node *previousRow;
    struct node *nextRow;
} Row;

typedef struct list {
    Row *firstRow;
    Row *currentRow;
    Row *lastRow;
    int quantRows;
    int currentLine;
    int currentCollumn;
    int flagInsertMode;
} List;


void initializeTextEditor(List *textEditor);
int isComand(char *textLine);
void addNewLine(List *textEditor, char *textLine);
void copyTextToNewLine(Row *newRow, char *textLine);
void setUpRow(Row *newRow);
int getQuantCharacter(char *textLine);
void updateRowsIDs(Row *row);
int checkCommand(int startIndexOfCommand, char *textLine);
void takeCommand(int starIndexOfCommand, char *textLine, char *command);
int stringSize(char *string);
int equalsToCommandReaded(char *string1, char *string2);
void changeCurrentLine(List *textEditor, char *command);
void getUltimoID(List *textEditor);
void printLines(List *textEditor, char *command);
void removeRows(List *textEditor, char *command);
int getTwoParametersOfCommand(char *command, int *firstArgument, int *secondArgument);
void printRow(Row *row);
int contains(char *string, char *subString);
int containsWithStartIndex(char *string, char *subString, int index);
void searchPattern(List *textEditor, char *textLine);
void changeOcorrences(Row *actualRow, char *command);

