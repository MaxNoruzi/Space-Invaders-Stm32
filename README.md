# 👾 STM32 Space Invaders Game – Embedded C Project

A fully interactive **Space Invaders-style arcade game** implemented in C for STM32 microcontrollers. Built from scratch with custom drivers for the LCD, keypad, and buzzer. Featuring animations, enemy waves, boss fights, real-time controls, and even a Super Mario soundtrack.

> 🎯 Designed for educational and entertainment purposes in embedded systems development.

---

## 🎮 Game Overview

- Fight waves of enemy invaders and a powerful boss using arrows.
- Move your spaceship (plane) across the LCD screen using a keypad.
- Choose difficulty levels and survive the attack.
- Enjoy audio feedback for hits, game events, and background music.

---

## 🧠 Features

- ✅ **Custom LCD Interface** with animations and scrolling effects
- 🎼 **Buzzer Music Engine** – Super Mario Theme, Boss Music, SFX
- 🎮 **Real-time gameplay** using timers and interrupts
- 💥 **Boss Fight Mode** with multi-tile enemies and advanced AI
- 📟 **UART Debug Output** for score tracking and game logs
- 🕹️ **Keypad Controls**:
  - Move left/right
  - Shoot arrows
  - Navigate menus
- 💾 Modular code structure (drivers, game manager, input, display, audio)

---

## 🧰 Hardware Used

| Component         | Description                        |
|------------------|------------------------------------|
| MCU               | STM32 (e.g., STM32F3, STM32F103)   |
| Display           | 20x4 LCD (HD44780-compatible)      |
| Input             | Keypad (4 keys minimum)            |
| Sound             | Active Buzzer (PWM controlled)     |
| Other             | Resistors, breadboard, jumpers     |

---

## 🛠️ Game Modes

- **Begin** – Splash screen and animation
- **Menu** – Choose between Info or Game Start
- **Game Info** – Display authors and current time/date
- **Enter Name** – Accepts player name via UART
- **Difficulty Selection** – Easy, Medium, Hard, Boss
- **Play** – Real-time battle mode
- **Finish** – Win/Lose result screen

---

## 📂 Code Structure
├── main.c # Peripheral initialization and main loop ├── GameManager.c # Main game logic and flow control ├── Buzzer.c # Music and sound effects ├── Keypad.c # Debounced keypad handler ├── Lcd.c # UI screen rendering ├── LiquidCrystal.c # Custom LCD driver for STM32 ├── Characters.h # Custom LCD characters (plane, enemy, arrows) └── project.cpp # (Optional ADF graph, unused in core game)
