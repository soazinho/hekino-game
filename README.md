# hekino game

## THiNGs
- Godot.app/Contents/MacOS/Godot --dump-extension-api
- Generate C++ bindings: scons platform="macos" custom_api_file="../extension_api.json"
- Build: scons platform="macos"
- scons -c
- For optimized builds, you should compile them using the target=template_release switch.