# Development Log
## 4/7
Starting on the final project, image synth idea already in mind.

Starting playing with ofSoundPlayer, trying to create a keyboard based on [this video](https://www.youtube.com/watch?v=BWMuQzDA_7U)

End up grabbing a random music sample of note C4, and using [piano frequency tuning](http://pages.mtu.edu/~suits/notefreqs.html) built an octave of a piano.

## 4/8
Want to see about integrating image processing for a demo for code review.

At first attempted to use ofxOpenCV, but was then told to shift to ofxCV, the modern equivalent.

After a bunch of flailing around with the two different libaries, I am unable to get ofxCV to load correctly due to a missing file error.

Still no luck figuring out ofxCV. Will try again tomorrow.

## 4/9
After doing some more searching on the topic, I realized that OpenFrameworks has an example on image loading.

Turns out that OpenFrameworks has an ofImage class that can be used to load an image and grab information on it. ofxCV/ofxOpenCV is overkill, so I will not be using them, at least for the moment.

After sending in a basic 16x16 image (a minecraft item texture), I am able to correctly grab the brightness of each pixel after following the example in OpenFrameworks.

Mapped the brightness to a 10 note scale via brightness mod 10, the image now plays sound. It isn't extremely musical, but it is a start.

## 4/13
Found that the [Synthesis Toolkit](https://ccrma.stanford.edu/software/stk/index.html) has an official [open frameworks plugin](https://github.com/Ahbee/ofxStk). Going to see if I can get it to work.

After messing around with it for about a half hour, unable to get it to compile. I'll try to play with it a bit more, if not I am going to explore other sound libraries on open frameworks and see if I can get any others to work.

At least for the example demos, the culprit seems to be that the projects were made for XCode, and not for VS2017.

## 4/15
Moved back to the base STK library. Want to see if I can get anything resembling music to play.

Update: Was successfully able to get an electric guitar from the examples compiled and playing. Going to see if I can make my own example now.

Also tested the electric guitar program with a midi keyboard, and was also able to get that to play.

## 4/16
After a lot of Googling around and struggling with STK, I was finally able to accomplish the equivalent of Hello World (in this case, Hello Sine) using the raw STK library. The next thing to figure out is live playback. If I can accomplish that, then I can finally start moving putting actual code into this repository and get something basic up and running.

Update after a few hours: after doing some major digging in the source code of the ofxSTK library, I noticed a key difference between it and the STK library itself: for some reason my system was not being recognized as a windows system (__\_\_WINDOWS_DS\_\___). By some miracle I happened to stumble across [this issue post](https://github.com/TonicAudio/Tonic/issues/265) about a different sound library, where they added two things to pre-processor definitions (__\_\_WINDOWS_DS\_\___ and __WIN32__). Upon adding that, the framework now successfully compiles, and I am able to press a key and play a sound via ofxStk. Sweet victory.

For some reason asiolist.cpp/asiolist.h were not complying, so for the time being I ended up removing them and now the project works as is.

Project is now names ChromesthesiaSynth, and first code push is through.