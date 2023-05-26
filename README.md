# Go-Game
 
The goal of the project is the creation of a simple implementation of a Go game as a console application. Go
is an abstract strategy board game for exactly two players. The goal of the game is to surround (“conquer”)
more territory than the opponent.
The rules of (a simplified version of) the game are as follows:
1. The game is played on a square boards (ja: goban), with 19 lines crossing the board horizontally and
19 lines crossing the board vertically (board 19x19 – 361 intersections). Sometimes, the board size is
13x13 or even 9x9.
2. Players put black and white stones on the intersections, one stone at the time. The player that plays
with the black ones is the one that starts first.
3. The goal is to surround the largest surface on the board using your own stones.
4. A stone that was put on the board stays there unless it is captured. The stone is captured when it is
surrounded from all four sides by either the stone stones of a opposing colour or the edge of the board.
The free sides are called liberties, e.g. a stone that is surrounded by two stones of a opposing colour
has two liberties.
5. The player is not allowed to put a suicide stone on the board (that is – a stone that after the placement
immediately does not have any liberties). The player can put a stone on a intersection with no liberties
if and only if after the placement one of the stones of a opposing colour are captured.
6. The Ko rule has to be kept – the stones on the board must never repeat a previous position of stones.
Moves which would do so are forbidden, and thus only moves elsewhere on the board are permitted
that turn
.![git2](https://github.com/olekblok/Go-Game/assets/132127130/eee02535-1981-4f2c-a116-237cffc5a808)
