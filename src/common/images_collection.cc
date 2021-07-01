/****************************************************************************
 *      This is part of the libYafaRay-Gui-Qt package
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

BEGIN_YAFARAY_GUI_QT

std::map<std::string, std::shared_ptr<Image>> *ImagesCollection::findView(const std::string &view_name)
{
	auto iterator = images_.find(view_name);
	if(iterator != images_.end()) return &iterator->second;
	else return nullptr;
}

const std::map<std::string, std::shared_ptr<Image>> *ImagesCollection::findView(const std::string &view_name) const
{
	auto iterator = images_.find(view_name);
	if(iterator != images_.end()) return &iterator->second;
	else return nullptr;
}

Image *ImagesCollection::findLayer(const std::string &view_name, const std::string &layer_name)
{
	std::map<std::string, std::shared_ptr<Image>> *layers = findView(view_name);
	if(!layers) return nullptr;

	auto iterator = layers->find(layer_name);
	if(iterator != layers->end()) return iterator->second.get();
	else return nullptr;
}

const Image *ImagesCollection::findLayer(const std::string &view_name, const std::string &layer_name) const
{
	const std::map<std::string, std::shared_ptr<Image>> *layers = findView(view_name);
	if(!layers) return nullptr;

	auto iterator = layers->find(layer_name);
	if(iterator != layers->end()) return iterator->second.get();
	else return nullptr;
}

void ImagesCollection::setColor(const std::string &view_name, const std::string &layer_name, unsigned int x, unsigned int y, const RgbaFloat &rgba)
{
	std::map<std::string, std::shared_ptr<Image>> *layers = findView(view_name);
	if(!layers)
	{
		std::map<std::string, std::shared_ptr<Image>> layers_new;
		layers_new[layer_name] = std::make_shared<Image>(images_width_, images_height_);
		images_[view_name] = layers_new;
		layers = findView(view_name);
	}
	Image *image = findLayer(view_name, layer_name);
	if(!image)
	{
		(*layers)[layer_name] = std::make_shared<Image>(images_width_, images_height_);
		image = findLayer(view_name, layer_name);
	}
	image->setColor(x, y, rgba);
}

RgbaFloat ImagesCollection::getColor(const std::string &view_name, const std::string &layer_name, unsigned int x, unsigned int y) const
{
	const Image *image = findLayer(view_name, layer_name);
	if(!image) return { };
	return image->getColor(x, y);
}

END_YAFARAY_GUI_QT