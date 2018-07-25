// Copyright (c) 2018 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "paddle/fluid/framework/details/ssa_graph_builder.h"

#include <string>

namespace paddle {
namespace framework {
namespace details {

class SSAGraghBuilderWithChecker : public SSAGraphBuilder {
 public:
  std::unique_ptr<ir::Graph> Apply(
      std::unique_ptr<ir::Graph> graph) const override {
    auto new_graph =
        Get<SSAGraphBuilder>("previous_pass").Apply(std::move(graph));
    PADDLE_ENFORCE(IsValidGraph(new_graph.get()));
    return new_graph;
  }

  int GetVarDeviceID(const std::string& var_name) const override {
    return Get<SSAGraphBuilder>("previous_pass").GetVarDeviceID(var_name);
  }

  bool IsValidGraph(const ir::Graph* graph) const;
};

}  // namespace details
}  // namespace framework
}  // namespace paddle
