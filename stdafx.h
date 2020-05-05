#ifndef ALGORITHM_STDAFX_H
#define ALGORITHM_STDAFX_H
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <iostream>
#include <bitset>
#include <time.h>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <math.h>
#include <vector>


#include "External/Math/Math.h"
#include "External/PlaneGeometry/PlaneGeometry.h"
#ifdef ALGORITHMLIB
#else
#define ALGORITHMLIB __declspec(dllimport)
#endif
#endif
