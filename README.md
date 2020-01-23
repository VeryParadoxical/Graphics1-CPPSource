# Graphics1-CPPSource
 This contains the source code for my graphics API produced as part of my Graphics 1 module at University. 

The compiledrelease folder contains an executable and model file that can be run to see the result of the base source code. 
The following files are not authored by myself: 
Matrix.cpp, Matrix.h, Framework.h, Framework.cpp, MD2Loader.h, MD2Loader.cpp, Bitmap.h, Bitmap.cpp.
All other work is my own unless explicity noted otherwise. 

It is worth noting that this code was written rather rapidly under a deadline and such there are certain things I did that I am not proud of. For example, under the Render method within the Rasteriser.cpp file there is a solid amount of code duplication as I wrote the state management code for display purposes. At the time of writing I was more concerned about the speed of production over code quality as I factored in that this could would have very limited usage and would not be shipped commerically so maximum performance and memory efficiency. Therefore, I ask that when judging code quality I humbly request that you understand that some decisions I have made here would not have been made under different circumstances such as those where code would cause technical debt or otherwise be in-efficient. 
