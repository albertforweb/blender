/* SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup editors
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct BMEdge;
struct BMFace;
struct BMVert;

struct ARegion;
struct Depsgraph;
struct ListBase;
struct Object;
struct Scene;
struct View3D;

/* transform_snap_object.cc */

/* ED_transform_snap_object_*** API */

typedef enum eSnapSelect {
  SNAP_ALL = 0,
  SNAP_NOT_SELECTED = 1,
  SNAP_NOT_ACTIVE = 2,
  SNAP_NOT_EDITED = 3,
  SNAP_SELECTABLE = 4,
} eSnapSelect;

typedef enum eSnapEditType {
  SNAP_GEOM_FINAL = 0,
  SNAP_GEOM_CAGE = 1,
  SNAP_GEOM_EDIT = 2, /* Bmesh for mesh-type. */
} eSnapEditType;

/** used for storing multiple hits */
struct SnapObjectHitDepth {
  struct SnapObjectHitDepth *next, *prev;

  float depth;
  float co[3];
  float no[3];
  int index;

  struct Object *ob_eval;
  float obmat[4][4];

  /* needed to tell which ray-cast this was part of,
   * the same object may be part of many ray-casts when dupli's are used. */
  unsigned int ob_uuid;
};

/** parameters that define which objects will be used to snap. */
struct SnapObjectParams {
  /* Special context sensitive handling for the active or selected object. */
  eSnapSelect snap_select;
  /* Geometry for snapping in edit mode. */
  eSnapEditType edit_mode_type;
  /* snap to the closest element, use when using more than one snap type */
  bool use_occlusion_test : true;
  /* exclude back facing geometry from snapping */
  bool use_backface_culling : true;
};

typedef struct SnapObjectContext SnapObjectContext;
SnapObjectContext *ED_transform_snap_object_context_create(struct Scene *scene, int flag);
void ED_transform_snap_object_context_destroy(SnapObjectContext *sctx);

/* callbacks to filter how snap works */
void ED_transform_snap_object_context_set_editmesh_callbacks(
    SnapObjectContext *sctx,
    bool (*test_vert_fn)(struct BMVert *, void *user_data),
    bool (*test_edge_fn)(struct BMEdge *, void *user_data),
    bool (*test_face_fn)(struct BMFace *, void *user_data),
    void *user_data);

bool ED_transform_snap_object_project_ray_ex(struct SnapObjectContext *sctx,
                                             struct Depsgraph *depsgraph,
                                             const View3D *v3d,
                                             const struct SnapObjectParams *params,
                                             const float ray_start[3],
                                             const float ray_normal[3],
                                             float *ray_depth,
                                             /* return args */
                                             float r_loc[3],
                                             float r_no[3],
                                             int *r_index,
                                             struct Object **r_ob,
                                             float r_obmat[4][4]);
bool ED_transform_snap_object_project_ray(SnapObjectContext *sctx,
                                          struct Depsgraph *depsgraph,
                                          const View3D *v3d,
                                          const struct SnapObjectParams *params,
                                          const float ray_origin[3],
                                          const float ray_direction[3],
                                          float *ray_depth,
                                          float r_co[3],
                                          float r_no[3]);

/**
 * Fill in a list of all hits.
 *
 * \param ray_depth: Only depths in this range are considered, -1.0 for maximum.
 * \param sort: Optionally sort the hits by depth.
 * \param r_hit_list: List of #SnapObjectHitDepth (caller must free).
 */
bool ED_transform_snap_object_project_ray_all(SnapObjectContext *sctx,
                                              struct Depsgraph *depsgraph,
                                              const View3D *v3d,
                                              const struct SnapObjectParams *params,
                                              const float ray_start[3],
                                              const float ray_normal[3],
                                              float ray_depth,
                                              bool sort,
                                              struct ListBase *r_hit_list);

short ED_transform_snap_object_project_view3d_ex(struct SnapObjectContext *sctx,
                                                 struct Depsgraph *depsgraph,
                                                 const ARegion *region,
                                                 const View3D *v3d,
                                                 unsigned short snap_to,
                                                 const struct SnapObjectParams *params,
                                                 const float mval[2],
                                                 const float prev_co[3],
                                                 float *dist_px,
                                                 float r_loc[3],
                                                 float r_no[3],
                                                 int *r_index,
                                                 struct Object **r_ob,
                                                 float r_obmat[4][4],
                                                 float r_face_nor[3]);
/**
 * Convenience function for performing snapping.
 *
 * Given a 2D region value, snap to vert/edge/face.
 *
 * \param sctx: Snap context.
 * \param mval: Screenspace coordinate.
 * \param prev_co: Coordinate for perpendicular point calculation (optional).
 * \param dist_px: Maximum distance to snap (in pixels).
 * \param r_loc: hit location.
 * \param r_no: hit normal (optional).
 * \return Snap success.
 */
short ED_transform_snap_object_project_view3d(struct SnapObjectContext *sctx,
                                              struct Depsgraph *depsgraph,
                                              const ARegion *region,
                                              const View3D *v3d,
                                              unsigned short snap_to,
                                              const struct SnapObjectParams *params,
                                              const float mval[2],
                                              const float prev_co[3],
                                              float *dist_px,
                                              /* return args */
                                              float r_loc[3],
                                              float r_no[3]);

/**
 * see: #ED_transform_snap_object_project_ray_all
 */
bool ED_transform_snap_object_project_all_view3d_ex(SnapObjectContext *sctx,
                                                    struct Depsgraph *depsgraph,
                                                    const ARegion *region,
                                                    const View3D *v3d,
                                                    const struct SnapObjectParams *params,
                                                    const float mval[2],
                                                    float ray_depth,
                                                    bool sort,
                                                    ListBase *r_hit_list);

#ifdef __cplusplus
}
#endif
