# Development Log
## 4/7
Starting on the final project, image synth idea already in mind.

Starting playing with ofSoundPlayer, trying to create a keyboard based on [this video](https://www.youtube.com/watch?v=BWMuQzDA_7U)

End up grabbing a random music sample of note C4, and using [piano frequency tuning](http://pages.mtu.edu/~suits/notefreqs.html) built an octave of a piano.

## 4/8
Want to see about integrating image processing for a demo for code review.

At first attempted to use ofxOpenCV, but was then told to shift to ofxCV, the modern equivalent.

After a bunch of flailing around with the two different libaries, I am unable to get ofxCV to load correctly due to a missing file error.

Still no luck figuring out ofxCV. 
Will try again tomorrow.

## 4/9
After doing some more searching on the topic, I realized that OpenFrameworks has an example on image loading.

Turns out that OpenFrameworks has an ofImage class that can be used to load an image and grab information on it. 
ofxCV/ofxOpenCV is overkill, so I will not be using them, at least for the moment.

After sending in a basic 16x16 image, I am able to correctly grab the brightness of each pixel after following the example in OpenFrameworks.

Mapped the brightness to a 10 note scale via brightness mod 10, the image now plays sound. 
It isn't extremely musical, but it is a start.

## 4/13
Found that the [Synthesis Toolkit](https://ccrma.stanford.edu/software/stk/index.html) has an official [open frameworks plugin](https://github.com/Ahbee/ofxStk). 
Going to see if I can get it to work.

After messing around with it for about a half hour, unable to get it to compile. 
I'll try to play with it a bit more, if not I am going to explore other sound libraries on open frameworks and see if I can get any others to work.

At least for the example demos, the culprit seems to be that the projects were made for XCode, and not for VS2017.

## 4/15
Moved back to the base STK library. Want to see if I can get anything resembling music to play.

Update: Was successfully able to get an electric guitar from the examples compiled and playing. Going to see if I can make my own example now.

Also tested the electric guitar program with a midi keyboard, and was also able to get that to play.

## 4/16
After a lot of Googling around and struggling with STK, I was finally able to accomplish the equivalent of Hello World (in this case, Hello Sine) using the raw STK library. The next thing to figure out is live playback. If I can accomplish that, then I can finally start moving putting actual code into this repository and get something basic up and running.

Update after a few hours: after doing some major digging in the source code of the ofxSTK library, I noticed a key difference between it and the STK library itself: for some reason my system was not being recognized as a windows system (__\_\_WINDOWS_DS\_\___). 
By some miracle I happened to stumble across [this issue post](https://github.com/TonicAudio/Tonic/issues/265) about a different sound library, where they added it to pre-processor definitions. 
Upon adding that, the framework now successfully compiles, and I am able to press a key and play a sound via ofxStk. 
Sweet victory.

For some reason asiolist.cpp/asiolist.h were not complying, so for the time being I ended up removing them and now the project works as is.

Project is now named ChromesthesiaSynth, and first code push is through.
The app now plays a sinewave through ofxStk when the 'a' key is pressed.

## 4/22
Goal for Code Review : have a single 'track' set up with the following progression: image -> data -> order -> instrument -> media
- image: Use file explorer to select an image on your computer, then display it in the GUI after it is selected
- data: What type of image data we want to feed our instrument (brightness, RGB values, etc.)
- order: In what order to use the aformentioned data (random, left to right, top to bottom, upscale to 16x16, etc.)
- instrument: Drop down menu of which instrument you want to play the data through
- media: Pause/play key, maybe a mute key.

Image loading via ofSystemLoadDialog is fairly straightfoward. Will need to implement file checking (to make sure an image is passed in), but will do so later.

Decided to add ofxDatGui to my project to help facilitate building the gui.

To cut down on my includes in ofApp.h, I want to include ofxStk.h (which has all of the #includes in it), but for some reason there is an error with SKINItbl.h so it is commented out for the time being.

There is a circular dependency with SKINItbl.h- it is already included in Skini.cpp.

ofxDatGuiTimeGraph.h had a problem identifying PI (might have to do with ofxStk also declaring pi?) so it was manually coded in to fix it.

## 4/23
Track class created, with some basic methods. Working on framing out the class structure on paper first.

DataExtracter class created, with the purpose of taking in an image and extracting out the requested pixel information to feed into an instrument. Produces a 2D array of floats.

Filtering in DataExtracter now works: red/green/blue. Going to try and integrate with a dropdown menu now.

Dropdown menu selection is now converted into the PixelData enum, and will correctly print the pixel data based on a dropdown menu.

Second dropdown menu for the ordering of the data added, and the two selection types now correctly return a vector of floats. Next goal is to convert those floats into a SKINI file.

Track class now integrates data_extracter and now writes to a SKINI file.

Project now internally plays music from a generated score. This is a huge breakthrough.