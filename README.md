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

1- We require a osu! map which you will play soon. Find the .osu! map file in Songs directory and copy it to cheat directory. In my code I also rename it to "hard.osu". This program has no GUI but if you are good with writing GUI you can use zenity for open file dialog.

2- We need to dechipter file. What we really need to get AR, OD, Timings and HitObjects. You should dump Timing and HitObject in a array as I did.

3- What we need now is set up errors. Yes you should predefine all errors. This errors contain: 
    A) The random gap between press key and release key. Like 60.000 - 100.000 nanoseconds.
    B) The scripted error margin for hit objects:
        ![?](/image.jpg)
        - As you can think OD line in percent. We need a create script that defines which object hit where in OD line.
        - If we create script like: {0, 15, 20, 50, 75, 100}:
            1st object hit Orange; 2nd, 3rd object hit green; 4th object hit blue; 5th oject hit green and last object hit orange. With this script you get %80ish accurity. Of course you should create this script more intellegently. In my code I create %100, %99.5, %99, %98.5, %98 scripts. Also add some random glimpse in the numbers. So you wont get excatly what you played before while you get the wanted accurity. The script should have 60-70 elements. 
            
4- Now this cheat tool wait a trigger.
    - In my code when I dechipter osu! file I also get first object X and Y.
    - When I pressed a "Z" key in black screen when map about start (deleted backgrounds), cheat detects it with using X Window Library and scan countinously the 50x50 area of the where first object should be. (opencv)
    - When cheat detect anything not black in the area, cheat start a countdown. This countdown is AR hide time. For exapmle when AR is 10, countdown wait 450.000 nano second.
    
5- After countdown ends, keyboard simulations starts.
    - Now a timer starts.
    - Remember we get objects times and timings.
    
    - Loop starts: 
        - When timer hits a (hit object time - Orange OD ) apllies related scripted error time. Use (HitObject%Script Element).
        - With using XWindow key emulate event it press Z or X key. In my code if hitobject near next one it press X.
        - While pressing event happen, press time error apllies.
        - In my code I added NumLock for break character. When NumLock state is OFF, simualation done.
      
    - Calculating the slider duratiton bit hard. Maybe you just copy how I do it :).
    
# Afterwords
    As i mentioned you cannot use this code in this state, it needs to be matured or it needs 
    Of course you still handle mouse by yourself :).
    IF you able to create more psudeo-randomized script, this cheat cannot be detected by humans or mahcines or maybe even AI. (Imagine Peppy spends millions of dollars to AI for only cathing cheaters) 
    And you need to get low audio latency. Follow The PooN's guide no matter what.
    Also run cheat in sudo for reading keyboard.
    Spare me Peppy, I do not have even osu! anymore. If I remember later for writing this thing, I install osu and upload my replay vidoes.
   
    

    
            
      
