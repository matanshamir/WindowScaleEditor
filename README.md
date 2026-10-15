# WindowScaleEditor

A lightweight, AI-assisted Unreal Engine editor plugin that allows you to adjust the **main editor window's UI scale independently** from other editor windows.

Designed for developers using multi-monitor setups, high-resolution displays, or unconventional editor layouts.

**Compatibility:** Unreal Engine 5.8

## Why I Created This

I use Unreal Engine across multiple monitors with different resolutions and layouts.

I wanted to reduce the UI scale of the main Unreal Editor window without affecting separately opened Blueprint editor windows.

Unreal Engine's built-in application scaling settings didn't provide the per-window control I was looking for.

Rather than changing my Windows display scaling or compromising my workspace layout, I decided to create a small editor plugin to solve this specific problem.

## Features

- **Independent UI Scaling** — Adjust the main editor window without changing the scale of detached Blueprint editor windows.
- **Quick Access** — Access scaling controls directly from the `Window Scale` menu in the editor's top menu bar.
- **Adjustable Scale** — Set the scale between 0.5× and 1.5×.
- **Precise Input** — Enter a specific scale value.
- **Reset to Default** — Restore the default scale of 1.0×.
- **Persistent Settings** — Save your preferred scale between editor sessions.
- **Editor Preferences Integration** — Access the settings through Unreal Engine's Editor Preferences.

## Installation

### Engine-Wide Installation (Recommended)

1. Download or clone this repository.
2. Open the `WindowScaleEditor_5.8` folder.
3. Copy the plugin into your Unreal Engine installation:

   `UE_5.8/Engine/Plugins/Marketplace/WindowScaleEditor/`

4. Launch Unreal Engine 5.8.
5. Navigate to **Edit → Plugins**.
6. Search for `WindowScaleEditor` and enable the plugin.
7. Restart the editor if prompted.

Installing the plugin at the engine level makes it available to projects using that engine installation.

### Project-Specific Installation

Alternatively, copy the plugin into:

`YourProject/Plugins/WindowScaleEditor/`

This makes the plugin available only to that project.

**Note:** This repository contains C++ source code. A compatible C++ development environment may be required to compile the plugin.

## Usage

1. Open Unreal Engine.
2. Find **Window Scale** in the editor's top menu bar.
3. Open the menu to access the scaling controls.
4. Adjust the scale using the numeric control.
5. Confirm your adjustment to apply the scaling.
6. Use **Reset to Default (1.0)** to restore the original scale.

The plugin targets the main editor window, leaving separately opened editor windows unaffected.

You can also find its settings under:

**Edit → Editor Preferences → Plugins → Window Scale Editor**

## How It Works

WindowScaleEditor uses Unreal Engine's C++ editor APIs, including:

- **Slate UI Framework** — For managing editor window scaling and UI controls.
- **MainFrame Module** — For accessing the main Unreal Editor window.
- **ToolMenus** — For integrating the plugin into the editor's menu bar.
- **Developer Settings** — For exposing configurable settings through Editor Preferences.

The plugin applies a custom DPI scale factor to the main editor window rather than changing Unreal Engine's global application scale.

## Development Transparency — AI-Assisted / Vibe Coded

**This project was primarily vibe coded using AI assistance.**

The C++ implementation was largely generated and iteratively refined with the help of ChatGPT.

My contributions included:

- Identifying the original Unreal Engine workflow problem.
- Defining the plugin's requirements and desired behavior.
- Deciding how the scaling controls should work and where they should appear.
- Integrating the generated code into Unreal Engine.
- Compiling, testing, and troubleshooting the plugin.
- Providing feedback and guiding improvements based on actual editor behavior.

I did not write the majority of the C++ implementation manually.

The goal of this project was to solve a practical problem in my development environment while exploring Unreal Engine's editor extensibility and plugin system.

I'm sharing the source code openly in case other developers find it useful.

## Known Limitations

- Window title-bar controls may scale along with the main editor UI.
- The plugin only targets the main Unreal Editor window.
- The current version was developed and tested with Unreal Engine 5.8.
- Compatibility with other Unreal Engine versions has not been verified.
- The plugin is provided as-is and may require adjustments for future engine releases.

## License

No open-source license has been added yet.

## Author

Created and tested by [matanshamir](https://github.com/matanshamir), with AI-assisted C++ development using ChatGPT.
