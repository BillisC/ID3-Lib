# ID3-Lib

This library is made for everyone and is free to use.

## What's an ID3 Tag?
ID3 is a metadata container most often used in conjunction with the MP3 audio file format. It allows information such as the title, artist, album, track number, and other information about the file to be stored in the file itself. There are two unrelated versions of ID3: ID3v1 and ID3v2. *(Wikipedia)*

## What can this library do?
This library is able to read, write and remove data on both ID3v1 and ID3v2. To be more specific:  
  -> **Reads:** ID3v1, ID3v2.2(Untested), ID3v2.3, ID3v2.4  
  -> **Writes:** ID3v1, ID3v2.3, ID3v2.4  
  -> **Removes:** ID3v1, ID3v2.3, ID3v2.4  

## How to build this library?
In the downloaded project folder run the following:  
```
 $ mkdir build && cd build
 $ cmake ..
 $ cmake --build ..
```
After that copy `libid3tag.a` and the `header files under include/` to your lib and include folders.  
The header files that should be included in your project are: `ID3v1.h` and `ID3v2.h`  
To use the library in your executable add these to the linker options (the second one is needed for some conversion functions):  
`$ -l id3tag -l ws2_32`

## How to use this library?
### ID3v1
**Class:** ID3v1  
**Parameters:** The song's path as a string  
**Functions:**   
- ```processTags()``` is the main function that must be called before all else. Returns false if file / tag doesn't exist.</br>
- ```set(Tag's name, Content you want to write)``` Adds/Rewrites the specified tag with the content you provide. Parameters have to be strings. Returns false when file / tag / tag  name doesn't exist.  
- ```read(Tag's name)``` returns a string with the content of the specified tag. Parameter has to be a string. Returns error string when file / tag / tag name doesn't exist.  
- ```remove(Tag's name)``` removes the specified tag. Parameter has to be a string. Returns false when file / tag / tag name doesn't exist.  
- ```removeAll()``` removes the whole ID3 tag. Returns false when file / tag doesn't exist.  

The allowed tag names are: TITLE, ARTIST, ALBUM, YEAR, COMMENT, GENRE  
For a list of genres check this: https://en.wikipedia.org/wiki/ID3#standard (Winamp **not** included)  

### ID3v2
**Class:** ID3v2  
**Parameters:** The song's path as a string  
**Functions:**  
- ```processTags()``` is the main function that must be called before all else. Returns false if file / tag doesn't exist or if there is compression detected in the header flags.  
- ```set(Frame's name, Content you want to write)``` sets the specified tag with the content you provide. Parameters have to be strings. Returns false when file / tag / frame doesn't exist.  
- ```read(Frame's name)``` returns a string with the content of the specified tag. Parameter has to be a string. Returns error string when file / tag / frame doesn't exist.  
- ```remove(Frame's name)``` removes the specified tag. Parameter has to be a string. Returns false when file / tag / frame doesn't exist.  
- ```removeAll()``` removes the whole ID3 tag. Returns false when file / tag doesn't exist.  

The frame names for ID3v2.2 can be found there: https://id3.org/id3v2-00 (Go to 4)  
The frame names for ID3v2.3 can be found there: https://id3.org/id3v2.3.0#Declared_ID3v2_frames  
The frame names for ID3v2.4 can be found there: https://id3.org/id3v2.4.0-frames (Go to 4)  

## Additional Notes
- You can still use the set() function even if processTags() fails. Doing so will automatically add support for ID3 with the tag you specified. The default version for setting up a new tag (if it doesn't exist) is v2.3 instead of v2.4. To change this behavior set the following static to 4: **int ID3v2::_DefaultVersion = 4;** If a wrong version value is inserted then the default will stay at v2.3.  
- **Important:** If you want to set the picture frame in ID3v2("PIC" for v2.2 and "APIC" for v2.3/v2.4) then in the content parameter you have to provide the image's path.
Also in the read() function the returned string is just raw image data. You can convert them to a char and then write them in a file to make them usable if your only purpose is to get the image file. I have already made a converter called <b>str2ch(std::string str, int max, int offset)</b> under /include/tools.h so feel free to use it (no need to include as it's already in both ID3v1.h and ID3v2.h).  
- The only allowed frames that can be read / set on v2 (for now) are all the Text Information Frames (excluding TXXX and TXX), the APIC/PIC image frame, the COMM/COM comment frame and all the URL Link Frames (excluding WXXX and WXX).  
- This library won't support unsynchronization because it's no longer needed.  
