# Heroes and Villains Challenge

"""_Heroes and Villains_ is a teambuilding exercise whereby players
each randomly (secretly) select a hero and a villain from among
the other players. Traditionally, each player then tries to
simulteaneously get as far as possible from their chosen
villain while getting as close as possible to their hero. However,
in our variant, we don't really care too much about distance. No,
see, in our variant, you have to line up your hero in between your
villain and yourself.

Now obviously, you can't move your hero or villain; you can only
move yourself. Therefore, the only way to line up your hero in
between yourself and your villain is to find the line between your
hero and villain, then to get yourself onto or near said line on
the side of your hero."""  
A project a friend gave me.  the names hero and villain are arbitrary. Pretty fun
challenge given the contraints and the strictly C implementation.
The inherent chaos in the problem made the debugging a bit difficult!

python dependencies are limited to strictly matplotlib.pyplot.
Each iteration of the game creates a new .txt file containing all
locations for visualizing the simulation

argparse will interface with the terminal for the dimensions
and the number of iterations. the last paramter is 1 for skipping
iterations by 100. 0 for visualizing every clock cycle

lhubbard@pdx.edu
