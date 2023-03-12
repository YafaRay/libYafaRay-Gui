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

#include <vector>
#include <cmath>

namespace yafaray_gui
{

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
		float absCol2Bri() const { return (0.2126f * std::abs(r_) + 0.7152f * std::abs(g_) + 0.0722f * std::abs(b_)); }

	private:
		static unsigned char floatColorTo8Bit(float color_float) { return static_cast<unsigned char>(std::max(0.f, std::min(color_float, 1.f) * 255.f)); }
		float r_ = 0.f;
		float g_ = 0.f;
		float b_ = 0.f;
		float a_ = 0.f;
};

class ImagesCollection;

class Image final
{
	public:
		Image() = default;
		Image(int width, int height) : width_(width), height_(height) { setSize(width, height); }
		void setSize(int width, int height) { width_ = width; height_ = height; data_.resize(width * height); }
		void setColor(int x, int y, const RgbaFloat &rgba);
		RgbaFloat getColor(int x, int y) const;
		int getWidth() const { return width_; }
		int getHeight() const { return height_; }

	private:
		int indexFromCoords(int x, int y) const { return y * width_ + x; }
		bool indexInBounds(int index) const { return index >= 0 && index < data_.size(); }
		int width_ = 0;
		int height_ = 0;
		std::vector<RgbaFloat> data_;
};

inline void Image::setColor(int x, int y, const RgbaFloat &rgba)
{
	const int index = indexFromCoords(x, y);
	if(indexInBounds(index)) data_[index] = rgba;
}

inline RgbaFloat Image::getColor(int x, int y) const
{
	const int index = indexFromCoords(x, y);
	if(indexInBounds(index)) return data_[index];
	else return {};
}

} // namespace yafaray_gui

#endif //LIBYAFARAY_GUI_IMAGE_H
