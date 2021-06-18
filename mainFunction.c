#include <stdio.h>
#include <stdlib.h>
#include "tda.h"

void initializeTextEditor(List *textEditor)
{
    textEditor->firstRow = NULL;
    textEditor->currentRow = NULL;
    textEditor->lastRow = NULL;
    textEditor->quantRows = 0;
    textEditor->flagInsertMode = 0;
    textEditor->currentCollumn = 0;
    textEditor->currentLine = 0;
}

int isComand(char *textLine)
{
    int i = 0;
    int dollarSignalFound = 0;

    //printf("\nString: %s\n", textLine);

    while (*(textLine + i) != '\0')
    {
        if (*(textLine + i) == '$')
        {
            return i;
            break;
        }
        i++;
    }
    return -1;
}

void addNewLine(List *textEditor, char *textLine)
{
    if (stringSize(textLine) < TOTAL_CHARACTER_PER_LINE)
    {
        if (textEditor->firstRow == NULL && textEditor->lastRow == NULL)
        {
            textEditor->firstRow = (Row *)(malloc(sizeof(Row)));
            setUpRow(textEditor->firstRow);

            copyTextToNewLine(textEditor->firstRow, textLine);
            textEditor->firstRow->idLine = 1;
            textEditor->currentLine = 1;
            textEditor->quantRows = 1;

            //printf("\nText Line: %d\n", textEditor -> quantRows);

            textEditor->lastRow = textEditor->firstRow;
            textEditor->currentRow = textEditor->lastRow;
            textEditor->currentRow->flagCurrentLine = 1;
        }
        else if (textEditor->currentRow != NULL)
        {
            Row *newRow = (Row *)(malloc(sizeof(Row)));

            setUpRow(newRow);
            copyTextToNewLine(newRow, textLine);

            newRow->flagCurrentLine = 1;
            newRow->idLine = textEditor->currentRow->idLine + 1;
            newRow->previousRow = textEditor->currentRow;

            textEditor->currentRow->flagCurrentLine = 0;

            if (textEditor->currentRow->idLine == textEditor->lastRow->idLine)
            {
                textEditor->currentRow->nextRow = newRow;
                textEditor->lastRow = newRow;
                textEditor->currentRow = newRow;
            }
            else
            {
                newRow->nextRow = textEditor->currentRow->nextRow;

                textEditor->currentRow->nextRow = newRow;
                newRow->nextRow->previousRow = newRow->nextRow;

                textEditor->currentLine = newRow->idLine;
                textEditor->currentRow = newRow;
            }
            textEditor->quantRows += 1;

            updateRowsIDs(textEditor->currentRow);
        }
        else if (textEditor->currentRow == NULL)
        {
            Row *newRow = (Row *)(malloc(sizeof(Row)));

            setUpRow(newRow);
            copyTextToNewLine(newRow, textLine);

            newRow->nextRow = textEditor->firstRow;
            textEditor->firstRow->previousRow = newRow;
            newRow->flagCurrentLine = 1;
            newRow->idLine = 1;
            textEditor->currentLine = 1;
            textEditor->firstRow = newRow;
            textEditor->currentRow = textEditor->firstRow;

            textEditor->quantRows += 1;
            updateRowsIDs(textEditor->currentRow);
        }
    }
    else
    {
        printf("\nERROR: Linha com a quantidade máxima de caracteres atingida\n");
    }
}

void copyTextToNewLine(Row *newRow, char *textLine)
{
    int i = 0;

    while (*(textLine + i) != '\0')
    {
        newRow->character[i] = *(textLine + i);
        i++;
    }
    newRow->endCharCollumn = i;
    newRow->character[i] = '\0';
}

void setUpRow(Row *row)
{
    row->idLine = 0;
    row->startCharCollumn = 0;
    row->endCharCollumn = 0;
    row->flagCurrentLine = 0;
    row->previousRow = NULL;
    row->nextRow = NULL;
}

int getQuantCharacter(char *textLine)
{
    int i = 0;

    while (*(textLine + i) != '\0')
    {
        i++;
    }
    return i;
}

void updateRowsIDs(Row *row)
{
    Row *actualRow = row->nextRow;

    while (actualRow != NULL)
    {
        actualRow->idLine = actualRow->previousRow->idLine + 1;
        actualRow = actualRow->nextRow;
    }
}

int checkCommand(int startIndexOfCommand, char *textLine)
{
    char command[20];

    takeCommand(startIndexOfCommand, textLine, command);

    if (equalsToCommandReaded(command, "inserir\0") != 0)
    {
        return 1;
    }
    if (equalsToCommandReaded(command, "remover\0") != 0)
    {
        return 2;
    }
    if (equalsToCommandReaded(command, "linha\0") != 0)
    {
        return 3;
    }
    if (equalsToCommandReaded(command, "localizar\0") != 0)
    {
        return 4;
    }
    if (equalsToCommandReaded(command, "alterar\0") != 0)
    {
        return 5;
    }
    if (equalsToCommandReaded(command, "ultimo\0") != 0)
    {
        return 6;
    }
    if (equalsToCommandReaded(command, "imprimir\0") != 0)
    {
        return 7;
    }
    if (equalsToCommandReaded(command, "fim\0") != 0)
    {
        return 8;
    }
    return -1;
}

void takeCommand(int startIndexOfCommand, char *textLine, char *command)
{
    int i = startIndexOfCommand + 1;
    int j = 0;

    while (*(textLine + i) != '\0' && *(textLine + i) != ' ')
    {
        command[j] = *(textLine + i);
        i++;
        j++;
    }
    command[j] = '\0';
}

int equalsToCommandReaded(char *string1, char *string2)
{
    int i = 0;
    int string1Size = stringSize(string1);
    int string2Size = stringSize(string2);

    if (contains(string1, "\n\0") != -1)
    {
        string1Size--;
    }

    if (contains(string2, "\n\0") != -1)
    {
        string2Size--;
    }
    // printf("\n%d == %d, %s == %s\n", string1Size, string2Size, string1, string2);

    if (string1Size != string2Size)
    {
        return 0;
    }

    while (i < string1Size)
    {
        if (*(string1 + i) != *(string2 + i))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int stringSize(char *string)
{
    int i = 0;

    while (*(string + i) != '\0')
    {
        i++;
    }
    return i;
}

void changeCurrentLine(List *textEditor, char *command)
{
    char lineNumber[] = {'a', 'a', 'a', 'a', 'a'};
    int i = 0;
    int j = 0;

    if (stringSize(command) < 8)
    {
        printf("\nERRO: PARAMETROS INSUFICIENTES\n");
    }
    else
    {
        i = 7;

        while (j < 5 && *(command + i) != '\0')
        {
            if (*(command + i) != ' ')
            {
                lineNumber[j] = *(command + i);
                j++;
            }
            i++;
        }

        int lineRefered = atoi(lineNumber);

        if (lineRefered > textEditor->quantRows || lineNumber < 0)
        {
            printf("ERRO: LINHA NÃO EXISTE");
        }
        else
        {
            int currentLine = textEditor->currentRow->idLine;

            if (lineRefered != 0)
            {
                if (currentLine == lineRefered)
                {
                    printf("\nAVISO: A LINHA ACTUAL JÁ ESTA SELECIONADA\n");
                }
                else
                {
                    if (lineRefered > currentLine)
                    {
                        int quantSteps = lineRefered - currentLine;
                        Row *auxRow = textEditor->currentRow;

                        textEditor->currentRow->flagCurrentLine = 0;

                        while (quantSteps > 0)
                        {
                            auxRow = auxRow->nextRow;
                            quantSteps--;
                        }
                        textEditor->currentLine = lineRefered;
                        textEditor->currentRow = auxRow;
                        textEditor->currentRow->flagCurrentLine = 1;
                    }
                    else
                    {
                        int quantSteps = currentLine - lineRefered;
                        Row *auxRow = textEditor->currentRow;

                        textEditor->currentRow->flagCurrentLine = 0;

                        while (quantSteps > 0)
                        {
                            auxRow = auxRow->previousRow;
                            quantSteps--;
                        }
                        textEditor->currentLine = lineRefered;
                        textEditor->currentRow = auxRow;
                        textEditor->currentRow->flagCurrentLine = 1;
                    }
                }
            }
            else
            {
                textEditor->currentLine = 0;
                textEditor->currentRow->flagCurrentLine = 0;
                textEditor->currentRow = NULL;
            }
        }
    }
}

void getUltimoID(List *textEditor)
{
    if (textEditor->lastRow != NULL)
    {
        printf("\n%d\n", textEditor->lastRow->idLine);
    }
    else
    {
        printf("\nEditor de Texto Vazio\n");
    }
}

int contains(char *string, char *subString)
{
    if (stringSize(subString) > stringSize(string))
    {
        return -1;
    }

    int flagSubStringFounded = 1;
    int mainStringSize = stringSize(string);
    int subStringSize = stringSize(subString);
    int quantPossibleSubstringInString = mainStringSize / subStringSize;

    for (int i = 0; i < quantPossibleSubstringInString; i++)
    {
        flagSubStringFounded = 1;
        for (int j = 0; j < subStringSize; j++)
        {
            if (subString[j] != string[i + j])
            {
                flagSubStringFounded = 0;
                break;
            }
        }

        if (flagSubStringFounded == 1)
        {
            return i;
        }
    }
    return -1;
}

int containsWithStartIndex(char *string, char *subString, int index)
{
    if (stringSize(subString) > stringSize(string))
    {
        return -1;
    }

    int flagSubStringFounded = 1;
    int mainStringSize = stringSize(string);
    int subStringSize = stringSize(subString);

    // printf("\n%s -> %d == %s -> %d\n", string, mainStringSize, subString, subStringSize);

    if (contains(string, "\n\0") != -1)
    {
        mainStringSize--;
    }

    if (contains(subString, "\n\0") != -1)
    {
        subStringSize--;
    }

    // printf("\n%s -> %d == %s -> %d\n", string, mainStringSize, subString, subStringSize);

    for (int i = index; i + subStringSize <= mainStringSize; i++)
    {
        flagSubStringFounded = 1;

        for (int j = 0; j < subStringSize; j++)
        {
            if (subString[j] != string[i + j])
            {
                flagSubStringFounded = 0;
                break;
            }
        }

        if (flagSubStringFounded == 1)
        {
            return i;
        }
    }
    return -1;
}

void printRow(Row *row)
{
    if (row != NULL)
    {
        if (row->flagCurrentLine != 1)
        {
            printf("\n%d %s", row->idLine, row->character);
        }
        else
        {
            printf("\n→ %d %s", row->idLine, row->character);
        }
    }
}

void printLines(List *textEditor, char *command)
{
    if (stringSize(command) < 13)
    {
        if (containsWithStartIndex(command, ",", 0) == -1)
        {
            printf("\nERRO: Falta virgula\n");
        }
        else
        {
            printf("\nERRO: QUANTIDADE DE PARAMETROS INSUFICIENTES\n");
        }
    }
    else
    {
        int printStart = 0;
        int printEnd = 0;

        int returnResult = getTwoParametersOfCommand(command, &printStart, &printEnd);

        if (returnResult == 1)
        {
            if (printStart > textEditor->quantRows || printEnd > textEditor->quantRows)
            {
                printf("\nERRO: Linhas fora do número actual de linhas no editor de texto: %d\n", textEditor->quantRows);
            }
            else
            {
                if (printStart == textEditor->currentRow->idLine)
                {
                    Row *actualRow = textEditor->currentRow;

                    while (printStart <= printEnd)
                    {
                        printRow(actualRow);
                        actualRow = actualRow->nextRow;
                        printStart++;
                    }
                }
                else
                {
                    Row *actualRow = textEditor->firstRow;

                    while (actualRow != NULL && actualRow->idLine != printStart)
                    {
                        actualRow = actualRow->nextRow;
                    }

                    while (printStart <= printEnd)
                    {
                        printRow(actualRow);
                        actualRow = actualRow->nextRow;
                        printStart++;
                    }
                }
            }
        }
        else
        {
            switch (returnResult)
            {
            case -1:
                printf("\nERRO: não existe a virgula no comando\n");
                break;
            case -2:
                printf("\nERRO: não tem espaço no comando e deve existir\n");
                break;
            case -3:
                printf("\nERRO: Linha não válida, linha não maior que 0\n");
                break;
            case -4:
                printf("\nERRO: Referência da linha de ínicio maior que a final\n");
                break;
            case -5:
                printf("\nERRO: Primeiro parametro não passado\n");
                break;
            default:
                break;
            }
        }
    }
}

void removeRows(List *textEditor, char *command)
{
    if (stringSize(command) < 13)
    {
        printf("\nERRO: QUANTIDADE DE PARAMETROS INSUFICIENTES\n");
    }
    else
    {
        int printStart = 0;
        int printEnd = 0;

        int returnResult = getTwoParametersOfCommand(command, &printStart, &printEnd);

        if (returnResult == 1)
        {
            if (printStart > textEditor->quantRows || printEnd > textEditor->quantRows)
            {
                printf("\nERRO: Linhas fora do número actual de linhas no editor de texto: %d\n", textEditor->quantRows);
            }
            else
            {
                Row *actualRow = textEditor->firstRow;
                Row *trashRow = NULL;

                if (textEditor->currentRow != NULL)
                {
                    textEditor->currentRow->flagCurrentLine = 0;
                }

                while (actualRow != NULL && actualRow->idLine != printStart)
                {
                    actualRow = actualRow->nextRow;
                }

                while (printStart <= printEnd)
                {
                    if (actualRow->idLine == textEditor->firstRow->idLine)
                    {
                        textEditor->firstRow = textEditor->firstRow->nextRow;
                        if (textEditor->firstRow != NULL)
                        {
                            textEditor->firstRow->previousRow = NULL;
                            textEditor->firstRow->idLine = 1;
                            updateRowsIDs(textEditor->firstRow);
                        }
                        else
                        {
                            textEditor->lastRow = NULL;
                            textEditor->currentRow = NULL;
                        }
                    }
                    else
                    {
                        if (actualRow->nextRow == NULL)
                        {
                            textEditor->lastRow = actualRow->previousRow;
                            textEditor->lastRow->nextRow = NULL;
                        }
                        else
                        {
                            actualRow->flagCurrentLine = 0;
                            actualRow->nextRow->previousRow = actualRow->previousRow;
                            actualRow->previousRow->nextRow = actualRow->nextRow;

                            updateRowsIDs(actualRow->previousRow);
                        }
                    }

                    trashRow = actualRow;
                    actualRow = actualRow->nextRow;

                    textEditor->quantRows -= 1;
                    free(trashRow);
                    printStart++;
                }

                if (actualRow != NULL)
                {
                    if (actualRow->previousRow != NULL)
                    {
                        textEditor->currentRow = actualRow->previousRow;
                        textEditor->currentRow->flagCurrentLine = 1;
                    }
                    else if (actualRow->idLine == textEditor->firstRow->idLine)
                    {
                        textEditor->currentRow = actualRow;
                        textEditor->currentRow->flagCurrentLine = 1;
                        textEditor->lastRow = actualRow;
                    }
                }
            }
        }
        else
        {
            switch (returnResult)
            {
            case -1:
                printf("\nERRO: não existe a virgula no comando\n");
                break;
            case -2:
                printf("\nERRO: não tem espaço no comando e deve existir\n");
                break;
            case -3:
                printf("\nERRO: Linha não válida, linha não maior que 0\n");
                break;
            case -4:
                printf("\nERRO: Referência da linha de ínicio maior que a final\n");
                break;
            case -5:
                printf("\nERRO: Primeiro parametro não passado\n");
                break;
            default:
                break;
            }
        }
    }
}

int getTwoParametersOfCommand(char *command, int *firstArgument, int *secondArgument)
{
    char startLine[] = {'a', 'a', 'a', 'a', 'a'};
    char endLine[] = {'a', 'a', 'a', 'a', 'a'};

    int commaIndex = contains(command, ",");

    if (commaIndex != -1)
    {
        int k = 0;
        int i = 0;

        for (i = commaIndex + 1; command[i] != '\0'; i++)
        {
            if (command[i] != ' ')
            {
                endLine[k] = command[i];
                k++;
            }
        }

        int spaceIndex = contains(command, " ");

        if (spaceIndex != -1)
        {
            for (i = spaceIndex + 1, k = 0; command[i] != '\0'; i++)
            {
                if (command[i] != ' ')
                {
                    startLine[k] = command[i];
                    k++;
                }
            }

            if (k == 0)
            {
                return -5; // Not first parameter passed
            }
            else
            {
                *firstArgument = atoi(startLine);
                *secondArgument = atoi(endLine);

                if (*firstArgument > 0 && *secondArgument > 0)
                {
                    if (*firstArgument > *secondArgument)
                    {
                        return -4; // Start greater than End
                    }
                }
                else
                {
                    return -3; // Not valid lines, not greater than 0
                }
            }
        }
        else
        {
            return -2; // there's no space on command and it must contain
        }
    }
    else
    {
        return -1; // there's no comma separator to command
    }
    return 1;
}

void searchPattern(List *textEditor, char *command)
{
    if (stringSize(command) < 13)
    {
        printf("\nERRO: QUANTIDADE DE PARAMETROS INVÁLIDOS\n");
    }
    else
    {
        int indexOfPercentage = containsWithStartIndex(command, "%\0", 0);

        if (indexOfPercentage != -1)
        {
            char searchElement[20];
            int k = 0;
            int i;
            int commandSize = stringSize(command);

            if (contains(command, "\n\0") != -1)
            {
                commandSize--;
            }

            for (i = indexOfPercentage + 1; command[i] != '\0' && command[i] != '\0' && i < commandSize; i++)
            {
                searchElement[k] = command[i];
                k++;
            }
            searchElement[k] = '\0';

            Row *actualRow = textEditor->firstRow;
            i = 0;
            int j = 0;
            int searchElementSize = stringSize(searchElement);
            printf("\n");
            k = 0;

            while (k < textEditor->quantRows)
            {
                if (actualRow->flagCurrentLine == 1)
                {
                    printf("\n→ ");
                }
                printf("%d ", actualRow->idLine);

                i = containsWithStartIndex(actualRow->character, searchElement, 0);

                if (i == -1)
                {
                    for (; actualRow -> character[j] != '\0' && actualRow -> character[j] != '\n'; j++) {
                        printf("%c", actualRow -> character[j]);
                    }
                }
                else
                {
                    while (i != -1)
                    {
                        int startIndex = i;
                        int endIndex = i + searchElementSize;

                        for (; j < startIndex; j++)
                        {
                            printf("%c", actualRow->character[j]);
                        }

                        for (j = startIndex; j < endIndex; j++)
                        {
                            printf("\033[32;1m%c\033[0m", actualRow->character[j]);
                        }
                        j = endIndex;
                        i = endIndex;

                        i = containsWithStartIndex(actualRow->character, searchElement, i);

                        if (i == -1) {
                            for (; actualRow -> character[j] != '\0' && actualRow -> character[j] != '\n'; j++) {
                                printf("%c", actualRow -> character[j]);
                            }
                        }
                    }
                }

                actualRow = actualRow->nextRow;
                i = 0;
                j = 0;
                k++;
                printf("\n");
            }
        }
    }
}

void changeOcorrences(Row *actualRow, char *command)
{
    if (stringSize(command) < 13)
    {
        printf("\nERRO: FALTA PARAMETROS PARA O COMANDO\n");
    }
    else
    {
        if (actualRow != 0)
        {
            char delimiter[2] = {command[stringSize(command) - 2], '\0'};

            if (delimiter[0] != '#' && delimiter[0] != '$' && delimiter[0] != '%')
            {
                printf("\nERRO: DELIMITADORES INCONSCISTENTE\n");
                return;
            }
            int i;
            int k = 0;
            char oldText[80];
            char newText[80];

            int firstDelimiterOcorrenceIndex = containsWithStartIndex(command, delimiter, 0);
            int secondDelimiterOcorrenceIndex = containsWithStartIndex(command, delimiter, firstDelimiterOcorrenceIndex + 1);
            int lastDelimiterOcorrenceIndex = stringSize(command) - 2;

            //printf("first: %d - Second: %d - Last: %d\n", firstDelimiterOcorrenceIndex, secondDelimiterOcorrenceIndex, lastDelimiterOcorrenceIndex);

            if (firstDelimiterOcorrenceIndex != -1 && secondDelimiterOcorrenceIndex != -1 && lastDelimiterOcorrenceIndex != -1)
            {
                for (k = 0, i = firstDelimiterOcorrenceIndex + 1; i < secondDelimiterOcorrenceIndex; i++)
                {
                    oldText[k] = command[i];
                    k++;
                }
                oldText[k] = '\0';
                int oldTextSize = stringSize(oldText);
                //printf("\nOld Text: %s Size: %d", oldText, oldTextSize);

                for (k = 0, i = secondDelimiterOcorrenceIndex + 1; i < lastDelimiterOcorrenceIndex; i++)
                {
                    newText[k] = command[i];
                    k++;
                }
                newText[k] = '\0';

                int newTextSize = stringSize(newText);
                //printf("\nNew Text: %s Size: %d", newText, newTextSize);

                k = 0;
                i = 0;
                int h = 0;
                int indexToReplace = 0;
                int mainStringSize = stringSize(actualRow->character);
                int auxStringSize = 0;
                indexToReplace = containsWithStartIndex(actualRow->character, oldText, indexToReplace);

                while (indexToReplace != -1)
                {
                    char text[TOTAL_CHARACTER_PER_LINE];

                    for (; k < indexToReplace; k++)
                    {
                        text[k] = actualRow->character[i];
                        i++;
                    }
                    text[k] = '\0';

                    for (h = 0; h < newTextSize; h++)
                    {
                        text[k] = newText[h];
                        k++;
                    }

                    i = indexToReplace + oldTextSize;

                    for (; i < mainStringSize; i++)
                    {
                        text[k] = actualRow->character[i];
                        k++;
                    }

                    text[k] = '\0';

                    auxStringSize = stringSize(text);
                    for (k = 0; k < auxStringSize; k++)
                    {
                        actualRow->character[k] = text[k];
                    }
                    actualRow->character[k] = '\0';

                    //printf("\nText: %s Size: %d", text, stringSize(text));
                    //printf("\nOld Text: %s Size: %d", actualRow -> character, stringSize(actualRow -> character));
                    h = 0;
                    i = 0;
                    k = 0;
                    mainStringSize = stringSize(actualRow->character);
                    indexToReplace = containsWithStartIndex(actualRow->character, oldText, indexToReplace + newTextSize);
                }
            }
            else
            {
                printf("\nERRO: PARAMETROS ENVIADOS INSUFICIENTES\n");
            }
        }
        else
        {
            printf("\nERROR: NÃO EXISTE LINHA CORRENTE VÁLIDA\n");
        }
    }
}

//ola ;)