# birthday-paradox
# Overview
This project explores the **Birthday Paradox**, a famous problem in probability theory and algorithm design. It focuses on answering the question of how many people need to be in a room for there to be a 50% chance that at least two of them share the same birthday.

In this project, we delve into both the theoretical aspects of the problem and provide a practical implementation using a C-based program to calculate the required number of people. The goal is to develop an algorithm that solves this problem and scientifically evaluate its effectiveness. The project is part of the GRA course.

# Functionality
The Birthday Paradox addresses the surprising fact that in a group of just 23 people, there is a 50% chance that at least two people share the same birthday. Intuitively, most people would expect a higher number, but the actual calculation shows otherwise.

By generalizing the problem, we can ask how many people, denoted as k, need to be in a room for there to be a 50% chance that two people share an element from a set M with n elements (for example, birthdays distributed across 365 days).

This number k can be calculated using the following formula:

$k \geq \frac{1 + \sqrt{1 + 8n \times \ln 2}}{2}$

For n = 365, this simplifies to approximately k ≈ 23.

# Theoretical Tasks:
Understand the probabilistic model behind the Birthday Paradox.
Explain the mathematical reasoning behind the formula used to calculate k.
Analyze and discuss why the intuitive guess for k is often much higher than the calculated result.

# Practical Implementation:
Implement the algorithm in C to calculate k for different values of n.
The program must use basic arithmetic operations only (addition, subtraction, multiplication, and division). Complex operations like square roots, logarithms, or exponentiation must be avoided.
The program should output the value of k for a given n, demonstrating the Birthday Paradox effect.

# Technologies Used
- Programming Language: C
- Mathematical Methods: Basic arithmetic, probability theory, logarithmic calculations (explained without using complex arithmetic functions in code).
- Development Environment: Any C compiler (e.g., GCC or Clang).
