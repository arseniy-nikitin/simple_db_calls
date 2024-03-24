#pragma once

#include <string>
#include <string_view>

#include <handlers/rofls_client.usrv.pb.hpp>
#include <handlers/rofls_service.usrv.pb.hpp>
#include <userver/components/component_list.hpp>
#include <userver/storages/postgres/component.hpp>
#include "rofls_client.hpp"

namespace simple_db_calls {

class Rofls final : public rofls::api::RoflsServiceBase::Component {
 public:
  Rofls(const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context)
      : rofls::api::RoflsServiceBase::Component(config, component_context),
        pg_cluster_(
            component_context
                .FindComponent<userver::components::Postgres>("postgres-db")
                .GetCluster()),
        client_(component_context.FindComponent<RoflsClient>()) {}

  void CreateRofl(rofls::api::RoflsServiceBase::CreateRoflCall& call,
                  rofls::api::RoflRequest&& request);
  void GetRofl(rofls::api::RoflsServiceBase::GetRoflCall& call,
               rofls::api::RoflRequest&& request);
  void UpdateRofl(rofls::api::RoflsServiceBase::UpdateRoflCall& call,
		  rofls::api::RoflRequest&& request);
  void DeleteRofl(rofls::api::RoflsServiceBase::DeleteRoflCall& call,
		  rofls::api::RoflRequest&& request);

 private:
  userver::storages::postgres::ClusterPtr pg_cluster_;
  RoflsClient& client_;
};

void AppendRofls(userver::components::ComponentList& component_list);

}  // namespace simple_db_calls
