/****************************************************************************
 *
 *      imagehandler_tiff.h: Tag Image File Format (TIFF) image handler
 *      This is part of the libYafaRay package
 *      Copyright (C) 2010 Rodrigo Placencia Vazquez
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
 *
 */

#ifndef YAFARAY_FORMAT_TIF_H
#define YAFARAY_FORMAT_TIF_H

#include "format.h"

BEGIN_YAFARAY

class TifFormat final : public Format
{
	public:
		static Format *factory(ParamMap &params);

	private:
		virtual std::string getFormatName() const override { return "TifFormat"; }
		virtual Image *loadFromFile(const std::string &name, const Image::Optimization &optimization, const ColorSpace &color_space, float gamma) override;
		virtual bool saveToFile(const std::string &name, const Image *image) override;
};

END_YAFARAY

#endif // YAFARAY_FORMAT_TIF_H