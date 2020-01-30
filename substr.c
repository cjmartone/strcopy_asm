#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline char * sub_str(char * dest, char * src, int s_idx, int edix){
    int len = edix-s_idx;
    for(int i = 0; i < len; i++){
        dest[i] = src[s_idx+i];
    }
    return dest;
}

static inline char * asm_sub_str(char * dest, char * src, int s_idx, int edix){
    asm(
        "movl %1, %%eax;"
        "movl %%eax, %0;"
        :"=r"(dest)
        :"r"(src + s_idx)
        :"%eax"
    );
    return dest;
}

int main(int arcg, char ** argv){
    char * s = argv[1];
    int s_idx = atoi(argv[2]);
    int e_idx = atoi(argv[3]);
    int length = e_idx - s_idx;
    char * d = malloc(length);

    printf("String: %s\nStart: %d\nEnd: %d\n", s, s_idx, e_idx);

    char * d1 = malloc(length);
    char * d2 = malloc(length);
    strcpy(d1, sub_str(d, s, s_idx, e_idx));
    d[0] = '\0';
    strcpy(d2, asm_sub_str(d, s, s_idx, e_idx));

    printf("Substring without inlining: %s\n", d1);
    printf("Substring with inlining: %s\n", d2);
    return 0;
}
