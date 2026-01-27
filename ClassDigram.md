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
        
    }

    class Input {
        
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


