# Diagramme de classes TP-OTRIO

```mermaid

classDiagram 

%% ----------- LIENS ----------- %%
    
    GameHandler *-- Board
    GameHandler o-- Player
    GameHandler *-- Display
    GameHandler *-- Input

    Board o-- Case

    Player <|-- Bot
    Player <|-- Human


%% ----------- CLASSES ----------- %%

    class GameHandler {
        -player[]
        -purrentPlayer
        + DetectWin()
    } 

    class Board {
        -int lenth
    } 

    class Case {
        -int circles 
        -int taillesOnCase []
    }

    class Player {
        -enum COLOR 
        -int taillesOnCase []
    }

    class Bot {
        -previsionsCoups []
        -void ThinkCoups ()
    }

    class Human {
        
    }

    class Display {
        - Case board[][]
        - string printBuff[][]
        - string pionSelPrintBuff[]]
        - int8_t selx
        - int8_t sely
        - bool pionSelEn
        - enum SIZE selPion

        - void loadGrille(void)
        - void loadCase(void)
        - void loadSelectedCase(void)
        - void loadCircleSmall(uint8_t, uint8_t, string)
        - void loadCircleMedium(uint8_t, uint8_t, string)
        - void loadCircleLarge(uint8_t, uint8_t, string)
        - void loadSelectedPion(enum SIZE)

        + void print(Board);
        + void printPionSelection(bool);
        + void setCursor(uint8_t, uint8_t);
        + void setCursor(enum SIZE);
        + uint8_t getNbPlayers(void);
        + uint8_t getNbRobot(void);
        + string getString(string);
    }

    class Input {
        # static Input* input_;

        + static Input *GetInstance(void);
        + void begin(void);
        + void end(void);
        + char waitForKey(void);
        + InputKey_t waitCtrlKey(void);
    }

    class  COLOR {
    <<enum>>

        RED
        BLUE
        PURPLE
        GREEN
    }

```


### BE CAREFUL WITH THIS 

int -> uint...

MAJ au debut des type qu'on créer exemple : Player

MAJ aux debut des methodes

Nom des variables en minuscule


