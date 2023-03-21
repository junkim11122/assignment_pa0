#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include "dir_file.h"
#include "utils.h"

int open_file(char* fname, FILE** input) {
    if (access(fname, F_OK) == -1) {
        ERR_PRINT("The '%s' file does not exists\n", fname);
        return -1;
    }

    *input = fopen(fname, "r");
    if (input == NULL) {
        ERR_PRINT("Failed open '%s' file\n", fname);
        return -1;
    }

    return 1;
}

// This function splits the input string (const char* str) to tokens
// and put the tokens in token_list. The return value must be the number
// of tokens in the given input string.

int parse_str_to_list(const char* str, char** token_list) {
    // 복사
    char* temp_str = strdup(str);

    // 딜리미터 설정
    const char* delimiter = "/\n";
    int token_count = 0;
    char* token = strtok(temp_str, delimiter);

    // 읽으며 저장
    while (token != NULL) {
        token_list[token_count] = strdup(token);
        token_count++;
        token = strtok(NULL, delimiter);
    }

    // 메모리 관리
    free(temp_str);
    return token_count;
}

void free_token_list(char** token_list, int num_tokens) {
    for (int i = 0; i < num_tokens; i++) {
        free(token_list[i]);
    }

    free(token_list);
}

