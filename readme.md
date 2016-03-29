# NRF51 Blinky using CMake

This is an example of how to compile NRF51 code using CMake.
The example is Blinky from Nordic, and assumes you have GCC and the Nordic SDK installed properly (please refer [here](https://github.com/ihassin/fruitymesh-ubuntu-vm) and [here](https://github.com/ihassin/fruitymesh-mac-osx) for information on how to automatically install the SDK for Ubuntu and Mac OS X respectively)

# Build

This repo shows you how to use CMake in order to build the binary for the device. Please refer [here](https://github.com/ihassin/nrf51-unity) for an example of using a makefile instead.

The CMake file is [here](https://github.com/ihassin/nrf51-blinky-cmake/blob/master/CMakeLists.txt) and assumes version 3.3 of CMake. Please feel free to change the version number to suite your needs.

```
git clone git@github.com:ihassin/nrf51-blinky-cmake.git
cd nrf51-blinky-cmake
mkdir build
cd build
cmake ..
make
```

# Flash

```
cd .. # Going back to the root of the project
./flash
```



```

You should see blinky work immediately on the device.

# Open questions

The resulting HEX file loads and runs, yet is different from the one created by ```make``` at the root, even though both use the same compiler flags.

Please comment and improve so that both binaries are identical!

# License

MIT, apart from anything belonging to Nordic.
```