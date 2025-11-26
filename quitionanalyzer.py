import random
import math

Max_try = 4
numb_of_word = 7
numb_of_ques = 5
numb_face = 4

class Animal:
    def __init__(self, word, name):
        self.word = word
        self.name = name

class User:
    def __init__(self, username="", password=""):
        self.username = username
        self.password = password
        self.word = [0] * numb_of_word
        self.attempts = 0

animals = [
    Animal([1/15, 1/15, 5/15, 0/15, 3/15, 4/15, 1/15], "DOG"),
    Animal([1/10, 1/10, 4/10, 1/10, 2/10, 3/10, 2/10], "CAT"),
    Animal([0.1, 0.2, 0.3, 0.1, 0.2, 0.4, 0.1], "RABBIT"),
    Animal([0.3, 0.3, 0.1, 0.2, 0.2, 0.2, 0.1], "LION")
]

predefined_users = [
    User("admin1234", "1234"),
    User("demo1234", "1234")
]

def calculate(user, animal):
    total = 0
    for i in range(numb_of_word):
        total += (user[i] - animal[i]) ** 2
    return total

def login(user):
    attempts = 0
    while attempts < Max_try:
        u = input("Enter Username: ")
        p = input("Enter Password: ")

        for udata in predefined_users:
            if u == udata.username and p == udata.username[-4:]:
                user.username = udata.username
                user.password = udata.password
                print("Login Successful! Welcome", user.username)
                return 1

        print("Login Failed")
        attempts += 1
        if attempts == Max_try:
            print("Account Locked. Contact Admin.")
            return 0
    return 0

def shuffle_questions(questions, options, score):
    for i in range(numb_of_ques):
        j = random.randint(0, numb_of_ques - 1)
        if i != j:
            questions[i], questions[j] = questions[j], questions[i]
            options[i], options[j] = options[j], options[i]
            score[i], score[j] = score[j], score[i]

def take_quiz(user):
    questions = [
        "1. You find a puzzle, you choose to: ",
        "2. When facing a challenge, you prefer to: ",
        "3. In a social group, you're often the one who: ",
        "4. On a rainy day, you would likely: ",
        "5. You are known for being: "
    ]

    options = [
        ["A. Solve it alone","B. Seek help","C. Observe first","D. Let others solve"],
        ["A. Lead the way","B. Plan carefully","C. Take risks","D. Wait for solution"],
        ["A. Take charge","B. Organize","C. Support","D. Enjoy space"],
        ["A. Read","B. Walk","C. Socialize","D. Build"],
        ["A. Outgoing","B. Reflective","C. Independent","D. Compassionate"]
    ]

    score = [
        [[2,0,0,0,0,0,1],[1,2,0,0,0,0,2],[0,0,2,0,0,0,1],[0,0,0,2,0,0,0]],
        [[2,0,0,0,0,0,1],[1,1,0,0,0,1,2],[0,0,2,0,2,0,0],[0,0,0,2,0,0,0]],
        [[2,1,0,0,0,1,1],[1,2,0,0,1,0,2],[0,0,2,0,0,0,0],[0,0,0,1,1,2,1]],
        [[0,0,1,0,0,2,2],[0,1,0,2,0,1,2],[1,0,0,1,1,0,0],[2,0,0,0,1,0,1]],
        [[1,0,0,0,2,0,1],[1,2,0,0,0,0,0],[0,1,2,0,0,0,1],[0,0,1,2,0,1,2]]
    ]

    shuffle_questions(questions, options, score)

    for i in range(numb_of_ques):
        print(questions[i])
        for op in options[i]:
            print(op)
        ans = input("Enter Choice (A-D): ").upper()
        idx = ord(ans) - ord('A')
        for j in range(numb_of_word):
            user.word[j] += score[i][idx][j]

def find_face(user):
    minv = float('inf')
    name = ""
    for ani in animals:
        v = calculate(user.word, ani.word)
        if v < minv:
            minv = v
            name = ani.name
    print("Your Animal Face:", name)

def try_again():
    c = input("Try Again? (Y/N): ")
    if c in ['Y','y']:
        return 1
    return 0

def main():
    user = User()
    if login(user):
        while True:
            user.word = [0] * numb_of_word
            take_quiz(user)
            find_face(user)
            if not try_again():
                break

main()
