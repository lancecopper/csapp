#include <stdio.h>
#include <stdlib.h>

struct coder{
    int rank;
    int age;
    char* lang;
};

int main(int argc, char **argv)
{   
    struct coder *coder1, *coder2;
    
    coder1 = malloc(sizeof(struct coder));
    coder2 = malloc(sizeof(struct coder));

    coder1->rank = 1;
    coder1->age = 1;
    coder1->lang = "python";

    *coder2 = *coder1;

    printf("sizeof int%ld\n", sizeof(int));
    printf("sizeof coder1 %ld\n", sizeof(coder1));
    printf("coder1 rank: %d, age: %d, lang: %s\n", coder1->rank, coder1->age, coder1->lang);
    printf("sizeof coder2 %ld\n", sizeof(coder2));
    printf("coder2 rank: %d, age: %d, lang: %s\n", coder2->rank, coder2->age, coder2->lang);


    printf("after reassignment ...\n");
    coder1->rank = 2;
    coder1->age = 28;
    coder1->lang = "cpp";


    printf("coder1 rank: %d, age: %d, lang: %s\n", coder1->rank, coder1->age, coder1->lang);
    printf("coder2 rank: %d, age: %d, lang: %s\n", coder2->rank, coder2->age, coder2->lang);


    coder2 = coder1;

    printf("coder1 rank: %d, age: %d, lang: %s\n", coder1->rank, coder1->age, coder1->lang);
    printf("coder2 rank: %d, age: %d, lang: %s\n", coder2->rank, coder2->age, coder2->lang);


    return 1;
}












