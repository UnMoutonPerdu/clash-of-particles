# ISAE-Supaero - IN101 Project


 Basic implementation of a simulation of the movement of particles confined in a box. 

 Two implementations are available: 
 * A naive implementation of the management of collisions between particles.
 * An implementation using a binary heap data structure to reduce the complexity of the algorithm and improve performance on the latest test files.

A script is also available for calculating an approximation of pi using the number of collisions between 2 particles. (See [this video by 3Blue1Brown](https://www.youtube.com/watch?v=HEfHFsfGXjs)).

## Commands

To compile the files:
```console
foo@bar:~$ make clean
foo@bar:~$ make clash-of-particles-naive
foo@bar:~$ make clash-of-particles-bh
foo@bar:~$ make calculate-pi-coll
```

You can then run these scripts with:
```console
foo@bar:~$ ./calculate-pi-coll
```

```console
foo@bar:~$ ./clash-of-particles-naive data/random-(number of particles).txt
```

```console
foo@bar:~$ ./clash-of-particles-bh data/random-(number of particles).txt
```
