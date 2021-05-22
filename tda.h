#define TOTAL_CHARACTER_PER_LINE 80

typedef struct node {
    int idLine;
    int startCharCollumn;
    int endCharCollumn;
    char character[TOTAL_CHARACTER_PER_LINE];
    int currentLine;
    struct node *previousLine;
    struct node *nextLine;
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
