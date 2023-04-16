using Plots

function cond(z::Complex)
    return abs2(z) > 4
end

function f(z::Complex, c::Complex)
    return c^2 + z^3
end

function iter_count(z0::Complex, c::Complex, max_iter::Int)
    z = z0
    for iter in 1:max_iter
        z = f(z, c)
        cond(z) && return iter
    end
    return max_iter + 1
end

function return_array(size::Int, z0::Complex=-0.1-0.2im, c::Complex=0.0+0.0im, max_iter::Int=30, scale::Float64=0.25, origin::Complex=0+0im)
    mandel_arr = [iter_count(point(i, j, size, scale, origin), point(i, j, size, scale, origin), max_iter) for i in 1:size, j in 1:size]
    julia_arr = [iter_count(point(i, j, size, scale, origin), c, max_iter) for i in 1:size, j in 1:size]
    return mandel_arr, julia_arr
end

function point(i::Int, j::Int, size::Int, scale::Float64, origin::Complex)
    x = (j / size - 1 / 2)
    y = (1 / 2 - i / size)
    z = ((x + y * im) + origin) / scale
    return z
end

mandel, julia = return_array(2000)

heatmap(mandel, color=:inferno)
# heatmap(julia, yflip=true, color=:inferno)
