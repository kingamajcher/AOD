# Kinga Majcher 272354

using JuMP
using GLPK

containers_matrix = [0 0 1 0 0 0 0;
                     0 0 0 0 0 0 1;
                     1 0 0 0 1 0 0;
                     1 0 0 0 0 0 1;
                     1 0 0 1 0 0 0;
                     0 0 1 0 0 0 1;
                     1 0 0 0 0 0 0]

camera_range = 4

function solve_problem(containers_matrix::Matrix, camera_range::Int)
    m, n = size(containers_matrix)
    model = Model(GLPK.Optimizer)

    # in each square there can be a camera 
    @variable(model, cameras_matrix[1:m, 1:n], Bin)

    for i in 1:m
        for j in 1:n
            if containers_matrix[i, j] == 1
                # if there is a container in square there cannot be a camera
                @constraint(model, cameras_matrix[i, j] == 0)

                # each container must be in range of at least one camera 
                @constraint(model,  sum(cameras_matrix[max(i - camera_range, 1):min(i + camera_range, m), j]) + sum(cameras_matrix[i, max(j - camera_range, 1):min(j + camera_range, n)]) >= 1)
            end
        end
    end

    # looking for minumal number of cameras
    @objective(model, Min, sum(cameras_matrix))

    optimize!(model)

    # Check if the solution is optimal
    if termination_status(model) == MOI.OPTIMAL
        minimal_cameras = objective_value(model)
        println("Minimal cameras: $minimal_cameras\n")
        display(containers_matrix -= value.(cameras_matrix))
        println("\n-1.0: camera")
        println(" 1.0: container")
    elseif termination_status(model) == MOI.INFEASIBLE
        println("The model is infeasible.")
        return nothing
    else
        println("No optimal solution found.")
        return nothing
    end
end

solve_problem(containers_matrix, camera_range)