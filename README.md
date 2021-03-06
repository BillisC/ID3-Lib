# ID3-Lib

This library is made for everyone and is free to use.

## What's an ID3 Tag?
ID3 is a metadata container most often used in conjunction with the MP3 audio file format. It allows information such as the title, artist, album, track number, and other information about the file to be stored in the file itself. There are two unrelated versions of ID3: ID3v1 and ID3v2. *(Wikipedia)*

## What can this library do?
This library is able to read, write and remove data on both ID3v1 and ID3v2. To be more specific:  
- **Reads:** ID3v1, ID3v2.2 (Untested), ID3v2.3, ID3v2.4  
- **Writes:** ID3v1, ID3v2.3, ID3v2.4  
- **Removes:** ID3v1, ID3v2.3, ID3v2.4  

## How to build this library?
In the downloaded project folder run the following:  
```
 $ mkdir build && cd build
 $ cmake .. -G "insert_your_makefile_generator"
 $ cmake ..
 $ make install
```
The generated files can be found under the new `output` folder.  
To include the library in your project simply add the following lines:
```
#include "(path_to_headers)/v1/ID3v1.h"
#include "(path_to_headers)/v2/ID3v2.h"
```
To link the library with your executable add these to the linker's options (the second one is needed for some conversion functions):  
`$ -l id3tag -l ws2_32`

## How to use this library?
### ID3v1
**Class:** ID3v1  
**Parameters:** The song's path as a string  
**Functions:**  
- ```processTags()``` is the main function that must be called before all else. Returns false if file / tag doesn't exist.</br>
- ```set("Tag's name", "Tag's value")``` Adds/Rewrites the specified tag with the value you provide. Parameters have to be strings. Returns false when file / tag / tag  name doesn't exist.  
- ```get("Tag's name")``` Prints the content of the specified tag. Parameter has to be a string. Returns false when file / tag / tag name doesn't exist.  
- ```remove("Tag's name")``` removes the specified tag. Parameter has to be a string. Returns false when file / tag / tag name doesn't exist.  
- ```removeAll()``` removes the whole ID3 tag. Returns false when file / tag doesn't exist.  

The allowed tag names are: **"TITLE"**, **"ARTIST"**, **"ALBUM"**, **"YEAR"**, **"COMMENT"**, **"GENRE"**  
For a full list of genres see this: https://en.wikipedia.org/wiki/ID3#standard (Winamp extensions **not** included yet)  

### ID3v2
**Class:** ID3v2  
**Parameters:** The song's path as a string  
**Functions:**  
- ```processTags()``` is the main function that must be called before all else. Returns false if file / tag doesn't exist or if there is compression detected in the header flags.  
- ```set("Frame's name", "Frame's value")``` sets the specified tag with the value you provide. Parameters have to be strings. Returns false when file / tag / frame doesn't exist.  
- ```get("Frame's name")``` Prints the content of the specified tag. Parameter has to be a string. Returns false when file / tag / frame doesn't exist.  
- ```getImage(imageSize)``` Returns a char pointer to image's raw data. Parameter is an int that's gonna hold the image size once the function finishes. Returns nullptr when file / tag / frame doesn't exist.
- ```remove("Frame's name")``` removes the specified tag. Parameter has to be a string. Returns false when file / tag / frame doesn't exist.  
- ```removeAll()``` removes the whole ID3 tag. Returns false when file / tag doesn't exist.  

The frame names for ID3v2.2 can be found there: https://id3.org/id3v2-00 (Go to 4)  
The frame names for ID3v2.3 can be found there: https://id3.org/id3v2.3.0#Declared_ID3v2_frames  
The frame names for ID3v2.4 can be found there: https://id3.org/id3v2.4.0-frames (Go to 4)  

## Additional Notes
- You can still use the `set()` function even if `processTags()` fails. Doing so will automatically add support for ID3 with the tag you specified. The default version for setting up a new tag (if it doesn't exist) is v2.3 instead of v2.4. To change this behavior add the following to your project: 
```
int ID3v2::_DefaultVersion = 4;
``` 
If a wrong version value is inserted then the default will stay at v2.3.  
- **Important:** If you want to set the picture frame (**"PIC"** / **"APIC"**) then in the content parameter you have to provide the image's path. Also in the `getImage(imageSize)` function it's recommended that you initialize the int with the value `0`;  
- **Important:** The only allowed frames that can be read / set on v2 (for now) are all the Text Information Frames (excluding **"TXXX"** and **"TXX"**), the **"APIC"** / **"PIC"** image frame (through `getImage(imageSize)`), the **"COMM"** / **"COM"** comment frame and all the URL Link Frames (excluding **"WXXX"** and **"WXX"**).  
- The `set("Frame's name", "Frame's value")` function only uses **ISO-8859-1** encoding which means that only **Afrikaans, Basque, Catalan, Danish, Dutch, English, Faeroese, Finnish, French, Galician, German, Icelandic, Irish, Italian, Norwegian, Portuguese, Spanish and Swedish** are supported for writing. However it can read **ISO-8859-1**, **UTF-16** and **UTF-8** so the `get("Frame's name")` function should print the tags correctly no matter the language.  
- This library is recommended to be used only with windows due to the usage of `wchar_t`.  
- This library won't support unsynchronization as it's no longer needed.  
