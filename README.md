# osu-king

Osu!-King is a hack tool for video game Osu! https://osu.ppy.sh

First of all with using this hack I climbed rank 5000+ from 200.000.
I guarantee it, no one can determine you are cheater or not.  
But well then I bored of this game and I decided to publish this.

Since I coded this tool for myself, code itself is pretty amateurish.

Osu!-King writed with C++ with using X Window libraries.

# Setup

This code works only for Linux. If you are not familiar with Linux, go back.
We will wine for running osu! in Linux.

Because of audio timing issues, I insist you should install clean a ARCHLinux and install wine with using this guide:
https://blog.thepoon.fr/osuLinuxAudioLatency/ .Writer of this guide should be a god :). 

Before compile and using this cheat tool, you really need to understand code.
I refuse to use any effort for detailed explaination but at least I show how algorithm work.
From that point you are free to change the code for yourself or you can even rewrite code in other languages.


# How this cheat work

1- We require a osu! map which you will play soon. Find the .osu! map file in Songs directory and copy it to cheat directory. This program has no GUI but if you are good with writing GUI you can use zenity for open file dialog.

2- We need to dechipter file. What we really need to get AR, OD, Timings and HitObjects. You should dump Timing and HitObject in a array as I did.

3- What we need now is set up errors. Yes you should predefine all errors. This errors contain: 
    - The random gap between press key and release key. Like 60.000 - 100.000 nanoseconds.
    - The scripted error margin for hit objects:
      ![?](/image.jpg)
      Format: ![Alt Text](url)
