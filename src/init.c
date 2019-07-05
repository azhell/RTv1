//
//
//
//
//
//
//
//
//
//

#include "rtv1.h"

void	ft_init(t_rtv1 *rt)
{
	rt->horizontal = (t_vector){4.0, 0.0, 0.0};
	rt->vertical = (t_vector){0.0, 2.0, 0.0};
	rt->left_corner = rt->camera.pos - (t_vector){2.0, 1.0, 1.0};
	printf("%f %f %f \n", rt->left_corner[X], rt->left_corner[Y], rt->left_corner[Z]);
}