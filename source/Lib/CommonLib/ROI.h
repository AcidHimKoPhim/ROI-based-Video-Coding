#ifndef __ROI__
#define __ROI__

#include <fstream>
#include "ChromaFormat.h"
#include "CommonDef.h"
#include "Common.h"
#include "TypeDef.h"
#include "Unit.h"
using namespace std;

class ROI : public Area
{

	uint8_t ROIQP;
	ChromaFormat chromaFormat;
	ComponentID compID;
public:
	ROI() : Area(), chromaFormat(NUM_CHROMA_FORMAT), compID(MAX_NUM_TBLOCKS) { ROIQP = 0; }

	ROI(const Area &_area, const uint32_t qp) : Area(_area){ ROIQP = qp; }
	ROI(const Position& _pos, const Size& _size, const uint32_t qp) : Area(_pos, _size) { ROIQP = qp; }
	ROI(const uint32_t _x, const uint32_t _y, const uint32_t _w, const uint32_t _h, const uint32_t qp) : Area(_x, _y, _w, _h) { ROIQP = qp; }
	
	uint8_t getROIQP() { return ROIQP; }
	Area getArea() { return Area(x, y, width, height); }

	void setROI(ChromaFormat _chromaFormat, ComponentID _compID, Area _area, uint32_t _qp)
	{
		chromaFormat = _chromaFormat;
		compID = _compID;
		x = _area.x; y = _area.y; width = _area.width; height = _area.height;
		ROIQP = _qp;
	}

	Size     chromaSize() const;
	Size     lumaSize()   const;

	Position compPos(const ComponentID _compID) const;
	Position chanPos(const ChannelType chType) const;

	Position topLeftComp(const ComponentID _compID) const { return recalcPosition(chromaFormat, compID, _compID, *this); }
	Position topRightComp(const ComponentID _compID) const { return recalcPosition(chromaFormat, compID, _compID, { (PosType)(x + width - 1), y }); }
	Position bottomLeftComp(const ComponentID _compID) const { return recalcPosition(chromaFormat, compID, _compID, { x                        , (PosType)(y + height - 1) }); }
	Position bottomRightComp(const ComponentID _compID) const { return recalcPosition(chromaFormat, compID, _compID, { (PosType)(x + width - 1), (PosType)(y + height - 1) }); }

	bool valid() const { return chromaFormat < NUM_CHROMA_FORMAT && compID < MAX_NUM_TBLOCKS && width != 0 && height != 0 && ROIQP < 51 && ROIQP >= 1; }

	const bool operator==(const ROI &other) const
	{
		if (chromaFormat != other.chromaFormat) return false;
		if (compID != other.compID)       return false;
		return Position::operator==(other) && Size::operator==(other);
	}

	const bool operator!=(const ROI &other) const { return !(operator==(other)); }

	void     repositionTo(const Position& newPos) { Position::repositionTo(newPos); }
	void     positionRelativeTo(const ROI& origROI) { Position::relativeTo(origROI); }
};
#endif
