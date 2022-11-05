
#include "ROI.h"



void ROI::xRecalcLumaToChroma()
{
  const uint32_t csx = getComponentScaleX(compID, chromaFormat);
  const uint32_t csy = getComponentScaleY(compID, chromaFormat);

  x >>= csx;
  y >>= csy;
  width >>= csx;
  height >>= csy;
}

Position ROI::chromaPos() const
{
  if (isLuma(compID))
  {
    uint32_t scaleX = getComponentScaleX(compID, chromaFormat);
    uint32_t scaleY = getComponentScaleY(compID, chromaFormat);

    return Position(x >> scaleX, y >> scaleY);
  }
  else
  {
    return *this;
  }
}

Size ROI::lumaSize() const
{
  if (isChroma(compID))
  {
    uint32_t scaleX = getComponentScaleX(compID, chromaFormat);
    uint32_t scaleY = getComponentScaleY(compID, chromaFormat);

    return Size(width << scaleX, height << scaleY);
  }
  else
  {
    return *this;
  }
}

Size ROI::chromaSize() const
{
  if (isLuma(compID))
  {
    uint32_t scaleX = getComponentScaleX(compID, chromaFormat);
    uint32_t scaleY = getComponentScaleY(compID, chromaFormat);

    return Size(width >> scaleX, height >> scaleY);
  }
  else
  {
    return *this;
  }
}

Position ROI::lumaPos() const
{
  if (isChroma(compID))
  {
    uint32_t scaleX = getComponentScaleX(compID, chromaFormat);
    uint32_t scaleY = getComponentScaleY(compID, chromaFormat);

    return Position(x << scaleX, y << scaleY);
  }
  else
  {
    return *this;
  }
}

Position ROI::compPos(const ComponentID compID) const
{
  return isLuma(compID) ? lumaPos() : chromaPos();
}

Position ROI::chanPos(const ChannelType chType) const
{
  return isLuma(chType) ? lumaPos() : chromaPos();
}
