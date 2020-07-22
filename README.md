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

