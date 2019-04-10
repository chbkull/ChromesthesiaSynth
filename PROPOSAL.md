# Final Project Proposal: Modular Image Synthesizer
For my final project, I am going to create an application that will allow a user to create music simply by feeding the program images.
The goal is to mimic a physical modular synthesizer, except that image pixel data can now be used as an input for modules.
Modular synthesizers are not exactly well-known, so it is a good idea to explain what that is first before going further.

## What is a modular synthesizer?

[This is a very good video on the topic](https://youtu.be/oFadopWxKjw?t=139) but I'll try to explain some of it myself.

Within a modular synth, the various modules are passing around two different sources of information: audio, and control voltage (CV).
Passing audio into a module will return a modified version of the audio (perhaps changing the speed, volume, clarity, etc.). Think of a module as a function, with the audio as the input and output.
What CV does is it changes the severity of the function, so for example sending a lot of CV into a module that modifies the speed of some audio will speed it up a lot, but sending very little CV into it will slow the audio down immensely. 
What makes modular synths powerful is that various modules can be daisy-chained together to modify not only the audio, but also the CV can be manipulated by various modules, such as a CV randomiser can lead to chaotic results.
A musician uses patch cables to connect various modules together, sending the outputs from one module into the input of another, and when you start getting a lot of modules in your system, the combinations are near endless. Though the rack itself may look like a rat's nest , it can produce some amazing music ([Clair De Lune- modular](https://youtu.be/8WDNgfnZ3HM)) 
No session at a modular synthesizer will be exactly the same (unless of course you write down all the connections you made, but where is the fun in that).

## Changing things up

So my program will try and match the functionally of a regular modular synth in a virtual space, but with one important twist: image data is now a valid input for all modules. In other words, images can be used as a substitute for audio (generating a melody), or as a substitute for CV. The user will be able to specify what information they will pull from an image, such as the brightness of each pixel, its color, the image's size, etc, and then feed said information into the synth. The end goal will be a program that can generate a piece of music based on a set of images and the user directing the program on how to use said images. In a sense this would be a manifestation of [synesthesia](https://en.wikipedia.org/wiki/Synesthesia), but instead of a person seeing color when they hear sound, the reverse will occur- the person can hear what an image sounds like. 

## What will be used in the project

The primary library that will be used for this project is the ofSound library, specifically ofSoundPlayer is being used, but ofSoundBuffer will also be used to provide more control over the manipulation of a sound. The other library being used is ofImage and everything built off of it (such as ofPixels) will be used to handle image processing and interpretation. If possible I would like to use the [Synthesis ToolKit](https://ccrma.stanford.edu/software/stk/index.html) as well, but I am still working on figuring out if it is compatible with OpenFrameworks. Aside from the actual libraries, I will likely store a set of preloaded audio samples to allow the user to mess with (piano, guitar, other instruments, maybe even sound effects), and if possible allow the user to provide their own .wav files to manipulate as well.

## What will need to be accomplished
The bulk of the task will be designing a modular system that can be built however the user pleases. From a design standpoint, this will likely involve an overarching module class, and then children classes that are the specific modules themselves. The modules will need to be standardized- all have flexible input/output types - but internally have different functions from one another. From a GUI standpoint, ideally the user can place down a module and then click between an input and an output to connect them together via a patch-cable. If this proves too difficult, the modules may be fixed in place. The other major component will be turning image information into readable data for the modules, and again, allowing the user to pick how each image is interpretted. 
