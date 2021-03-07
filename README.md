# HackCU---007
Hack that will be submitted to the HackCU - 007 (2021) hackathon for the beginner track. I will be working on my own to create the hack.

The hack was decided to be a slot machine that the user was able to play and test their luck! Inspiration came from my favorite 007 movie - Casino Royale.
I implemented the hack in VS Code using C++. I was hoping to learn how to create a GUI to make the hack more appealing to the user, however I was unable to find
sufficient resources to implement this aspect during the hackathon.

The slot machine first prompts the user to input how much money they currently have. This will be their running amount and once this is all lost the machine auto exits.
The machine then prompts the user for how much money they wish to "risk" on the current roll. This will be used to determine the amount won/lost in some cases. If there is not a 
match then the user losses the money they risked, but if they get a match then they gain what they risked plus bonus depending on the type of match they got.
The machine then asks if they want to play again, thus only exiting when all of their money is lost or they say "no" to this play again request.
