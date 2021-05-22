#include <stdio.h>
#include <stdlib.h>
#include "tda.h"

void initializeTextEditor(List *textEditor);
int checkComand(char *textLine);
void addNewLine(List *textEditor, char *textLine);
void copyTextToNewLine(Row *newRow, char *textLine);
void setUpNewRow(List *textEditor, Row *newRow);


int main() {
    List *textEditor = (List *)(malloc(sizeof(List)));
    char textLine[TOTAL_CHARACTER_PER_LINE];


    while(1 == 1) {
        fgets(textLine, sizeof(textLine), stdin);

        int isCommandPresent = checkComand(textLine);

        if (isCommandPresent == 0) {
            addNewLine(textEditor, textLine);
        } else {

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

int checkComand(char *textLine) {
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
    return 1;
}

void addNewLine(List *textEditor, char *textLine) {
    if (textEditor -> firstRow == NULL && textEditor -> lastRow == NULL) {
        textEditor -> firstRow = (Row *)(malloc(sizeof(Row)));
        textEditor -> lastRow = textEditor -> firstRow;
        textEditor -> currentRow = textEditor -> lastRow;
    }

    Row *newRow = (Row *)(malloc(sizeof(Row)));

    setUpNewRow(textEditor, newRow);
    copyTextToNewLine(newRow, textLine);
}

void copyTextToNewLine(Row *newRow, char *textLine) {
    int i = 0;


}

void setUpNewRow(List *textEditor, Row *newRow) {
    int idLine;
    int startCharCollumn;
    int endCharCollumn;
    char character[TOTAL_CHARACTER_PER_LINE];
    int currentLine;
    struct node *previousLine;
    struct node *nextLine;
}