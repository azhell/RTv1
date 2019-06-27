
#include "rtv1.h"

t_rtv1	*ft_mem_main(void)
{
	t_rtv1	*rt;

	rt = ft_memalloc(sizeof(t_rtv1));

	return (rt);
}

int		main(void)
{
	t_rtv1	*rt;

	rt = ft_mem_main();

	ft_sdl_init(rt);
	ft_sdlloop(rt);

	return (0);
}