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

#include "yafaray_gui_c_api.h"
#include <yafaray_c_api.h>
#include <string>

int main()
{
	char *version_string = yafaray_gui_getVersionString();
	/* Basic libYafaRay C API usage example, rendering a cube with a TGA texture */

	/* YafaRay standard rendering interface */
	yafaray_Logger *yafaray_logger_ = yafaray_createLogger(nullptr, nullptr, YAFARAY_DISPLAY_CONSOLE_HIDDEN);
	yafaray_setConsoleLogColorsEnabled(yafaray_logger_, YAFARAY_BOOL_TRUE);
	yafaray_setConsoleVerbosityLevel(yafaray_logger_, YAFARAY_LOG_LEVEL_DEBUG);
	yafaray_printInfo(yafaray_logger_, "***** Test client 'test01' for libYafaRay-Gui *****");
	yafaray_printInfo(yafaray_logger_, ("Using libYafaRay version (" + std::to_string(yafaray_getVersionMajor()) + "." + std::to_string(yafaray_getVersionMinor()) + "." + std::to_string(yafaray_getVersionPatch()) + ") and libYafaRay-Gui version " + std::string(version_string)).c_str());

	/* Creating image from RAM or file */
	const int tex_width = 200;
	const int tex_height = 200;
	size_t object_id = 0;
	size_t material_id = 0;
	size_t image_id = 0;
	int i, j;

	yafaray_ParamMap *param_map = yafaray_createParamMap();
	yafaray_ParamMapList *param_map_list = yafaray_createParamMapList();
	yafaray_Scene *yafaray_scene = nullptr;
	yafaray_Renderer *yafaray_renderer = nullptr;
	yafaray_Film *yafaray_film = nullptr;

	yafaray_clearParamMap(param_map);
	yafaray_setParamMapString(param_map, "scene_accelerator", "yafaray-kdtree-original");
	yafaray_scene = yafaray_createScene(yafaray_logger_, "Scene_Gui", param_map);

	yafaray_clearParamMap(param_map);
	yafaray_setParamMapString(param_map, "type", "ColorAlpha");
	yafaray_setParamMapString(param_map, "image_optimization", "none"); /* Note: only "none" allows more HDR values > 1.f */
	yafaray_setParamMapInt(param_map, "width", tex_width);
	yafaray_setParamMapInt(param_map, "height", tex_height);
	yafaray_setParamMapString(param_map, "filename", "test01_tex.tga");
	yafaray_createImage(yafaray_scene, "Image01", &image_id, param_map);

	for(i = 0; i < tex_width; ++i)
		for(j = 0; j < tex_height; ++j)
			yafaray_setImageColor(yafaray_scene, image_id, i, j, 0.01f * static_cast<float>(i), 0.01f * static_cast<float>(j), 0.01f * static_cast<float>(i + j), 1.f);

	/* Creating texture from image */
	yafaray_clearParamMap(param_map);
	yafaray_setParamMapString(param_map, "type", "image");
	yafaray_setParamMapString(param_map, "image_name", "Image01");
	yafaray_createTexture(yafaray_scene, "TextureTGA", param_map);

	/* Creating material */
	/* Shader tree definition */
	yafaray_clearParamMapList(param_map_list);
	yafaray_clearParamMap(param_map);
	yafaray_addParamMapToList(param_map_list, param_map);
	yafaray_setParamMapString(param_map, "element", "shader_node");
	yafaray_setParamMapString(param_map, "name", "diff_layer0");
	yafaray_setParamMapString(param_map, "input", "map0");
	yafaray_setParamMapString(param_map, "type", "layer");
	yafaray_setParamMapString(param_map, "blend_mode", "mix");
	yafaray_setParamMapColor(param_map, "upper_color", 1.f,1.f,1.f,1.f);
	yafaray_addParamMapToList(param_map_list, param_map);
	yafaray_clearParamMap(param_map);
	yafaray_setParamMapString(param_map, "element", "shader_node");
	yafaray_setParamMapString(param_map, "name", "map0");
	yafaray_setParamMapString(param_map, "type", "texture_mapper");
	yafaray_setParamMapString(param_map, "mapping", "cube");
	yafaray_setParamMapString(param_map, "texco", "orco");
	yafaray_setParamMapString(param_map, "texture", "TextureTGA");
	yafaray_addParamMapToList(param_map_list, param_map);
	/* General material parameters and Actual material creation */
	yafaray_clearParamMap(param_map);
	yafaray_setParamMapString(param_map, "type", "shinydiffusemat");
	yafaray_setParamMapColor(param_map, "color", 0.9f, 0.9f, 0.9f, 1.f);
	yafaray_setParamMapString(param_map, "diffuse_shader", "diff_layer0");
	yafaray_createMaterial(yafaray_scene, nullptr, "MaterialTGA", param_map, param_map_list);

	/* Creating a geometric object */
	yafaray_clearParamMap(param_map);
	yafaray_setParamMapBool(param_map, "has_orco", static_cast<yafaray_Bool>(true));
	yafaray_setParamMapString(param_map, "type", "mesh");
	yafaray_createObject(yafaray_scene, &object_id, "Cube", param_map);
	/* Creating vertices for the object */
	yafaray_addVertexWithOrco(yafaray_scene, object_id, -4.f, 1.5f, 0.f, -1.f, -1.f, -1);
	yafaray_addVertexWithOrco(yafaray_scene, object_id, -4.f, 1.5f, 2.f, -1.f, -1.f, 1);
	yafaray_addVertexWithOrco(yafaray_scene, object_id, -4.f, 3.5f, 0.f, -1.f, 1.f, -1);
	yafaray_addVertexWithOrco(yafaray_scene, object_id, -4.f, 3.5f, 2.f, -1.f, 1.f, 1);
	yafaray_addVertexWithOrco(yafaray_scene, object_id, -2.f, 1.5f, 0.f, 1.f, -1.f, -1);
	yafaray_addVertexWithOrco(yafaray_scene, object_id, -2.f, 1.5f, 2.f, 1.f, -1.f, 1);
	yafaray_addVertexWithOrco(yafaray_scene, object_id, -2.f, 3.5f, 0.f, 1.f, 1.f, -1);
	yafaray_addVertexWithOrco(yafaray_scene, object_id, -2.f, 3.5f, 2.f, 1.f, 1.f, 1);
	/* Setting up material for the faces (each face or group of faces can have different materials assigned) */
	yafaray_getMaterialId(yafaray_scene, &material_id, "MaterialTGA");
	/* Adding faces indicating the vertices indices used in each face */
	yafaray_addTriangle(yafaray_scene, object_id, 2, 0, 1, material_id);
	yafaray_addTriangle(yafaray_scene, object_id, 2, 1, 3, material_id);
	yafaray_addTriangle(yafaray_scene, object_id, 3, 7, 6, material_id);
	yafaray_addTriangle(yafaray_scene, object_id, 3, 6, 2, material_id);
	yafaray_addTriangle(yafaray_scene, object_id, 7, 5, 4, material_id);
	yafaray_addTriangle(yafaray_scene, object_id, 7, 4, 6, material_id);
	yafaray_addTriangle(yafaray_scene, object_id, 0, 4, 5, material_id);
	yafaray_addTriangle(yafaray_scene, object_id, 0, 5, 1, material_id);
	yafaray_addTriangle(yafaray_scene, object_id, 0, 2, 6, material_id);
	yafaray_addTriangle(yafaray_scene, object_id, 0, 6, 4, material_id);
	yafaray_addTriangle(yafaray_scene, object_id, 5, 7, 3, material_id);
	yafaray_addTriangle(yafaray_scene, object_id, 5, 3, 1, material_id);

	/* Creating light/lamp */
	yafaray_clearParamMap(param_map);
	yafaray_setParamMapString(param_map, "type", "pointlight");
	yafaray_setParamMapColor(param_map, "color", 1.f, 1.f, 1.f, 1.f);
	yafaray_setParamMapVector(param_map, "from", 5.3f, -4.9f, 8.9f);
	yafaray_setParamMapFloat(param_map, "power", 150.f);
	yafaray_createLight(yafaray_scene, "light_1", param_map);

	/* Creating scene background */
	yafaray_clearParamMap(param_map);
	yafaray_setParamMapString(param_map, "type", "constant");
	yafaray_setParamMapColor(param_map, "color", 1.f, 1.f, 1.f, 1.f);
	yafaray_defineBackground(yafaray_scene, param_map);

	/* Setting up render parameters and creating renderer */
	yafaray_clearParamMap(param_map);
	yafaray_renderer = yafaray_createRenderer(yafaray_logger_, yafaray_scene, "Renderer_Gui", YAFARAY_DISPLAY_CONSOLE_HIDDEN, param_map);

	/* Creating surface integrator */
	yafaray_clearParamMap(param_map);
	/*yafaray_setParamMapString(param_map, "type", "directlighting");*/
	yafaray_setParamMapString(param_map, "type", "photonmapping");
	yafaray_defineSurfaceIntegrator(yafaray_renderer, param_map);

	/* Creating volume integrator */
	yafaray_clearParamMap(param_map);
	yafaray_setParamMapString(param_map, "type", "none");
	yafaray_defineVolumeIntegrator(yafaray_renderer, yafaray_scene, param_map);

	/* Setting up film parameters and creating image film */
	const int result_width = 400;
	const int result_height = 400;
	yafaray_clearParamMap(param_map);
	yafaray_setParamMapInt(param_map, "width", result_width);
	yafaray_setParamMapInt(param_map, "height", result_height);
	//yafaray_setParamMapInt(param_map, "AA_minsamples",  50);
	//yafaray_setParamMapInt(param_map, "AA_passes",  100);
	yafaray_film = yafaray_createFilm(yafaray_logger_, yafaray_renderer, "Film_Gui", param_map);

	/* Creating camera */
	yafaray_clearParamMap(param_map);
	yafaray_setParamMapString(param_map, "type", "perspective");
	yafaray_setParamMapInt(param_map, "resx", result_width);
	yafaray_setParamMapInt(param_map, "resy", result_height);
	yafaray_setParamMapFloat(param_map, "focal", 1.1f);
	yafaray_setParamMapVector(param_map, "from", 8.6f, -7.2f, 8.1f);
	yafaray_setParamMapVector(param_map, "to", 8.0f, -6.7f, 7.6f);
	yafaray_setParamMapVector(param_map, "up", 8.3f, -6.8f, 9.f);
	yafaray_defineCamera(yafaray_film, "cam_1", param_map);

	/* Creating image output */
	yafaray_clearParamMap(param_map);
	yafaray_setParamMapString(param_map, "image_path", "./test01-output1.tga");
	yafaray_createOutput(yafaray_film, "output1_tga", param_map);

	/* Rendering */
	yafaray_gui_createRenderWidget(yafaray_logger_, &yafaray_scene, &yafaray_renderer, &yafaray_film, YAFARAY_GUI_QT, 640, 480, 0, 0, YAFARAY_BOOL_FALSE, YAFARAY_BOOL_FALSE);

	/* Final cleanup */
	yafaray_destroyFilm(yafaray_film);
	yafaray_destroyRenderer(yafaray_renderer);
	yafaray_destroyScene(yafaray_scene);
	yafaray_destroyParamMapList(param_map_list);
	yafaray_destroyParamMap(param_map);
	yafaray_gui_destroyCharString(version_string);
	return 0;
}
