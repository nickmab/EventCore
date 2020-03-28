# Toy project "EventCore" but probably misnamed

...and the structure of the project, the namespaces etc. are definitely not the best =P

This is just for my learning; this doesn't really serve any great purpose in the world.

It's basically just to help me get hands on with socket programming, event models, tools like visual studio, cmake *etc.*

## Usage

Windows only at the moment. 

Should *almost* work "out of the box" with a Visual Studio 2019 with CMake support (open this as a "folder", not a "solution").

Only catch is you need protobuf installed somewhere and you need to change the CMakeLists.txt files to point the compiler and linker to it.

## Demo apps

Take a look at the folders and readmes under **/apps** to see usage of the libraries. 

## libs

The library contains working code that demos how to do stuff like:
- One-to-many TCP Server -> TCP Clients with a protobuf binary protocol.
- Pre-compiled header.
- Profiling (not really using atm. - I wouldn't say it's a *good* example).
- Raise and handle events throughout the application.
- Capture and respond to console signals (e.g. CTRL+C). 