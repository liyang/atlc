bin_PROGRAMS = atlc rect_in_rect circ_in_circ rect_cen_in_rect \
circ_in_rect rect_in_circ readbin sym_strip \
design_coupler generate_coupler_bitmap generate_bmp_for_coupled_microstrip\
find_optimal_dimensions_for_microstrip_coupler

atlc_SOURCES = nrutil.c atlc.c read_bitmap_file_headers.c \
byteswap.c string.c setup_arrays.c finite_difference_single_threaded.c \
finite_difference_multi_threaded.c usage_atlc.c\
check_for_shorts.c bmp.h definitions.h Erdata.h \
check_for_boundaries.c find_energy_per_metre.c \
update_voltage_array.c get_file_pointer_with_right_filename.c \
find_maximum_values.c calculate_colour_data.c find_electric_fields.c \
get_options.c error_and_exit.c do_fd_calculation.c \
swap_conductor_voltages.c print_copyright.c print_data_for_directional_couplers.c\
print_data_for_two_conductor_lines.c set_data_to_sensible_starting_values.c\
write_fields_for_two_conductor_lines.c write_fields_for_directional_couplers.c

rect_in_rect_SOURCES = rect_in_rect.c usage_rect_in_rect.c write_bitmap.c \
get_Er1_and_Er2_colours.c convert_rect_in_rect_dimensions_to_integers.c \
string.c nrutil.c write_bitmap_out.c byteswap.c \
align_bitmap_image.c fill_rect_in_rect.c check_rect_in_rect.c \
check_error.c get_options.c definitions.h  error_and_exit.c print_copyright.c

rect_cen_in_rect_SOURCES = rect_cen_in_rect.c usage_rect_cen_in_rect.c \
write_bitmap.c \
get_Er1_and_Er2_colours.c convert_rect_in_rect_dimensions_to_integers.c \
string.c nrutil.c write_bitmap_out.c byteswap.c \
align_bitmap_image.c fill_rect_in_rect.c check_rect_in_rect.c \
check_error.c get_options.c definitions.h error_and_exit.c \
print_copyright.c Erdata.h
 
generate_bmp_for_coupled_microstrip_SOURCES =\
usage_generate_bmp_for_coupled_microstrip.c\
generate_bmp_for_coupled_microstrip.c get_Er1_and_Er2_colours.c\
convert_generate_coupled_microstrip_bitmap_dimensions_to_integers.c\
print_copyright.c byteswap.c write_bitmap_out.c string.c nrutil.c\
get_options.c check_parameters_of_generate_bmp_for_coupled_microstrip.c \
write_bitmap.c align_bitmap_image.c\
fill_image_vector_for_generate_bmp_for_coupled_microstrip.c \
check_error.c error_and_exit.c Erdata.h definitions.h 

circ_in_circ_SOURCES = circ_in_circ.c usage_circ_in_circ.c write_bitmap.c \
get_Er1_and_Er2_colours.c convert_circ_in_circ_dimensions_to_integers.c \
string.c nrutil.c write_bitmap_out.c byteswap.c \
align_bitmap_image.c fill_circ_in_circ.c check_circ_in_circ.c \
check_error.c get_options.c definitions.h error_and_exit.c \
print_copyright.c Erdata.h

circ_in_rect_SOURCES = circ_in_rect.c usage_circ_in_rect.c write_bitmap.c \
get_Er1_and_Er2_colours.c convert_circ_in_rect_dimensions_to_integers.c \
string.c nrutil.c write_bitmap_out.c byteswap.c \
align_bitmap_image.c fill_circ_in_rect.c check_circ_in_rect.c \
check_error.c get_options.c definitions.h error_and_exit.c \
print_copyright.c Erdata.h

rect_in_circ_SOURCES = rect_in_circ.c usage_rect_in_circ.c write_bitmap.c \
get_Er1_and_Er2_colours.c convert_rect_in_circ_dimensions_to_integers.c \
string.c nrutil.c write_bitmap_out.c byteswap.c \
align_bitmap_image.c fill_rect_in_circ.c check_rect_in_circ.c \
check_error.c get_options.c definitions.h error_and_exit.c \
print_copyright.c Erdata.h

readbin_SOURCES = readbin.c definitions.h byteswap.c usage_readbin.c \
get_options.c error_and_exit.c print_copyright.c

sym_strip_SOURCES = sym_strip.c fill_image_vector_for_sym_strip.c \
usage_sym_strip.c string.c nrutil.c write_bitmap_out.c\
align_bitmap_image.c byteswap.c calculate_sym_strip_impedance.c\
elliptic_integral.c get_options.c definitions.h error_and_exit.c \
print_copyright.c

generate_coupler_bitmap_SOURCES = generate_coupler_bitmap.c usage_generate_coupler_bitmap.c \
calculate_Zodd_and_Zeven.c get_options.c definitions.h \
calculate_integer_values.c write_bitmap.c \
string.c nrutil.c write_bitmap_out.c byteswap.c \
align_bitmap_image.c fill_make_coupler.c \
check_error.c  definitions.h  error_and_exit.c \
get_Er1_and_Er2_colours.c print_copyright.c 

design_coupler_SOURCES = design_coupler.c usage_design_coupler.c \
get_options.c print_copyright.c calculate_Zodd_and_Zeven.c \
give_examples_of_using_design_coupler.c

find_optimal_dimensions_for_microstrip_coupler_SOURCES =\
find_optimal_dimensions_for_microstrip_coupler.c

EXTRA_DIST = output_from_design_coupler-Sun-Ultra-80.txt

