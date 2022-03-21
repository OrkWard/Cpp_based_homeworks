This workspace is used to learn basic C++ language. Only single source files, perhaps.

### Project3
The procedure are listed below:
 - First, player enter the game, and see the lobby.
 - Second, choose a direction and go to the next room.
 - Recurtion, until find the princess or the monster.
 - If found the monster, the game end, and the player can choose to quit or replay; or if found the princess, communicate and begin to go back to lobby.
 - If back to the lobby, then player wins the game.

There are only one important object in the game, the map. The map is a matrix of rooms, which is a class containing a **flag** to show it's lobby, princess, monster or normal; four **direction** to show how go to the next room. 
How to construct the map? 
1. Set the lobby at the center;
2. Construct the princess and the monster room randomly; 
3. Construct the doors randomly(travel through the whole maps, check for each door and rondomly decide whether there is a door or not)
4. check if the princess and the monster are reachable, if not, reconstruct the map.