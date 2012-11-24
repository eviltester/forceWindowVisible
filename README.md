Force Window Visible
=====================

Force Window Visible is a small support tool to allow you to display any window on screen, even if it would normally restore off the screen.  Derived from sHideWin, by Romain Vallet

Force Window Visible is a small support tool to allow you to display any window on screen, even if it would normally restore off the screen.

Derived from [sHideWin](http://wistinga.online.fr/shidewin/), by [Romain Vallet](http://wistinga.sourceforge.net/) this utility is completely free and licenced under the GNU General Public License.

Released (v1.1 20/12/2005)

ForceWindowVisible is as simple to use as the [sHideWin](http://wistinga.online.fr/shidewin/) program it is derived from.

- Simply start the application and it will display a list of all the windows available to the system.
- The windows which are visible are selected in the list.
- To hide a window, click on one of the listed windows which are selected.
- To show a window, click on one of the listed windows which are not selected.

ForceWindowVisible is different from the [sHideWin](http://wistinga.online.fr/shidewin/) program in one major way; when you click on a window to display it, it will be displayed in the top left of the screen. The window size will remain the same unless it is bigger than the screen (in which case it will be shrunk to the size of the screen) or you press shift (in which case it will be 300x300 pixels in size).

Why?, well [sHideWin](http://wistinga.online.fr/shidewin/) (and [Processs Explorer](http://technet.microsoft.com/en-us/sysinternals/bb896653.aspx)) does a great job of hiding and displaying windows, but not if they are off the screen.

Having windows off the screen is a [common problem](http://blogs.msdn.com/b/oldnewthing/archive/2005/03/14/395271.aspx) and I encounter it when I move my laptop from a multi-monitor setup to stand alone mode. Some applications just insist on starting up off the screen.

That is why I made this little variant on [Romain Vallet](http://wistinga.sourceforge.net/)'s [sHideWin](http://wistinga.online.fr/shidewin/). All I did was add some extra code, remove some of the prettiness and recompile under [bloodshed DevC++](http://www.bloodshed.net/devcpp.html).

This has been useful for me, hopefully it will be useful for you. Feel free to hack and extend it, and pass on any changes to Romain

