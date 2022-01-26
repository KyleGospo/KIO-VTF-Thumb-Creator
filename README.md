A KF5 update of [KIO-VTF-Thumb-Creator](https://github.com/panzi/KIO-VTF-Thumb-Creator) by Mathias "Panzi" Panzenböck.

Run `build_and_install.sh` to build and install (duh).

# TODO
- Fix DXT1 alpha bug.
- Find out if there's a way to require that a file has both the .vtf extension *and* `VTF\x00` magic to fix VPK thumbnail bug.
- Maybe add animated hover-over preview for animated textures.

![preview](https://raw.githubusercontent.com/AndrewBetson/KIO-VTF-Thumb-Creator/master/img/vtfthumbcreator_preview.png)

Original README
========================

KIO Thumbnail VTF Plugin
========================

Plugin for KDE KIO thumbnail to load Valve Texture Files (read-only).
Using this you will be able to preview VTF files in KDE programs like Dolphin.

For a general read-only integration into Qt applications (e.g. view VTF files in
Gwenview) see [qvtf](https://github.com/panzi/qvtf) and for the same for Gtk+ see
[pixbufloader-vtf](https://github.com/panzi/pixbufloader-vtf).

### Setup

	git clone https://github.com/panzi/KIO-VTF-Thumb-Creator.git
	mkdir KIO-VTF-Thumb-Creator/build
	cd KIO-VTF-Thumb-Creator/build
	cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
	make
	sudo make install

To enable previews in Dolphin open the settings dialog (Control -> Configure
Dolphin...) and enable Valve Texture Format under General -> Previews.

### Dependencies

 * [VTFLib](https://github.com/panzi/VTFLib)

### License

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
