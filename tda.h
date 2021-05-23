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
