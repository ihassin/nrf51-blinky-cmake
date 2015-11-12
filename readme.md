# Blinky using CMake

This is an example of how to compile NRF51 code using CMake.

The example is Blinky from Nordic.

# Build

```
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

```flash.sh``` will use ```upload.jlink``` as the parameter file. It will reset the device, load S110 softdevice to it then load ```build/nrf51822_xxac.hex```.

You should see blinky work immediately on the device.

# Open questions

The resulting HEX file loads and runs, yet is different from the one created by ```make``` at the root, even though both use the same compiler flags.

Please comment and improve so that both binaries are identical!

# License

MIT, apart from anything belonging to Nordic.

