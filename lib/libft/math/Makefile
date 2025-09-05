NAME			:= libftmath.a

SRC			:= ./vec2d/vec2_dot_product.c \
			./vec2d/vec2_magnitude.c \
			./vec2d/vec2_mult_scalar.c \
			./vec2d/vec2_clamp.c \
			./vec2d/vec2_reflect.c \
			./vec2d/vec2_sub.c \
			./vec2d/vec2_div.c \
			./vec2d/vec2_distance.c \
			./vec2d/vec2_angle.c \
			./vec2d/vec2_add.c \
			./vec2d/vec2_mult.c \
			./vec2d/vec2_normalise.c \
			./vec2d/vec2_div_scalar.c \
			./vec2d/vec2_project.c \
			./vec2d/vec2_perpendicular.c \
			./vec2d/vec2_rotate.c \
			./vec2d/vec2_lerp.c \
			./matrix3d/matrix3d_inverse.c \
			./matrix3d/matrix3d_multiply.c \
			./matrix3d/matrix3d_add.c \
			./matrix3d/matrix3d_transform.c \
			./matrix3d/matrix3d_identity.c \
			./matrix3d/matrix3d_scalar_multiply.c \
			./matrix3d/matrix3d_determinant.c \
			./matrix3d/matrix3d_transpose.c \
			./matrix3d/matrix3d_sub.c \
			./matrix2d/matrix2d_transpose.c \
			./matrix2d/matrix2d_transform.c \
			./matrix2d/matrix2d_scalar_multiply.c \
			./matrix2d/matrix2d_sub.c \
			./matrix2d/matrix2d_inverse.c \
			./matrix2d/matrix2d_identity.c \
			./matrix2d/matrix2d_multiply.c \
			./matrix2d/matrix2d_determinant.c \
			./matrix2d/matrix2d_add.c \
			./vec4d/vec4_clamp.c \
			./vec4d/vec4_angle.c \
			./vec4d/vec4_sub.c \
			./vec4d/vec4_project.c \
			./vec4d/vec4_lerp.c \
			./vec4d/vec4_reflect.c \
			./vec4d/vec4_dot_product.c \
			./vec4d/vec4_mult.c \
			./vec4d/vec4_cross.c \
			./vec4d/vec4_distance.c \
			./vec4d/vec4_magnitude.c \
			./vec4d/vec4_add.c \
			./vec4d/vec4_minor.c \
			./vec4d/vec4_rotate.c \
			./vec4d/vec4_normalise.c \
			./vec4d/vec4_scalar_mult.c \
			./misc/normalize.c \
			./misc/lerp.c \
			./misc/maprange.c \
			./vec3d/vec3_clamp.c \
			./vec3d/vec3_normalise.c \
			./vec3d/vec3_add.c \
			./vec3d/vec3_angle.c \
			./vec3d/vec3_reflect.c \
			./vec3d/vec3_dot_product.c \
			./vec3d/vec3_mult_scalar.c \
			./vec3d/vec3_div.c \
			./vec3d/vec3_mult.c \
			./vec3d/vec3_distance.c \
			./vec3d/vec3_project.c \
			./vec3d/vec3_magnitude.c \
			./vec3d/vec3_lerp.c \
			./vec3d/vec3_rotate.c \
			./vec3d/vec3_perpendicular.c \
			./vec3d/vec3_div_scalar.c \
			./vec3d/vec3_sub.c \
			./colours/colour_get.c \
			./colours/colour_rgba.c \
			./matrix4d/matrix4d_rotate_x.c \
			./matrix4d/matrix4d_sub.c \
			./matrix4d/matrix4d_rotate_y.c \
			./matrix4d/matrix4d_rotate_z.c \
			./matrix4d/matrix4d_inverse.c \
			./matrix4d/matrix4d_multiply.c \
			./matrix4d/matrix4d_add.c \
			./matrix4d/matrix4d_cofactor_row.c \
			./matrix4d/matrix4d_transform.c \
			./matrix4d/matrix4d_rotate.c \
			./matrix4d/matrix4d_transpose.c \
			./matrix4d/matrix4d_determinant.c \
			./matrix4d/matrix4d_scaling.c \
			./matrix4d/matrix4d_translation.c \
			./matrix4d/matrix4d_identity.c \
			./matrix4d/matrix4d_scalar_multiply.c

# 			./matrix4d/matrix4d_look_at.c

OBJDIR		:= obj
OBJ			:= $(patsubst ./%,$(OBJDIR)/%,$(SRC:.c=.o))

# module dependencies
DEPS			:=

CC			:= gcc
AR			:= ar rcs
CFLAGS		:= -Wall -Wextra -Werror
INCLUDE		:= -I$(INCDIR)
INCLUDE		+= -I../include -I../../include

all: $(LIBDIR)/$(NAME)

$(LIBDIR)/$(NAME): $(OBJ) | $(LIBDIR)
	for dep in $(DEPS); do \
		 $(MAKE) -C ../$$dep LIBDIR=$(LIBDIR) INCDIR=$(INCDIR); \
	done
	$(AR) $@ $(OBJ)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Pattern rule to build .o files from .c files in subdirectories
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBDIR):
	mkdir -p $(LIBDIR)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(LIBDIR)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
