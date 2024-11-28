#include <stdio.h>
#include <stdalign.h>

struct person
{
    char name;
    char surname;
    int age;
    int GPA;
};

#pragma pack(push,1)
struct compressed_person
{
    char name;
    char surname;
    int age;
    int GPA;
};
#pragma(pop)

int main ()
{
    printf("size p = %ld\nsize com_p = %ld\n", sizeof(person),sizeof(compressed_person));
    printf("align p = %ld\nalign com_p = %ld\n", alignof(person),alignof(compressed_person));
    return 0;
}