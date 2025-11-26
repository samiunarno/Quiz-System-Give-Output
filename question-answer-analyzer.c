#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define Max_try 4
#define numb_of_word 7
#define numb_of_ques 5
#define numb_face 4

typedef struct {
    double word[numb_of_word];
    char name[20];
} Animal;

typedef struct {
    char usename[20];
    char password[10];
    double word[numb_of_word];
    int attempts;
} User;

Animal animals[numb_face] = {
    {{1.0/15 , 1.0/15 , 5.0/15 , 0.0/15 , 3.0/15 , 4.0/15 , 1.0/15}, "DOG"},
    {{1.0/10 , 1.0/10 , 4.0/10 , 1.0/10 , 2.0/10 , 3.0/10 , 2.0/10}, "CAT"},
    {{0.1, 0.2, 0.3, 0.1, 0.2, 0.4, 0.1}, "RABBIT"},
    {{0.3, 0.3, 0.1, 0.2, 0.2, 0.2, 0.1}, "LION"}
};

User predefined_users[2] = {
    {"12345678", "5678", {0,0,0,0,0,0,0}, 0},
    {"87654321", "4321", {0,0,0,0,0,0,0}, 0}
};

double calculate(double a[], double b[]) {
    double sum = 0;
    for (int i = 0; i < numb_of_word; i++) sum += pow(a[i] - b[i], 2);
    return sum;
}

int login(User *user) {
    char input_pass[10];
    int wrong = 0;
    while (wrong < Max_try) {
        printf("Enter Username: ");
        scanf("%s", user->usename);
        printf("Enter Password: ");
        scanf("%s", input_pass);
        for (int i = 0; i < 2; i++) {
            if (strcmp(user->usename, predefined_users[i].usename)==0 &&
                strncmp(input_pass, predefined_users[i].usename+4,4)==0) {
                *user = predefined_users[i];
                printf("Login Successful\n");
                return 1;
            }
        }
        wrong++;
        if (wrong == Max_try) {
            printf("Account Locked. Login admin to unlock.\n");
            while (1) {
                char a[20], p[20];
                printf("Admin Username: ");
                scanf("%s", a);
                printf("Admin Password: ");
                scanf("%s", p);
                if (strcmp(a,"admin")==0 && strcmp(p,"6666")==0) {
                    printf("Account Unlocked.\n");
                    return login(user);
                } else printf("Wrong Admin Login.\n");
            }
        }
        printf("Wrong Password. Try Again.\n");
    }
    return 0;
}

void shuffle(char* q[], char* op[][4], int score[numb_of_ques][4][numb_of_word]) {
    srand(time(0));
    for (int i = 0; i < numb_of_ques; i++) {
        int j = rand() % numb_of_ques;
        char* tq = q[i]; q[i] = q[j]; q[j] = tq;
        for (int k = 0; k < 4; k++) {
            char* to = op[i][k]; op[i][k] = op[j][k]; op[j][k] = to;
            int ts[numb_of_word];
            for (int m = 0; m < numb_of_word; m++) {
                ts[m] = score[i][k][m];
                score[i][k][m] = score[j][k][m];
                score[j][k][m] = ts[m];
            }
        }
    }
}

void take_quiz(User *user) {
    char *q[numb_of_ques] = {
        "1. You find a puzzle, you choose to:",
        "2. When facing a challenge, you prefer to:",
        "3. In a group, you're the one who:",
        "4. On a rainy day, you would:",
        "5. You are known for being:"
    };
    char *o[numb_of_ques][4] = {
        {"A. Solve alone","B. Seek help","C. Observe","D. Let others do"},
        {"A. Lead","B. Plan","C. Risk","D. Wait"},
        {"A. Charge","B. Organize","C. Support","D. Alone"},
        {"A. Read","B. Walk","C. Social","D. Build"},
        {"A. Outgoing","B. Reflective","C. Independent","D. Kind"}
    };
    int score[numb_of_ques][4][numb_of_word] = {
        {{2,1,0,0,0,0,1},{1,2,0,0,0,0,2},{0,0,2,0,0,0,1},{0,0,0,2,0,0,0}},
        {{2,0,0,0,0,1,1},{1,1,0,0,0,1,2},{0,0,2,0,2,0,0},{0,0,0,2,0,0,0}},
        {{2,1,0,0,0,1,1},{1,2,0,0,1,0,2},{0,0,2,0,0,0,0},{0,0,0,1,1,2,1}},
        {{0,0,1,0,0,2,2},{0,1,0,2,0,1,2},{1,0,0,1,1,0,0},{2,0,0,0,1,0,1}},
        {{1,0,0,0,2,0,1},{1,2,0,0,0,0,0},{0,1,2,0,0,0,1},{0,0,1,2,0,1,2}}
    };

    shuffle(q, o, score);

    int skipped[60] = {0};
    int skip_count = 0;

    for (int i = 0; i < numb_of_ques; i++) {
        printf("%s\n", q[i]);
        for (int j = 0; j < 4; j++) printf("%s\n", o[i][j]);
        printf("Enter A/B/C/D or S to skip: ");
        char c;
        scanf(" %c", &c);
        if (c=='S'||c=='s') {
            skipped[skip_count++] = i+1;
            continue;
        }
        int idx = c - 'A';
        for (int j = 0; j < numb_of_word; j++) user->word[j] += score[i][idx][j];
    }

    double total = 0;
    for (int i = 0; i < numb_of_word; i++) total += user->word[i];

    printf("\nScores:\n");
    printf("DOM %.2f\nSTR %.2f\nCOM %.2f\nSOL %.2f\nAGI %.2f\nSEC %.2f\nAES %.2f\n",
        user->word[0],user->word[1],user->word[2],user->word[3],
        user->word[4],user->word[5],user->word[6]);

    printf("\nRatios:\n");
    for (int i = 0; i < numb_of_word; i++) printf("%.2f ", user->word[i]/total);

    printf("\n\nSkipped Questions (%d): ", skip_count);
    for (int i = 0; i < skip_count; i++) printf("%d ", skipped[i]);
    printf("\n");
}

void find_face(User *user) {
    double total = 0;
    double ratio[numb_of_word];
    for (int i = 0; i < numb_of_word; i++) total += user->word[i];
    for (int i = 0; i < numb_of_word; i++) ratio[i] = user->word[i] / total;
    double min = INFINITY;
    int id = -1;
    for (int i = 0; i < numb_face; i++) {
        double s = calculate(ratio, animals[i].word);
        if (s < min) { min = s; id = i; }
    }
    printf("\nClosest Animal: %s\n", animals[id].name);
}

int again() {
    char c;
    printf("\nTry Again? Y/N: ");
    scanf(" %c", &c);
    return (c=='Y'||c=='y');
}

int main() {
    User user = {0};
    if (login(&user)) {
        do {
            for (int i = 0; i < numb_of_word; i++) user.word[i]=0;
            take_quiz(&user);
            find_face(&user);
        } while (again());
    }
    return 0;
}
