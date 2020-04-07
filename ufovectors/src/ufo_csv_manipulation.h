#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    char row_delimiter;
    char column_delimiter;
    char escape;
    char quote;
    bool use_double_quote_escape;
    bool use_escape_character;
    //bool strip_whitespace;
} tokenizer_t;

typedef enum {
    TOKENIZER_INITIAL,
    TOKENIZER_FIELD,
    TOKENIZER_UNQUOTED_FIELD,
    TOKENIZER_QUOTED_FIELD,
    TOKENIZER_QUOTE,
    TOKENIZER_TRAILING,
    TOKENIZER_ESCAPE,
    TOKENIZER_FINAL,
}  tokenizer_state_value_t;

typedef enum {
    TOKENIZER_OK,
    TOKENIZER_NEW_COLUMN,
    TOKENIZER_END_OF_FILE,
    TOKENIZER_PARSE_ERROR,
    TOKENIZER_ERROR,
} tokenizer_result_t;

typedef struct {
    char  *string;
    size_t size;
    long   position_start;
    long   position_end;
} tokenizer_token_t;

typedef struct {
    char  *buffer;
    size_t max_size;
    size_t size;
} tokenizer_token_buffer_t;

typedef struct {
    FILE                     *file;
    tokenizer_state_value_t   state;
    long                      initial_offset; // long because fseek offset uses long
    long                      read_characters;
    long                      current_offset;
    long                      end_of_last_token;
    char                     *read_buffer;
    tokenizer_token_buffer_t *token_buffer;
} tokenizer_state_t;

tokenizer_t               csv_tokenizer ();

tokenizer_state_t        *tokenizer_state_init (char *path, long initial_offset, size_t buffer_size);
void                      tokenizer_state_close (tokenizer_state_t *);

tokenizer_token_buffer_t *tokenizer_token_buffer_init (size_t max_size);
tokenizer_token_t        *tokenizer_token_buffer_get_token (tokenizer_token_buffer_t *buffer);
int                       tokenizer_token_buffer_append (tokenizer_token_buffer_t *buffer, char c);
void                      tokenizer_token_buffer_clear (tokenizer_token_buffer_t *buffer);
void                      tokenizer_token_buffer_free (tokenizer_token_buffer_t *buffer);

tokenizer_token_t        *tokenizer_token_empty ();

const char               *tokenizer_result_to_string (tokenizer_result_t);


tokenizer_result_t next (tokenizer_t *tokenizer, tokenizer_state_t *state, tokenizer_token_t **token, bool *end_row);