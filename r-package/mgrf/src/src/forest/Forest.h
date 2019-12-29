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

#ifndef MGRF_FOREST_H_
#define MGRF_FOREST_H_

#include <memory>

#include "tree/TreeTrainer.h"
#include "commons/globals.h"
#include "tree/Tree.h"
#include "commons/DefaultData.h"
#include "commons/Observations.h"
#include "eigen3/Eigen/Eigen"

class Forest {
public:
  static Forest create(std::vector<std::shared_ptr<Tree>> trees,
                       Data* data,
                       std::unordered_map<size_t, std::vector<size_t>> observables);

  Forest(const std::vector<std::shared_ptr<Tree>>& trees,
         const Observations& observations,
         size_t num_variables);

  const Observations& get_observations() const {
    return observations;
  };

  const std::vector<std::shared_ptr<Tree>>& get_trees() const {
    return trees;
  }

  const size_t get_num_variables() const {
    return num_variables;
  }

protected:
  std::vector<std::shared_ptr<Tree>> trees;
  Observations observations;
  size_t num_variables;
};

#endif /* MGRF_FOREST_H_ */
