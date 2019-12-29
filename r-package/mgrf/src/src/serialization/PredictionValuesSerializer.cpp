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

#include "serialization/PredictionValuesSerializer.h"
#include "commons/utility.h"

void PredictionValuesSerializer::serialize(std::ostream& stream, const PredictionValues& prediction_values) {
  size_t num_nodes = prediction_values.get_num_nodes();
  stream.write((char*) &num_nodes, sizeof(num_nodes));

  size_t num_types = prediction_values.get_num_types();
  stream.write((char*) &num_types, sizeof(num_types));

  for (size_t node = 0; node < num_nodes; node++) {
    auto values = prediction_values.get_values(node);
    size_t values_size = values.size();
    stream.write((char*) &values_size, sizeof(values_size));
    for (size_t i = 0; i < values_size; i++) {
      write_matrix(values[i], stream);
    }
  }
}

PredictionValues PredictionValuesSerializer::deserialize(std::istream& stream) {
  size_t num_nodes;
  stream.read((char*) &num_nodes, sizeof(num_nodes));

  size_t num_types;
  stream.read((char*) &num_types, sizeof(num_types));

  std::vector<std::vector<Eigen::MatrixXd>> all_values;
  for (size_t i = 0; i < num_nodes; i++) {
    size_t values_size;
    stream.read((char*) &values_size, sizeof(values_size));
    std::vector<Eigen::MatrixXd> values (values_size);
    for (size_t j = 0; j < values_size; j++) {
      values[j] = read_matrix(stream);
    }
    all_values.push_back(values);
  }
  return PredictionValues(all_values, num_nodes, num_types);
}
