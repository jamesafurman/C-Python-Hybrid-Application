# Cpp-Portfolio-Project

### Summarize the project and what problem it was solving.

CornerGrocerTracking is designed to help a grocery store track and analyze daily item purchases by reading in a list of items purchased and printing various representations of purchases per item.

### What did you do particularly well?

I kept main() concise, implemented an extensible interface class for Python code integration, and documented the program clearly and thoroughly. 

### Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?

The program could be slightly more efficient by adding a couple of string pointers in Source.cpp and adding overloads to the CallIntFunc member function of PyInterface.cpp (detailed in Source.cpp's lead comments). 

Additionally, the UserMenu class module implements a linked list that is unnecessary and mildly inefficient in this use case; I took the time making it to practice implementing a linked list. 

### Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?

The most difficult portion to deal with was the PyInterface class, as it dealt with entirely separate libraries from the material we had been working with. Guido van Rossum's documentation on "Extending and Embedding the Python Interpreter" (linked below) was immensely helpful for learning the functions and broadening the application of the code provided for this project. 

van Rossum, 1998: http://web.mit.edu/people/amliu/vrut/python/ext/ext.html

Implementing a pointer linked list was also challenging since this was my first time doing so from scratch. The challenge was simply overcome by reviewing and cross-referencing my code and our learning material, and making fixes until functionality occurred.

I will be using syntax checkers to look for code errors. A Python synax checker was especially  helpful in debugging my integrated Python code, since error message printing is iffy in embedded Python.

### What skills from this project will be particularly transferable to other projects or course work?

Integrating multiple programming languages was valuable. More than learning the specific syntax for embedding Python into C++, starting to get to grips with the concepts of embedding one language's compiler (or interpreter) into a program in another language was useful and I expect it to be applicable going forward. 

I regret not using the project as an opportunity to develop test harnesses for my classes; that would have been a valuable skill to practice, and one that I haven't yet practiced in an organic, open-ended scenario like this. It's a missed opportunity, and I may take time in the upcoming winter break to go back and do that if I'm able. 

I believe the most important skill that I practiced in this project is the ability to independently research and implement code design according to a project's specifications without hand-holding from educational material, as I did in the PyInterface class. 

### How did you make this program maintainable, readable, and adaptable?

Inserting comments in Javadoc style, which makes them compatible with multiple C++ API tools,  lends to the readability of the program. Otherwise, I made it readable through its conceptual design, which fairly intuitively structures it along object-oriented principles. 

Its readability lends to its maintainability. Further, the program's modularity allows functionality to be easily updated, modified, or added. GUI implementation, addition of a password system, or addition of analytical or data visualization functions are examples of ways this program could be extended. 

It is also adaptable in parts. The PyInterface class can be reused and extended in any usecase that involves embedding Python in C++, and I plan to save it for future use. The UserMenu and MenuItem classes serve as a generic linked list skeleton, and I also would be unsurprised to reuse them in
the future. Source.cpp (which is the main() file), and the GrocerMenuFuncs class are both usecase specific, so neither is likely adaptable for other uses, but again, they can be modified to adapt this program to demands for other functionality. 
