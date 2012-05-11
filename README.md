wifi-keep-alive
===============

A little something I'm trying to fix a peculiar connection problem with.

As of right now, this only keeps track of stdin and outputs to the console. I have the easy part done; next up is using the Win32 API for the first time.

Usage: `ping -t somesite.com | wifi-keep-alive.exe`