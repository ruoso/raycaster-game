# Raycaster game

This is an exercise in implementing a raycaster game in C++

## src

### datamodel

The datamodel diretory represents the data structures used to model
the game. This uses the [immutable value/mutable
companion](http://martin-moene.blogspot.com/2012/08/growing-immutable-value.html)
pattern, then uses `std::shared_ptr` to allow the immutable values to
be shared.

The only mutable object is `raycaster::datamodel::GameRun`, which
holds the current state of the game. The implementation is basically
doing lots of copies, but those copies will be shallow because the
objects all are immutable and have their data held in shared pointers.

### toy1-datamodel-only

This is a simple executable that exercises the datamodel objects,
showing how you are supposed to manipulate those immutable values.

### gameloader

This will hold the implementation of logic to load and store game
level data into json.

### math

This will contain calculation functions without side-effects that will
be used by the game.

### mechanics

This will contain the evaluation function that takes a game state and
a game level definitions as inputs, as well as the ellapsed time and
return a new game state.

### events

This will contain the definition of the different event types, as well
as the machinery to execute

### render

This is the part that renders the game during the level gameplay.

### ui

This is the part between levels, such as title screen, pause screen, etc.