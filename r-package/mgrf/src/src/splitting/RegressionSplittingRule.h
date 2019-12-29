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

#ifndef MGRF_REGRESSIONSPLITTINGRULE_H
#define MGRF_REGRESSIONSPLITTINGRULE_H

#include "tree/Tree.h"
#include "splitting/SplittingRule.h"
#include <unordered_map>
#include "commons/DefaultData.h"

class RegressionSplittingRule: public SplittingRule {
public:
  RegressionSplittingRule(Data* data, double alpha);

  ~RegressionSplittingRule();

  bool find_best_split(size_t node,
                       const std::vector<size_t>& possible_split_vars,
                       const std::unordered_map<size_t, Eigen::VectorXd>& labels_by_sample,
                       const std::vector<std::vector<size_t>>& samples,
                       std::vector<size_t>& split_vars,
                       std::vector<double>& split_values);

private:
  virtual void find_best_split_value_small_q(size_t node,
                                             size_t var,
                                             Eigen::VectorXd sum_node,
                                             size_t num_samples_node,
                                             size_t min_child_samples,
                                             double& best_value,
                                             size_t& best_var,
                                             double& best_decrease,
                                             const std::unordered_map<size_t, Eigen::VectorXd>& responses_by_sample,
                                             const std::vector<std::vector<size_t>>& samples);
  virtual void find_best_split_value_large_q(size_t node,
                                             size_t var,
                                             Eigen::VectorXd sum_node,
                                             size_t num_samples_node,
                                             size_t min_child_samples,
                                             double& best_value,
                                             size_t& best_var,
                                             double& best_decrease,
                                             const std::unordered_map<size_t, Eigen::VectorXd>& responses_by_sample,
                                             const std::vector<std::vector<size_t>>& samples);

  Data* data;
  size_t* counter;
  Eigen::VectorXd* sums;
  double alpha;

  DISALLOW_COPY_AND_ASSIGN(RegressionSplittingRule);
};


#endif //MGRF_REGRESSIONSPLITTINGRULE_H
