
#ifndef VTABLE_H
#define VTABLE_H

typedef struct s_vtable
{
    bool		(*is_hit)(const t_ray, const void *, t_hit_record *);
	t_vector2	(*get_uv_coordinate)(const void *, const t_vector3 hit_point);
	void		(*delete)(void *);
	void		(*scale_height)(void *, const t_action);
	void		(*scale_diameter)(void *, const t_action);
}t_vtable;

#endif /* vtable.h */