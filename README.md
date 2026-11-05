<p align="center">
  <img src="installer_assets/rdnacast_logo.png" alt="SiliconCast" width="280">
</p>

<h1 align="center">SiliconCast</h1>

<p align="center">
  <strong>Low-overhead 2K recording &amp; streaming for macOS and Apple Silicon.</strong><br>
  <em>A lightweight OBS Studio fork tuned for ScreenCaptureKit, VideoToolbox, and minimal game FPS impact.</em>
</p>

<p align="center">
  <a href="#building-siliconcast-for-macos">Build</a> &bull;
  <a href="#features">Features</a> &bull;
  <a href="#performance">Performance</a> &bull;
  <a href="#rdna-cast-legacy-windows-build">RDNA Cast Legacy</a>
</p>

## App Screenshots

<p align="center">
  <img src="docs/screenshots/rdna-cast-app-1.png" alt="RDNA Cast main window" width="32%">
  <img src="docs/screenshots/rdna-cast-output-optimizer.png" alt="RDNA Cast output optimizer" width="32%">
  <img src="docs/screenshots/rdna-cast-app-3.png" alt="RDNA Cast settings" width="32%">
</p>

---

## Disclaimer

**SiliconCast is an independent open-source project.** It is **not affiliated with, endorsed by, or sponsored by** Apple Inc., Advanced Micro Devices, Inc., or the OBS Project. "Apple", "macOS", "Apple Silicon", "AMD", "Radeon", and "RDNA" are trademarks of their respective owners, used only descriptively to indicate target hardware compatibility.

SiliconCast is a fork of [OBS Studio](https://obsproject.com), redistributed under the GNU General Public License v2.0. See [COPYING](COPYING) for the full GPL text and [THIRD_PARTY_LICENSES.md](THIRD_PARTY_LICENSES.md) for bundled-library licenses.

## What is this?

SiliconCast is a **lightweight fork of [OBS Studio](https://obsproject.com) 31.0.3**, built for **macOS gaming capture on Apple Silicon**. It keeps the native macOS capture and encoder stack, strips heavyweight optional modules, defaults to 2560x1440 at 60 FPS, and uses Apple VideoToolbox hardware encoding to reduce the FPS loss seen with stock OBS setups.

## Performance

| Metric | Stock OBS 31.0.3 | SiliconCast target |
|--------|-------------------|-----------|
| **Plugin modules** | Broad stock plugin set | **Minimal native Mac set** |
| **Preview GPU load** | Full preview refresh | **15 FPS default preview throttle** |
| **Streaming output** | User-configured | **2560x1440 @ 60 FPS target** |
| **Encoder path** | User-configured | **Apple VideoToolbox hardware** |
| **Gaming FPS impact** | 20-30 FPS loss reported | **Target: low single-digit FPS hit** |

## Features

### SiliconCast macOS
- **Apple VideoToolbox defaults** — H.264 for streaming compatibility, HEVC for recording when available
- **2K-first output** — defaults to up to 2560x1440 at 60 FPS instead of OBS's conservative 720p/30 initial profile
- **Preview throttling** — preview defaults to an efficient 15 FPS while output remains full FPS
- **Minimal native plugin set** — ScreenCaptureKit capture, AVFoundation capture, CoreAudio AAC, VideoToolbox, outputs, filters, transitions, image/text sources, and x264 fallback
- **Reduced encoder texture pressure** — smaller GPU encode queue for lite builds
- **No browser, websocket, WebRTC, DeckLink, AJA, VST, VLC, or scripting in the default SiliconCast build**

### RDNA Cast Legacy Windows Core
- **AMD-first encoder defaults** — AMF HEVC is the default encoder. Dropdown: AMD AV1 > HEVC > H.264 > x264 fallback
- **11 plugins** instead of 36 — only what you need for streaming and recording
- **AVX2 + /favor:AMD64 compiler optimizations** — built for Zen 3+ instruction scheduling
- **D3D11-only rendering** — AMD's best-optimized driver path on Windows

### RDNA Cast Legacy Gaming-Friendly
- **Preview throttled to ~40 FPS** — GPU renders preview every 4th frame instead of 165 FPS. Encoder still gets every frame at full quality
- **Pre-analysis disabled** — eliminates the AMF pre-encode pass that steals GPU cycles from your game
- **Reduced GPU encode textures** (10 → 6) — frees VRAM for game textures
- **Reduced async frame cache** (30 → 12) — less memory pressure
- **No profiler overhead** in the render loop

### UX
- **Portable by default** — settings, scenes, profiles live next to the executable
- **Close-to-tray** — X minimizes to system tray (like Steam/AMD Adrenalin). Recording keeps running
- **Tray controls** — right-click for Stream, Record, Replay Buffer, Save Replay, Exit
- **GitHub Releases updates** — Help → GitHub Releases opens the official release page for installers
- **About dialog** with GPLv2-or-later, MIT additions, and bundled-library notices
- **Windows installer** with custom branding via Inno Setup

### AMD Encoder Fixes

These fixes address long-standing AMD AMF issues reported across [OBS #12013](https://github.com/obsproject/obs-studio/issues/12013), [OBS #12512](https://github.com/obsproject/obs-studio/issues/12512), [AMF #465](https://github.com/GPUOpen-LibrariesAndSDKs/AMF/issues/465), and [AMF #323](https://github.com/GPUOpen-LibrariesAndSDKs/AMF/issues/323):

| Fix | Problem | Solution |
|-----|---------|----------|
| **AV1 filler data bug** | Stock OBS compares AV1 rate control against H.264 enum constants — filler data never activates for AV1 CBR. Causes bitrate drops to 0 on static scenes. | Use correct `AMF_VIDEO_ENCODER_AV1_RATE_CONTROL_METHOD_CBR` enum |
| **VBV buffer too large** | Stock OBS sets VBV = 1 full second of bitrate, allowing spikes up to ~2x target before correction | VBV = 500ms (`bitrate / 2`) — cuts maximum spike in half |
| **Startup encoder overload** | H.264 pre-analysis (`PREENCODE_ENABLE`) consumes first GOP, causing 2-3 second frame drops at stream start | Pre-analysis disabled |
| **HQCBR filler data** | High Quality CBR mode didn't enable filler data on any codec | Filler data now enabled for both CBR and HQCBR on H.264, HEVC, and AV1 |

## Target Hardware

| Component | Recommended |
|-----------|-------------|
| **CPU/GPU** | Apple Silicon Mac |
| **OS** | macOS 14+ with ScreenCaptureKit support |
| **Output** | 2560x1440 at 60 FPS |
| **Encoder** | Apple VideoToolbox H.264 / HEVC |

Intel Macs may build through the stock macOS path, but SiliconCast is optimized for Apple Silicon first.

## What's Removed From Legacy RDNA Cast

### Non-AMD Encoders
- `obs-nvenc` — NVIDIA GPU encoder
- `obs-qsv11` — Intel Quick Sync Video
- `nv-filters` — NVIDIA GPU filters

### Non-Windows Platform Code
- `libobs-opengl`, `libobs-metal`, all macOS/Linux/BSD plugins

### Heavyweight Optional Plugins
- `obs-browser` — Chromium (can be re-enabled with `-DENABLE_BROWSER=ON`)
- `obs-websocket`, `obs-webrtc`, `vlc-video`, `decklink`, `aja`, `obs-vst`, `text-freetype2`, `obs-libfdk`
- Lua/Python scripting, frontend-tools plugin

### What Remains (11 core plugins)

| Plugin | Purpose |
|--------|---------|
| `obs-ffmpeg` | FFmpeg muxing + **AMF hardware encoder** (H.264, HEVC, AV1) |
| `obs-x264` | Software H.264 fallback |
| `obs-filters` | Video/audio filters |
| `obs-transitions` | Scene transitions |
| `obs-outputs` | RTMP, SRT, RIST streaming + recording |
| `obs-text` | Windows text rendering |
| `image-source` | Image/slideshow sources |
| `rtmp-services` | Streaming service configs (Twitch, YouTube, etc.) |
| `win-capture` | Window, game, and monitor capture |
| `win-dshow` | Webcams and capture cards (DirectShow) |
| `win-wasapi` | Windows audio capture/output |

## Building SiliconCast for macOS

### Prerequisites
- Full Xcode 15.1+ with the macOS 14.2+ SDK
- CMake 3.28+
- Git

### Quick Build
```bash
./build-siliconcast-macos.sh
```

Equivalent manual commands:
```bash
cmake --preset siliconcast-macos
cmake --build build_siliconcast_macos --config RelWithDebInfo --parallel
```

The SiliconCast build is controlled by `OBS_MAC_LITE=ON`.

## RDNA Cast Legacy Windows Build

### Prerequisites
- Visual Studio 2022 (Community or BuildTools) with **Desktop development with C++** workload + ATL
- CMake 3.28+
- Git
- Inno Setup 6 (for installer, optional)

### Quick Build
```cmd
git clone https://github.com/gkaragioul/RDNA_Cast.git
cd RDNA_Cast
cmake --preset amd-lite-x64
cmake --build build_amd_lite --config RelWithDebInfo --parallel
```

### With Browser Source
```cmd
cmake --preset amd-lite-x64 -DENABLE_BROWSER=ON -DENABLE_WEBSOCKET=ON
cmake --build build_amd_lite --config RelWithDebInfo --parallel
```

### Full Build + Installer
Run `build.bat` — handles CMake configure, build, and Inno Setup packaging in one step.

## How It Works

SiliconCast changes are gated behind the `OBS_MAC_LITE` CMake flag and `#ifdef OBS_MAC_LITE` preprocessor guards. The legacy RDNA Cast Windows path remains gated behind `OBS_AMD_LITE`. Building without either flag produces stock OBS Studio behavior.

## Credits

- [OBS Studio](https://obsproject.com) by the OBS Project — the foundation this project is built on
- [AMD AMF SDK](https://github.com/GPUOpen-LibrariesAndSDKs/AMF) — hardware encoding interface
- All upstream OBS contributors listed in [AUTHORS](AUTHORS)

If you use RDNA Cast and want to support the upstream project that makes it possible, please **[contribute to OBS Studio](https://obsproject.com/contribute)**.

## License

SiliconCast is an OBS Studio fork. The combined application and binary distributions are redistributed under the **GNU General Public License v2.0 or later**; see [COPYING](COPYING).

Original RDNA Cast additions are also offered under the **MIT License** by George Karagioules; see [RDNA_CAST_ADDITIONS_LICENSE.md](RDNA_CAST_ADDITIONS_LICENSE.md). That MIT grant applies only to original RDNA Cast additions and does not relicense OBS Studio or the combined OBS-derived application.

Bundled third-party libraries retain their own licenses. See [THIRD_PARTY_LICENSES.md](THIRD_PARTY_LICENSES.md). Installers ship `LICENSE.txt`, `COPYING`, `AUTHORS`, and `THIRD_PARTY_LICENSES.md` alongside the application.
