# Chess Master (SFML)

A **classic chess** game written in **C++** using **object-oriented programming** and **SFML** for graphics and input. Play **two players locally** on one machine, or **versus the computer** (Black plays random legal moves).

---

## Features

- Full **8×8** board with textured pieces and a side status panel  
- **Main menu**: 1 Player (vs PC) or 2 Players (local)  
- **Mouse controls**: select a piece, click destination (or click again to deselect / switch selection)  
- **Standard rules**: all piece moves, **castling**, **en passant**, **pawn promotion** (to **Queen**)  
- **Check**, **checkmate**, and **stalemate** detection with on-screen messages  
- **Console board** output via `Board::Display()` (useful for debugging)  
- **OOP design**: `Piece` base class with virtual moves; concrete pieces (`Pawn`, `Rook`, `Knight`, `Bishop`, `Queen`, `King`); `Board` for logic; `Game` for SFML loop and UI  

---

## Requirements

- **Windows** (project is set up for **Visual Studio** / MSVC)  
- **Visual Studio 2022** (or compatible) with **Desktop development with C++**  
- **SFML 2.x** — this repo expects the SFML SDK under a local `SFML/` folder (see **Project layout**)  
- **C++** compiler with support used by your VS toolset (project uses MSVC **Conformance Mode**)  

---

## Project layout
OOP_Final_Project/ ├── Main.cpp # Entry point: creates Game and runs Start() ├── Implementation.cpp # Piece rules, Board logic, Game + SFML code ├── Header.h # Class declarations, enums, prototypes ├── OOP_Final_Project.vcxproj ├── assets/ # Fonts + piece PNGs (required for best visuals) │ ├── board_font.ttf # (optional if Windows fonts fallback works) │ ├── w_pawn.png, b_pawn.png, ... │ └── ... └── SFML/ # SFML headers + libs (as configured in .vcxproj) ├── include/ └── lib/


---

## Build (Visual Studio)

1. Clone or download this repository.  
2. Ensure **`SFML/`** matches the **include** and **lib** paths in `OOP_Final_Project.vcxproj` (defaults: `$(ProjectDir)SFML\include` and `$(ProjectDir)SFML\lib`).  
3. Open **`OOP_Final_Project.vcxproj`** in Visual Studio.  
4. Choose **Debug** or **Release** and **x64** (or **Win32**, matching your SFML build).  
5. **Build → Build Solution** (`Ctrl+Shift+B`).  

**Run:** Start debugging (`F5`) or run the generated `.exe` under `x64\Debug\`, `x64\Release\`, etc.

> **Note:** If the game fails to start with errors about missing **SFML DLLs**, copy the matching DLLs from your SFML **`bin`** folder next to the `.exe` (Debug vs Release names differ, e.g. `sfml-graphics-2.dll` vs `sfml-graphics-d-2.dll` depending on your SFML version).

---

## Assets

Place images and font under **`assets/`** (paths are hard-coded in `Game::LoadAssets()`):

| Symbol | File (white) | File (black) |
|--------|----------------|---------------|
| P / p | `w_pawn.png` | `b_pawn.png` |
| R / r | `w_rook.png` | `b_rook.png` |
| N / n | `w_knight.png` | `b_knight.png` |
| B / b | `w_bishop.png` | `b_bishop.png` |
| Q / q | `w_queen.png` | `b_queen.png` |
| K / k | `w_king.png` | `b_king.png` |

If a texture fails to load, the game **falls back** to drawing the piece letter with `sf::Text`. The font loader tries `assets/board_font.ttf`, then common Windows fonts (**Arial** / **Consolas**).

---

## How to play

1. Launch the game.  
2. On the **menu**, click **1 Player (vs PC)** or **2 Players (Local)**.  
3. **White** always moves first.  
4. Click your piece, then click a valid square to move.  
5. In **vs PC** mode, **Black** is played automatically after your move.  

Board area: **800×800** pixels (left side of the window). The **right panel** shows turn, check, checkmate, stalemate, or invalid move messages.

---

## Architecture (short)

- **`Piece`**: color, `hasMoved`, `IsValidMove`, `GetSymbol`  
- **Specialized pieces**: override movement rules  
- **`Board`**: `Piece* Grid[8][8]`, setup, `Move`, `IsCheck`, `HasAnyValidMove`, promotion, last-move tracking for en passant  
- **`Game`**: SFML window, textures, input, rendering, menu, and simple AI for Black  

---

## Credits

- **SFML** — [https://www.sfml-dev.org/](https://www.sfml-dev.org/)  
- **Author:** *[Your Name]*  
- **Course / institution (optional):** *[e.g. OOP Final Project, 2026]*  

---

