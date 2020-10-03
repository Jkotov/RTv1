#include "rtv1.h"

void	cl_build(t_cl *cl)
{
	char	*src;
	int		fd;
	size_t	g_work_size;

	g_work_size = 10;
	src = malloc(sizeof(char) * 4096);
	fd = open("source/rt.cl", O_RDONLY);
	read(fd, src, 4096);
	cl->prog =  clCreateProgramWithSource(cl->context, 1, (const char**)&src,\
	NULL, &cl->ret);
	free(src);
	error(cl->ret);
	cl->ret = clBuildProgram(cl->prog, 0, NULL,\
	NULL, NULL, NULL);
	error(cl->ret);
	cl->kernel = clCreateKernel(cl->prog, "hello", &cl->ret);
	error(cl->ret);
	cl->ret = clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 1, NULL,\
	&g_work_size, NULL, 0, NULL, NULL);
	error(cl->ret);
}

t_cl	cl_init(t_sdl *sdl)
{
	t_cl cl;

	cl.ret = clGetPlatformIDs(2, &cl.platform_id, \
    &cl.ret_num_platforms);
	error(cl.ret);
	cl.ret = clGetDeviceIDs(cl.platform_id, CL_DEVICE_TYPE_GPU, \
    2, &cl.device_id, &cl.ret_num_devices);
	error(cl.ret);
	cl.context = clCreateContext(NULL, 1, &cl.device_id, \
    NULL, NULL, &cl.ret);
	error(cl.ret);
	cl.command_queue = clCreateCommandQueueWithProperties(cl.context, \
    cl.device_id, NULL, &cl.ret);
	error(cl.ret);
	cl.buf = clCreateBuffer(cl.context, CL_MEM_READ_WRITE,\
	sdl->width * sdl->height * sizeof(int), sdl->buffer, &cl.ret);
	error(cl.ret);
	cl_build(&cl);
	return (cl);
}
