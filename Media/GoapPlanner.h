#pragma once

#include "CoreMinimal.h"
#include "Actions.h"
#include "Goals.h"

/**
 * The Nodes that the planner uses to create and check possible sequences of action to achieve a goal.
 */
class FNode : public TSharedFromThis<FNode>
{
public:
	/// <summary>
	/// The node that will be evaluated after the completion of this node's action.
	/// If this node represents the goal, Parent will be nullptr.
	/// </summary>
	TSharedPtr<FNode> Parent;

	/// <summary>
	/// The AgentAction that will be carried out by this node.
	/// </summary>
	TSharedPtr<FAgentAction> Action;

	/// <summary>
	/// The World States that need to be made true for the plan to be valid
	/// </summary>
	TSet<TSharedPtr<FWorldState>> ProblemStates;

	/// <summary>
	/// The cost of moving to this node (Same variable as cost in other parts of the framework) 
	/// </summary>
	float GCost;

	/// <summary>
	/// The Heuristic, this represents the number of problems for this action
	/// </summary>
	int32 HCost;

	/// <summary>
	/// The combined cost of GCost and HCost
	/// </summary>
	float FCost;

	
	/// <summary>
	/// Constructor for the goal node
	/// </summary>
	/// <param name="GoalDesiredEffects">The World States that the goal is trying to solve</param>
	FNode(const TSet<TSharedPtr<FWorldState>>& GoalDesiredEffects);

	/// <summary>
	/// Constructor for action nodes
	/// </summary>
	/// <param name="parent">The node that will be evaluated after the completion of this node's action.</param>
	/// <param name="action">The AgentAction that will be carried out by this node.</param>
	FNode(TSharedPtr<FNode> parent, TSharedPtr<FAgentAction> action);

	~FNode();
};

/**
 * The class that a completed plan is returned as to an AAIController
 */
class FActionPlan : public TSharedFromThis<FActionPlan>
{
public:
	/// <summary>
	/// The goal this ActionPlan hopes to achieve
	/// </summary>
	FAgentGoal* agentGoal;

	/// <summary>
	/// The queue of actions to be taken to achieve the goal.
	/// </summary>
	TArray<TSharedPtr<FAgentAction>> ActionQueue;

	/// <summary>
	/// The cost of all actions combined
	/// </summary>
	float TotalCost;

	FActionPlan(FAgentGoal& Goal, TQueue<TSharedPtr<FAgentAction>>* Actions, float GCost);
	~FActionPlan();
	
private:
	
	bool operator==(const FNode& n1, const FNode& n2) const;
};

/**
 * 
 */
class ENEMYAIWORKSPACE_API FGoapPlanner
{
public:
	/// <summary>
	/// Variable used to keep track of the number of created nodes for debugging purposes
	/// </summary>
	static inline int32 DebugNodeCount = 0;

	static TSharedPtr<FActionPlan> Plan(
		TSet<TSharedPtr<FAgentAction>>& Actions, TSet<TSharedPtr<FAgentGoal>>& Goals, FAgentGoal* MostRecentGoal);

	static TSharedPtr<FNode> FindPath(FNode& GoalNode, TSet<TSharedPtr<FAgentAction>>& Actions);

private:
	/// <summary>
	/// The list of viable Nodes to check
	/// </summary>
	static inline TArray<TSharedPtr<FNode>> OpenList{};
	static inline TSharedPtr<FNode> CheapestNodeFound = nullptr;

	static void FindHelpfulActions(FNode& Parent, TSet<TSharedPtr<FAgentAction>>& Actions);
	
	static void CleanUpNodes();
};
