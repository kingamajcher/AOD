# Kinga Majcher 272354

using JuMP
using GLPK
using Printf

prices = [9, 7, 6, 5]
material_costs = [4, 1, 1, 1]
demand = [400, 100, 150, 500]
availibility = [60, 60, 60]
machine_costs = [2, 2, 3]
machine_time_matrix = [5 10 6; 3 6 4; 4 5 3; 4 2 1]

function solve_problem(prices::Vector, material_costs::Vector, demand::Vector, availibility::Vector, machine_costs::Vector, machine_time_matrix::Matrix)
    m, n = size(machine_time_matrix) # m - products, n - machines
    model = Model(GLPK.Optimizer)

    availibility *= 60
    machine_costs /= 60

    # amount of each product cannot be negative (>=0)
    @variable(model, amount_produced[1:m] >= 0)

    # each machine cannot exceed weekly time limit
    @constraint(model, [j in 1:n], sum(amount_produced[i]*machine_time_matrix[i, j] for i in 1:m) <= availibility[j])

    # cannot produce more than demand
    @constraint(model, amount_produced .<= demand)

    # looking for maximum profit
    @objective(model, Max, sum((prices[i] - material_costs[i]) * amount_produced[i] for i in 1:m) - sum(machine_costs[j] * sum(machine_time_matrix[i, j] * amount_produced[i] for i in 1:m) for j in 1:n))

    optimize!(model)

    # Check if the solution is optimal
    if termination_status(model) == MOI.OPTIMAL
        maximum_profit = objective_value(model)
        println("Maximum profit: $maximum_profit\n")
        n = length(amount_produced)
        println("Optimal amounts to produce:")
        for i in 1:n
            @printf("%-10s ", value(amount_produced[i]))
        end
        println()
    elseif termination_status(model) == MOI.INFEASIBLE
        println("The model is infeasible.")
        return nothing
    else
        println("No optimal solution found.")
    end
end

solve_problem(prices, material_costs, demand, availibility, machine_costs, machine_time_matrix)