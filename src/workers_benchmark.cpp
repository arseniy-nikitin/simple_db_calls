#include "workers.hpp"

#include <cstdint>   // for std::uint64_t
#include <iterator>  // for std::size
#include <string_view>

#include <benchmark/benchmark.h>
#include <userver/engine/run_standalone.hpp>

void CreateWorkerBenchmark(benchmark::State& state) {
  userver::engine::RunStandalone([&] {
    workers::api::Worker worker;
    worker.set_id(1);
    worker.set_position("Senior Latte Drinker");

    workers::api::CreateWorkerRequest request;
    request.set_allocated_worker(&worker);

    workers::api::CreateWorkerResponse response;

    for (auto _ : state) {
      simple_db_calls::CreateWorker(request, &response);
      benchmark::DoNotOptimize(response);
    }
  });
}

BENCHMARK(CreateWorkerBenchmark);

void GetWorkerBenchmark(benchmark::State& state) {
  userver::engine::RunStandalone([&] {
    workers::api::GetWorkerRequest request;
    request.set_id(1);

    workers::api::GetWorkerResponse response;

    for (auto _ : state) {
      simple_db_calls::GetWorker(request, &response);
      benchmark::DoNotOptimize(response);
    }
  });
}

BENCHMARK(GetWorkerBenchmark);

void UpdateWorkerBenchmark(benchmark::State& state) {
  userver::engine::RunStandalone([&] {
    workers::api::Worker worker;
    worker.set_id(1);
    worker.set_position("Junior Latte Drinker");

    workers::api::UpdateWorkerRequest request;
    request.set_allocated_worker(&worker);

    workers::api::UpdateWorkerResponse response;

    for (auto _ : state) {
      simple_db_calls::UpdateWorker(request, &response);
      benchmark::DoNotOptimize(response);
    }
  });
}

BENCHMARK(UpdateWorkerBenchmark);

void DeleteWorkerBenchmark(benchmark::State& state) {
  userver::engine::RunStandalone([&] {
    workers::api::DeleteWorkerRequest request;
    request.set_id(1);

    workers::api::DeleteWorkerResponse response;

    for (auto _ : state) {
      simple_db_calls::DeleteWorker(request, &response);
      benchmark::DoNotOptimize(response);
    }
  });
}

BENCHMARK(DeleteWorkerBenchmark);