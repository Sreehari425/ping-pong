# Ping Pong ASM+C

This is just a fun little hobby project where I combined **Assembly** and **C** to make a simple ping pong game.

---

## What’s this?

- Game logic like ball movement and collision done in x86-64 Assembly (yep, hardcore stuff).
- Rendering, input, and window handled by C with SDL2.
- Basically me messing around to learn how to mix ASM and C and get a game running.

---

## How to run

1. Make sure you have `gcc`, `nasm`, `make`, and SDL2 dev libs installed.
2. Run `make`
3. Run the game with `./build/game`

---

## Controls

- Left paddle: **W** (up), **S** (down)
- Right paddle: arrow keys (up/down)
- Close the window to quit.

---

## What’s working?

- Ball bounces and resets if it goes off screen.
- Paddles move with keyboard input.
- Collision detection and ball bounce logic are done in Assembly.
- Simple white rectangles for paddles and ball.
- Score System

---

## What’s next? (if I get bored again)

- Make ball bounce more interesting (like add spin or speed).
- Add sound effects.
- Make paddle movement smoother.
- Maybe try doing the whole thing in Assembly for the real challenge.

---

## Why?

Just wanted to see if I could actually mix Assembly with C and make something that works. Spoiler: it does!

---

Made for fun, learning, and showing off a bit. Feel free to copy or improve if you want.

---

Peace ✌️

[Sreehari Anil](https://github.com/Sreehari425/)
