https://github.com/fiddyBoi/TTK4155-Byggern

Notes:
- messages.c and .h is now in both Node1 and Node2 even though they are identical. This is a temporary solution.

Known bugs:
- While playing, if the motor position is controlled very quick/recklessly Node1 will fail and return to the menu even though it is in a infinite while loop in GAME_Start()
