#include "rofls.hpp"
#include "rofls_queries.hpp"

#include <fmt/format.h>

#include <userver/clients/dns/component.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/utils/assert.hpp>

namespace simple_db_calls {

void Rofls::CreateRofl(rofls::api::RoflsServiceBase::CreateRoflCall& call,
                       rofls::api::RoflRequest&& request) {
  auto razryvnaya = request.razryvnaya();
  if (razryvnaya.empty()) {
    grpc::Status status(grpc::StatusCode::INVALID_ARGUMENT, "Empty string");
    call.FinishWithError(status);
  }
    
  auto result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster,
      kCreateRoflQuery,
      razryvnaya);
  if (!result) {
    grpc::Status status(grpc::StatusCode::INVALID_ARGUMENT, "Invalid string");
    call.FinishWithError(status);
  }

  int id = result.AsSingleRow<int>();
  rofls::api::RoflResponse response;
  response.set_id(id);
  call.Finish(response);
}

void Rofls::GetRofl(rofls::api::RoflsServiceBase::GetRoflCall& call,
                    rofls::api::RoflRequest&& request) {
  auto id = request.id();

  auto result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster,
      kGetRoflQuery,
      id);
  if (!result) {
    grpc::Status status(grpc::StatusCode::INVALID_ARGUMENT, "Invalid id");
    call.FinishWithError(status);
  }

  rofls::api::RoflResponse response;
  response.set_rofl(rofl);
  call.Finish(response);
}

void Rofls::UpdateRofl(rofls::api::RoflsServiceBase::UpdateRoflCall& call,
                       rofls::api::RoflRequest&& request) {
  auto id = request.id();
  auto razryvnaya = request.razryvnaya();
  if (razryvnaya.empty()) {
    grpc::Status status(grpc::StatusCode::INVALID_ARGUMENT, "Empty string");
    call.FinishWithError(status);
  }
  
  auto result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster,
      kUpdateRoflQuery,
      razryvnaya,
      id);
  if (!result) {
    grpc::Status status(grpc::StatusCode::INVALID_ARGUMENT, "Invalid id");
    call.FinishWithError(status);
  }

  call.Finish();
}

void Rofls::DeleteRofl(rofls::api::RoflsServiceBase::DeleteRoflCall& call,
                       rofls::api::RoflRequest&& request) {
  auto id = request.id();

  auto result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster,
      kDeleteRoflQuery,
      id);
  if (!result) {
    grpc::Status status(grpc::StatusCode::INVALID_ARGUMENT, "Invalid id");
    call.FinishWithError(status);
  }

  call.Finish();
}

void AppendRofls(userver::components::ComponentList& component_list) {
  component_list.Append<Rofls>();
  component_list.Append<userver::components::Postgres>("postgres-db");
  component_list.Append<userver::clients::dns::Component>();
}

}  // namespace simple_db_calls
