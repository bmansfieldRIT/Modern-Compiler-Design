/*
*   lex.c
*   Transcribed from Modern Compiler Design (Grune, 2000)
*       By Brian Mansfield
*/

#include "input.h"      /* for get_input() */
#include "lex.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char *input;
static int dot;         /* dot position in input */
static int input_char;  /* charater at dot position */

#define next_char()             (input_char = input[++dot])

#define is_end_of_input(ch)     ((ch) == '\0')
#define is_layout(ch)           (!is_end_of_input(ch) && (ch) <= ' ')
#define is_comment_starter(ch)  ((ch) == '#')
#define is_comment_stopper(ch)  ((ch) == '#' || (ch) == '\n')

#define is_uc_letter(ch)        ('A' <= (ch) && (ch) <= 'Z')
#define is_lc_letter(ch)        ('a' <= (ch) && (ch) <= 'z')
#define is_letter(ch)           (is_uc_letter(ch) || is_lc_letter(ch))
#define is_digit(ch)            ('0' <= (ch) && (ch) <= '9')
#define is_letter_or_digit(ch)  (is_letter(ch) || is_digit(ch))
#define is_underscore(ch)       ((ch) == '_')
#define is_operator(ch)         (strchr("+-*/", (ch)) != 0)
#define is_separator(ch)        (strchr(";,(){}", (ch)) != 0)

Token_Type Token;

void start_lex(void) {
    input = get_input();
    dot = 0;
    input_char = input[dot];
}

void skip_layout_and_comment(void) {
    while (is_layout(input_char)) {
        next_char();
    }
    if (is_comment_starter(input_char)){
        next_char();
        while (!is_comment_stopper(input_char)){
            if (is_end_of_input(input_char)){
                return;
            }
            next_char();
            while(is_layout(input_char)) {
                next_char();
            }
        }
    }
}

void recognize_identifier(void){
    Token.class = IDENTIFIER;
    next_char();
    while (is_letter_or_digit(input_char)){
        next_char();
    }
    while (is_underscore(input_char) && is_letter_or_digit(input_char)){
        next_char();
        while (is_letter_or_digit(input_char)){
            next_char();
        }
    }
}

void recognize_integer(void){
    Token.class = INTEGER;
    next_char();
    while(is_digit(input_char)){
        next_char();
    }
}

char* input_to_zstring(int start, int end){
    int i = 0;
    char *buffer = malloc(end-start + 1);
    while (start != end){
        buffer[i++] = input[start++];
    }
    buffer[i] = '\0';
    return buffer;
}

void get_next_token(void) {
    int start_dot;
    skip_layout_and_comment();
    //note_token_position();
    start_dot = dot;
    if (is_end_of_input(input_char)){
        Token.class = EOF;
        Token.repr = "<EOF>";
        return;
    }
    if (is_letter(input_char)){
        recognize_identifier();
    } else if (is_digit(input_char)) {
        recognize_integer();
    } else if (is_operator(input_char) || is_separator(input_char)){
        Token.class = input_char;
        next_char();
    } else {
        Token.class = input_char;
        next_char();
    }

    Token.repr = input_to_zstring(start_dot, dot);
}
