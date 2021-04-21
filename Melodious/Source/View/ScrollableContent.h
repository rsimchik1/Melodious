#pragma once

class ScrollableContent
{
public:
	virtual void scrollX(float deltaX) = 0;
	virtual void scrollY(float deltaY) = 0;
	virtual void setScrollX(float x) = 0;
	virtual void setScrollY(float y) = 0;
	virtual float getContentWidth() = 0;
	virtual float getContentHeight() = 0;
};
