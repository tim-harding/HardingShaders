# Harding Shaders
Harding Shaders is a collection of utility shaders for the [Arnold Renderer](https://www.solidangle.com/arnold/).  See the [wiki](https://github.com/timmythetiny/HardingShaders/wiki) for details on what's included.


## Maya installation
Download the DLL and source code from the [latest release](https://github.com/timmythetiny/HardingShaders/releases) and unzip it.  In the following steps, you may choose to install files anywhere, though a common choice would be C:\solidangle\mtoadeploy\shaders, or a network location if sharing with a studio.  Copy the folders `bin` and `ae` from the unzipped source code Assets folder to your install location, and then copy the file HardingShaders.dll to the `bin` folder as well.  In your Maya.env, add the variable ARNOLD_PLUGIN_PATH pointing to your `bin` folder, and the variable MTOA_TEMPLATES_PATH pointing to your `ae` folder.  The shaders should be available the next time you open Maya.


## Building for Windows
Clone the project.  Set the environment variable ARNOLD_PLUGIN_PATH to the location you would like the DLLs installed to.  If you will be using Maya, set the environment variable MTOA_TEMPLATES_PATH to the location you would like the template files to be copied.  Close any applications that may be using Arnold, then open the Visual Studio solution and build.  The shaders should now be available to Kick and Maya.  If you'll be extending the shaders, the Assets folder included with the project contains test scenes you can run with Kick.  
