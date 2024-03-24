#pragma once

#include <handlers/rofls_client.usrv.pb.hpp>
#include <userver/components/component_list.hpp>
#include <userver/components/loggable_component_base.hpp>
#include <userver/components/component.hpp>
#include <userver/ugrpc/client/client_factory_component.hpp>

namespace simple_db_calls {

class RoflsClient final : public userver::components::LoggableComponentBase {
 public:
  static constexpr std::size_t kMaxStringLength = 255;

  RoflsClient(const userver::components::ComponentConfig& config,
              const userver::components::ComponentContext& component_context)
      : userver::components::LoggableComponentBase(config, component_context),
        client_factory_(
            component_context
                .FindComponent<userver::ugrpc::client::ClientFactoryComponent>()
                .GetFactory()),
        // The client needs a fixed endpoint
        client_(client_factory_.MakeClient<rofls::api::RoflsServiceClient>(
            "rofls-client", config["endpoint"].As<std::string>())) {}
  
  int CreateRofl(std::string razryvnaya);
  rofls::api::Rofl GetRofl(int id);
  void UpdateRofl(rofls::api::Rofl rofl);
  void DeleteRofl(int id);
	
  static userver::yaml_config::Schema GetStaticConfigSchema();

 private:
  userver::ugrpc::client::ClientFactory& client_factory_;
  rofls::api::RoflsServiceClient client_;
};

void AppendRoflsClient(userver::components::ComponentList& component_list);


}  // namespace simple_db_calls

template <>
inline constexpr bool userver::components::kHasValidate<simple_db_calls::RoflsClient> = true;
