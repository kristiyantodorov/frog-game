# frog-game
Problem: Given a set of frogs(symbols) looking at opposite directions (>/<), output a solution which switches the two sets' positions.
A frog can jump to the next free slot in its direction or jump over another frog in its direction.

Example:

```
N = 3
Starting point:  > > > _ < < <
Expected result:
    > > > _ < < <
    > > _ > < < <
    > > < > _ < <
    > > < > < _ <
    > > < _ < > <
    > _ < > < > <
    _ > < > < > <
    < > _ > < > <
    < > < > _ > <
    < > < > < > _
    < > < > < _ >
    < > < _ < > >
    < _ < > < > >
    < < _ > < > >
    < < < > _ > >
    < < < _ > > >

Where > is a frog looking right, < is a frog looking left, and _ is an empty space.
```

The solution is using DFS graph traversal to solve the puzzle