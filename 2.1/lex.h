/*
*   lex.h
*   Transcribed from Modern Compiler Design (Grune, 2000)
*       By Brian Mansfield
*/
#define EOF         256
#define IDENTIFIER  257
#define INTEGER     258
#define ERRONEOUS   259

typedef struct {
    char *file_name;
    int line_number;
    int char_number;
} Position_in_file;

typedef struct {
    int class;
    char *repr;
    Position_in_file pos;
} Token_Type;

extern Token_Type Token;

extern void start_lex(void);
extern void get_next_token(void);
