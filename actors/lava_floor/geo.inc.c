#include "src/game/envfx_snow.h"

const GeoLayout lava_floor_geo[] = {
	GEO_CULLING_RADIUS(7000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, lava_floor_area_geo_001_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
