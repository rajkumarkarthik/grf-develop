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

#ifndef MGRF_QUANTILERELABELINGSTRATEGY_H
#define MGRF_QUANTILERELABELINGSTRATEGY_H

#include "commons/Observations.h"
#include "tree/Tree.h"
#include "relabeling/RelabelingStrategy.h"

class QuantileRelabelingStrategy: public RelabelingStrategy {
public:
  QuantileRelabelingStrategy(const std::vector<double>& quantiles);
  std::unordered_map<size_t, Eigen::VectorXd> relabel(
      const std::vector<size_t>& samples,
      const Observations& observations);
private:
  std::vector<double> quantiles;
};


#endif //MGRF_QUANTILERELABELINGSTRATEGY_H