#CG - a computational geometry library
---

I plan to implement some elementary computational geometry algorithms
and some example programs which use them.

##Running

You must have SFML installed to compile the examples.
If you're using Linux, its likely that SFML is available in your
distro's default package repositories. For example, on Arch-based
distros it is available in the `sfml` package and on Debian-based
distros, it goes by the name `libsfml-dev`.

`cd` to the root and run

    g++ -c convex-hull-example.cpp && g++ convex-hull-example.o -o convex-hull.app -lsfml-graphics -lsfml-window -lsfml-system Graphics.cpp && ./convex-hull.app
