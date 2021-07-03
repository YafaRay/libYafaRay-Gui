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

#ifndef LIBYAFARAY_GUI_IMAGES_COLLECTION_H
#define LIBYAFARAY_GUI_IMAGES_COLLECTION_H

#include "common/yafaray_gui_common.h"
#include <string>
#include <map>
#include <memory>

BEGIN_YAFARAY_GUI_QT

class RgbaFloat;
class Image;

class ImagesCollection final
{
	public:
		ImagesCollection(unsigned int width, unsigned int height) : images_width_(width), images_height_(height) { }
		unsigned int getWidth() const { return images_width_; }
		unsigned int getHeight() const { return images_height_; }
		void setColor(const std::string &view_name, const std::string &layer_name, unsigned int x, unsigned int y, const RgbaFloat &rgba);
		RgbaFloat getColor(const std::string &view_name, const std::string &layer_name, unsigned int x, unsigned int y) const;

	private:
		std::map<std::string, std::shared_ptr<Image>> *findView(const std::string &view_name);
		const std::map<std::string, std::shared_ptr<Image>> *findView(const std::string &view_name) const;
		Image *findLayer(const std::string &view_name, const std::string &layer_name);
		const Image *findLayer(const std::string &view_name, const std::string &layer_name) const;
		unsigned int images_width_ = 0;
		unsigned int images_height_ = 0;
		std::map<std::string, std::map<std::string, std::shared_ptr<Image>>> images_;
};

END_YAFARAY_GUI_QT

#endif //LIBYAFARAY_GUI_IMAGES_COLLECTION_H
