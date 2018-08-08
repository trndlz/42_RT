./src/filters/blind_lights.c:	hit->hit_obj = NULL;
./src/filters/blind_lights.c:	hit->t = INFINITY;
./src/filters/blind_lights.c:	hit->t1 = -1;
./src/filters/blind_lights.c:	hit->t2 = -1;
./src/raytracer/colors.c:	if (hit->hit_obj->o_type == SPHERE && (hit->hit_obj->texture == EARTH
./src/raytracer/colors.c:		|| hit->hit_obj->texture == NEARTH || hit->hit_obj->texture == PERLIN))
./src/raytracer/colors.c:		return (hit->hit_obj->col);
./src/raytracer/colors.c:	rm = vec_norm(vec_sub(vec_mult(hit->n, 2 * hit->cost), hit->lm));
./src/raytracer/colors.c:	dot_spec = ratio_limits(pow(vec_dot(rm, vec_norm(vec_mult(hit->v, -1.0))),
./src/raytracer/colors.c:	dot_diff = ratio_limits(hit->cost);
./src/raytracer/colors.c:	color_spec = multiply_color(light->col, dot_spec * hit->hit_obj->phong.x);
./src/raytracer/colors.c:			dot_diff * hit->hit_obj->phong.y);
./src/raytracer/colors.c:	if (hit->hit_obj->perturb == 0)
./src/raytracer/colors.c:	else if (hit->hit_obj->perturb == 1)
./src/raytracer/colors.c:		hit->n.z += 0.1 * tan(0.05 * hit->hit_inter.y);
./src/raytracer/colors.c:		hit->n.z += 0.1 * tan(0.05 * hit->hit_inter.z);
./src/raytracer/colors.c:	else if (hit->hit_obj->perturb == 2)
./src/raytracer/colors.c:		hit->n.z += 0.3 * sin(0.05 * hit->hit_inter.z);
./src/raytracer/colors.c:	else if (hit->hit_obj->perturb == 3)
./src/raytracer/colors.c:		hit->n.z += 0.1 * tan(0.1 * hit->hit_inter.y);
./src/raytracer/colors.c:		hit->n.z += 0.1 * tan(0.1 * hit->hit_inter.z);
./src/raytracer/colors.c:	else if (hit->hit_obj->perturb == 4)
./src/raytracer/colors.c:		hit->n.z += 0.2 * sin(0.8 * hit->hit_inter.z);
./src/raytracer/colors.c:	hit->n = vec_norm(hit->n);
./src/raytracer/colors.c:	hit->n = normal_vectors(hit, hit->hit_obj, ray);
./src/raytracer/colors.c:	if (hit->hit_obj->texture == NEARTH)
./src/raytracer/colors.c:		hit->n = bump_map(ray, hit);
./src/raytracer/colors.c:	hit->v = inter_position(ray, hit->t);
./src/raytracer/colors.c:	color = multiply_color(get_obj_color(hit, ray), hit->hit_obj->phong.z);
./src/raytracer/colors.c:		hit->lm = vec_norm(vec_sub(llst->pos, hit->v));
./src/raytracer/colors.c:		hit->cost = vec_dot(hit->n, hit->lm);
./src/raytracer/colors.c:	if (!(textures_coef(hit->hit_obj, hit, ray)))
./src/raytracer/descartes.c:	norm = vec_norm(hit->n);
./src/raytracer/descartes.c:		n = hit->hit_obj->descartes.z;
./src/raytracer/descartes.c:		n = 1 / hit->hit_obj->descartes.z;
./src/raytracer/descartes.c:	r = (!(textures_coef(hit->hit_obj, hit, ray)))
./src/raytracer/descartes.c:		? hit->hit_obj->descartes.y : 0;
./src/raytracer/descartes.c:	hit->nt--;
./src/raytracer/descartes.c:	r_ray.origin = inter_position(ray, hit->t);
./src/raytracer/descartes.c:	if (hit->hit_obj->descartes.z > 1.0)
./src/raytracer/descartes.c:	hit->nr--;
./src/raytracer/descartes.c:	r = hit->hit_obj->descartes.x;
./src/raytracer/descartes.c:	r_ray.direction = vec_sub(vec_mult(hit->n, 2
./src/raytracer/descartes.c:				* vec_dot(r_ray.direction, hit->n)), r_ray.direction);
./src/raytracer/descartes.c:	r_ray.origin = hit->hit_inter;
./src/raytracer/normal_vectors.c:	m = vec_x(ray.direction, obj->rot) * hit->t + vec_x(x, obj->rot);
./src/raytracer/normal_vectors.c:	n = vec_add(vec_mult(ray.direction, hit->t), x);
./src/raytracer/normal_vectors.c:	m = vec_x(ray.direction, obj->rot) * hit->t + vec_x(x, obj->rot);
./src/raytracer/normal_vectors.c:	n = vec_add(vec_mult(ray.direction, hit->t), x);
./src/raytracer/normal_vectors.c:	m = vec_x(ray.direction, obj->rot) * hit->t + vec_x(x, obj->rot);
./src/raytracer/normal_vectors.c:	n = vec_add(vec_mult(ray.direction, hit->t), x);
./src/raytracer/normal_vectors.c:		return (vec_norm(vec_sub(inter_position(ray, hit->t), obj->pos)));
./src/raytracer/object_hit.c:	if (t > D_ZERO && t < hit->t)
./src/raytracer/object_hit.c:		hit->t = t;
./src/raytracer/object_hit.c:		hit->hit_obj = obj;
./src/raytracer/object_hit.c:	if (t > D_ZERO && t < hit->t && vec_x(inter, clst->rot) > D_ZERO)
./src/raytracer/object_hit.c:		hit->t = t;
./src/raytracer/object_hit.c:		hit->hit_obj = obj;
./src/raytracer/object_hit.c:	else if (t > D_ZERO && t_cut < hit->t
./src/raytracer/object_hit.c:		&& hit->t1 < t_cut && hit->t2 > t_cut && t_cut > D_ZERO)
./src/raytracer/object_hit.c:		hit->t = t_cut;
./src/raytracer/object_hit.c:		hit->hit_obj = clst;
./src/raytracer/object_hit.c:	hit->hit_obj = NULL;
./src/raytracer/object_hit.c:	hit->t = INFINITY;
./src/raytracer/object_hit.c:	hit->t1 = -1;
./src/raytracer/object_hit.c:	hit->t2 = -1;
./src/raytracer/raytracer.c:	hit->nr = 1;
./src/raytracer/raytracer.c:	hit->nt = 5;
./src/raytracer/raytracer.c:	hit->hit_inter = inter_position(ray, hit->t);
./src/raytracer/raytracer.c:	if (hit->hit_obj->descartes.y > 0 && hit->nt > 0)
./src/raytracer/raytracer.c:	if (hit->hit_obj->descartes.x > 0.01 && hit->nr > 0)
./src/raytracer/shadows.c:	light_r.origin = inter_position(ray, hit->t);
./src/raytracer/solver.c:	hit->t1 = (t1 < t2) ? t1 : t2;
./src/raytracer/solver.c:	hit->t2 = (t1 < t2) ? t2 : t1;
./src/textures/bump_map.c:	sph_pos = vec_norm(vec_mult(vec_sub(inter_position(ray, hit->t),
./src/textures/bump_map.c:		hit->hit_obj->pos), (1 / hit->hit_obj->size)));
./src/textures/bump_map.c:	sph_pos = rot_all_axis(sph_pos, hit->hit_obj->rot);
./src/textures/bump_map.c:	a = (int)(v * (hit->hit_obj->file_height.size[1] - 1));
./src/textures/bump_map.c:	b = (int)(u * (hit->hit_obj->file_height.size[0] - 1));
./src/textures/bump_map.c:	return (hit->hit_obj->file_height.tab[a][b]);
./src/textures/bump_map.c:		return (vec_add(hit->n, modif));
./src/textures/bump_map.c:	return (hit->n);
./src/textures/textures_cylinder_cone.c:	inter = inter_position(ray, hit->t);
./src/textures/textures_cylinder_cone.c:	p = vec_mod(vec_sub(vec_sub(inter, vec_mult(hit->n, hit->hit_obj->size)),
./src/textures/textures_cylinder_cone.c:		hit->hit_obj->pos));
./src/textures/textures_cylinder_cone.c:	x = vec_x(vec_norm(inter), vec_norm(hit->hit_obj->rot));
./src/textures/textures_cylinder_cone.c:	if ((int)(mod + p / hit->hit_obj->txt_size) % 2)
./src/textures/textures_cylinder_cone.c:	inter = inter_position(ray, hit->t);
./src/textures/textures_cylinder_cone.c:	r = vec_mod(vec_sub(inter, hit->hit_obj->pos)) * sin(hit->hit_obj->size);
./src/textures/textures_cylinder_cone.c:	p = vec_mod(vec_sub(vec_sub(inter, vec_mult(hit->n, r)),
./src/textures/textures_cylinder_cone.c:		hit->hit_obj->pos));
./src/textures/textures_cylinder_cone.c:	x = vec_x(vec_norm(inter), vec_norm(hit->hit_obj->rot));
./src/textures/textures_cylinder_cone.c:	if ((int)(mod + p / hit->hit_obj->txt_size) % 2)
./src/textures/textures_sphere_plane.c:	sph_pos = vec_norm(vec_mult(vec_sub(inter_position(ray, hit->t),
./src/textures/textures_sphere_plane.c:		hit->hit_obj->pos), (1 / hit->hit_obj->size)));
./src/textures/textures_sphere_plane.c:	sph_pos = rot_all_axis(sph_pos, hit->hit_obj->rot);
./src/textures/textures_sphere_plane.c:	if ((int)(hit->hit_obj->txt_size * v) % 2)
./src/textures/textures_sphere_plane.c:	sph_pos = vec_norm(vec_mult(vec_sub(inter_position(ray, hit->t),
./src/textures/textures_sphere_plane.c:		hit->hit_obj->pos), (1 / hit->hit_obj->size)));
./src/textures/textures_sphere_plane.c:	sph_pos = rot_all_axis(sph_pos, hit->hit_obj->rot);
./src/textures/textures_sphere_plane.c:	if ((int)(hit->hit_obj->txt_size * u) % 2)
./src/textures/textures_sphere_plane.c:	sph_pos = vec_norm(vec_mult(vec_sub(inter_position(ray, hit->t),
./src/textures/textures_sphere_plane.c:		hit->hit_obj->pos), (1 / hit->hit_obj->size)));
./src/textures/textures_sphere_plane.c:	sph_pos = rot_all_axis(sph_pos, hit->hit_obj->rot);
./src/textures/textures_sphere_plane.c:	if (((int)(hit->hit_obj->txt_size * u) % 2
./src/textures/textures_sphere_plane.c:			+ (int)(hit->hit_obj->txt_size * v)) % 2)
./src/textures/textures_sphere_plane.c:	sph_pos = vec_norm(vec_mult(vec_sub(inter_position(ray, hit->t),
./src/textures/textures_sphere_plane.c:		hit->hit_obj->pos), (1 / hit->hit_obj->size)));
./src/textures/textures_sphere_plane.c:	sph_pos = rot_all_axis(sph_pos, hit->hit_obj->rot);
./src/textures/textures_sphere_plane.c:	a = (int)(v * (hit->hit_obj->file_txt.size[1] - 1));
./src/textures/textures_sphere_plane.c:	b = (int)(u * (hit->hit_obj->file_txt.size[0] - 1));
./src/textures/textures_sphere_plane.c:	return (hit->hit_obj->file_txt.tab[a][b]);
./src/textures/textures_sphere_plane.c:	xy_pos = vec_sub(vec_add(vec_mult(ray.direction, hit->t),
./src/textures/textures_sphere_plane.c:		ray.origin), hit->hit_obj->pos);
./src/textures/textures_sphere_plane.c:	teta = acos(vec_dot(hit->hit_obj->rot, (t_vc){0, 0, 1}));
./src/textures/textures_sphere_plane.c:	if (abs((int)((int)xy_pos.x / hit->hit_obj->txt_size
./src/textures/textures_sphere_plane.c:				- (int)xy_pos.y / hit->hit_obj->txt_size)) % 2 == mod)
