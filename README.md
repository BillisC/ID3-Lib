# ID3-Lib

This library is made for everyone and is free to use.

<h2>What's an ID3 Tag?</h2>
ID3 is a metadata container most often used in conjunction with the MP3 audio file format. It allows information such as the title, artist, album, track number, and other information about the file to be stored in the file itself. There are two unrelated versions of ID3: ID3v1 and ID3v2. <i>(Wikipedia)</i>

<h2>What can this library do?</h2>
This library is able to read, write and remove data on both ID3v1 and ID3v2. To be more specific:</br>
  -> <b>Reads:</b> ID3v1, ID3v2.2(Untested), ID3v2.3, ID3v2.4</br>
  -> <b>Writes:</b> ID3v1, ID3v2.3, ID3v2.4</br>
  -> <b>Removes:</b> ID3v1, ID3v2.3, ID3v2.4</br>

<h2>How to build this library?</h2>
In the downloaded project folder run the following:</br>
  $ cmake .</br>
  $ cmake --build .</br>
After that copy <b>libid3tag.a</b> and the <b>header files under include/</b> to your lib and include folders.</br>
The header files that should be included in your project are: <b>ID3v1.h</b> and <b>ID3v2.h</b></br>
To use the library in your executable add these to the linker options (the second one is needed for some conversion functions):</br>
  $ -l id3tag -l ws2_32</br>

<h2>How to use this library?</h2>
<h3>ID3v1</h3>
<b>Class:</b> ID3v1</br>
For initialization you have to use the song's path as a string parameter (e.g. <b>ID3v1 id(path_to_file);</b>)</br>
<b>Functions:</b></br> 
-> processTags(). The main function that must be called before all else. Returns false if file / tag doesn't exist</br>
-> set(Tag's name, Content you want to write). Adds/Rewrites the specified tag with the content you provide. Parameters have to be strings. Returns false when file / tag / tag  name doesn't exist</br>
-> read(Tag's name). Returns a string with the content of the specified tag. Parameter has to be a string. Returns error string when file / tag / tag name doesn't exist</br>
-> remove(Tag's name). Removes the specified tag. Parameter has to be a string. Returns false when file / tag / tag name doesn't exist</br>
-> removeAll(). Removes the whole ID3 tag. Returns false when file / tag doesn't exist</br>
The allowed tag names are: TITLE, ARTIST, ALBUM, YEAR, COMMENT, GENRE. So for example if you want to change the title you simply have to write: <b>{class_object_name}.set("TITLE", "New title");</b>
For a list of genres check this: https://en.wikipedia.org/wiki/ID3#standard (Winamp <b>not</b> included)</br>

<h3>ID3v2</h3>
v2's syntax is very similar to v1's.</br>
<b>Class:</b> ID3v2</br>
For initialization you have to use the song's path as a string parameter (e.g. <b>ID3v2 id(path_to_file);</b>)</br>
<b>Functions:</b></br> 
-> processTags(). The main function that must be called before all else. Returns false if file / tag doesn't exist or if there is compression detected in the header flags</br>
-> set(Tag's name, Content you want to write). Adds/Rewrites the specified tag with the content you provide. Parameters have to be strings. Returns false when file / tag / frame doesn't exist</br>
-> read(Tag's name). Returns a string with the content of the specified tag. Parameter has to be a string. Returns error string when file / tag / frame doesn't exist</br>
-> remove(Tag's name). Removes the specified tag. Parameter has to be a string. Returns false when file / tag / frame doesn't exist</br>
-> removeAll(). Removes the whole ID3 tag. Returns false when file / tag doesn't exist</br>
The allowed tag names for ID3v2.2 can be found there: https://id3.org/id3v2-00 (Go to 4)</br>
The allowed tag names for ID3v2.3 can be found there: https://id3.org/id3v2.3.0#Declared_ID3v2_frames</br>
The allowed tag names for ID3v2.4 can be found there: https://id3.org/id3v2.4.0-frames (Go to 4)</br>
So if you want to change the title for example on v2.3/v2.4 you have to write: <b>{class_object_name}.set("TIT2", "New title");</b></br>

<h2>Additional Notes</h2>
-> You can still use the set() function even if processTags() fails. Doing so will automatically add support for ID3 with the tag you specified. The default version for setting up a new tag (if it doesn't exist) is v2.3 instead of v2.4. To change this behavior set the following static to 4: <b>int ID3v2::_DefaultVersion = 4;</b> If a wrong version value is inserted then the default will stay at v2.3.</br>
-> <b>Important:</b> If you want to set the picture frame in ID3v2("PIC" for v2.2 and "APIC" for v2.3/v2.4) then in the content parameter you have to provide the image's path.
Also in the read() function the returned string is just raw image data. You can convert them to a char and then write them in a file to make them usable if your only purpose is to get the image file. I have already made a converter called <b>str2ch(std::string str, int max, int offset)</b> under /include/tools.h so feel free to use it (no need to include as it's already in both ID3v1.h and ID3v2.h).</br>
-> The only allowed frames that can be read / set on v2 (for now) are all the Text Information Frames (excluding TXXX and TXX), the APIC/PIC image frame, the COMM/COM comment frame and all the URL Link Frames (excluding WXXX and WXX).</br>
-> This library won't support unsynchronization because it's no longer needed.</br>
