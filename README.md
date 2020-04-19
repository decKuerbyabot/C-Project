# Group 106
## member: Victor Cheung(3035685902); Wang Qi(3035638818)

**Game description:

This game is a explorational maze game.

**Functions:**

The game will generate a map using the seed values given by the player, the map will be represented using a 2-D or 3-D array or vector (suspended), random demons and token chests should be generated *inside* the map, players will go in from the entry and start exploring.

**Features:**

*Player:* initially has 5 life points.

*Chest:* They move spratically by one block each time the player takes a move, there are other chests that may or may not contain weapons/magic potions but when the a chest appear within the 24 blocks around the player, it will become static automatically, open one needs 2 bare hand strikes and 1 saber strike, but it will damage the saber, the saber will be invalid after opening two chests, exit chest cannot be opened without keys.

*Demons:* There are two types of them, one of which is faster than your movement and the other is slower, static by default both will begin to persue the player when agitated, destroying them needs 3 bare hand strikes and 1 saber strike, one attack from the demon will cause one lost life point.

**Players can only strike the chest or the demon when they make an attack, and one attack takes one regular step, players must be in the adjacent block and facing the target to attack.**

*Magic potions:* randomly attained in chests.

*Saber:* player carries one that is initially granted, but can also be randomly attained in chests, used to kill demons or open chests.

*Key out:* Attained after killing the last demon, used on the exit chest.

Both demons and chests will require a possibility game(RPS game), to conquer by weapon, but when administered with potion, demons can be conquered without one, user commands should be specified here.

Magic potions: randomly attained in chests.

Saber: player carries one that is initially granted, can be used to kill demons or open chests.

Key: Attained after killing the lase demon.


**Movements:**

Movements are controlled using w, a, s, d, and then enter, the orientation will be automatically adjusted when a or d is pressed, but it doesn't consume step.

By default, the player can only go one block each turn, slow demon will go one block per two turns, fast demons will go two blocks per turn, fast demons will be reduced to slow demons when administered with potion.


After pressing enter, the periphery (4x4 grid) where the player is located will be displayed below in text-based format.

Caveats of demons and chests within the 5x5 grid will also be shown.

**Data structures:**

The player will be stored using a struct or class.

**Dynamic memory management:**

Will use new and delete if necessary, check out the final code for details.

**File input/output (e.g., for loading/saving game status):

When a game is halfway terminated, the map will be stored with a map datatype.

**Program codes in multiple files:**

Will include many headers files, function.cpp files for auxillary functions.
