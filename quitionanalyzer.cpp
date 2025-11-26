#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

#define Max_try 4
#define numb_of_word 7
#define numb_of_ques 5
#define numb_face 4

struct Animal {
    double word[numb_of_word];
    string name;
};

struct User {
    string username;
    string password;
    double word[numb_of_word]{0};
    int attempts = 0;
    bool locked = false;
};

Animal animals[numb_face] = {
    {{1.0/15,1.0/15,5.0/15,0,3.0/15,4.0/15,1.0/15},"DOG"},
    {{1.0/10,1.0/10,4.0/10,1.0/10,2.0/10,3.0/10,2.0/10},"CAT"},
    {{0.1,0.2,0.3,0.1,0.2,0.4,0.1},"RABBIT"},
    {{0.3,0.3,0.1,0.2,0.2,0.2,0.1},"LION"}
};

double calculate(double u[], double a[]) {
    double sum = 0;
    for(int i=0;i<numb_of_word;i++) sum += pow(u[i]-a[i],2);
    return sum;
}

bool admin_unlock(User &u){
    string id, pass;
    cout<<"ADMIN ID: ";
    cin>>id;
    cout<<"ADMIN PASS: ";
    cin>>pass;
    if(id=="admin" && pass=="6666"){
        u.locked=false;
        u.attempts=0;
        cout<<"Account Unlocked\n";
        return true;
    }
    cout<<"Invalid Admin Login\n";
    return false;
}

bool login(User &u){
    while(u.attempts<Max_try){
        cout<<"Enter Username: ";
        cin>>u.username;
        cout<<"Enter Password: ";
        cin>>u.password;

        if(u.username.size()==8 && u.password==u.username.substr(4,4)){
            cout<<"Login Successful\n";
            return true;
        }

        cout<<"Login Failed\n";
        u.attempts++;

        if(u.attempts==Max_try){
            u.locked=true;
            cout<<"Account Locked. Admin Required.\n";
            while(!admin_unlock(u));
            return login(u);
        }
    }
    return false;
}

void shuffleQ(string q[], string opt[][4], int score[numb_of_ques][4][numb_of_word]){
    srand(time(0));
    for(int i=0;i<numb_of_ques;i++){
        int j=rand()%numb_of_ques;
        swap(q[i],q[j]);
        for(int k=0;k<4;k++){
            swap(opt[i][k],opt[j][k]);
            for(int x=0;x<numb_of_word;x++)
                swap(score[i][k][x],score[j][k][x]);
        }
    }
}

void take(User &u){
    string q[numb_of_ques]={
        "1. You find a puzzle, you choose to:",
        "2. When facing a challenge, you prefer to:",
        "3. In a social group, you are the one who:",
        "4. On a rainy day, you would:",
        "5. You are known for being:"
    };

    string opt[numb_of_ques][4]={
        {"A. Solve it alone","B. Ask help","C. Observe","D. Ignore"},
        {"A. Lead","B. Plan","C. Risk","D. Wait"},
        {"A. Lead","B. Organize","C. Support","D. Alone"},
        {"A. Read","B. Walk","C. Socialize","D. Build"},
        {"A. Outgoing","B. Reflective","C. Independent","D. Kind"}
    };

    int score[numb_of_ques][4][numb_of_word]={
        {{2,0,0,0,0,0,1},{1,2,0,0,0,0,2},{0,0,2,0,0,0,1},{0,0,0,2,0,0,0}},
        {{2,0,0,0,0,0,1},{1,1,0,0,0,1,2},{0,0,2,0,2,0,0},{0,0,0,2,0,0,0}},
        {{2,1,0,0,0,1,1},{1,2,0,0,1,0,2},{0,0,2,0,0,0,0},{0,0,0,1,1,2,1}},
        {{0,0,1,0,0,2,2},{0,1,0,2,0,1,2},{1,0,0,1,1,0,0},{2,0,0,0,1,0,1}},
        {{1,0,0,0,2,0,1},{1,2,0,0,0,0,0},{0,1,2,0,0,0,1},{0,0,1,2,0,1,2}}
    };

    shuffleQ(q,opt,score);

    for(int i=0;i<numb_of_ques;i++){
        cout<<q[i]<<endl;
        for(int j=0;j<4;j++) cout<<opt[i][j]<<endl;
        char ans;
        cin>>ans;
        int idx=ans-'A';
        for(int k=0;k<numb_of_word;k++) u.word[k]+=score[i][idx][k];
    }
}

void face(User &u){
    double best=1e18;
    int idx=-1;
    for(int i=0;i<numb_face;i++){
        double v=calculate(u.word,animals[i].word);
        if(v<best){best=v; idx=i;}
    }
    cout<<"Your Animal Face: "<<animals[idx].name<<endl;
}

int main(){
    User u;
    if(login(u)){
        do{
            take(u);
            face(u);
            cout<<"Again? (Y/N): ";
            char c; cin>>c;
            if(c=='N'||c=='n') break;
        }while(true);
    }
}
