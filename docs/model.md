📘 Overview

This document describes all data structures, models, and relationships used in the Personality to Animal Analyzer System.
It defines how users, questions, scoring weights, and animals are represented internally.

1. Data Model Summary
Entity	Description
User	Stores username, password, lock status
Animal	Stores the 7-dimension personality vector + name
Question	Stores question text, options, and scoring matrix
Score Vector	Accumulates user’s personality profile
System State	Manages login, attempts, and quiz flow
2. The Seven-Dimension Personality Vector

The entire system is based on 7 core personality dimensions.

Index	Field	Meaning
0	DOM	Dominance
1	STR	Strategy / Planning
2	COM	Communication
3	SOL	Solitude / Independence
4	AGI	Agility / Adaptiveness
5	SEC	Social Energy
6	AES	Aesthetic / Emotional Sensitivity
Representation
vector = [DOM, STR, COM, SOL, AGI, SEC, AES]

3. Animal Model
Structure
Animal {
    name: string
    word: float[7]
}

Example
DOG = [0.066, 0.066, 0.333, 0.0, 0.2, 0.266, 0.066]
CAT = [0.1, 0.1, 0.4, 0.1, 0.2, 0.3, 0.2]
...


Each animal represents a unique “behavior signature”.

4. User Model
Structure
User {
    password: string
    locked: bool
}

Properties
Field	Meaning
password	User authentication
locked	Becomes true when user fails login 4 times

The system stores users as a dictionary / map:

users = {
    "admin1234": { password: "1234", locked: false },
    "demo1234":  { password: "1234", locked: false }
}

5. Question Model

Each question consists of:

Question {
    text: string
    options: string[4]
    scores: int[4][7]
}

Explanation:

There are 5 questions.

Each question has 4 choices.

Each choice affects 7 dimensions.

Example for one question:

Question:
"On a rainy day you would:"
Options:
A. Read
B. Walk
C. Socialize
D. Build

Scores:
A: [0, 0, 1, 0, 0, 2, 2]
B: [0, 1, 0, 2, 0, 1, 2]
C: [1, 0, 0, 1, 1, 0, 0]
D: [2, 0, 0, 0, 1, 0, 1]

6. Score Vector Model

User’s final personality vector is generated from question answers.

Structure
score: float[7]


Initialization:

score = [0, 0, 0, 0, 0, 0, 0]


Update logic:

score[i] += scores[question][choice][i]

7. System Relationship Diagram
User ─── logs in ───▶ Quiz System
Quiz System ─── uses ───▶ Questions
Questions ─── contain ───▶ Score Weights
Score Weights ─── update ───▶ Score Vector
Score Vector ─── compared with ───▶ Animal Models


Output: Best matched animal

🇨🇳 中文版本
📘 概述

本文档解释本系统使用的所有 数据结构 与 模型设计。
包括用户模型、动物模型、题目模型、评分模型等。

1. 数据模型概述
实体	描述
User（用户）	保存密码、锁定状态
Animal（动物）	保存七维向量与名称
Question（题目）	保存文本、选项与加权矩阵
Score Vector（评分向量）	用户最终人格数据
System State（系统状态）	处理登录、测验流程
2. 七维人格模型
索引	字段	含义
0	DOM	支配性
1	STR	策略 / 思考
2	COM	表达沟通
3	SOL	独立 / 孤独偏好
4	AGI	适应性
5	SEC	社交能量
6	AES	情绪敏感度

向量结构：

V = [DOM, STR, COM, SOL, AGI, SEC, AES]

3. 动物模型

结构：

Animal {
    name: string
    word: float[7]
}


示例：

DOG = [0.066, 0.066, 0.333, 0, 0.2, 0.266, 0.066]
CAT = [0.1, 0.1, 0.4, 0.1, 0.2, 0.3, 0.2]

4. 用户模型

结构：

User {
    password: string
    locked: bool
}


解释：

字段	含义
password	密码
locked	失败 4 次后锁定
5. 题目模型

结构：

Question {
    text: string
    options: string[4]
    scores: int[4][7]
}


每个题目：

4 个选项

每个选项对应 7 个得分维度

6. 评分向量模型

结构：

score: float[7]


通过题目累加形成：

score[i] += weights[question][choice][i]

7. 系统关系图
用户 → 登录 → 测验系统
测验系统 → 使用 → 题库
题库 → 包含 → 权重矩阵
权重矩阵 → 更新 → 评分向量
评分向量 → 对比 → 动物模型
最终输出：最佳匹配动物