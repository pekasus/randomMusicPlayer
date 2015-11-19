# randomMusicPlayer
Music player that randomly plays songs in root folder.

This respository provides software to randomly play music files such as MP3, AAC, Ogg Vorbis, WMA, MIDI, FLAC, and WAV on an Arduino Uno with an Adafruit VS1053 Breakout Board using the board's library from Adafruit as well as the standard SD library.

There were two methods considered to randomly choose files. The first was to count files, then randomly generate a number and and skip that number of files and play the next. The way that was chosen was to rename the files 1 - (# of files), then convert a random number into a string and play that file. This method was chosen because the SD library requires that filenames are 8 characters or less, and therefore the files would have to be renamed anyway.

This repository also contains a python script that will rename all the files in a folder to be incremental numbers.
