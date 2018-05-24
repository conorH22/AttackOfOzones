# Build Notes

## Dependencies: 
Cocos2d-x v14, JDK/SDK1.6+, Keytool, Android command-line tools, NDK r13b, Eclipse Android Development Tools,  Apache Ant and Python 2.7.13

## Instructions:

- To test if cocos is installed correctly type the following command 
```
cocos -v 
```

- To compile Attackofozones in debug mode, run the following command in cmd in the project folder.
```
cocos compile-p android –-ap android-23
```
- To compile  Attackofozones in release mode, run the following command:
```
cocos compile . -p android -m release --ap android-23
```
or 
```
cocos compile -q -s ~/attackofozones -p android --ap android-23 -m release -o ~/attackofozones/bin
```

- To run Atackofozones in debug mode, run the following command:
```
cocos run -s ~/attackofozones -p android

```

- To deploy Atackofozones, run the following command:
```
cocos deploy -s ~/attackofozones -p android -m release
```


For more information please see the following [link](http://cocos2d-x.org/docs/cocos2d-x/en/editors_and_tools/cocosCLTool.html)

## Problems during development:

The first issue was the Android  command line tools option for cocos2d-x developers was deprecated by Google which led to problems using cocos commands that was used on the Android.

The problem was solved by reverting to old version of android studio which was android-studio-bundle-145.3537739-windows. The latest version of android studio was uninstalled and old version was installed.  The rollback android studio version was installed before the update had occurred after researching the issue.

The next issue was lack documentation by cocos to create a release version of cocos2d-x game. Using the command Cocos compile -p android -–ap android-23 -m release command lead to issues.  The solution was found by compiling the debug version through command prompt, then importing the attack of Ozones game to eclipse IDE, along with libscocos2d-x library then generating a release version of the game with signed apk as google play store only accepts signed apk.

To sign the apk, the developer had to generate two security keys using the keytool exe, provided in the jdk/bin/keytool. The AttackOfOzone. keystore file was used in singing the apk

The next issue was the accelerometer controls during the alpha and beta.

When testing the game on the play store, Certain devices didn’t work with the tilt controls to move the player spaceship to avoid the enemies. The spaceship would render in the middle of the screen then move up to the top of the screen.  This issue was tested on physical devices from selected testers, the phones were the controls didn’t work was Samsung s7 edge, Asus zenfone max, the controls worked on moto g4 plus, Samsung s5 x2 and HTC m7 phones. The issue still needs more testing
