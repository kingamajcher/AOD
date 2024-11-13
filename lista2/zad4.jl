# Kinga Majcher 272354

using JuMP
using GLPK

cities = 10
starting_city = 1
ending_city = 10
max_time = 15
arches_data = [[1, 2, 3, 4], 
[1, 3, 4, 9], 
[1, 4, 7, 10], 
[1, 5, 8, 12], 
[2, 3, 2, 3], 
[3, 4, 4, 6], 
[3, 5, 2, 2], 
[3, 10, 6, 11], 
[4, 5, 1, 1], 
[4, 7, 3, 5], 
[5, 6, 5, 6], 
[5, 7, 3, 3], 
[5, 10, 5, 8], 
[6, 1, 5, 8], 
[6, 7, 2, 2], 
[6, 10, 7, 11], 
[7, 3, 4, 6], 
[7, 8, 3, 5], 
[7, 9, 1, 1], 
[8, 9, 1, 2], 
[9, 10, 2, 2]]

my_cities = 10
my_starting_city = 1
my_ending_city = 10
my_max_time = 18
my_arches_data = [
[1, 2, 3, 4],
[1, 3, 5, 6],
[1, 4, 8, 7],
[1, 7, 2, 10],
[2, 5, 2, 3],
[2, 6, 4, 6],
[3, 5, 3, 2],
[3, 6, 4, 4],
[4, 6, 1, 2],
[4, 7, 2, 5],
[5, 8, 3, 3],
[6, 9, 6, 5],
[7, 9, 7, 3],
[7, 10, 1, 10],
[8, 10, 5, 6],
[9, 10, 2, 3]]


function print_used_arches(matrix)
    rows, cols = size(matrix)
    for i in 1:rows
        for j in 1:cols
            if matrix[i, j] != 0.0
                println("($i, $j)")
            end
        end
    end
end

function solve_problem(cities::Int, starting_city::Int, ending_city::Int, max_time::Int, arches_data::Vector{Vector{Int}}
    )
    arches_matrix = zeros(cities, cities)
    costs_matrix = zeros(cities, cities)
    times_matrix = zeros(cities, cities)

    for arch in arches_data
        i, j, c_ij, t_ij = arch
        arches_matrix[i, j] = 1
        costs_matrix[i, j] = c_ij
        times_matrix[i, j] = t_ij
    end

    model = Model(GLPK.Optimizer)

    # each arch can be either used or unused
    @variable(model, 0 <= arches_used[1:cities, 1:cities] <= 1, Int)

    # if arch does not exist it cannot be used
    @constraint(model, arches_used .<= arches_matrix)

    # there can be only one arch used starting from starting city and zero arches ending in it
    @constraint(model, sum(arches_used[starting_city, :]) == 1)
    @constraint(model, sum(arches_used[:, starting_city]) == 0)

    # there can be only one arch used ending in ending city and no arches starting in it
    @constraint(model, sum(arches_used[:, ending_city]) == 1)
    @constraint(model, sum(arches_used[ending_city, :]) == 0)
    

    # for any other city number of arches starting in it must equal number of arches ending in it
    for i in 1:cities
        if i != starting_city && i != ending_city
            @constraint(model, sum(arches_used[i, :]) == sum(arches_used[:, i]))
        end
    end

    # each journey between starting city and ending city cannot exceed max time
    @constraint(model, sum(arches_used .* times_matrix) <= max_time)

    # looking for minimal cost
    @objective(model, Min, sum(arches_used .* costs_matrix))

    optimize!(model)

    # Check if the solution is optimal
    if termination_status(model) == MOI.OPTIMAL
        minimal_cost = objective_value(model)
        println("Minimal cost: $minimal_cost\n")
        println("Arches used:")
        display(value.(arches_used))
        println()
        print_used_arches(value.(arches_used))
    elseif termination_status(model) == MOI.INFEASIBLE
		println("The model is infeasible.")
		return nothing
    else
        println("No optimal solution found.")
        return nothing
    end
end

solve_problem(cities, starting_city, ending_city, max_time, arches_data)

solve_problem(my_cities, my_starting_city, my_ending_city, my_max_time, my_arches_data)