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
    char usename[10];
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
    {"admin1234", "1234", {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}, 0},
    {"demo1234", "1234", {7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 0}
};

double calculate(double user[], double animal[]) {
    double sum = 0;
    for (int i = 0; i < numb_of_word; i++) {
        sum += pow(user[i] - animal[i], 2);
    }
    return sum;
}

int login(User *user) {
    char input_pass[10];
    int success = 0;

    while (success < Max_try) {
        printf("Enter Your Username: ");
        scanf("%s", user->usename);
        printf("Enter Your Password: ");
        scanf("%s", input_pass);

        for (int i = 0; i < 2; i++) {
            if (strcmp(user->usename, predefined_users[i].usename) == 0 && 
                strncmp(input_pass, user->usename + 4, 4) == 0) {
                *user = predefined_users[i];
                printf("Login Successful! Welcome to Your Pey Analyzer App, %s\n", user->usename);
                return 1;
            }
        }

        printf("Login Failed! Try Again.\n");
        success++;
        
        if (success == Max_try) {
            printf("Maximum Login Attempts Reached. Account Locked! Contact Admin.\n");
            return 0;
        }
    }
    return 0;
}

void shuffle_questions(char* questions[], char* options[][4], int score[numb_of_ques][4][numb_of_word]) {
    srand(time(0)); 
    for (int i = 0; i < numb_of_ques; i++) {
        int j = rand() % numb_of_ques;
        if (i != j) {
            char *temp_q = questions[i];
            questions[i] = questions[j];
            questions[j] = temp_q;
            
            for (int k = 0; k < 4; k++) {
                char *temp_o = options[i][k];
                options[i][k] = options[j][k];
                options[j][k] = temp_o;
                
                int temp_s[numb_of_word];
                for (int m = 0; m < numb_of_word; m++) {
                    temp_s[m] = score[i][k][m];
                    score[i][k][m] = score[j][k][m];
                    score[j][k][m] = temp_s[m];
                }
            }
        }
    }
}

void take_quiz(User *user) {
    char *questions[numb_of_ques] = {
        "1. You find a puzzle, you choose to: ",
        "2. When facing a challenge, you prefer to: ",
        "3. In a social group, you're often the one who: ",
        "4. On a rainy day, you would likely: ",
        "5. You are known for being: "
    };

    char *options[numb_of_ques][4] = {
        {"A. Solve it alone", "B. Seek help from others", "C. Observe first", "D. Let others solve it"},
        {"A. Lead the way", "B. Plan carefully", "C. Take risks", "D. Wait for a solution"},
        {"A. Take charge", "B. Organize people", "C. Listen and support", "D. Enjoy your own space"},
        {"A. Read a book", "B. Go for a walk", "C. Socialize", "D. Build something"},
        {"A. Outgoing", "B. Reflective", "C. Independent", "D. Compassionate"}
    };

    int score[numb_of_ques][4][numb_of_word] = {
        {{2, 0, 0, 0, 0, 0, 1}, {1, 2, 0, 0, 0, 0, 2}, {0, 0, 2, 0, 0, 0, 1}, {0, 0, 0, 2, 0, 0, 0}},
        {{2, 0, 0, 0, 0, 0, 1}, {1, 1, 0, 0, 0, 1, 2}, {0, 0, 2, 0, 2, 0, 0}, {0, 0, 0, 2, 0, 0, 0}},
        {{2, 1, 0, 0, 0, 1, 1}, {1, 2, 0, 0, 1, 0, 2}, {0, 0, 2, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 2, 1}},
        {{0, 0, 1, 0, 0, 2, 2}, {0, 1, 0, 2, 0, 1, 2}, {1, 0, 0, 1, 1, 0, 0}, {2, 0, 0, 0, 1, 0, 1}},
        {{1, 0, 0, 0, 2, 0, 1}, {1, 2, 0, 0, 0, 0, 0}, {0, 1, 2, 0, 0, 0, 1}, {0, 0, 1, 2, 0, 1, 2}}
    };

    shuffle_questions(questions, options, score);

    for (int i = 0; i < numb_of_ques; i++) {
        printf("%s\n", questions[i]);
        for (int j = 0; j < 4; j++) {
            printf("%s\n", options[i][j]);
        }
        char answer;
        printf("Enter Your Choice: (A/B/C/D): ");
        scanf(" %c", &answer);

        int index = answer - 'A';
        for (int j = 0; j < numb_of_word; j++) {
            user->word[j] += score[i][index][j];
        }
    }
}

void find_face(User *user) {
    double min_SSD = INFINITY;
    int closest_face = -1;

    for (int i = 0; i < numb_face; i++) {
        double SSD = calculate(user->word, animals[i].word);
        if (SSD < min_SSD) {
            min_SSD = SSD;
            closest_face = i;
        }
    }

    printf("The animal most similar to you is: %s\n", animals[closest_face].name);
}

int try_again() {
    char choice;
    printf("Would you like to try again? (Y/N): ");
    scanf(" %c", &choice);
    if (choice == 'Y' || choice == 'y') {
        return 1;
    } else {
        printf("Thank you For Using Our Application. Goodbye");
        return 0;
    }
}

int main () {
    User user = {0};

    if (login(&user)) {
        do {
            take_quiz(&user);
            find_face(&user);
        } while (try_again());
    }

    return 0;
}
