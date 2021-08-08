# ID3-Lib

This library is made for everyone and is free to use.

<h2>What's an ID3 Tag?</h2>
ID3 is a metadata container most often used in conjunction with the MP3 audio file format. It allows information such as the title, artist, album, track number, and other information about the file to be stored in the file itself. There are two unrelated versions of ID3: ID3v1 and ID3v2. <i>(Wikipedia)</i>

<h2>What can this library do?</h2>
This library is able to read, write and remove data on both ID3v1 and ID3v2. To be more specific:</br>
  -> <b>Reads:</b> ID3v1, ID3v2.2(Untested), ID3v2.3, ID3v2.4</br>
  -> <b>Writes:</b> ID3v1, ID3v2.3, ID3v2.4</br>
  -> <b>Removes:</b> ID3v1, ID3v2.3, ID3v2.4</br>

<h2>How to use this library?</h2>
Simply include the following files:</br>
```c++
#include "/include/ID3v1.h"
#include "/include/ID3v2.h"
```
