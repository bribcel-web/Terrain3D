// Copyright © 2025 Cory Petkovsek, Roope Palmroos, and Contributors.

#ifndef TERRAIN3D_MESHER_CLASS_H
#define TERRAIN3D_MESHER_CLASS_H

#include "constants.h"

using namespace godot;

class Terrain3D;

class Terrain3DMesher {
	CLASS_NAME_STATIC("Terrain3DMesher");

public: // Constants
	enum MeshType {
		TILE,
		EDGE_A,
		EDGE_B,
		FILL_A,
		FILL_B,
		STANDARD_TRIM_A,
		STANDARD_TRIM_B,
		STANDARD_TILE,
		STANDARD_EDGE_A,
		STANDARD_EDGE_B,
	};

private:
	Terrain3D *_terrain = nullptr;
	Vector2 _last_target_position = V2_MAX;

	Array _mesh_rids;
	Array _ocean_mesh_rids;
	// LODs -> MeshTypes -> Instances
	Array _clipmap_rids;
	Array _ocean_clipmap_rids;

	// Mesh offset data
	// LOD0 only
	PackedVector3Array _trim_a_pos;
	PackedVector3Array _trim_b_pos;
	PackedVector3Array _tile_pos_lod_0;
	// LOD1 +
	PackedVector3Array _fill_a_pos;
	PackedVector3Array _fill_b_pos;
	PackedVector3Array _tile_pos;
	// All LOD Levels
	real_t _offset_a = 0.f;
	real_t _offset_b = 0.f;
	real_t _offset_c = 0.f;
	PackedVector3Array _edge_pos;

	void _generate_mesh_types(const int p_size, Array &p_mesh_rids_array, const RID mat);
	RID _generate_mesh(const Vector2i &p_size, const bool p_standard_grid = false, const RID mat = RID());
	RID _instantiate_mesh(const PackedVector3Array &p_vertices, const PackedInt32Array &p_indices, const AABB &p_aabb, const RID mat);
	void _generate_clipmap(const int p_size, const int p_lods, const RID &p_scenario, Array &p_instance_rids, Array &p_mesh_rids, RID p_material_rid);
	void _generate_instances(Array &p_instance_rids, Array &p_mesh_rids, const int p_lods, const RID &p_scenario);
	void _generate_offset_data(const int p_mesh_size);

	void _clear_clipmap(Array &p_instances);
	void _clear_mesh_types(Array &p_mesh_rids);

public:
	Terrain3DMesher() {}
	~Terrain3DMesher() { destroy(); }

	void initialize(Terrain3D *p_terrain);
	void destroy();

	void snap();
	void _update_mesh_transforms(Array _instance_rids, real_t vertex_spacing, Vector3 snapped_pos);
	void reset_target_position() { _last_target_position = V2_MAX; }
	void update();
	void update_aabbs();
};
// Inline Functions

#endif // TERRAIN3D_MESHER_CLASS_H
