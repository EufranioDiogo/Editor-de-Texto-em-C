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
int stringSize(char *string);
int equalsToCommandReaded(char *string1, char *string2);
void changeCurrentLine(List *textEditor, char *command);
void getUltimoID(List *textEditor);
void printLines(List *textEditor, char *command);
void removeRows(List *textEditor, char *command);


int main() {
    List *textEditor = (List *)(malloc(sizeof(List)));
    int flagRunning = 1;

    while(flagRunning == 1) {
        char commandLine[TOTAL_CHARACTER_PER_LINE];
        fgets(commandLine, sizeof(commandLine), stdin);

        int isCommand = isComand(commandLine);

        if (isCommand != -1) {
            int startCommandIndex = isCommand;

            int commandCode = checkCommand(startCommandIndex, commandLine);
            printf("\nCommand code: %d\n", commandCode);

            switch (commandCode) {
                case 1: // Inserir
                    char text[TOTAL_CHARACTER_PER_LINE];

                    gets(text, sizeof(text), stdin);
                    addNewLine(textEditor, text);
                    break;
                case 2: // remover m, n
                    removeRows(textEditor, commandLine)
                    break;
                case 3: // linha m (to test)
                    changeCurrentLine(textEditor, commandLine);
                    break;
                 case 4: // localizar %x
                    // TO-DO 
                    break;
                case 5: // alterar %x %y %
                    // TO-DO 
                    break;
                case 6: // ultimo (to test)
                    getUltimoID(textEditor);
                    break;
                case 7: // imprimir m, n
                    // TO-DO 
                    break;
                case 8: // fim
                    flagRunning = 0;
                    break;
                default:
                    // TO-DO 
                    break;
            }
        } else {
            printf("\nPlease Enter a command");
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
        return -1;
    }
    return i;
}

void addNewLine(List *textEditor, char *textLine) {
    if (stringSize(textLine) < TOTAL_CHARACTER_PER_LINE) {
        if (textEditor -> firstRow == NULL && textEditor -> lastRow == NULL) {
            textEditor -> firstRow = (Row *)(malloc(sizeof(Row)));
            setUpRow(textEditor -> firstRow);

            copyTextToNewLine(textEditor -> firstRow, textLine);
            textEditor -> firstRow -> idLine = 1;
            textEditor -> currentLine = 1;
            textEditor -> quantRows = 1;

            textEditor -> lastRow = textEditor -> firstRow;
            textEditor -> currentRow = textEditor -> lastRow;
            textEditor -> currentRow -> flagCurrentLine = 1;
        } else {
            Row *newRow = (Row *)(malloc(sizeof(Row)));

            setUpRow(newRow);
            copyTextToNewLine(newRow, textLine);

            newRow -> flagCurrentLine = 1;
            newRow -> idLine = textEditor -> currentRow -> idLine + 1;
            newRow -> previousRow = textEditor -> currentRow;

            if (textEditor -> currentRow -> idLine == textEditor -> lastRow -> idLine) {
                textEditor -> currentRow -> nextRow = newRow;
                textEditor -> lastRow = newRow;
                textEditor -> currentRow = newRow;
            } else {
                newRow -> nextRow = textEditor -> currentRow -> nextRow;

                textEditor -> currentRow -> nextRow = newRow;
                newRow -> nextRow -> previousRow = newRow -> nextRow;

                textEditor -> currentLine = newRow -> idLine;
                textEditor -> currentRow = newRow;
            }
            textEditor -> quantRows += 1;

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
    newRow -> character[i] = '\0';
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

    if (equalsToCommandReaded(command, "inserir") != 0) {
        printf("\nInserir Command\n");
        return 1;
    } else if (equalsToCommandReaded(command, "remover") != 0) {
        printf("\nRemover Command\n");
        return 2;
    } else if (equalsToCommandReaded(command, "linha") != 0) {
        printf("\nLinha Command\n");
        return 3;
    } else if (equalsToCommandReaded(command, "localizar") != 0) {
        printf("\nLocalizar Command\n");
        return 4;
    } else if (equalsToCommandReaded(command, "alterar") != 0) {
        printf("\nAlterar Command\n");
        return 5;
    } else if (equalsToCommandReaded(command, "ultimo") != 0) {
        printf("\nUltimo Command\n");
        return 6;
    } else if (equalsToCommandReaded(command, "imprimir") != 0) {
        printf("\nImprimir Command\n");
        return 7;
    } else if (equalsToCommandReaded(command, "fim") != 0) {
        printf("\nFim Command\n");
        return 8;
    } else {
        return -1;
    }
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

int equalsToCommandReaded(char *string1, char *string2) {
    int i = 0;
    int string1Size = stringSize(string1) - 1;
    int string2Size = stringSize(string2);

    printf("\n%d == %d, %s == %s\n", string1Size, string2Size, string1, string2);

    if (string1Size != string2Size) {
        return 0;
    }

    while (i < string1Size) {
        if (*(string1 + i) != *(string2 + i)) {
            return 0;
        }
        i++;
    }
    return 1;
}

int stringSize(char *string) {
    int i = 0;

    while (*(string + i) != '\0') {
        i++;
    }
    return i;
}

void changeCurrentLine(List *textEditor, char *command) {
    char lineNumber[] = {'a', 'a', 'a', 'a', 'a'};
    int i = 0;
    int j = 0;

    if(stringSize(command) < 8) {
        printf("ERRO: PARAMETROS INSUFICIENTES");
    } else {
        i = 7;

        while (j < 5 && *(command + i) != '\0') {
            lineNumber[j] = *(command + i);
            i++;
            j++;
        }

        int lineRefered = atoi(lineNumber);

        if (lineRefered > textEditor -> quantRows || lineNumber <= 0) {
            printf("ERRO: LINHA NÃO EXISTE");
        } else {
            int currentLine = textEditor -> currentLine;

            if (currentLine == lineRefered) {
                printf("LINHA JÁ É A ACTUAL");
            } else {
                if (lineRefered > currentLine) {
                    int quantSteps = lineRefered - currentLine;
                    Row *auxRow = textEditor -> currentRow;

                    textEditor -> currentRow -> flagCurrentLine = 0;

                    while (quantSteps > 0) {
                        auxRow = auxRow -> nextRow;
                        quantSteps--;
                    }
                    textEditor -> currentLine = lineRefered;
                    textEditor -> currentRow = auxRow;
                    textEditor -> currentRow -> flagCurrentLine = 1;
                } else {
                    int quantSteps = currentLine - lineRefered; 
                    Row *auxRow = textEditor -> currentRow;

                    textEditor -> currentRow -> flagCurrentLine = 0;

                    while (quantSteps > 0) {
                        auxRow = auxRow -> previousRow;
                        quantSteps--;
                    }
                    textEditor -> currentLine = lineRefered;
                    textEditor -> currentRow = auxRow;
                    textEditor -> currentRow -> flagCurrentLine = 1;
                }
            }
        }
    }
}

void getUltimoID(List *textEditor) {
    if (textEditor -> lastRow != NULL) {
        printf("\n%d", textEditor -> lastRow -> idLine);
    } else {
        printf("\nTextEditor Vazio");
    }
}

int contains(char *string, char *subString) {
    if (stringSize(subString) > stringSize(string)) {
        return -1;
    }

    int flagSubStringFounded;
    int mainStringSize = stringSize(string);
    int subStringSize = stringSize(subString);
    int quantPossibleSubstringInString = mainStringSize / subStringSize;

    for (int i = 0; i < quantPossibleSubstringInString; i++) {
        flagSubStringFounded = 1;
        for (int j = 0; j < subStringSize; j++) {
            if (subString[j] != string[i + j]) {
                flagSubStringFounded = 0;
                break;
            }
        }

        if (flagSubStringFounded == 1) {
            return i;
        }
    }
    return 0;
}

void printLines(List *textEditor, char *command) {
    if (stringSize(command) < 13) {
        printf("ERRO: QUANT PARAMETROS NÃO VALIDOS");
    } else {
        char startLine[] = {'a', 'a', 'a', 'a', 'a'};
        char endLine[] = {'a', 'a', 'a', 'a', 'a'};

        int commaIndex = contains(command, ",");
        int k = 0;
        int i = 0;

        for (i = commaIndex + 1; command[i] != '\0'; i++, k++) {
            endLine[k] = command[i];
        }

        int spaceIndex = contains(command, " ");

        for (i = spaceIndex + 1, k =  0; command[i] != '\0'; i++, k++) {
            startLine[k] = command[i];
        }

        int printStart = atoi(startLine);
        int printEnd = atoi(endLine);

        if (printEnd > 0 && printStart > 0) {
            if (printStart > printEnd) {
                printf("\nERROR: Start line greater than printStart");
            } else {
                
            }
        } else {
            printf("\nERROR: NOT VALID LINES");
        }
        
    }
}

void removeRows(List *textEditor, char *command) {

}