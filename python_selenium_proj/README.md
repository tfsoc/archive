## Desc
Script that tests (plays) the web-based [game](https://www.invokergame.com/).

It is played in guest (no-login) mode, thus the score is not recorded.

`-c, --with-click` - simulated the mouse click over html element instead of deafault keypress

`-m <val>, --game-mode <val>` - sets the game mode

| val | mode | desc |
| :---: |:----- |:----|
| 0   | Survival |How long can you take it? Difficulty will increase as time goes by!|
| 1   | Classic |Invoke 10 spells as fast as you can|
| 2   | Combo |Invoke and execute as many Combos you can in 30 sec|
| 3   | Hattrick |Invoke and execute as many 3xCombos you can in 30 sec|
| 4   | Random |You get randomly 1-3 spells, and its random if you have to use them|

