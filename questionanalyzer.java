import java.util.Random;
import java.util.Scanner;

public class questionanalyzer {
    static final int NUM_WORD = 7;
    static final int NUM_QUE = 5;
    static final int NUM_TRIES = 4;

    static class Animal {
        double[] word;
        String name;
        Animal(double[] word, String name) {
            this.word = word;
            this.name = name;
        }
    }

    static class User {
        String username;
        String password;
        double[] word = new double[NUM_WORD];
        boolean locked = false;
        User(String username, String password) {
            this.username = username;
            this.password = password;
        }
    }

    static Scanner scanner = new Scanner(System.in);

    static Animal[] animals = {
        new Animal(new double[]{1.0/15,1.0/15,5.0/15,0.0/15,3.0/15,4.0/15,1.0/15}, "DOG"),
        new Animal(new double[]{1.0/10,1.0/10,4.0/10,1.0/10,2.0/10,3.0/10,2.0/10}, "CAT"),
        new Animal(new double[]{0.1,0.2,0.3,0.1,0.2,0.4,0.1}, "RABBIT"),
        new Animal(new double[]{0.3,0.3,0.1,0.2,0.2,0.2,0.1}, "LION")
    };

    static User[] users = {
        new User("admin1234", "1234"),
        new User("demo1234", "1234")
    };

    public static double calculate(double[] u, double[] a) {
        double s = 0;
        for (int i = 0; i < NUM_WORD; i++) s += Math.pow(u[i] - a[i], 2);
        return s;
    }

    public static User findUser(String name) {
        for (User u : users) if (u.username.equals(name)) return u;
        return null;
    }

    public static void adminMode(User admin) {
        System.out.println("Admin Mode Enabled");
        System.out.print("Enter admin command: ");
        String cmd = scanner.nextLine();
        if (cmd.startsWith("unlock ")) {
            String usern = cmd.substring(7);
            User u = findUser(usern);
            if (u != null) {
                u.locked = false;
                System.out.println("User " + usern + " unlocked.");
            } else System.out.println("User not found.");
        }
    }

    public static boolean login(User user) {
        int attempts = 0;
        while (attempts < NUM_TRIES) {
            System.out.print("Enter Username: ");
            String un = scanner.nextLine();
            System.out.print("Enter Password: ");
            String pw = scanner.nextLine();

            for (User u : users) {
                if (u.username.equals(un) && u.password.equals(pw)) {
                    if (u.locked) {
                        System.out.println("Profile Locked. Contact Admin.");
                        return false;
                    }
                    user.username = un;
                    user.password = pw;
                    if (un.equals("admin1234")) adminMode(u);
                    return true;
                }
            }
            attempts++;
            System.out.println("Login Failed (" + attempts + "/" + NUM_TRIES + ")");
        }
        User u = findUser(user.username);
        if (u != null) u.locked = true;
        return false;
    }

    public static void shuffle(String[] q, String[][] o, int[][][] s) {
        Random r = new Random();
        for (int i = 0; i < NUM_QUE; i++) {
            int j = r.nextInt(NUM_QUE);
            String tq = q[i];
            q[i] = q[j];
            q[j] = tq;
            for (int k = 0; k < 4; k++) {
                String to = o[i][k];
                o[i][k] = o[j][k];
                o[j][k] = to;
                int[] ts = s[i][k];
                s[i][k] = s[j][k];
                s[j][k] = ts;
            }
        }
    }

    public static void takequiz(User u) {
        String[] q = {
            "1. You find a puzzle, you choose to:",
            "2. When facing a challenge, you prefer to:",
            "3. In a social group, you're often:",
            "4. On a rainy day, you'd:",
            "5. You are known for being:"
        };

        String[][] o = {
            {"A. Solve alone","B. Seek help","C. Observe","D. Let others solve"},
            {"A. Lead","B. Plan","C. Risk","D. Wait"},
            {"A. Lead","B. Organize","C. Listen","D. Stay alone"},
            {"A. Read","B. Walk","C. Socialize","D. Build"},
            {"A. Outgoing","B. Reflective","C. Independent","D. Kind"}
        };

        int[][][] s = {
            {{2,0,0,0,0,0,1},{1,2,0,0,0,0,2},{0,0,2,0,0,0,1},{0,0,0,2,0,0,0}},
            {{2,0,0,0,0,0,1},{1,1,0,0,0,1,2},{0,0,2,0,2,0,0},{0,0,0,2,0,0,0}},
            {{2,1,0,0,0,1,1},{1,2,0,0,1,0,2},{0,0,2,0,0,0,0},{0,0,0,1,1,2,1}},
            {{0,0,1,0,0,2,2},{0,1,0,2,0,1,2},{1,0,0,1,1,0,0},{2,0,0,0,1,0,1}},
            {{1,0,0,0,2,0,1},{1,2,0,0,0,0,0},{0,1,2,0,0,0,1},{0,0,1,2,0,1,2}}
        };

        shuffle(q, o, s);

        for (int i = 0; i < NUM_QUE; i++) {
            System.out.println(q[i]);
            for (int j = 0; j < 4; j++) System.out.println(o[i][j]);

            System.out.print("Enter choice (A-D): ");
            char ch = scanner.next().charAt(0);
            int idx = ch - 'A';
            for (int w = 0; w < NUM_WORD; w++) u.word[w] += s[i][idx][w];
        }
        scanner.nextLine();
    }

    public static void findface(User u) {
        double min = Double.MAX_VALUE;
        int id = -1;
        for (int i = 0; i < animals.length; i++) {
            double v = calculate(u.word, animals[i].word);
            if (v < min) {
                min = v;
                id = i;
            }
        }
        if (id != -1) System.out.println("Your Animal Face: " + animals[id].name);
    }

    public static boolean again() {
        System.out.print("Try Again? (Y/N): ");
        char c = scanner.next().charAt(0);
        scanner.nextLine();
        return c == 'Y' || c == 'y';
    }

    public static void main(String[] a) {
        User u = new User("", "");
        if (login(u)) {
            do {
                u.word = new double[NUM_WORD];
                takequiz(u);
                findface(u);
            } while (again());
        }
    }
}
