# Project
Connect 4 w/ terminal UI and AI

# Motivation
I started writing this project when I was learning C in my second year of undergrad.
I was motivated to rebuild my old Connect 4 project, but this time get the AI to work
as intended. I wrote it in C because I heard that "C is fast," and I wanted the AI to
be as performant as possible. Little did I know at the time I started coding that the
most important aspect in the performance of the code was the opitmizations to the
minimax algorithm, and that writing the whole thing from scratch in C would end up
being very difficult.

# Features
This project features a terminal-based Connect 4 game where the user plays against an
intelligent AI. The AI uses the minimax algorithm, along with several optimizations to
achieve a maximum search depth of ~17 moves. Perfect Connect 4 AIs exist, meaning they
can play the perfect move at every point in the game. With more optimizations, my AI
could achieve similar results. However, I came to a big roadblock when I tried to
implement transposition tables on my own, since I had to develop my own HashTable, and
I failed at the time to implement this successfully. 

The successfully implemented AI includes minimax with alpha-beta pruning, iterative
deepening, and a rudimentary heuristic for move ordering that starts inwards and
goes outwards from the center of the board. It also uses a bitboard (as opposed to
a 2D array of digits) to represent the board, as this is much more efficient in
terms of space and time to search.

# Future Work
If I ever revisit this project, I'll want to revisit the transposition tables, as
well as look into other optimizations like killer heuristic and static lookup tables.