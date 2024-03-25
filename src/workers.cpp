#include "workerss.hpp"
#include "workers_queries.hpp"

#include <fmt/format.h>

#include <userver/clients/dns/component.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/utils/assert.hpp>

namespace simple_db_calls {

void Workers::CreateWorker(workers::api::WorkersServiceBase::CreateWorkerCall& call,
                           workers::api::CreateWorkerRequest&& request) {
  auto position = request.worker().position();
  if (position.empty() || position.size() > kMaxStringLength) {
    grpc::Status status(grpc::StatusCode::INVALID_ARGUMENT, "Invalid position argument");
    call.FinishWithError(status);
  }
    
  auto result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster,
      kCreateWorkerQuery,
      position);
  if (result.empty()) {
    grpc::Status status(grpc::StatusCode::INVALID_ARGUMENT, "Error while creating worker");
    call.FinishWithError(status);
  }

  int id = result.AsSingleRow<int>();
  workers::api::WorkersResponse response;
  response.set_id(id);
  call.Finish(response);
}

void Workers::GetWorker(workers::api::WorkersServiceBase::GetWorkerCall& call,
                        workers::api::GetWorkerRequest&& request) {
  auto id = request.id();

  auto result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster,
      kGetWorkerQuery,
      id);
  if (result.empty()) {
    grpc::Status status(grpc::StatusCode::INVALID_ARGUMENT, "Error while getting worker");
    call.FinishWithError(status);
  }

  const auto& row = result.rows().front();
  int worker_id = row["id"].As<int>();
  std::string position = row["position"].As<std::string>();

  workers::api::Worker worker;
  worker.set_id(worker_id);
  worker.set_position(position);

  workers::api::WorkersResponse response;
  *response.mutable_worker() = worker;
  call.Finish(response);
}

void Workers::UpdateWorker(workers::api::WorkersServiceBase::UpdateWorkerCall& call,
                           workers::api::UpdateWorkerRequest&& request) {
  auto id = request.worker().id();
  auto position = request.worker().position();
  if (position.empty() || position.size() > kMaxStringLength) {
    grpc::Status status(grpc::StatusCode::INVALID_ARGUMENT, "Invalid position argument");
    call.FinishWithError(status);
  }
  
  auto result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster,
      kUpdateWorkerQuery,
      position,
      id);
  if (result.empty()) {
    grpc::Status status(grpc::StatusCode::INVALID_ARGUMENT, "Error while updating worker");
    call.FinishWithError(status);
  }

  workers::api::WorkersResponse response;
  response.set_id(id);
  call.Finish(response);
}

void Workers::DeleteWorker(workers::api::WorkersServiceBase::DeleteWorkerCall& call,
                           workers::api::DeleteWorkerRequest&& request) {
  auto id = request.id();

  auto result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster,
      kDeleteWorkerQuery,
      id);
  if (result.empty()) {
    grpc::Status status(grpc::StatusCode::INVALID_ARGUMENT, "Error while deleting worker");
    call.FinishWithError(status);
  }

  const auto& row = result.rows().front();
  int worker_id = row["id"].As<int>();
  std::string position = row["position"].As<std::string>();

  workers::api::Worker worker;
  worker.set_id(worker_id);
  worker.set_position(position);

  workers::api::WorkersResponse response;
  *response.mutable_worker() = worker;
  call.Finish(response);
}

void AppendWorkers(userver::components::ComponentList& component_list) {
  component_list.Append<Workers>();
  component_list.Append<userver::components::Postgres>("postgres-db");
  component_list.Append<userver::clients::dns::Component>();
}

}  // namespace simple_db_calls
