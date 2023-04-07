# Crypt Game Engine

This is the Crypt Engine, written entirely in C by myself.
The purpose of this engine is to provide a fast, modular engine whose parts can be included when needed.
The goal is to remove the overhead of systems not needed by the user by allowing them to include only what they need.

To contact me regarding questions, requests, bugs, or to just say hello, please feel free to contact me at my email aPanarello20@gmail.com
or on my github at https://github.com/AtPan

# License

This project is licensed under the GNU General Public License (version 3).

The usage of code, binaries, tools, and other services provided by this project must be compliant with the aforementioned license.

# Usage

The engine is split into several linked libraries that can be linked to at compile time.
In the future I plan on writing a tool that generates the linking flags for all the modules requested by the user.

# Features

Not much is present now, but I plan on including the following features at a minimum:
- Support for two- and three-dimension graphics rendering
- Support for most input systems (keyboard-and-mouse, Xbox controllers, Dualshock controllers, joysticks, etc.)
- Sound system
- Physics engine
- Allow full customization (change what key maps to what input, how the physics engine interacts with entities, etc.)

# Notes

When switching compilation from debug to release (or vice versa), you must run 'make clean'.
If you do not, the object files will not be recompiled and you will end up with the same build but in a different location.

--

# Build Environment

This project is built on Ubuntu 18.04 LTS and written in C99.  
The compiler I used is GCC version 8.4.0  
My make is running version 4.1  
