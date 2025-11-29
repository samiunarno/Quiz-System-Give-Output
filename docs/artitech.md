┌───────────────────────────────┐
│           User Layer           │
│  - Console Input/Output        │
└───────────────┬───────────────┘
                │
┌───────────────▼────────────────┐
│       Application Layer         │
│  - Login Module                 │
│  - Quiz Engine                  │
│  - Shuffle Engine               │
│  - Face Matching Engine         │
│  - Admin Commands               │
└───────────────┬────────────────┘
                │
┌───────────────▼────────────────┐
│          Data Layer             │
│  - User Data Store              │
│  - Animal Model Store           │
│  - Question Bank                │
│  - Scoring Matrices             │
└───────────────┬────────────────┘
                │
┌───────────────▼────────────────┐
│          Utility Layer          │
│  - Random Generator             │
│  - Input Reader                 │
│  - Math Engine                  │
└─────────────────────────────────┘


┌───────────────────────────┐
│        User Layer          │
│   - printf / scanf         │
│   - Choice input (A/B/C/D) │
│   - Login interaction      │
└───────────────┬───────────┘
                │
┌───────────────▼───────────┐
│    Application Layer        │
│  login()                    │
│  take_quiz()                │
│  find_face()                │
│  try_again()                │
│  shuffle_questions()        │
└───────────────┬───────────┘
                │
┌───────────────▼───────────┐
│         Data Layer          │
│ - animals[] (static)        │
│ - predefined_users[]        │
│ - questions[]               │
│ - options[][]               │
│ - score matrix              │
└───────────────┬───────────┘
                │
┌───────────────▼───────────┐
│     Utility Layer           │
│  - calculate()              │
│  - rand()/time()            │
│  - pow() math               │
└────────────────────────────┘
