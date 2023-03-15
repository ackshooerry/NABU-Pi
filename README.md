# NABU-Pi
Pi Spigot Algorithm for NABU PC, written in C, along with some screen drawing stuff
* main.c contains the code; it's pretty well documented, I think.
* main.bat is used by z88dk to compile the file and make it available to the NABU via DJ Sures' NABU Internet Adapter Software, as described on his website: https://nabu.ca/homebrew-c-tutorial
The Excel file shows how I created the data arrays used in main.c to draw the picture. To reiterate, though, I haven't implemented anything having to do with color here. Instead, I am just populating cells with 0/1 (indicators) and then assigning random colors to the "yes" pixels in C.
Thanks.
