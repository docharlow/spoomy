
Debian
====================
This directory contains files used to package zumyd/spoomy-qt
for Debian-based Linux systems. If you compile zumyd/spoomy-qt yourself, there are some useful files here.

## spoomy: URI support ##


spoomy-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install spoomy-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your spoomy-qt binary to `/usr/bin`
and the `../../share/pixmaps/zumy128.png` to `/usr/share/pixmaps`

spoomy-qt.protocol (KDE)

