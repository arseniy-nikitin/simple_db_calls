#pragma once

#include <string>
#include <string_view>

#include <handlers/workers_client.usrv.pb.hpp>
#include <handlers/workers_service.usrv.pb.hpp>
#include <userver/components/component_list.hpp>
#include <userver/storages/postgres/component.hpp>
#include "workers_client.hpp"

namespace simple_db_calls {

class Workers final : public workers::api::WorkersServiceBase::Component {
 public:
  static constexpr std::size_t kMaxStringLength = 55;

  Workers(const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context)
      : workers::api::WorkersServiceBase::Component(config, component_context),
        pg_cluster_(
            component_context
                .FindComponent<userver::components::Postgres>("postgres-db")
                .GetCluster()),
        client_(component_context.FindComponent<WorkersClient>()) {}

  void CreateWorker(workers::api::WorkersServiceBase::CreateWorkerCall& call,
                    workers::api::CreateWorkerRequest&& request);
  void GetWorker(workers::api::WorkersServiceBase::GetWorkerCall& call,
                 workers::api::GetWorkerRequest&& request);
  void UpdateWorker(workers::api::WorkersServiceBase::UpdateWorkerCall& call,
                    workers::api::UpdateWorkerRequest&& request);
  void DeleteWorker(workers::api::WorkersServiceBase::DeleteWorkerCall& call,
                    workers::api::DeleteWorkerRequest&& request);

 private:
  userver::storages::postgres::ClusterPtr pg_cluster_;
  WorkersClient& client_;
};

void AppendWorkers(userver::components::ComponentList& component_list);

}  // namespace simple_db_calls
