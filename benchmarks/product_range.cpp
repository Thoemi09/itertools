// Copyright (c) 2019-2020 Simons Foundation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0.txt
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <benchmark/benchmark.h>
#include <itertools/itertools.hpp>

using namespace itertools;

// ===== Range Loop

static void multi_loop_product(benchmark::State &state) {
  long a = 1 << state.range(0);
  long b = 1 << state.range(1);

  for (auto _ : state) {
    for (auto [i, j] : product_range(a, b)) { benchmark::ClobberMemory(); }
  }
}
BENCHMARK(multi_loop_product)->ArgsProduct({{8, 10}, {8, 10}});

// ===== Bare Loop

static void multi_loop_bare(benchmark::State &state) {
  long a = 1 << state.range(0);
  long b = 1 << state.range(1);

  for (auto _ : state) {
    for (auto i = 0; i < a; ++i) {
      for (auto j = 0; j < b; ++j) { benchmark::ClobberMemory(); }
    }
  }
}
BENCHMARK(multi_loop_bare)->ArgsProduct({{8, 10}, {8, 10}});
