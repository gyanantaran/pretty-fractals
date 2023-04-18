#=
AUTHOR: Vishal Paudel
DATE: Wed Apr 19 00:26:21 IST 2023

NOTE: None
TODO: None
=#

using Images, Colors, ColorSchemes


# returns the number of iteration before the number($z_{n}$) blows off
# the output computed on z0 and c will be used for colouring later in `return_image` function

# Param
    # z0 is the z0 in z1 -> z0^2 + c for example
    # c is the c in z^2 + c for example
    # max_iter is the max number of iterations before to classify as NOT blew off
    # f is the iteration function, z -> z^2 + c
    # cond to return as blown
function iter_count(z0::Complex, c::Complex, max_iter::Int, f::Function=f, cond::Function=cond)
    z = z0  # just for naming ease
    for iter in 1:max_iter
        z = f(z, c)
        cond(z) && return iter  # return if condition is satisfied
    end
    return max_iter + 1
end


# the condition to break stop iterating in `iter_count` function
function cond(z::Complex)
    # current condition is a property of z -> z^2 + c
    # i.e. once |z| > 2, then stop iterating because z_n will blow
    # abs2 is faster as it returns |z|^2 and does not have to 
    # compute square root. Just a little bit faster
    return abs2(z) > 4
end


# the function for iterating over $z_{n + 1} = f(z_{n})$
function f(z::Complex, c::Complex)
    return (z)^2 + c
end


# takes in the dimensions of the array to be produced arround the given origin and for the given scale
function return_image(size, max_iter::Int=30, scale::Float64=1.0, origin::Complex=0+0im, Z0::Complex=0.0+0.0im, C::Complex=0.0+0.0im, scheme=ColorSchemes.inferno)
    height = size[1]
    width = size[2]

    # only the width is scaled, the height is free to take any range
    dot_size = 2 * scale / width                            # imagine the width going from -scale to scale then dot size is the size of the dots that cover the width
    topright_elem = scale + (height / width) * scale * 1im  # depicting the frame arround origin

    # the four corner cordinates
    real_max = origin.re + topright_elem.re
    real_min = origin.re - topright_elem.re

    imag_max = origin.im + topright_elem.im
    imag_min = origin.im - topright_elem.im

    # precalculated colour coonversions for all possible iteration number before blowing
    scheme_sized = get_cmap(scheme, max_iter)

    # the iteration for different points(cordinates (real, imag)) on the canvas
    real_range = range(real_min, real_max - dot_size, step=dot_size)
    imag_range = range(imag_min, imag_max - dot_size, step=dot_size)

    # The complex-number array in the current frame to evaluate on
    complexes = complex.(real_range', imag_range)

    # mandel(parameter-space) - Z0 is constant and c is changing, the colors are for different c
    # julia(state-space) - C is constant and z0 is changing, the colors are for different z0
    mandel_steps = iter_count.(Z0, complexes, max_iter)
    julia_steps = iter_count.(complexes, C, max_iter)

    mandel_image = scheme_sized[:, mandel_steps]
    julia_image = scheme_sized[:, julia_steps]

    return mandel_image, julia_image
end


# saves all possible color scheme values computed once in a list,
# instead of calculating them again repeatedly on new occurrences
function get_cmap(colorscheme, max_iter)
    colors = zeros(Float64, (3, max_iter+1))
    for i=1:max_iter 
        colors[:,i] = get_color(colorscheme, i, max_iter)
    end
    colors[:,max_iter+1] = [0.0, 0.0, 0.0]
    return colors
end


# the function to map iter num to a colour
function get_color(colorscheme, step, max_iter)
    if step == max_iter + 1
        return [0, 0, 0]  # return black if took too many steps
    end
    color = get(colorscheme, step, (1, max_iter))  # a gradient in the colorscheme
    return [color.r, color.g, color.b]  # return only relevant things from color struct
end


# MAIN -----------------------------------------
size = (100000, 100000)
output = return_image(size, 25, 0.125, -1.15+0.3im)
mandel = output[1]
julia = output[2]

save("test.bmp", colorview(RGB, mandel))
# save("./tanh_julia_vishal.bmp", colorview(RGB, julia))

