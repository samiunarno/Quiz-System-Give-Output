const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

const NUM_WORD = 7;
const NUM_QUE = 5;

const animals = [
    { word: [1/15,1/15,5/15,0/15,3/15,4/15,1/15], name:"DOG" },
    { word: [1/10,1/10,4/10,1/10,2/10,3/10,2/10], name:"CAT" },
    { word: [0.1,0.2,0.3,0.1,0.2,0.4,0.1], name:"RABBIT" },
    { word: [0.3,0.3,0.1,0.2,0.2,0.2,0.1], name:"LION" }
];

let users = {
    admin1234: { password:"1234", locked:false },
    demo1234: { password:"1234", locked:false }
};

function calculate(u,a){
    let s=0;
    for(let i=0;i<NUM_WORD;i++) s+=(u[i]-a[i])**2;
    return s;
}

function ask(q){
    return new Promise(r=>rl.question(q,r));
}

async function login(){
    for(let i=0;i<4;i++){
        let u = await ask("Enter Username: ");
        let p = await ask("Enter Password: ");
        if(users[u] && users[u].password===p){
            if(users[u].locked){
                console.log("Profile Locked");
                return null;
            }
            if(u==="admin1234") await adminMode();
            return u;
        }
        console.log("Login Failed");
    }
    return null;
}

async function adminMode(){
    let cmd = await ask("Enter admin command: ");
    if(cmd.startsWith("unlock ")){
        let u = cmd.split(" ")[1];
        if(users[u]) users[u].locked=false;
    }
}

function shuffle(q,o,s){
    for(let i=0;i<NUM_QUE;i++){
        let j=Math.floor(Math.random()*NUM_QUE);
        [q[i],q[j]]=[q[j],q[i]];
        [o[i],o[j]]=[o[j],o[i]];
        [s[i],s[j]]=[s[j],s[i]];
    }
}

async function takequiz(){
    let q=[
        "1. You find a puzzle, you choose:",
        "2. When facing a challenge:",
        "3. In a social group:",
        "4. On a rainy day:",
        "5. You are known for:"
    ];

    let o=[
        ["A. Solve alone","B. Seek help","C. Observe","D. Others solve"],
        ["A. Lead","B. Plan","C. Risk","D. Wait"],
        ["A. Lead","B. Organize","C. Listen","D. Alone"],
        ["A. Read","B. Walk","C. Socialize","D. Build"],
        ["A. Outgoing","B. Reflective","C. Independent","D. Kind"]
    ];

    let s=[
        [[2,0,0,0,0,0,1],[1,2,0,0,0,0,2],[0,0,2,0,0,0,1],[0,0,0,2,0,0,0]],
        [[2,0,0,0,0,0,1],[1,1,0,0,0,1,2],[0,0,2,0,2,0,0],[0,0,0,2,0,0,0]],
        [[2,1,0,0,0,1,1],[1,2,0,0,1,0,2],[0,0,2,0,0,0,0],[0,0,0,1,1,2,1]],
        [[0,0,1,0,0,2,2],[0,1,0,2,0,1,2],[1,0,0,1,1,0,0],[2,0,0,0,1,0,1]],
        [[1,0,0,0,2,0,1],[1,2,0,0,0,0,0],[0,1,2,0,0,0,1],[0,0,1,2,0,1,2]]
    ];

    shuffle(q,o,s);
    let score = Array(NUM_WORD).fill(0);

    for(let i=0;i<NUM_QUE;i++){
        console.log(q[i]);
        for(let j=0;j<4;j++) console.log(o[i][j]);
        let ch=(await ask("Choice (A-D): ")).toUpperCase();
        let idx=ch.charCodeAt(0)-65;
        for(let k=0;k<NUM_WORD;k++) score[k]+=s[i][idx][k];
    }
    return score;
}

function findface(arr){
    let min=1e9,idx=-1;
    for(let i=0;i<animals.length;i++){
        let v=calculate(arr,animals[i].word);
        if(v<min){min=v;idx=i;}
    }
    console.log("Your Animal Face:",animals[idx].name);
}

async function main(){
    let u=await login();
    if(!u){rl.close();return;}

    while(true){
        let s=await takequiz();
        findface(s);
        let again=await ask("Try Again? (Y/N): ");
        if(again!=="Y" && again!=="y") break;
    }
    rl.close();
}

main();
