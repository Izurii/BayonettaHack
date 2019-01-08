# BayonettaHack

I'm using Visual Studio 2015 but almost work with Studio 2017. When calling the function "FindPattern" you need to put a cast to "char pointer" (aka->char*) on the mask. 

Example: "FindPattern(startAddress, 6000, (PBYTE)"\x11\x22\x33\x44\x55", __(char*)__"xxxxxx");" ~C-style cast

Example 2: "FindPattern(startAddress, 6000, (PBYTE)"\x11\x22\x33\x44\x55", __const_cast<cast*>("xxxxxx")__);" ~Now is more like c++.


Just inject the dll and use the functions keys to active the cheats.

F1 ~ Unlimited Gold

F2 ~ Unlimited Health

F3 ~ Unlimited Witch Time 

F4 ~ Unlimited Magic

F5 ~ One Hit Kill 

F6 ~ Max Giga/Mega Ton

F7 ~ Infinite Jump

F8 ~ Max All Items (You need to have at least one item to max him <- This doesn't count the compounds needed to make the Lollipops etc) (Now working) (If you don't have the item you want to max, just make him with the compounds and after that activate the cheat again and voila)

F9 ~ Infinite Alfheim Life

F10 ~ Unlimited Alfheim Time

F11 ~ *.*-_-*.*

F12 ~ -_-*.*-_-

P.S: Now you can deactivate the cheats, just press the function key again.

All cheats working perfectly.

Now I just need to work for a message appears on the screen, this beep-beep sound is sickining my ears
