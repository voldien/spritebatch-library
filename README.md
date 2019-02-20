# Spritebatch


## Motivation
A library originally develop as part of the [https://github.com/voldien/ELT](ELT) project that was later branched into
its own library. Where it would provide both rendering of sprites and font rendering.

## Installation
The software can be easily installed with invoking the following command.
```bash
mkdir build && cd build
cmake ..
cmake --build .
make install
```

 Dependencies 
----------------
In order to compile the program, the following Debian packages is required.
```bash
apt-get install  libgl1-mesa-dev
```

The unit testing required additional packages. the following Debian packages is required. 
```bash
apt-get install libsdl2-dev libgl1-mesa-dev check libsubunit-dev
```

## License
This project is licensed under the GPL+3 License - see the [LICENSE](LICENSE) file for details
