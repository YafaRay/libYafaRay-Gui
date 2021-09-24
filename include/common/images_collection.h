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

BEGIN_YAFARAY_GUI

class RgbaFloat;
class Image;

class ImagesCollection final
{
	public:
		int getWidth() const;
		int getHeight() const;
		void setColor(const std::string &view_name, const std::string &layer_name, int x, int y, const RgbaFloat &rgba);
		RgbaFloat getColor(const std::string &view_name, const std::string &layer_name, int x, int y) const;
		int getExportedChannels(const std::string &layer_name) const;
		std::string getExportedLayerName(const std::string &layer_name) const;
		const std::map<std::string, int> &getLayersAndExportedChannels() const { return layers_exported_channels_; };
		std::map<std::string, std::shared_ptr<Image>> *findView(const std::string &view_name);
		const std::map<std::string, std::shared_ptr<Image>> *findView(const std::string &view_name) const;
		Image *findLayer(const std::string &view_name, const std::string &layer_name);
		const Image *findLayer(const std::string &view_name, const std::string &layer_name) const;
		void clear();
		void defineView(const std::string &view_name);
		void defineLayer(const std::string &internal_layer_name, const std::string &exported_layer_name, int width, int height, int channels_exported);
	private:
		std::map<std::string, std::map<std::string, std::shared_ptr<Image>>> images_;
		std::map<std::string, int> layers_exported_channels_;
		std::map<std::string, std::string> dict_internal_exported_layers_;
};

END_YAFARAY_GUI

#endif //LIBYAFARAY_GUI_IMAGES_COLLECTION_H
