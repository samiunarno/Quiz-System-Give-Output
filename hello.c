#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Max_try 4
#define numb_of_word 7
#define numb_of_ques 5
#define numb_face 4

typedef struct {
    double word[numb_of_word];
    char name[20];
} Animal;

typedef struct {
    char usename [10];
    char password [10];
    double word[numb_of_word];
    int attempts;
} User;

Animal animals[numb_face] = {
    {{1.0/15 , 1.0/15 , 5.0/15 , 0.0/15 , 3.0/15 , 4.0/15 , 1.0/15}, "DOG"},
    {{1.0/10 , 1.0/10 , 4.0/10 , 1.0/10 , 2.0/10 , 3.0/10 , 2.0/10}, "CAT"},
    {{0.1,0.2,0.3,0.1,0.2,0.4,0.1}, "RABBIT"},
    {{0.3,0.3,0.1,0.2,0.2,0.2,0.1}, "LION"}
};

double calculate(double user[] , double animal[]){
    double sum = 0;
    for(int i = 0; i<numb_of_word; i++){
        sum += pow(user[i] - animal[i], 2);
    }
    return sum;
}