# v5gdb &times; pros example

This is a v5gdb example that uses the PROS framework.

## Prereq's

Install the pros CLI. The UV python package manager is a good cross platform option:

```sh
uv tool install pros-cli --python python3.10 --with setuptools<81
```

Now install version 14 of the [GNU ARM toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads). This is more platform-dependent, but here is one way you can
do that on macOS:

```sh
brew osx-cross/arm/arm-gcc-bin@14
brew link arm-gcc-bin@14 --force
```

You could also try using the PROS VS Code extension to install both of these at once.
