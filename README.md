# FeatherPal
Simple Bot for mobile game Fire Emblem Heroes

This git includes only source code of the program, for it to work you also need to have catalog named "adb" next to your executable, and inside of it files named "adb.exe", "AdbWinApi.dll" and "AdbWinUsbApi.dll", you can get them from Android SDK or compile them yourself from the sources on Android Open Source Project.

Additionally you need to have debugging over USB enabled.

To farm any implemented mode (in version 1. its Rival domains - lunatic), open your game, go to the coresponding mode screen (the one where you pick difficulty), start the program, it will automatically farm for you and loop untill you write 0 and press enter (yes, its interactive !, woah, the power of using threads), then it will finish the current loop and close.
For best results its adviced you setup your team for fast clear, there are new guides every week posted by helpful people, most clears take around 15 seconds. If your clear takes more time you can recompile the code with changed value of waiting times, or you can just wait, nothing should break, it will just use 2 loops instead of 1 to clear the rd, wasting some time in the process.
