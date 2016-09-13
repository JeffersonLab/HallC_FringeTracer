# Fringe tracer

This is a simple Geant4 simulation used for studying the effects of SHMS fringe
fields on the beam traveling to the beam dump.

## Components

- ### Beam gun

Beam gun is firing mono-energetic electrons as a primary beam. It simulates a
square raster with an uniform particle distribution. The beam energy and the
raster size can be set in the configuration file.

- ### Target

The target is used to introduce an energy loss and multiple scattering to obtain
a more realistic beam profile for transporting through the fringe fields. A
carbon target of 1.5% radiation length is currently implemented.

- ### Screen

A screen is set 51.8 m from the target to simulate the beam dump face. It is set
as a sensitive detector, recording the position and type of particles hitting
it. This information is then recorded in a `.csv` file for further analysis.
The name of the output file can be set in the configuration file.

- ### Magnetic fields

Magnetic fields are read in from Tosca field maps compressed with an `xz`
algorithm (method exists for also reading them as a plain text file). A
trilinear interpolation is used when getting the value of the field from the
grid. Only half a field map is needed (and used) since the values for y < 0 are
obtained by mirroring.

The grid needs to be ordered from lowest to highest values of coordinates.

The z coordinate should change fastest and x slowest.

The field maps to be read in and their orientation with regards to the target
coordinate system are defined in the configuration file.

## Installation

A CMake (>=2.6) and Geant4 (>=10.0) are needed for compiling the source. No
special flags need to be set.

A simple `CMakeLists.txt` file is provided.

Only works on Linux due to the way the reading in the xz compressed field maps.
Also needs an `xz` utility to handle the uncompression.

## Run-time configuration

- ### Command line options

Currently supported command line options are:
- `-h`: displays help
- `-c fname`: sets file name that is used as a configuration file
- `-m fname`: sets file name that is used as a batch mode macro file

The default configuration file is `config.txt`. If batch mode macro file is not
set, a interactive session will be started.

Each options has to be entered separately!

- ### Configuration file

A configuration file is used to set up the parameters of the simulation. The
sintax is (note the spaces around `=` sign).

    # comment line
    keyword1 = value1
    keyword2 = value2 # comments

Currently supported keywords are:
- `screenHit.outName`: sets output file name for hits in beam dump screen
- `shms.angle`: sets the angle of the SHMS (in degrees)
- `beam.energy`: sets the beam energy (in GeV)
- `beam.raster.x (y)`: sets the raster size (+- in mm)
- field block: sets the magnetic field

The magnet block needs following options set:
- `magnet.name`: sets the name of the magnetic field. Need to be the first entry
of the field block!
- `magnet.fieldMap`: the file name of the Tosca field map
- `magnet.trans.l`: the distance from the center of target coordinate system to
the center of Tosca coordinate system (in cm)
- `magnet.trans.alpha0`: the angle between z-axis of target coordinate system
and the center of Tosca coordinate system if the spectrometer would be set at
0 deg (in deg)
- `magnet.trans.beta0`: the angle between z-axis of target coordinate system and
the z-axis of Tosca coordinate system

A sample `config.txt` configuration file with all settings is provided with the code.

- ### Macro files

There are three macro files that are used for fine-tuning of the various Geant4
parameters.
- `init.mac`: initialization of interactive mode without visualization
- `init_vis.mac`: initialization of interactive mode with visualization
- `vis.mac`: visualization setting in the initialization phase

Additionally, a batch mode macro can be set using via command line arguments.

Sample macro files are provided with the code.
