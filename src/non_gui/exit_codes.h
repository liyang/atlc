/* atlc - arbitrary transmission line calculator, for the analysis of
transmission lines are directional couplers. 

Copyright (C) 2002. Dr. David Kirkby, PhD (G8WRB).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either package_version 2
of the License, or (at your option) any later package_version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
USA.

Dr. David Kirkby, e-mail drkirkby@ntlworld.com 

*/

#define OKAY                                                       0
#define CANT_OPEN_FILE_FOR_READING                                 1
#define CANT_OPEN_FOR_WRITING                                      2
#define CANT_OPEN_FILE_FOR_APPENDING                               3
#define CANT_CLOSE_FILE                                            4
#define WRITE_FAILURE                                              5
#define THE_WIDTH_w_DIVIDED_BY_THE_HEIGHT_H_IS_TOO_LARGE           6
#define PROGRAM_NOT_IMPLEMENTED                                    7
#define PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS              8
#define UNACCEPTABLE_ERROR_WHEN_CONVERTING_TO_INTEGERS             9
#define MEMORY_ALLOCATION_ERROR_IN_VECTOR                         10
#define MEMORY_ALLOCATION_ERROR_IN_IVECTOR                        11
#define MEMORY_ALLOCATION_ERROR_IN_CVECTOR                        12
#define MEMORY_ALLOCATION_ERROR_IN_DVECTOR                        13
#define MEMORY_ALLOCATION_ERROR_IN_CMATRIX                        14
#define MEMORY_ALLOCATION_ERROR_IN_UCMATRIX                       15
#define MEMORY_ALLOCATION_ERROR_IN_MATRIX                         16
#define MEMORY_ALLOCATION_ERROR_IN_DMATRIX                        17
#define MEMORY_ALLOCATION_ERROR_IN_IMATRIX                        18
#define MEMORY_ALLOCATION_ERROR_IN_STRING                         19
#define MEMORY_ALLOCATION_ERROR_IN_USTRING                        20
#define SILLY_ARGUMENTS_IN_FREE_VECTOR                            21
#define SILLY_ARGUMENTS_IN_FREE_IVECTOR                           22
#define SILLY_ARGUMENTS_IN_FREE_CVECTOR                           23
#define SILLY_ARGUMENTS_IN_FREE_DVECTOR                           24
#define SILLY_ARGUMENTS_IN_FREE_DMATRIX                           25
#define SILLY_ARGUMENTS_IN_FREE_CMATRIX                           26
#define SILLY_ARGUMENTS_IN_FREE_UCRMATRIX                         27
#define SILLY_ARGUMENTS_IN_FREE_IMATRIX                           28
#define SILLY_ARGUMENTS_IN_FREE_STRING                            29
#define SILLY_ARGUMENTS_IN_FREE_USTRING                           30
#define VOLTAGE_OUT_OF_RANGE                                      31
#define ARGUMENT_w_OUT_OF_RANGE                                   32
#define ARGUMENT_h_OUT_OF_RANGE                                   33
#define ARGUMENT_s_OUT_OF_RANGE                                   34
#define ARGUMENT_g_OUT_OF_RANGE                                   35
#define ARGUMENT_Er1_OUT_OF_RANGE                                 36
#define ARGUMENT_Er2_OUT_OF_RANGE                                 37
#define ARGUMENT_W_OUT_OF_RANGE                                   36
#define ARGUMENT_H_OUT_OF_RANGE                                   38
#define ARGUMENT_t_OUT_OF_RANGE                                   39
