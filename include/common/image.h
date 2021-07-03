#pragma once
/****************************************************************************
 *      This is part of the libYafaRay-Gui package
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2.1 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library; if not, write to the Free Software
 *      Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef LIBYAFARAY_GUI_IMAGE_H
#define LIBYAFARAY_GUI_IMAGE_H

#include "common/yafaray_gui_common.h"
#include <vector>

BEGIN_YAFARAY_GUI_QT

class RgbaFloat
{
	public:
		RgbaFloat() = default;
		RgbaFloat(float r, float g, float b, float a = 1.f) : r_(r), g_(g), b_(b), a_(a) { }
		float getR() const { return r_; }
		float getG() const { return g_; }
		float getB() const { return b_; }
		float getA() const { return a_; }
		unsigned char getR8Bit() const { return floatColorTo8Bit(r_); }
		unsigned char getG8Bit() const { return floatColorTo8Bit(g_); }
		unsigned char getB8Bit() const { return floatColorTo8Bit(b_); }
		unsigned char getA8Bit() const { return floatColorTo8Bit(a_); }

	private:
		static unsigned char floatColorTo8Bit(float color_float) { return static_cast<unsigned char>(std::max(0.f, std::min(color_float, 1.f) * 255.f)); }
		float r_ = 0.f;
		float g_ = 0.f;
		float b_ = 0.f;
		float a_ = 0.f;
};

struct ImagesCollection;

class Image final
{
	public:
		Image() = default;
		Image(unsigned int width, unsigned int height) : width_(width), height_(height) { setSize(width, height); }
		void setSize(unsigned int width, unsigned int height) { width_ = width; height_ = height; data_.resize(width * height); }
		void setColor(unsigned int x, unsigned int y, const RgbaFloat &rgba) { if(x < width_ && y < height_) data_[y * width_ + x] = rgba; }
		RgbaFloat getColor(unsigned int x, unsigned int y) const { if(x < width_ && y < height_) return data_[y * width_ + x]; else return {}; }

	private:
		unsigned int width_ = 0;
		unsigned int height_ = 0;
		std::vector<RgbaFloat> data_;
};

END_YAFARAY_GUI_QT

#endif //LIBYAFARAY_GUI_IMAGE_H
