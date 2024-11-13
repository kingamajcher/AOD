# Kinga Majcher 272354

using JuMP
using GLPK

supply = [275000, 550000, 660000]
demand = [110000, 220000, 330000, 440000]
prices_matrix = [10 7 8; 
                 10 11 14; 
                 9 12 4; 
                 11 13 9]

function solve_problem(supply::Vector, demand::Vector, prices_matrix::Matrix)
    model = Model(GLPK.Optimizer)
    m, n = size(prices_matrix) # m - demand, airports; n - supply, companies

    # each company must send some fuel (>=0)
    @variable(model, fuel_amount_matrix[1:m, 1:n] >= 0)

    # each company must not send more than its max fuel supply
    @constraint(model, [i in 1:n], sum(fuel_amount_matrix[:, i]) <= supply[i])

    # the demand of each airport must be met
    @constraint(model, [j in 1:m], sum(fuel_amount_matrix[j, :]) == demand[j])

    # looking for minimal cost
    @objective(model, Min, sum(prices_matrix[j, i] * fuel_amount_matrix[j, i] for j in 1:m, i in 1:n))


    optimize!(model)

    # Check if the solution is optimal
    if termination_status(model) == MOI.OPTIMAL
        minimal_cost = objective_value(model)
        println("Minimal cost: $minimal_cost\n")
        println("Optimal fuel amounts to transport:")
        display(value.(fuel_amount_matrix))
    elseif termination_status(model) == MOI.INFEASIBLE
		println("The model is infeasible.")
		return nothing
    else
        println("No optimal solution found.")
        return nothing
    end
end

solve_problem(supply, demand, prices_matrix)
