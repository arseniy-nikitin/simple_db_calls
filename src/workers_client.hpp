#pragma once

#include <cstdint>

#include <handlers/workers_client.usrv.pb.hpp>
#include <userver/components/component_list.hpp>
#include <userver/components/loggable_component_base.hpp>
#include <userver/components/component.hpp>
#include <userver/ugrpc/client/client_factory_component.hpp>

namespace simple_db_calls {

class WorkersClient final : public userver::components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "workers-client";

  WorkersClient(const userver::components::ComponentConfig& config,
              const userver::components::ComponentContext& component_context)
      : userver::components::LoggableComponentBase(config, component_context),
        client_factory_(
            component_context
                .FindComponent<userver::ugrpc::client::ClientFactoryComponent>()
                .GetFactory()),
        client_(client_factory_.MakeClient<workers::api::WorkersServiceClient>(
            "workers-client", config["endpoint"].As<std::string>())) {}
  
  int32_t CreateWorker(workers::api::Worker worker);
  workers::api::Worker GetWorker(int id);
  int32_t UpdateWorker(workers::api::Worker worker);
  workers::api::Worker DeleteWorker(int id);
	
  static userver::yaml_config::Schema GetStaticConfigSchema();

 private:
  userver::ugrpc::client::ClientFactory& client_factory_;
  workers::api::WorkersServiceClient client_;
};

void AppendWorkersClient(userver::components::ComponentList& component_list);


}  // namespace simple_db_calls

template <>
inline constexpr bool userver::components::kHasValidate<simple_db_calls::WorkersClient> = true;
