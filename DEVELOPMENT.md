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
