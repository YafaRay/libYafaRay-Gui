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

#include "common/images_collection.h"

#include <memory>
#include "common/image.h"

namespace yafaray_gui
{

Image *ImagesCollection::findLayer(const std::string &layer_name)
{
	auto iterator = images_.find(layer_name);
	if(iterator != images_.end()) return iterator->second.get();
	else return nullptr;
}

const Image *ImagesCollection::findLayer(const std::string &layer_name) const
{
	auto iterator = images_.find(layer_name);
	if(iterator != images_.end()) return iterator->second.get();
	else return nullptr;
}

void ImagesCollection::setColor(const std::string &layer_name, int x, int y, const RgbaFloat &rgba)
{
	Image *image = findLayer(layer_name);
	if(!image) return;
	image->setColor(x, y, rgba);
}

RgbaFloat ImagesCollection::getColor(const std::string &layer_name, int x, int y) const
{
	const Image *image = findLayer(layer_name);
	if(!image) return {};
	return image->getColor(x, y);
}

int ImagesCollection::getExportedChannels(const std::string &layer_name) const
{
	auto iterator = layers_exported_channels_.find(layer_name);
	if(iterator != layers_exported_channels_.end()) return iterator->second;
	else return 0;
}

std::string ImagesCollection::getExportedLayerName(const std::string &layer_name) const
{
	auto iterator = dict_internal_exported_layers_.find(layer_name);
	if(iterator != dict_internal_exported_layers_.end()) return iterator->second;
	else return "(unknown)";
}

void ImagesCollection::clear()
{
	images_.clear();
	layers_exported_channels_.clear();
	dict_internal_exported_layers_.clear();
}

void ImagesCollection::defineLayer(const std::string &internal_layer_name, const std::string &exported_layer_name, int width, int height, int channels_exported)
{
	images_[internal_layer_name] = std::make_shared<Image>(width, height);
	layers_exported_channels_[internal_layer_name] = channels_exported;
	dict_internal_exported_layers_[internal_layer_name] = exported_layer_name;
}

int ImagesCollection::getWidth() const
{
	int result = 0;
	for(const auto &image : images_)
	{
		const int image_dimension = image.second->getWidth();
		if(result < image_dimension) result = image_dimension;
	}
	return result;
}

int ImagesCollection::getHeight() const
{
	int result = 0;
	for(const auto &image : images_)
	{
		const int image_dimension = image.second->getHeight();
		if(result < image_dimension) result = image_dimension;
	}
	return result;
}

} // namespace yafaray_gui