/// \file ivol4D.cxx
/// a simple example of reading and writing an nrrd file
/// Version v0.1.1

/*
  IJK: Isosurface Jeneration Code
  Copyright (C) 20017 Rephael Wenger

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

#include <assert.h>
#include <sys/types.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ijkscalar_grid.txx"
#include "ijkgrid_nrrd.txx"

#include "ijkNrrd.h"
#include "ivol4D_types.h"

using namespace std;
using namespace IVOL4D;

// local types
typedef IJK::NRRD_DATA<int, AXIS_SIZE_TYPE> NRRD_HEADER;


// global variables
char * output_filename = NULL;
const int ARRAY_SIZE = 8;
SCALAR_TYPE array[ARRAY_SIZE]; 

// routines
void read_nrrd_file
(const char * input_filename, SIMPLENRRD_SCALAR_GRID & scalar_grid, 
 NRRD_HEADER & nrrd_header);
void ivol_lift
(SIMPLENRRD_SCALAR_GRID & scalar_grid, NRRD_HEADER & nrrd_header);

void memory_exhaustion();
void help(), usage_error();
void parse_command_line(int argc, char **argv);


int main(int argc, char **argv)
{
  SIMPLENRRD_SCALAR_GRID scalar_grid;
  IJK::NRRD_DATA<int, AXIS_SIZE_TYPE> nrrd_header;
  IJK::PROCEDURE_ERROR error("main");

  std::set_new_handler(memory_exhaustion);

  try {

    parse_command_line(argc, argv);

    assert(input_filename != NULL);
    assert(output_filename != NULL);

    ivol_lift(scalar_grid, nrrd_header);
    write_scalar_grid_nrrd(output_filename, scalar_grid, nrrd_header);

  }
  catch (IJK::ERROR & error) {
    if (error.NumMessages() == 0) {
      cerr << "Unknown error." << endl;
    }
    else { error.Print(cerr); }
    cerr << "Exiting." << endl;
    exit(20);
  }
  catch (...) {
    cerr << "Unknown error." << endl;
    exit(50);
  };

}

void ivol_lift
(SIMPLENRRD_SCALAR_GRID & scalar_grid, NRRD_HEADER & nrrd_header)
{

    AXIS_SIZE_TYPE axis_size[3] = {4,4,4};
    scalar_grid.SetSize(3,axis_size);
    nrrd_header.SetSize(3, axis_size);

    for(int k = 0; k < 4; k++) {
      for(int j = 0; j < 4; j++) {
	for(int i = 0; i < 4; i++) {
	  VERTEX_INDEX iw = i + j*4 + k*4*4;
	  int arr_index = i/2 + j/2*2 + k/2*4;
	  scalar_grid.Set(iw, array[arr_index]);
	}
      }
    }

}

void read_nrrd_file
(const char * input_filename, SIMPLENRRD_SCALAR_GRID & scalar_grid, 
 NRRD_HEADER & nrrd_header)
{
  IJK::GRID_NRRD_IN<int, AXIS_SIZE_TYPE> nrrd_in;
  IJK::PROCEDURE_ERROR error("read_nrrd_file");

  nrrd_in.ReadScalarGrid(input_filename, scalar_grid, nrrd_header, error);
  if (nrrd_in.ReadFailed()) { throw error; }

  std::vector<COORD_TYPE> grid_spacing;
  nrrd_header.GetSpacing(grid_spacing);

  for (int d = 0; d < scalar_grid.Dimension(); d++) {
    scalar_grid.SetSpacing(d, grid_spacing[d]);
  };

}


void memory_exhaustion()
{
  cerr << "Error: Out of memory.  Terminating program." << endl;
  exit(10);
}

void parse_command_line(int argc, char **argv)
{
  char * function_name = NULL;

  int iarg = 1;

  while (iarg < argc && argv[iarg][0] == '-') {
    if (string(argv[iarg]) == "-help") {
      help();
    }
    else {
      usage_error();
    };
    iarg++;
  };

  if (argc != iarg+ARRAY_SIZE+1) { usage_error(); };

  for(int i = 0; i < ARRAY_SIZE; i++) {
    std::istringstream istring_argv;
    istring_argv.str(argv[iarg+i]);
    istring_argv >> array[i];
  }

  output_filename = argv[iarg+ARRAY_SIZE];
}

void usage_msg()
{
  cerr << "Usage: gen_ivol4D v1 v2 v3 v4 v5 v6 v7 v8 <output filename>"
       << endl;
}

void usage_error()
{
  usage_msg();
  exit(10);
}


void help()
{
  usage_msg();
  cerr << "No more help available." << endl;
  exit(10);
}
