package ques

import (
	"bufio"
	"fmt"
	"math"
	"math/rand"
	"os"
	"strings"
	"time"
)

const (
	NUM_WORD = 7
	NUM_QUE  = 5
)

type Animal struct {
	word []float64
	name string
}

type User struct {
	password string
	locked   bool
}

var animals = []Animal{
	{[]float64{1.0 / 15, 1.0 / 15, 5.0 / 15, 0, 3.0 / 15, 4.0 / 15, 1.0 / 15}, "DOG"},
	{[]float64{1.0 / 10, 1.0 / 10, 4.0 / 10, 1.0 / 10, 2.0 / 10, 3.0 / 10, 2.0 / 10}, "CAT"},
	{[]float64{0.1, 0.2, 0.3, 0.1, 0.2, 0.4, 0.1}, "RABBIT"},
	{[]float64{0.3, 0.3, 0.1, 0.2, 0.2, 0.2, 0.1}, "LION"},
}

var users = map[string]*User{
	"admin1234": {password: "1234", locked: false},
	"demo1234":  {password: "1234", locked: false},
}

var rd = bufio.NewReader(os.Stdin)

func input(prompt string) string {
	fmt.Print(prompt)
	t, _ := rd.ReadString('\n')
	return strings.TrimSpace(t)
}

func calculate(u, a []float64) float64 {
	s := 0.0
	for i := 0; i < NUM_WORD; i++ {
		s += math.Pow(u[i]-a[i], 2)
	}
	return s
}

func adminMode() {
	cmd := input("Enter admin command: ")
	if strings.HasPrefix(cmd, "unlock ") {
		u := strings.TrimSpace(cmd[7:])
		if users[u] != nil {
			users[u].locked = false
			fmt.Println("Unlocked:", u)
		}
	}
}

func login() string {
	for i := 0; i < 4; i++ {
		u := input("Enter Username: ")
		p := input("Enter Password: ")
		if users[u] != nil && users[u].password == p {
			if users[u].locked {
				fmt.Println("Profile Locked")
				return ""
			}
			if u == "admin1234" {
				adminMode()
			}
			return u
		}
		fmt.Println("Login Failed")
	}
	return ""
}

func shuffle(q []string, o [][]string, s [][][]int) {
	rand.Seed(time.Now().UnixNano())
	for i := 0; i < NUM_QUE; i++ {
		j := rand.Intn(NUM_QUE)
		q[i], q[j] = q[j], q[i]
		o[i], o[j] = o[j], o[i]
		s[i], s[j] = s[j], s[i]
	}
}

func takequiz() []float64 {
	q := []string{
		"1. You find a puzzle, you choose:",
		"2. When facing a challenge:",
		"3. In a social group:",
		"4. On a rainy day:",
		"5. You are known for:",
	}

	o := [][]string{
		{"A. Solve alone", "B. Seek help", "C. Observe", "D. Others solve"},
		{"A. Lead", "B. Plan", "C. Risk", "D. Wait"},
		{"A. Lead", "B. Organize", "C. Listen", "D. Alone"},
		{"A. Read", "B. Walk", "C. Socialize", "D. Build"},
		{"A. Outgoing", "B. Reflective", "C. Independent", "D. Kind"},
	}

	s := [][][]int{
		{{2, 0, 0, 0, 0, 0, 1}, {1, 2, 0, 0, 0, 0, 2}, {0, 0, 2, 0, 0, 0, 1}, {0, 0, 0, 2, 0, 0, 0}},
		{{2, 0, 0, 0, 0, 0, 1}, {1, 1, 0, 0, 0, 1, 2}, {0, 0, 2, 0, 2, 0, 0}, {0, 0, 0, 2, 0, 0, 0}},
		{{2, 1, 0, 0, 0, 1, 1}, {1, 2, 0, 0, 1, 0, 2}, {0, 0, 2, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 2, 1}},
		{{0, 0, 1, 0, 0, 2, 2}, {0, 1, 0, 2, 0, 1, 2}, {1, 0, 0, 1, 1, 0, 0}, {2, 0, 0, 0, 1, 0, 1}},
		{{1, 0, 0, 0, 2, 0, 1}, {1, 2, 0, 0, 0, 0, 0}, {0, 1, 2, 0, 0, 0, 1}, {0, 0, 1, 2, 0, 1, 2}},
	}

	shuffle(q, o, s)
	score := make([]float64, NUM_WORD)

	for i := 0; i < NUM_QUE; i++ {
		fmt.Println(q[i])
		for _, op := range o[i] {
			fmt.Println(op)
		}
		ch := input("Choice (A-D): ")
		idx := int(ch[0] - 'A')
		for k := 0; k < NUM_WORD; k++ {
			score[k] += float64(s[i][idx][k])
		}
	}
	return score
}

func findface(arr []float64) {
	min := 1e9
	idx := -1
	for i := range animals {
		v := calculate(arr, animals[i].word)
		if v < min {
			min = v
			idx = i
		}
	}
	fmt.Println("Your Animal Face:", animals[idx].name)
}

func main() {
	u := login()
	if u == "" {
		return
	}

	for {
		s := takequiz()
		findface(s)
		a := input("Try Again? (Y/N): ")
		if a != "Y" && a != "y" {
			break
		}
	}
}
