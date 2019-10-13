/*
 This file is part of the MinGfx Project.
 
 Copyright (c) 2017,2018 Regents of the University of Minnesota.
 All Rights Reserved.
 
 Original Author(s) of this File:
	Dan Keefe, 2018, University of Minnesota
	
 Author(s) of Significant Updates/Modifications to the File:
	...
 */

// The file config.h.in is processed by cmake to produce config.h.  This
// replaces strings of the form "at"CMAKE_VARIABLE_NAME"at" with the value
// of the corresponding cmake variable, allowing us to pass directory paths
// and other information configured with cmake into our C++ code.


#define MINGFX_DATA_DIR_BUILD "D:/Daniel/Desktop/TTC_Sim/TTC_Sim/external/MinGfx/data"
#define MINGFX_DATA_DIR_INSTALL "D:/Daniel/Desktop/TTC_Sim/TTC_Sim/share/MinGfx-1.0/data"

#define MINGFX_SHADERS_DIR_BUILD "D:/Daniel/Desktop/TTC_Sim/TTC_Sim/external/MinGfx/src/shaders"
#define MINGFX_SHADERS_DIR_INSTALL "D:/Daniel/Desktop/TTC_Sim/TTC_Sim/share/MinGfx-1.0/shaders"

