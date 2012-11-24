                  ====================
                  Force Window Visible
                  ====================

ForceWindowVisible is an amendment to SHideWin.

All I did was add some code to change the position of the window
so that it appears on screen at 0,0
- if you display a window with the SHIFT key pressed the window size will be 300x300 pixels
- otherwise it will use the size of the window,
- unless, the window is bigger than the desktop  in which case it will be resized to fit the desktop

Use ForceWindowVisible when the window is off the screen and download and use ShideWin
for all your other show/hide needs.

Amendments Coded by: Alan Richardson, Compendium Developments, 2005 - alan@compendiumdev.co.uk

ForceWindowVisible was compiled using bloodshed DevC++ (http://www.bloodshed.net/devcpp.html)

I had to remove the code for tooltips and for the pretty fonts. Sorry but ForceWindowVisible was
produced for one purpose - to get windows off the screen back on the screen.

The rest of this document is the original help text that came with shideWin.

Enjoy, and many thanks to Romain for release shideWin under the GNU license.

----------------------------------------------------------------------------

                  ===================================
                  ShideWin - Show / Hide your windows
                  ===================================

                Copyright (C) 2002-2005  Romain VALLET


Introduction
============
ShideWin enumerates all top-level windows and allows you to show or hide them.

It can help you get back windows that were made invisible for some reason:
  - Your multiple virtual desktop software crashed
  - The window is only accessible via the system tray and the icon disappeared
    (when explorer.exe is killed for instance)
  - You've hidden it with ShideWin ;)

It can also be interesting to see what windows are actually in your desktop 
environment without you even being aware of it.


How to use ShideWin
==================
When launched, ShideWin fills a listbox with the captions of all top-level 
windows. If a caption can't be found, then the window's handle is used.
Selected items are the visible windows.

You can show or hide a window by selecting/deselecting an item.
To do this, you can:
  - Click on the item
  - Use the Space key. Use the Up and Down keys to navigate through the items.

If you leave the mouse cursor on an item, a tooltip box will show some
information on the window (position and size).

Use the F5 key to refresh the list.

Use the Esc key to exit the program.


License
=======
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

See the GNU General Public License details in copying.txt.


About
=====
ShideWin was written in C++ using the SciTE editor
  http://www.scintilla.org/SciTE.html

It was compiled with Microsoft Visual C++ Toolkit 2003
  http://msdn.microsoft.com/visualc/vctoolkit2003/

The Microsoft Platform SDK was used for the Win32 libraries
  http://www.microsoft.com/msdownload/platformsdk/sdkupdate/
  
This program was written with raw Win32 functions.
As a result, ShideWin is quite small and fast, though it took some hard work 
just to have that ugly minimalist interface ;)


Contact
=======
Romain VALLET
e-mail:  romain.vallet@gmail.com
web:     http://wistinga.sourceforge.net/shidewin/




