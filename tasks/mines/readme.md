# Minesweeper

The class which realises the backend of the game 'minesweeper'.

## Structure of the class

### Constructors
- taking the size of the field and the number of mines - places mines on the field randomly
- taking the size of the field and the list of cells - places mines on the specified cells

### Methods
- `NewGame` - initializes a new game; has two options similar to constructors
- `OpenCell` - analogous to a left-click
  - if the game is won or lost, does nothing
  - if a cell has a flag on it, does nothing
  - if the cell is unchecked, it opens the cell; the algorithm for opening the cells is described below
- `MarkCell` - analogous to a right-click
  - if the game is won or lost, does nothing 
  - marks an empty cell with a flag
  - removes the flag from the cell with the flag
- `GetGameStatus` - returns the status of the game
- `GetGameTime` - returns the game time in seconds. The time starts counting down at the first click in the game and freezes when you win or lose. Before the first click in the game returns 0.
- `RenderField` - returns a list of rows corresponding to the rendered field. Matching elements to symbols:
  - closed cell - `-`
  - a cell with a mine - `*`
  - a cell  with a flag - `?`
  - open cell without mines - the number from `1` to `8` (corresponds to the number of mines in neighboring cells), instead of 0 is written `.`

## Cell opening algorithm:
- If the cell contains a mine:
  - all cells open
  - the game ends with a loss
- If the cell does not contain a mine, but there is a mine in the neighboring cell, then only this cell opens.
- If the cell and its neighbors do not contain mines, the current cell opens.
 - the algorithm for opening a cell is applied to all neighbors of the current cell without a flag.

The game is considered won when all the cells are open except those on which there are mines.
