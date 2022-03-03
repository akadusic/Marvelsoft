BASIC DEVELOPMENT AND RUNTIME ENVIRONMENT SPECIFICATIONS
 - compiled on gcc compiler, version v11.2.0
 - build system Cmake version v3.18.4
 - code written in Neovim IDE version v0.4.4
 - operating system Linux Ubuntu 21.04

REQUIREMENTS FOR STARTING APPLICATION
 - gcc compiler version above or equal...
 - Boost library installed https://www.boost.org/users/download/
 - Cmake version above 3.0.0 https://cmake.org/download/

STEPS FOR RUN APPLICATION
 - open Marvelsoft folder in terminal
 - go to build folder
 - type "cmake .." and hit the enter button
 - type "make" and hit the enter buton
 - type "./OrderBook" and hit the enter button
 - after that application should start

WHAT IS OUTPUT FROM APPLICATION
 - in "build" folder you can find output txt files with intentions for every instrument and json files with for every instrument

WHAT WAS MY LOGIC DURING SOLVING OF PROBLEM
 - I made class columnInTable which is abstract class and it represent columns in table of Order Book. But column in table can be bid or ask
   so I also made two classes BID and ASK which inherits columnInTable class. Classess BID and ASK have same properties but they have different
   behaviour and different meaning.
 - After that, a few days I observed how to handle a big input.json file and came to idea to consider every row in input.json as one object.
   They can be, obviously, book or trade, so I create two more classess, BOOK class and TRADE class.
 - The next problem was how to take them all into one container but I had to keep order of occurrence because this was really important for next steps.
   And here I used any boost library and put them all into one vector of any's.
 - The next step was to take this vector of any's, go through it and take all records with same symol property. On this way I separate 
   input.json files into vectors of any's with same symbol. This was big step for me.
 - Next, I realize that I have four possible scenarios in input.json file. So, we can have book after book, trade after book, book after trade
   and trade after trade in json file. I observed every of these four situations and realized what is happening. You can find these steps in 
   mainLogicFunction in app.
 - And when I finished with observing possible solutions I ofstream convenient message into txt file.

During resolving of this problem I use a lot of for loops, vector containers, and tehnical stuffs which are familiar to me. I was on safe 
soil with these things and on this way I was sure that I don't have memory leaks, segmentation faults and thins like that. Sure, it is 
possible to optimize this application and do some more improvement. I had a few more ideas to solve this problem but I didn't have enought
time for experimenting.
And the most important thing for me, and I belive for you also is that I wrote every line of code alone, with help of Google and book which
I attached with other stuffs.
