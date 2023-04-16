#=
# AUTHOR: Vishal Paudel
# DATE: Sat Apr 16 11:13:11 IST 2023
#
# NOTE: None
# TODO: None
=#

using Plots

function cond(z::Complex)
    return (abs2(z)) > 4
end


function f(z::Complex, c::Complex)
    return c * c + z * z * z
end


function iterCount(z0::Complex, C::Complex, maxIter::Int)
    z = z0
    c = C
    for iter = 1:1:maxIter
        z = f(z, c)
        if cond(z)
            return iter
        end
    end
    return maxIter + 1  # to show more than maxIter
end


function returnArray(size::Int)
    Z0 = Complex(-0.1, -0.2) # 0 + 0im
    C = Complex(0.0, 0.0)

    # Sqare only
    mandelArr = zeros(Int, (size, size))
    juliaArr = zeros(Int, (size, size))

    # Odd values can leave one line of pixels uncoloured
    scale = 0.25
    origin = 0 + 0im

    function point(i::Int, j::Int)
        x = (j / size - 1 / 2)
        y = (1 / 2 - i / size)
        z = ((x + y * im) + origin) / scale
        return z
    end

    maxIter = 30
    for i = 1:1:size
        for j = 1:1:size
            p = point(i, j)
            z0 = p
            c = p

            mandelArr[i, j] = iterCount(Z0, c, maxIter)
            juliaArr[i, j] = iterCount(z0, C, maxIter)
        end
    end

    return mandelArr, juliaArr
end

mandel, julia = returnArray(2000)

Plots.heatmap(mandel, color=:inferno)
# Plots.heatmap(julia, yflip=true, color=:inferno)
