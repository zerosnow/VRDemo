#pragma once

#include "cocos2d.h"
#include "gvr_types.h"
#include <math.h>
using namespace cocos2d;

Vec3 GetAngleFromQuaternion(gvr_quatf orientation)
{
	Vec3 ret;
	float x = orientation.qx, y = orientation.qy, z = orientation.qz, w = orientation.qw;

  float sqx = x * x;
  float sqy = y * y;
  float sqz = z * z;
  ret.z = atan2(2.0f * z * w - 2.0f * y * x, 1.0f - 2.0f * sqz - 2.0f * sqx);
  ret.y = asin(2.0f * (w * y - z * x));
  ret.x = atan2(2.0f * y * w - 2.0f * z * x, 1.0f - 2.0f * sqy - 2.0f * sqx);
      
  return ret;
}