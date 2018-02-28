# wBépo layout

This layout is based on the french [bépo](https://bepo.fr/wiki/Accueil) layout, which I have been using for 10+ years. It includes the changes and tweaks I gradually implemented after using an ergodox for ~1 year, slowly taking advantage of qmk's features.

## reason of changes from the bépo layout
I have made a few change of the bépo layout to accomodate fewer keys keyboard (60%). I also, as a programmer, changed some key as they are non-present in my use ('«»' for example).

But as the bépo layout is standarized, and in xorg xkb (`setxkbmap fr bepo`) I also wanted a keyboard that function on any unix machine, that use that pc-side software layout to gives me easy access to french specific character. i.e all my works will be inside the keyboard, I don't want to touch the pc's layout definition or create my own.

To not use the bépo/bepo name and confuse peoples, I named my layout wbepo as it's biggest change is to move the w to the far left.

### keys removed
To use on smaller keyboard, I have removed a few keys that are not that much used (certainly a personla bias here):
- Ç : moved on alt-gr c, replacing the useless copyright symbol
- È : is replace by its dead accent "`"
- À : can now be done with the above dead accent

__testing__ maybe put è on a layer e, and also à on layer a ? this approach would completely free the bépo è key.

### W Z
For symetry, the W and Z needed to move.
- Z takes the place of the old À
- W takes the place on the left of the A (caps lock on normal keyboard)

### «»
The french guillemets are removed. By habits, < and > are left in alt-gr, but that still free two direct acces key for the top layer ones that now miss a key : ESC and %.

## layer
I like the raise/lower layer, but don't use the adapt layer as I don't like to have both thumb locked for typing anything else. Instead I add 2 other layer: rise/drop.

On the bépo layout, alt-gr has a frequent use for some symbols. As I wanted to do some change on the alt-gr 'layer' too, I will use the raise layer that will replicate most of the alt-gr modifier (same key placement).

The lower key would have KC_ALT accessible wit tap dance, and the more usefull alt-shortcut habit (like alt-tab) will be remade accesible directly with macro on the lower layer.

### base layer
 - __testing__ shift keys on SFT_T , and c.
 - __testing__ ctrl keys on CTL_T w and m.

### raise (alt-gr)
 - various symbols (|&\~_)
 - __testing__ lower effort ()[] to uniformize with {}<>

### lower
 - directional keys (wasd style, I have never got used to the hjkl style)
 - window changing key (tmux, vim)
 - some french alt letter (ïçæœùè)

### rise
 - Functions keys F0-F12
 - movments: home, end, page up/down (wasd style)

### drop
 - mostly numeric pad
 - some media shortcut
