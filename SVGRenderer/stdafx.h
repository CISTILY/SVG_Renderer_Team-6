// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <iostream>
#include <string>

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <fstream>
#include <shellapi.h>
#include <locale>
#include <cmath>
#include <codecvt>

// TODO: reference additional headers your program requires here

#include "Screen.h"
#include "Gradient.h"

// Resource include for main
#include "SVGRenderer.h"

// Class header file for storing shape's data
#include "ShapeData.h"

// Base class header files
#include "Shape.h"
#include "Point2D.h"

// Class header file for parsing svg
#include "SVG.h"

// RapidXml library
#include "rapidxml.hpp"

// header file for drawing shape
#include "Draw.h"

// group class header file
#include "Group.h"

// Shape class header files
#include "Rect.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Text.h"
#include "Line.h"
#include "Polygon.h"
#include "Polyline.h"
#include "Path.h"