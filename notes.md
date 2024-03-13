# OpenGL

## Shaders
OpenGL doesn't handle shaders as a specific file time - instead it's just a character stream. 
As such, any text file can be loaded as a shader file, the char array is used as the shader object.
Loading this is simple, just load it as you would any text file, store as a char array.
Initially, loading was done through writing to a string and then storing this as a char array.
This feels counter productive, there must be a better way of doing this...
Nope! As far as I can tell, this method makes the most sense! lets keep doing this :)
Or, a small memory save is not to iterate through each line, lets see if it works...
