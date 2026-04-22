### Terminal Snake Game (C + ncurses)

A fully interactive Snake Game built in C using the ncurses library, featuring multiple game modes, save/load system, and dynamic obstacles.

## Installation of ncurses
1. Type `sudo apt upgrade` in terminal
2. Type `sudo apt install libncurses5-dev libncursesw5-dev` for Ubuntu/Debian or `sudo dnf install ncurses-devel` for Fedora
## How to Run

1. Type `make run` in terminal  
2. Run the game  
   `./snake`

## Gameplay Overview

1. The game starts with a menu interface  
2. Navigate menus using UP_ARROW and DOWN_ARROW  
3. Press ENTER to select an option  
4. The game is best for playing in VS Code Terminal. 

## How to Play the Game

1. Starting Game Menu is displayed and different options are shown.  

2. If new game is clicked, it asks for difficulty, showing a menu.  
   2.1 Slow Mode: Green snake (Head is '@' and body is 'o') of length 1 spawns and as more food of red colour is eaten (red coloured '0' icon), the length increases.  
   2.2 Medium Mode: same as Slow Mode but speed is faster than Slow Mode.  
   2.3 Fast Mode: same as Medium Mode but speed is faster than Medium mode.  
   2.4 Hardcore Mode: Obstacles spawn as snake length increases. First two obstacles are vertical static walls, after that moving obstacles spawn and if snake touches obstacle, the game is over again.  

### Controls

Key               Action  
W / UP_ARROW      Move Up  
A / LEFT_ARROW    Move Left  
S / DOWN_ARROW    Move Down  
D / RIGHT_ARROW   Move Right  
P                 Pause / Resume  
Q                 Quit Game  
ENTER_KEY         When a selector is highlighting an option in a menu and ENTER_KEY is pressed, that option is executed.  

3. If p is pressed, game pauses, and shows menu. If p is pressed again in menu or when Resume is chosen, it unpauses. If Restart is chosen, it starts a new game again of same difficulty. If Save And Exit is is chosen, it shows a menu for a slot. If slot is chosen and it saves the game in that slot and then returns to starting menu. If Quit is chosen, the game quits.  

4. The game is over when snake collides with itself or an obstacle. After game is over, it displays Score, highest score throughout all played games of all difficulties and shows a menu.  
If Restart is chosen, then again a game of previous difficulty starts.  
If Quit is chosen, then game quits.
If Main Menu is chosen, the starting menu is displayed again.

6. In starting menu, if Resume game is chosen, then it asks for slot to load game from and starts game exactly from that saved slot.  
If quit is chosen, the game quits.  

7. Type `make clean` in terminal to remove the object files, library and executable.

## Notable Features

- Menu-driven interface (keyboard navigation using arrow keys)  
- Multiple difficulty levels:  
  - Slow  
  - Medium  
  - Fast  
  - Hardcore  
- Hardcore mode with dynamic obstacles  
- Save and Load system (3 slots)  
- Pause, Resume, Restart functionality  
- Global High Score tracking  
- Real-time keyboard controls  

## Technologies Used

- C Programming  
- ncurses (terminal graphics & input handling)  
- Makefile (build automation)  

## Future Improvements

- Better UI animations  
- Sound effects  
- Configurable controls  
- More obstacle patterns  
- Different types of food  

## Author

Kanishka Chakraborty
