# HorseDbServer

This (horse-themed) two-application project 
was an exercise in network programming with 
sockets. <a href="https://github.com/mkkekkonen/HorseDbClient/tree/master">The client is here.</a>

The server was coded with with C++. 

I framed the messages by using fixed-size 
variables and arrays in both endpoints. I 
also used a buffered file stream to handle 
socket I/O server-side.
