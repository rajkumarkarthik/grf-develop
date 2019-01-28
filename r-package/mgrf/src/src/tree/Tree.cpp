/*-------------------------------------------------------------------------------
  This file is part of generalized random forest (mgrf).

  mgrf is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  mgrf is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with mgrf. If not, see <http://www.gnu.org/licenses/>.
 #-------------------------------------------------------------------------------*/

#include <iterator>
#include "sampling/RandomSampler.h"

#include "tree/Tree.h"
#include "commons/utility.h"

Tree::Tree(size_t root_node,
           const std::vector<std::vector<size_t>>& child_nodes,
           const std::vector<std::vector<size_t>>& leaf_samples,
           const std::vector<size_t>& split_vars,
           const std::vector<double>& split_values,
           const std::vector<size_t>& oob_samples,
           const PredictionValues& prediction_values) :
    root_node(root_node),
    child_nodes(child_nodes),
    leaf_samples(leaf_samples),
    split_vars(split_vars),
    split_values(split_values),
    oob_samples(oob_samples),
    prediction_values(prediction_values) {}

std::vector<size_t> Tree::find_leaf_nodes(Data* prediction_data,
                                          const std::vector<size_t>& samples) {
  bool use_subsample = !samples.empty();
  const std::vector<std::vector<size_t>>& child_nodes = get_child_nodes();

  std::vector<size_t> prediction_leaf_nodes;
  prediction_leaf_nodes.resize(prediction_data->get_num_rows());

  size_t num_samples_predict = use_subsample ? samples.size() : prediction_data->get_num_rows();

  for (size_t i = 0; i < num_samples_predict; ++i) {
    size_t sample = use_subsample ? samples[i] : i;

    size_t node = root_node;
    while (true) {
      // Break if terminal node
      if (is_leaf(node)) {
        break;
      }

      // Move to child
      size_t split_var = get_split_vars()[node];
      double value = prediction_data->get(sample, split_var);
      if (value <= get_split_values()[node]) {
        // Move to left child
        node = child_nodes[0][node];
      } else {
        // Move to right child
        node = child_nodes[1][node];
      }
    }

    prediction_leaf_nodes[sample] = node;
  }
  return prediction_leaf_nodes;
}

void Tree::prune_empty_leaves() {
  size_t num_nodes = leaf_samples.size();
  for (size_t n = num_nodes; n > root_node; n--) {
    size_t node = n - 1;
    if (is_leaf(node)) {
      continue;
    }

    size_t& left_child = child_nodes[0][node];
    if (!is_leaf(left_child)) {
      prune_node(left_child);
    }

    size_t& right_child = child_nodes[1][node];
    if (!is_leaf(right_child)) {
      prune_node(right_child);
    }
  }
  prune_node(root_node);
}

void Tree::prune_node(size_t& node) {
  size_t left_child = child_nodes[0][node];
  size_t right_child = child_nodes[1][node];

  // If either child is empty, prune this node.
  if (is_empty_leaf(left_child) || is_empty_leaf(right_child)) {
    // Empty out this node.
    child_nodes[0][node] = 0;
    child_nodes[1][node] = 0;

    // If one of the children is not empty, promote it.
    if (!is_empty_leaf(left_child)) {
      node = left_child;
    } else if (!is_empty_leaf(right_child)) {
      node = right_child;
    }
  }
}

bool Tree::is_leaf(size_t node) {
  return child_nodes[0][node] == 0 && child_nodes[1][node] == 0;
}

bool Tree::is_empty_leaf(size_t node) {
  return is_leaf(node) && leaf_samples[node].empty();
}
