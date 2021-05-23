#include <stdio.h>
#include <stdlib.h>
#include "tda.h"

void initializeTextEditor(List *textEditor);
int isComand(char *textLine);
void addNewLine(List *textEditor, char *textLine);
void copyTextToNewLine(Row *newRow, char *textLine);
void setUpRow(Row *newRow);
int getQuantCharacter(char *textLine);
void updateRowsIDs(Row *row);
int checkCommand(int startIndexOfCommand, char *textLine);
void takeCommand(int starIndexOfCommand, char *textLine, char *command);


int main() {
    List *textEditor = (List *)(malloc(sizeof(List)));
    char textLine[TOTAL_CHARACTER_PER_LINE];


    while(1 == 1) {
        fgets(textLine, sizeof(textLine), stdin);

        int isCommand = isComand(textLine);

        if (isCommand == 0) {
            addNewLine(textEditor, textLine);
        } else {
            int startCommandIndex = isCommand;

            checkCommand(startCommandIndex, textLine);
        }
    }
}

void initializeTextEditor(List *textEditor) {
    textEditor -> firstRow = NULL;
    textEditor -> currentRow = NULL;
    textEditor -> lastRow = NULL;
    textEditor -> quantRows = 0;
    textEditor -> flagInsertMode = 0;
    textEditor -> currentCollumn = 0;
    textEditor -> currentLine = 0;
}

int isComand(char *textLine) {
    int i = 0;
    int dollarSignalFound = 0;

    while (*(textLine + i) != '\0') {
        if (*(textLine + i) == '$') {
            dollarSignalFound = 1;
            break;
        }
        i++;
    }

    if (dollarSignalFound == 0) {
        return 0;
    }
    return i;
}

void addNewLine(List *textEditor, char *textLine) {
    if (getQuantCharacter(textLine) < TOTAL_CHARACTER_PER_LINE) {
        if (textEditor -> firstRow == NULL && textEditor -> lastRow == NULL) {
            textEditor -> firstRow = (Row *)(malloc(sizeof(Row)));
            setUpRow(textEditor -> firstRow);

            copyTextToNewLine(textEditor -> firstRow, textLine);
            textEditor -> firstRow -> idLine = 1;
            textEditor -> firstRow -> flagCurrentLine = 1;
            textEditor -> currentLine = 1;

            textEditor -> lastRow = textEditor -> firstRow;
            textEditor -> currentRow = textEditor -> lastRow;
        } else {
            Row *newRow = (Row *)(malloc(sizeof(Row)));

            setUpRow(newRow);
            copyTextToNewLine(newRow, textLine);

            newRow -> previousRow = textEditor -> currentRow;
            newRow -> nextRow = textEditor -> currentRow -> nextRow;
            textEditor -> currentRow -> nextRow = newRow;
            newRow -> nextRow -> previousRow = newRow;
            newRow -> idLine = newRow -> previousRow -> idLine + 1;
            textEditor -> currentRow = newRow;
            textEditor -> currentLine = newRow -> idLine;

            updateRowsIDs(textEditor -> currentRow);
        }
    } else {
        printf("ERROR: Linha com a quantidade máxima de caracteres atingida");
    }
    

    
}

void copyTextToNewLine(Row *newRow, char *textLine) {
    int i = 0;

    while (*(textLine + i) != '\0') {
        newRow -> character[i] = *(textLine + i);
        i++;
    }
    newRow -> endCharCollumn = i;
    newRow -> character[i] = *(textLine + i);
}

void setUpRow(Row *row) {
    row -> idLine = 0;
    row -> startCharCollumn = 0;
    row -> endCharCollumn = 0;
    row -> flagCurrentLine = 0;
    row -> previousRow = NULL;
    row -> nextRow = NULL;
}

int getQuantCharacter(char *textLine) {
    int i = 0;

    while (*(textLine + i) != '\0') {
        i++;
    }
    return i;
}

void updateRowsIDs(Row *row) {
    Row *actualRow = row -> nextRow;

    while (actualRow != NULL) {
        actualRow -> idLine = actualRow -> previousRow -> idLine + 1;
        actualRow = actualRow -> nextRow;
    }
}

int checkCommand(int startIndexOfCommand, char *textLine) {
    char command[20];

    takeCommand(startIndexOfCommand, textLine, command);

    
}

void takeCommand(int startIndexOfCommand, char *textLine, char *command) {
    int i = startIndexOfCommand + 1;
    int j = 0;

    while(*(textLine + i) != '\0' && *(textLine + i) != ' ') {
        command[j] = *(textLine + i);
        i++;
        j++;
    }
    command[j] = '\0';
}