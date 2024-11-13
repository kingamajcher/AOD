# Kinga Majcher 272354

using JuMP
using GLPK

basic_production_costs = [6000, 4000, 8000, 9000]
additional_production_costs = [8000, 6000, 10000, 11000]
storage_cost = 1500
max_basic_production = [100, 100, 100, 100]
max_additional_production = [60, 65, 70, 60]
demand = [130, 80, 125, 195]
starting_stored_amount = 15
storage_capacity = 70

function solve_problem(basic_production_costs::Vector, additional_production_costs::Vector, storage_cost::Int, max_basic_production::Vector, max_additional_production::Vector, demand::Vector, starting_stored_amount::Int, storage_capacity::Int)
    K = length(basic_production_costs)
    model = Model(GLPK.Optimizer)

    # amount of basic units produced must not be negative
    @variable(model, basic_units_produced[1:K] >= 0)

    # amount of additional units produced must not be negative
    @variable(model, additional_units_produced[1:K] >= 0)

    # amount of stored units must not be negative
    @variable(model, stored_units[1:K+1] >= 0)

    # amount of basic units produced cannot exceed max basic production
    @constraint(model, basic_units_produced .<= max_basic_production)

    # amount of additional units produced cannot exceed max additional production
    @constraint(model, additional_units_produced .<= max_additional_production)

    # amount of units in storage cannot exceed storage capacity
    @constraint(model, [j in 1:K], stored_units[j] <= storage_capacity)

    # only what is left after meeting demand can be put into storage
    @constraint(model, [j in 1:K], stored_units[j+1] == basic_units_produced[j] + additional_units_produced[j] + stored_units[j] - demand[j])

    # at the end storage must be empty
    @constraint(model, stored_units[K+1] == 0)

    # at first period there is nothing that can be put in storage so s_1 = s_0
    @constraint(model, stored_units[1] == starting_stored_amount)

    # looking for minimal cost
    @objective(model, Min, sum(basic_production_costs .* basic_units_produced) + sum(additional_production_costs .* additional_units_produced) + sum(stored_units .* storage_cost))

    optimize!(model)

    # Check if the solution is optimal
    if termination_status(model) == MOI.OPTIMAL
        minimal_cost = objective_value(model)
        println("Minimal cost: $minimal_cost\n")
        println("Basic units produced:")
        display(value.(basic_units_produced))
        println()
        println("Additional units produced:")
        display(value.(additional_units_produced))
        println()
        println("Stored units:")
        display(value.(stored_units))
        println()
    elseif termination_status(model) == MOI.INFEASIBLE
        println("The model is infeasible.")
        return nothing
    else
        println("No optimal solution found.")
        return nothing
    end
end

solve_problem(basic_production_costs, additional_production_costs, storage_cost, max_basic_production, max_additional_production, demand, starting_stored_amount, storage_capacity)
