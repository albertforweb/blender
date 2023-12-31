# SPDX-FileCopyrightText: 2011 Blender Foundation
#
# SPDX-License-Identifier: GPL-2.0-or-later

set(INC
  ../include
  ../../blenfont
  ../../blenkernel
  ../../blenlib
  ../../blenloader
  ../../blentranslation
  ../../depsgraph
  ../../gpu
  ../../imbuf
  ../../makesdna
  ../../makesrna
  ../../windowmanager
  ../../../../intern/guardedalloc

  # dna_type_offsets.h
  ${CMAKE_CURRENT_BINARY_DIR}/../../makesdna/intern
  # RNA_prototypes.h
  ${CMAKE_BINARY_DIR}/source/blender/makesrna
)

set(INC_SYS
)

set(SRC
  clip_buttons.cc
  clip_dopesheet_draw.cc
  clip_dopesheet_ops.cc
  clip_draw.cc
  clip_editor.cc
  clip_graph_draw.cc
  clip_graph_ops.cc
  clip_ops.cc
  clip_utils.cc
  space_clip.cc
  tracking_ops.cc
  tracking_ops_detect.cc
  tracking_ops_orient.cc
  tracking_ops_plane.cc
  tracking_ops_solve.cc
  tracking_ops_stabilize.cc
  tracking_ops_track.cc
  tracking_ops_utils.cc
  tracking_select.cc

  clip_intern.h
  tracking_ops_intern.h
)

set(LIB
  bf_blenkernel
  bf_blenlib
)


blender_add_lib(bf_editor_space_clip "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")

# Needed so we can use dna_type_offsets.h for defaults initialization.
add_dependencies(bf_editor_space_clip bf_dna)
# RNA_prototypes.h
add_dependencies(bf_editor_space_clip bf_rna)
