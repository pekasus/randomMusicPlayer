// File Renamer
// By: pekasus
// CC by 3.0

// This program will rename all files that end in .mp3 within a folder.

import os

songlist = "songlist.txt"
i = 1

with open(songlist, 'w') as fout:
    fout.write("Legend of Songs\n\n");
    fout.close()

for filename in os.listdir('/Volumes/musbox'):
    if filename.lower().endswith(".mp3"):

        with open(songlist, 'a') as fout:
            fout.write( str(i) + ".  ")
            fout.write(filename + "\n")
            fout.close
        print str(i) + ":  " + filename

        newfilename = str(i) + ".mp3"
#        print filename + " / " + newfilename
        os.rename(filename, newfilename)

        i += 1



print (os.path.dirname(os.path.abspath(__file__)))
