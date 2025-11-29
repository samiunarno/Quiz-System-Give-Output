📘 Overview

This document explains the core algorithms used in the Personality → Animal Matching System.
The system evaluates user answers, scores a seven-dimension personality vector, and then finds the best-matching animal using SSD (Sum of Squared Differences).

1. Personality Vector Model

Each user and each animal is represented as:

V = [DOM, STR, COM, SOL, AGI, SEC, AES]


Where each value is a numeric weight.

Example (Dog):

DOG = [1/15, 1/15, 5/15, 0, 3/15, 4/15, 1/15]

2. Question Weight Model

Each question contains 4 answer choices (A–D).
Each choice contributes a different amount to the 7 personality dimensions.

Example structure:

scoreWeights[question][choice][dimension]


Thus for 5 questions, 4 choices, 7 dimensions:

score[7]
for q in 1..5:
    user_choice = input
    for dim in 7:
        score[dim] += weight[q][choice][dim]

3. Shuffle Algorithm

(Fisher–Yates Shuffle)

Used to randomize:

question order

answer order

scoring weight order (structurally linked)

This ensures:

each test is unpredictable

prevents memorizing answer patterns

Pseudocode
for i = N−1 downto 1:
    j = random(0, i)
    swap(item[i], item[j])


Applied simultaneously to:

questions[i]
options[i]
weights[i]

4. Score Calculation Algorithm
Pseudocode
initialize score[7] to all zeros

for each question:
    display question
    get choiceIndex (0–3)
    for dim in 0..6:
        score[dim] += weights[question][choiceIndex][dim]


Final output = user’s 7-dimension personality vector.

5. Animal Matching Algorithm (SSD)

We calculate distance between:

user vector U

animal vector A

Using Sum of Squared Differences:

SSD = Σ ( U[i] - A[i] )² for i in 0..6

Why SSD?

simple

fast

works in all languages

stable

scales well

Pseudocode
minDist = +∞
bestAnimal = null

for each animal:
    dist = 0
    for dim in 0..6:
        diff = U[dim] - A[dim]
        dist += diff * diff
    if dist < minDist:
        minDist = dist
        bestAnimal = animal


Output: bestAnimal.name

6. Login & Account Lock Algorithm
Rules

4 failed attempts → user.locked = true

locked users cannot log in

only admin can unlock

Admin Unlock Command
unlock <username>

Pseudocode
if login fails:
    attempts++
    if attempts == 4:
        user.locked = true

7. Full System Flow (Algorithmic View)
START
|
|--> LOGIN
       |--> FAIL 4 times → LOCK → STOP
       |--> ADMIN → UNLOCK
|
|--> SHUFFLE questions/options/weights
|
|--> ASK each question
|
|--> UPDATE seven-dimension score
|
|--> CALCULATE SSD for all animals
|
|--> RETURN closest match
|
|--> Ask "Try again?"
|
END

8. Time Complexity
Step	Complexity
Shuffle	O(n)
Quiz scoring	O(numQuestions × 7)
SSD match	O(numAnimals × 7)
Overall	O(n) (linear)
🇨🇳 中文版本
📘 概述

本文件详细解释 人格 → 动物匹配系统 的核心算法。
系统通过用户回答的问题生成七维度人格向量，并使用 SSD（平方差之和）算法 匹配最接近的动物类型。

1. 人格七维度模型

每个用户与动物均以一个七维向量表示：

V = [DOM, STR, COM, SOL, AGI, SEC, AES]


示例（狗 DOG）：

DOG = [1/15, 1/15, 5/15, 0, 3/15, 4/15, 1/15]

2. 题目加权机制

每个题目包含 A–D 四个选项，每个选项对七维度人格具有不同评分。

结构：

weights[题目][选项][维度]


最后将所有题目的权重累加，得到最终的评分向量。

3. 随机算法（Fisher–Yates 洗牌）

对以下内容进行随机：

题目顺序

选项顺序

权重顺序（保持结构一致）

保证每次测验完全不同。

4. 人格评分计算算法

伪代码：

初始化 score[7] = 0

对于每个题目:
    用户选择 choice
    对于每个维度 dim:
        score[dim] += weights[question][choice][dim]


输出：用户七维人格向量。

5. 动物匹配算法（SSD）

计算用户向量与动物向量之间的 平方差之和：

SSD = Σ ( U[i] - A[i] )²


SSD 越小 → 越相似。

伪代码：

minDist = +∞
bestAnimal = null

对每个动物:
    dist = 0
    对每个维度:
        diff = U[dim] - A[dim]
        dist += diff * diff
    如果 dist < minDist:
        bestAnimal = animal


输出：最接近的动物类型。

6. 登录与账号锁定算法

密码错误 4 次 → 自动锁定

锁定后无法登录

管理员可以解锁

管理员指令：

unlock 用户名

7. 系统流程（算法视角）
程序开始
|
|→ 登录
|     |→ 失败 4 次 → 锁定 → 结束
|     |→ 管理员 → 解锁
|
|→ Fisher–Yates 洗牌题库
|
|→ 用户回答 5 个题目
|
|→ 计算七维度评分
|
|→ 执行 SSD 匹配动物
|
|→ 输出结果
|
|→ 是否重新测试？
|
结束

8. 时间复杂度
步骤	时间复杂度
洗牌	O(n)
评分计算	O(题目数 × 7)
SSD 匹配	O(动物数 × 7)
总复杂度	O(n)（线性）