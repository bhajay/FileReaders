# FileReaders

This is a collection of file parsers for scientific software. Check below for more information on the file formats that are supported.

## Compile the code
- The entire code for each application is written into one file. For example, in the AdCirc folder the file AdCirc_op.cpp has all the data for output formats for the platform AdCirc
- It uses the Eigen library extensively to define all the matrices
- You can compile the code with the command, for example "g++ -I/include/Eigen AdCirc_op.cpp". Each folder has a file "compile" that has the suggested commands to compile and run the code

## Possible issues
- There are no error / warning messages at the moment
- It does not account for additional blank lines that can be created

## AdCirc
At present, the below files are supported
- fort.62: Contains the depth-averaged velocity time series at specified velocity recording stations. Depth-averaged velocity time series output at the velocity recording stations as specified in the model parameter and periodic boundary condition file.

## Release information

Hydro-UQ is released as an open-source research application under a [BSD 3-Clause License] (https://github.com/bhajay/FileReaders/blob/main/LICENSE.md)