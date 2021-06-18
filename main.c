#include <stdio.h>
#include <stdlib.h>
#include "tda.h"
#define STYLE_BOLD "\033[1m"
#define STYLE_NO_BOLD "\033[22m"
#define STYLE_UNDERLINE "\033[4m"
#define STYLE_NO_UNDERLINE "\033[24m"



int main()
{
    List *textEditor = (List *)(malloc(sizeof(List)));
    int flagRunning = 1;
    int flagInsertMode = 0;

    while (flagRunning == 1)
    {
        char commandLineInput[TOTAL_CHARACTER_PER_LINE];
        fgets(commandLineInput, sizeof(commandLineInput), stdin);

        int isCommand = isComand(commandLineInput);

        //printf("\nCommand: %d", isCommand);

        if (isCommand == -1 && flagInsertMode == 1)
        {
            //printf("\nQuant Rows: %d\n", textEditor -> quantRows);
            addNewLine(textEditor, commandLineInput);
        }
        else if (isCommand != -1)
        {
            int startCommandIndex = isCommand;
            int commandCode = checkCommand(startCommandIndex, commandLineInput);

            switch (commandCode)
            {
            case 1: // Inserir
                flagInsertMode = 1;
                break;
            case 2: // remover m, n (More tests)
                removeRows(textEditor, commandLineInput);
                flagInsertMode = 0;
                break;
            case 3: // linha m (to test)
                changeCurrentLine(textEditor, commandLineInput);
                flagInsertMode = 0;
                break;
            case 4: // localizar %x
                printf("\n---------------------------------------------------------------");
                searchPattern(textEditor, commandLineInput);
                flagInsertMode = 0;
                printf("\n---------------------------------------------------------------\n");
                break;
            case 5: // alterar %x %y %
                changeOcorrences(textEditor->currentRow, commandLineInput);
                flagInsertMode = 0;
                break;
            case 6: // ultimo (to test)
                getUltimoID(textEditor);
                flagInsertMode = 0;
                break;
            case 7: // imprimir m, n
                printf("\n---------------------------------------------------------------");
                printLines(textEditor, commandLineInput);
                flagInsertMode = 0;
                printf("\n---------------------------------------------------------------\n");
                break;
            case 8: // fim
                flagRunning = 0;
                flagInsertMode = 0;
                break;
            case -1:
                printf("\nERRO: COMANDO NÃO VÁLIDO\n");
                break;
            default:
                // TO-DO
                flagInsertMode = 0;
                break;
            }
        }
        else
        {
            printf("\nERRO: Comandos devem começar com $\n");
        }
    }
}