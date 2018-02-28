# wBépo layout

This layout is based on the french [bépo](https://bepo.fr/wiki/Accueil) layout.

## reason of changes from the bépo layout
I have made a few change of the bépo layout to accomodate fewer keys keyboard (60%). I also, as a programmer, changed some key as they are non-present in my use ('«»' for example).

But as the bépo layout is standarized, and in xorg xkb (`setxkbmap fr bepo`) I also wanted a keyboard that function on any unix machine, that use that pc-side software layout. i.e all my works will be inside the keyboard, I don't want to touch the pc's layout definition or create my own.

### keys removed
To use on smaller keyboard, I have removed a few keys that are not that much used:
- Ç : moved on alt-gr c, replacing the useless copyright symbol
- È : is replace by its dead accent "`"
- À : can now be done with the above dead accent

### W Z
For symetry, the W and Z needed to move.
- Z takes the place of the old À
- W takes the place on the left of the A (caps lock on normal keyboard)

### «»
The french guillemets are removed. By habits, < and > are left in alt-gr, but that still free two direct acces key for later.

## layer

### alt-gr as raise
On the bépo layout, alt-gr has a frequent use for some symbols. As I wanted to do some change on the alt-gr 'layer' too, I will use a full layer `RAISE` that will replicate most of the alt-gr modifier.


