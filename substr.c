#include <stdio.h>
#include <stdlib.h>

static inline char * sub_str(char * src, int s_idx, int e_idx){
    int len = e_idx-s_idx;
    char * dest = malloc(len+1);
    dest = src + s_idx;
    dest[len] = '\0';
    return dest;
}

static inline char * asm_sub_str(char * src, int s_idx, int e_idx){
    int len = e_idx - s_idx;
    char * dest = malloc(len+1);
    int d0,d1,d2;
    asm(
        "1:\tlodsb\n\t"
        "stosb\n\t"
        "testb %%al,%%al\n\t"
        "jne 1b"
        : "=&S" (d0), "=&D" (d1), "=&a" (d2)
        : "0" (src+s_idx), "1" (dest)
        : "memory"
    );
    return dest;
}

int main(int arcg, char ** argv){
    char * s = argv[1];
    int s_idx = atoi(argv[2]);
    int e_idx = atoi(argv[3]);
    if(e_idx >= sizeof(s)){
        printf("Index %d is not in the string", e_idx);
        return 0;
    }

    char * d1 = sub_str(s, s_idx, e_idx);
    char * d2 = asm_sub_str(s, s_idx, e_idx);

    printf("Substring without inlining: %s\n", d1);
    printf("Substring with inlining: %s\n", d2);
    return 0;
}
