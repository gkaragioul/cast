# Third-party licences

RDNA Cast (Windows) and SiliconCast (Mac) are built on [OBS Studio](https://github.com/obsproject/obs-studio) and include other people's open-source code. This file lists what each app contains and the licence of each part.

**The apps as a whole** are licensed under the GNU General Public License, version 2 or later (GPL-2.0-or-later), the same as OBS Studio. The full text is in [COPYING](COPYING). The complete source code of every release is in this repository, under the release's tag.

This list is a summary. For each component, the licence file in its own source is the one that counts. If you find a mistake, please [open an issue](https://github.com/gkaragioul/cast/issues).

## In both apps

| Component | Licence | Source |
|---|---|---|
| OBS Studio (libobs, the user interface and the plugins kept in these builds) | GPL-2.0-or-later | https://github.com/obsproject/obs-studio |
| Qt 6 | LGPL-3.0 | https://www.qt.io |
| FFmpeg | LGPL-2.1-or-later | https://ffmpeg.org |
| x264 | GPL-2.0-or-later | https://www.videolan.org/developers/x264.html |
| mbed TLS | Apache-2.0 | https://github.com/Mbed-TLS/mbedtls |
| SRT | MPL-2.0 | https://github.com/Haivision/srt |
| librist | BSD-2-Clause | https://code.videolan.org/rist/librist |
| Jansson | MIT | https://github.com/akheron/jansson |
| libcaption | MIT | https://github.com/szatmary/libcaption |
| json11 | MIT | https://github.com/dropbox/json11 |
| BLAKE2 | CC0-1.0 | https://github.com/BLAKE2/BLAKE2 |
| SIMDe | MIT | https://github.com/simd-everywhere/simde |
| uthash | BSD-1-Clause | https://troydhanson.github.io/uthash/ |
| libnsgif | MIT | https://www.netsurf-browser.org/projects/libnsgif/ |
| zlib | zlib | https://zlib.net |
| libpng | libpng | http://www.libpng.org |

The Qt and FFmpeg libraries are shipped as separate files inside the app, so you can replace them with your own builds, as the LGPL allows.

## Only in RDNA Cast (Windows)

| Component | Licence | Source |
|---|---|---|
| AMD AMF SDK headers (hardware encoding on Radeon cards) | MIT | https://github.com/GPUOpen-LibrariesAndSDKs/AMF |
| Chromium Embedded Framework (browser sources and docks) | BSD-3-Clause, plus the licences of Chromium's own components | https://bitbucket.org/chromiumembedded/cef |
| obs-browser | GPL-2.0-or-later | https://github.com/obsproject/obs-browser |
| libdshowcapture (webcams and capture cards) | GPL-2.0-or-later | https://github.com/obsproject/libdshowcapture |
| Microsoft Detours | MIT | https://github.com/microsoft/Detours |
| libcurl | curl (MIT-style) | https://curl.se |
| w32-pthreads | LGPL-2.1 | https://sourceware.org/pthreads-win32/ |

RDNA Cast uses the AMD graphics driver that is already on your PC. It does not include AMD's driver or runtime.

## Only in SiliconCast (Mac)

| Component | Licence | Source |
|---|---|---|
| FreeType (text sources) | FreeType License (FTL) | https://freetype.org |

SiliconCast also uses macOS's own frameworks for capture and encoding (ScreenCaptureKit, AVFoundation, CoreAudio and VideoToolbox). These are part of macOS and are not included in the app.

## Left out of both

Neither app includes obs-websocket, scripting (Lua or Python), NVIDIA or Intel encoders, VLC, DeckLink, AJA or VST support. SiliconCast also leaves out the browser engine.
