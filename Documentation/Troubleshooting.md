# Troubleshooting

In case of an error, you might find an answer of how to deal with it here.

## Building Ladybird

### CMake fails to configure the build because it's outdated

Ensure your CMake version is >= 3.25 with `cmake --version`. If your system doesn't provide a suitable
version of CMake, you can download a binary release from the [CMake website](https://cmake.org/download).

### GCC is missing or is outdated

Ensure your gcc version is supported by the [build system](BuildInstructionsLadybird.md#build-prerequisites) with
`gcc --version`. Otherwise, install it. If your gcc binary is not called `gcc` you have to specify the names of your
C and C++ compiler when you run cmake, e.g. `cmake ../.. -GNinja -DCMAKE_C_COMPILER=gcc-13 -DCMAKE_CXX_COMPILER=g++-13`.

### Legacy renegotiation is disabled

Ensure your `/etc/ssl/openssl.cnf` file has the following options:

```console
[openssl_init]
ssl_conf = ssl_sect

[ssl_sect]
system_default = system_default_sect

[system_default_sect]
MinProtocol = TLSv1.2
CipherString = DEFAULT@SECLEVEL=1
Options = UnsafeLegacyRenegotiation
```

### “Targets may link only to libraries. CMake is dropping the item” message (when building with the Qt UI on macOS)

When building with the Qt UI on macOS, you may encounter the following message:

```
CMake Warning at /opt/homebrew/Cellar/qt/6.7.0_1/lib/cmake/Qt6/FindWrapOpenGL.cmake:48 (target_link_libraries):
Target "ladybird" requests linking to directory "/usr/X11R6/lib". Targets
may link only to libraries. CMake is dropping the item.
```

…followed by 14-line stack trace, the top of which is this:

```
Build/vcpkg/scripts/buildsystems/vcpkg.cmake:859 (_find_package)
```

…and all of it shown in bright yellow, making you think it must be important and something must need to be fixed. But that’s not the case. Instead, despite that, you’ll be able to build successfully with the Qt UI.

## Running Ladybird

### Race condition on exit when running headless on systems with `llvmpipe`

When running `--headless=text` or `--headless=layout-tree` on a UNIX system with the [llvmpipe](https://docs.mesa3d.org/drivers/llvmpipe.html) software rasterizer
(common default on virtual machines), Ladybird will occasionally terminate with:

```
double free or corruption (!prev)
```

Run Ladybird with `--force-cpu-painting` to make that go away.

Likely explanation ([this thread](https://github.com/LadybirdBrowser/ladybird/issues/5097)):

> suspect […] atexit handlers are registered twice possibly due to llvmpipe and fork/exec interaction issues when starting WebContent process
