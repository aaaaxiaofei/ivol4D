/// \file ivol4D_types.h
/// Type definitions for simplenrrd.

/*
  IJK: Isosurface Jeneration Kode
  Copyright (C) 2017 Rephael Wenger

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public License
  (LGPL) as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _IVOL4D_TYPES_
#define _IVOL4D_TYPES_

namespace IVOL4D {

  // Scalar types
  typedef float SCALAR_TYPE;     ///< Scalar value type.
  typedef float COORD_TYPE;      ///< Isosurface vertex coordinate type.
  typedef int VERTEX_INDEX;      ///< Grid vertex index type.
  typedef int GRID_COORD_TYPE;   ///< Grid vertex coordinate type.
  typedef int AXIS_SIZE_TYPE;    ///< Axis size type.

  // Grid types
  typedef IJK::GRID_PLUS<int, AXIS_SIZE_TYPE, VERTEX_INDEX, VERTEX_INDEX> 
    GRID_PLUS;                     ///< Regular grid.
  typedef IJK::GRID_SPACING<COORD_TYPE, GRID_PLUS>
    SIMPLENRRD_GRID;                  ///< Grid and spacing information.
  typedef IJK::SCALAR_GRID_BASE<SIMPLENRRD_GRID, SCALAR_TYPE> 
    SIMPLENRRD_SCALAR_GRID_BASE;      ///< Scalar grid base.
  typedef IJK::SCALAR_GRID<SIMPLENRRD_GRID, SCALAR_TYPE> 
    SIMPLENRRD_SCALAR_GRID;           ///< Scalar grid.

};

#endif
