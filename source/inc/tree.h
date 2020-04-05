#ifndef __tree_h__
#define __tree_h__

#include <functional>
#include <limits>
#include <vector>
#include "node.h"
#include "types.h"

class Tree {
 public:
  Tree(std::function<double(const Joint&, const Joint&)> distance_metric,
       const size_t max_nodes);

  static constexpr NodeID kNone = -1;

  NodeID Add(const Node& new_node, bool is_goal = false);
  bool IsFull() const;
  std::vector<NodeID> near_idxs(const Joint& position, double radius);
  NodeID nearest(const Joint& position);
  Node GetNode(const NodeID node_id) const;
  Joint GetBestNodePosition();
  std::vector<NodeID> Solution() const;
  void SetNode(const NodeID node_id, const Node& node);
  double CalculateNearRadius();
  void Report();

 private:
  const std::function<double(const Joint&, const Joint&)> distance_metric_;
  const size_t kMaxNodes;
  std::vector<Node> nodes_;
  std::vector<NodeID> goal_node_idxs_;
  std::pair<NodeID, double> best_node_and_cost_to_go_ =
      std::make_pair(kNone, std::numeric_limits<double>::infinity());
};

#endif
