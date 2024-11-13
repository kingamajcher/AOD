# Kinga Majcher 272354

using JuMP
using GLPK

min_police_cars_per_shift = [10, 20, 18]
min_police_cars_per_district = [10, 14, 13]

min_police_cars_matrix = [
	2 4 3;
	3 6 5;
	5 7 8]

max_police_cars_matrix = [
	3 5 7;
	5 7 10;
	8 12 10]

function solve_problem(min_police_cars_per_shift::Vector, min_police_cars_per_district::Vector, min_police_cars_matrix::Matrix, max_police_cars_matrix::Matrix)
    m = length(min_police_cars_per_district)
    n = length(min_police_cars_per_shift)
    model = Model(GLPK.Optimizer)

    # number of police cars used
    @variable(model, police_cars_used[1:m, 1:n] >= 0, Int)

    # for each shift there must be more police cars than min_cars_per_shift
    @constraint(model, [i in 1:m], sum(police_cars_used[:, i]) >= min_police_cars_per_shift[i])

    # for each district there must be more police cars than min_police_cars_per_district
    @constraint(model, [j in 1:n], sum(police_cars_used[j, :]) >= min_police_cars_per_district[j])

    # number of police cars must be between minimum and maximum
    @constraint(model, min_police_cars_matrix .<= police_cars_used .<= max_police_cars_matrix)

    # looking for minimum police cars number
    @objective(model, Min, sum(police_cars_used))

    optimize!(model)

    # Check if the solution is optimal
    if termination_status(model) == MOI.OPTIMAL
        minimal_cars = objective_value(model)
        println("Minimal police cars: $minimal_cars\n")
        println("Police cars by district and shift: used:")
        display(value.(police_cars_used))
        println()
    elseif termination_status(model) == MOI.INFEASIBLE
		println("The model is infeasible.")
		return nothing
    else
        println("No optimal solution found.")
        return nothing
    end
end

solve_problem(min_police_cars_per_shift, min_police_cars_per_district, min_police_cars_matrix, max_police_cars_matrix)