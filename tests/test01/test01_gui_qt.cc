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

#include "yafaray_gui_qt_c_api.h"
#include <yafaray_c_api.h>
#include <memory>

int main()
{
	const int version_string_size = 100;
	char *version_c_string = (char *) malloc(version_string_size * sizeof(char));
	yafaray_gui_qt_getVersionString(version_c_string, version_string_size);
	const std::string version_string {version_c_string};
	free(version_c_string);

	/* Basic libYafaRay C API usage example, rendering a cube with a TGA texture */

	/* YafaRay standard rendering interface */
	yafaray_Interface_t *yi = yafaray_createInterface(YAFARAY_INTERFACE_FOR_RENDERING, "test01.xml", nullptr, nullptr, YAFARAY_DISPLAY_CONSOLE_NORMAL);
	yafaray_setConsoleLogColorsEnabled(yi, YAFARAY_BOOL_TRUE);
	yafaray_setConsoleVerbosityLevel(yi, YAFARAY_LOG_LEVEL_DEBUG);
	yafaray_setInteractive(yi, YAFARAY_BOOL_TRUE);
	yafaray_printInfo(yi, ("***** Test client 'test01' for libYafaRay-Gui-Qt *****" + version_string).c_str());
	yafaray_printInfo(yi, ("Using libYafaRay version (" + std::to_string(yafaray_getVersionMajor()) + "." + std::to_string(yafaray_getVersionMinor()) + "." + std::to_string(yafaray_getVersionPatch())).c_str());

	/* Creating scene */
	yafaray_paramsSetString(yi, "type", "yafaray");
	yafaray_createScene(yi);
	yafaray_paramsClearAll(yi);

	/* Creating image from RAM or file */
	const int tex_width = 200;
	const int tex_height = 200;
	yafaray_Image_t *image = nullptr;
	int i, j;

	yafaray_paramsSetString(yi, "type", "ColorAlpha");
	yafaray_paramsSetString(yi, "image_optimization", "none"); /* Note: only "none" allows more HDR values > 1.f */
	yafaray_paramsSetInt(yi, "tex_width", tex_width);
	yafaray_paramsSetInt(yi, "tex_height", tex_height);
	yafaray_paramsSetString(yi, "filename", "test01_tex.tga");
	image = yafaray_createImage(yi, "Image01");
	yafaray_paramsClearAll(yi);

	for(i = 0; i < tex_width; ++i)
		for(j = 0; j < tex_height; ++j)
			yafaray_setImageColor(image, i, j, 0.01f * i, 0.01f * j, 0.01f * (i + j), 1.f);

	/* Creating texture from image */
	yafaray_paramsSetString(yi, "type", "image");
	yafaray_paramsSetString(yi, "image_name", "Image01");
	yafaray_createTexture(yi, "TextureTGA");
	yafaray_paramsClearAll(yi);

	/* Creating material */
	/* General material parameters */
	yafaray_paramsSetString(yi, "type", "shinydiffusemat");
	yafaray_paramsSetColor(yi, "color", 0.9f, 0.9f, 0.9f, 1.f);
	/* Shader tree definition */
	yafaray_paramsPushList(yi);
	yafaray_paramsSetString(yi, "element", "shader_node");
	yafaray_paramsSetString(yi, "name", "diff_layer0");
	yafaray_paramsSetString(yi, "input", "map0");
	yafaray_paramsSetString(yi, "type", "layer");
	yafaray_paramsSetString(yi, "blend_mode", "mix");
	yafaray_paramsSetColor(yi, "upper_color", 1.f,1.f,1.f,1.f);
	yafaray_paramsPushList(yi);
	yafaray_paramsSetString(yi, "element", "shader_node");
	yafaray_paramsSetString(yi, "name", "map0");
	yafaray_paramsSetString(yi, "type", "texture_mapper");
	yafaray_paramsSetString(yi, "mapping", "cube");
	yafaray_paramsSetString(yi, "texco", "orco");
	yafaray_paramsSetString(yi, "texture", "TextureTGA");
	yafaray_paramsEndList(yi);
	/* Actual material creation */
	yafaray_paramsSetString(yi, "diffuse_shader", "diff_layer0");
	yafaray_createMaterial(yi, "MaterialTGA");
	yafaray_paramsClearAll(yi);

	/* Creating geometric objects in the scene */
	yafaray_startGeometry(yi);

	/* Creating a geometric object */
	yafaray_paramsSetBool(yi, "has_orco", static_cast<yafaray_bool_t>(true));
	yafaray_paramsSetString(yi, "type", "mesh");
	yafaray_createObject(yi, "Cube");
	yafaray_paramsClearAll(yi);
	/* Creating vertices for the object */
	yafaray_addVertexWithOrco(yi, -4.f, 1.5f, 0.f, -1.f, -1.f, -1);
	yafaray_addVertexWithOrco(yi, -4.f, 1.5f, 2.f, -1.f, -1.f, 1);
	yafaray_addVertexWithOrco(yi, -4.f, 3.5f, 0.f, -1.f, 1.f, -1);
	yafaray_addVertexWithOrco(yi, -4.f, 3.5f, 2.f, -1.f, 1.f, 1);
	yafaray_addVertexWithOrco(yi, -2.f, 1.5f, 0.f, 1.f, -1.f, -1);
	yafaray_addVertexWithOrco(yi, -2.f, 1.5f, 2.f, 1.f, -1.f, 1);
	yafaray_addVertexWithOrco(yi, -2.f, 3.5f, 0.f, 1.f, 1.f, -1);
	yafaray_addVertexWithOrco(yi, -2.f, 3.5f, 2.f, 1.f, 1.f, 1);
	/* Setting up material for the faces (each face or group of faces can have different materials assigned) */
	yafaray_setCurrentMaterial(yi, "MaterialTGA");
	/* Adding faces indicating the vertices indices used in each face */
	yafaray_addTriangle(yi, 2, 0, 1);
	yafaray_addTriangle(yi, 2, 1, 3);
	yafaray_addTriangle(yi, 3, 7, 6);
	yafaray_addTriangle(yi, 3, 6, 2);
	yafaray_addTriangle(yi, 7, 5, 4);
	yafaray_addTriangle(yi, 7, 4, 6);
	yafaray_addTriangle(yi, 0, 4, 5);
	yafaray_addTriangle(yi, 0, 5, 1);
	yafaray_addTriangle(yi, 0, 2, 6);
	yafaray_addTriangle(yi, 0, 6, 4);
	yafaray_addTriangle(yi, 5, 7, 3);
	yafaray_addTriangle(yi, 5, 3, 1);

	/* Ending definition of geometric objects */
	yafaray_endGeometry(yi);

	/* Creating light/lamp */
	yafaray_paramsSetString(yi, "type", "pointlight");
	yafaray_paramsSetColor(yi, "color", 1.f, 1.f, 1.f, 1.f);
	yafaray_paramsSetVector(yi, "from", 5.3f, -4.9f, 8.9f);
	yafaray_paramsSetFloat(yi, "power", 150.f);
	yafaray_createLight(yi, "light_1");
	yafaray_paramsClearAll(yi);

	/* Creating scene background */
	yafaray_paramsSetString(yi, "type", "constant");
	yafaray_paramsSetColor(yi, "color", 1.f, 1.f, 1.f, 1.f);
	yafaray_createBackground(yi, "world_background");
	yafaray_paramsClearAll(yi);

	/* Creating camera */
	const int result_width = 400;
	const int result_height = 400;
	yafaray_paramsSetString(yi, "type", "perspective");
	yafaray_paramsSetInt(yi, "resx", result_width);
	yafaray_paramsSetInt(yi, "resy", result_height);
	yafaray_paramsSetFloat(yi, "focal", 1.1f);
	yafaray_paramsSetVector(yi, "from", 8.6f, -7.2f, 8.1f);
	yafaray_paramsSetVector(yi, "to", 8.0f, -6.7f, 7.6f);
	yafaray_paramsSetVector(yi, "up", 8.3f, -6.8f, 9.f);
	yafaray_createCamera(yi, "cam_1");
	yafaray_paramsClearAll(yi);

	/* Creating scene view */
	yafaray_paramsSetString(yi, "camera_name", "cam_1");
	yafaray_createRenderView(yi, "view_1");
	yafaray_paramsClearAll(yi);

	/* Creating image output */
	yafaray_paramsSetString(yi, "type", "image_output");
	yafaray_paramsSetString(yi, "image_path", "./test01-output1.tga");
	yafaray_createOutput(yi, "output1_tga", YAFARAY_BOOL_TRUE);
	yafaray_paramsClearAll(yi);

	/* Creating surface integrator */
	/*yafaray_paramsSetString(yi, "type", "directlighting");*/
	yafaray_paramsSetString(yi, "type", "photonmapping");
	yafaray_createIntegrator(yi, "surfintegr");
	yafaray_paramsClearAll(yi);

	/* Creating volume integrator */
	yafaray_paramsSetString(yi, "type", "none");
	yafaray_createIntegrator(yi, "volintegr");
	yafaray_paramsClearAll(yi);

	/* Defining internal and exported layers */
	yafaray_paramsSetString(yi, "type", "combined");
	yafaray_paramsSetString(yi, "image_type", "ColorAlpha");
	yafaray_paramsSetString(yi, "exported_image_name", "Combined");
	yafaray_paramsSetString(yi, "exported_image_type", "ColorAlphaWeight");
	yafaray_defineLayer(yi);
	yafaray_paramsClearAll(yi);

	yafaray_setupLayersParameters(yi);
	yafaray_paramsClearAll(yi);

	/* Setting up render parameters */
	yafaray_paramsSetString(yi, "integrator_name", "surfintegr");
	yafaray_paramsSetString(yi, "volintegrator_name", "volintegr");
	yafaray_paramsSetString(yi, "scene_accelerator", "yafaray-kdtree-original");
	yafaray_paramsSetString(yi, "background_name", "world_background");
	yafaray_paramsSetInt(yi, "width", result_width);
	yafaray_paramsSetInt(yi, "height", result_height);
/*	yafaray_paramsSetInt(yi, "AA_minsamples",  50);*/
/*	yafaray_paramsSetInt(yi, "AA_passes",  100);*/
	yafaray_paramsSetInt(yi, "threads", -1);
	yafaray_paramsSetInt(yi, "threads_photons", -1);
	yafaray_setupRender(yi);
	yafaray_paramsClearAll(yi);
	/* Rendering */
	yafaray_gui_qt_createRenderWidget(yi, 640, 480, 0, 0, YAFARAY_BOOL_TRUE, YAFARAY_BOOL_FALSE);
	/* Destroying YafaRay interface. Scene and all objects inside are automatically destroyed */
	yafaray_destroyInterface(yi);
	return 0;
}
