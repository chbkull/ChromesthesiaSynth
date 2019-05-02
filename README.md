# ChromesthesiaSynth

Chromesthesia Synth is an OpenFrameworks application that uses the ofxDatGui and ofxStk libraries to take in a set of images, assign some parameters to those images, then get an instrument to play what that image would sound like.

## Requirements
- OpenFrameworks
- ofxDatGui and ofxStk installed in add-ons
- Visual Studio (developed in VS2017, not tested in XCode or other IDEs)

Note: It is possible that you may need to define the following preprocessor definitions to compile the code on a windows machine:
(under project->properties->c/c++->preprocessor) \_\_WINDOWS\_DS\_\_ and \_\_LITTLE\_ENDIAN\_\_.

You also may need to modify the character set to Not Set (under project->properties->general->character set).

## Usage
When you open up the program, you will see that there are four distinct columns on the screen, representing 4 different tracks. In order to play some sounds, you need to select an image for a track, select an instrument for the track, select a data type to extract, and finally select an order to extract the data in. There is also a volume slider that can be modified to change the volume of the track.

## Tips
Due to how synthesizers in general work, my main piece of advice is simply to keep messing around with it. One instrument that does sound particularly good is the Percussion Flute, especially when paired up with a colorful picture.
