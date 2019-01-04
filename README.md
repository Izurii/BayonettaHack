# BayonettaHack

I'm using Visual Studio 2015 but almost work with Studio 2017. When calling the function "FindPattern" you need to put a cast to "char pointer" (aka->char*) on the mask. 

Example: "FindPattern(startAddress, 6000, (PBYTE)"\x11\x22\x33\x44\x55", __(char*)__"xxxxxx");" ~C-style cast

Example 2: "FindPattern(startAddress, 6000, (PBYTE)"\x11\x22\x33\x44\x55", __const_cast<cast*>("xxxxxx")__);" ~Now is more like c++.


Just inject the dll and use the functions keys to active the cheats.

F1 ~ Unlimited Gold (Now working!!!)

F2 ~ Unlimited Health (Working too!!)

F3 ~ Unlimited Witch Time (working)

F4 ~ Unlimited Magic (Apparently working flawlessly)

F5 ~ One Hit Kill (Worki...)

F6 ~ Max Giga/Mega Ton (Yes, it's working.)

F7 ~ Infinite Jump (You already know. <- working)

F8 ~ Max All Items (You need to have at least one item to max him <- This doesn't count the compounds needed to make the Lollipops etc) (Not workin...)

F9 ~ Infinite Alfheim Life (Not today bro)

F10 ~ Unlimited Alfheim Time (...)

F11 ~ *.*-_-*.*

F12 ~ -_-*.*-_-

P.S: Now you can deactivate the cheats, just press the function key again.
