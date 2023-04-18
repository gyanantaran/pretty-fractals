
using Images, Colors, ColorSchemes


# returns the number of iteration before the number($z_{n}$) blows off
# the output computed on z0 and c will be used for colouring later in `return_array` function
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
    return tanh(z) + c
end


# takes in the dimensions of the array to be produced arround the given origin
function return_image(size, max_iter::Int=30, scale::Float64=1.0, origin::Complex=0+0im, Z0::Complex=0.0+0.0im, C::Complex=0.0+0.0im, scheme=ColorSchemes.inferno)
    height = size[1]
    width = size[2]

    mandel_arr = zeros(Float64, (3, height, width))
    julia_arr = zeros(Float64, (3, height, width))

    # only the width is scaled, the height is free to take any range
    dot_size = 2 * scale / width                            # imagine the width going from -scale to scale then dot size is the size of the dots that cover the width
    topright_elem = scale + (height / width) * scale * 1im  # depicting the frame arround origin

    # the four corner cordinates
    real_max = origin.re + topright_elem.re
    real_min = origin.re - topright_elem.re

    imag_max = origin.im + topright_elem.im
    imag_min = origin.im - topright_elem.im


    # the iteration for different points(cordinates (real, imag)) on the canvas
    j = 1
    for imag=imag_min:dot_size:(imag_max-dot_size)
        i = 1
        for real=real_min:dot_size:(real_max-dot_size)

            c = real + imag * 1im  # for a fixed Z0(default 0 + 0im) and a particular c on the canvas
            # mandel(parameter-space) - Z0 is constant and c is changing, the colors are for different c
            mandel_arr[:, j, i] = get_color(scheme, iter_count(Z0, c, max_iter), max_iter)  # get color for the num of iterations
    
            z0 = real + imag * 1im  # for a fixed C(default 0 + 0im) and a particular z0 on the canvas 
            # julia(state-space) - C is constant and z0 is changing, the colors are for different z0
            julia_arr[:, j, i] = get_color(scheme, iter_count(z0, C, max_iter), max_iter)  # get color for the num of iterations

            i += 1
        end
        j += 1
    end

    return mandel_arr, julia_arr
end


# the function to map iter num to a colour
function get_color(colorscheme, step, max_steps)
    if step == max_steps + 1
        return [0, 0, 0]  # return black if took too many steps
    end
    color = get(colorscheme, step, (1, max_steps))  # a gradient in the colorscheme
    return [color.r, color.g, color.b]  # return only relevant things from color struct
end


output = return_image((15000, 15000), 25, 1.0, 0.0-1im)
mandel = output[1]
julia = output[2]


# MAIN -----------------------------------------
# save("test.bmp", colorview(RGB, mandel))
# save("./tanh_julia_vishal.bmp", colorview(RGB, julia))

