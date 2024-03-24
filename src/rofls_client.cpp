#include "rofls_client.hpp"

#include <fmt/format.h>

#include <userver/yaml_config/merge_schemas.hpp>

namespace simple_db_calls {

int RoflsClient::CreateRofl(std::string razryvnaya) {
  if (razryvnaya.size() > kMaxStringLength) {
    throw std::invalid_argument("razryvnaya is too long");
  }
  rofls::api::CreateRoflRequest request;
  request.set_razryvnaya(std::move(razryvnaya));

  auto context = std::make_unique<grpc::ClientContext>();                                                                                                                            
  context->set_deadline(
      userver::engine::Deadline::FromDuration(std::chrono::seconds{20}));

  auto stream = client_.CreateRofl(request, std::move(context));

  rofls::api::CreateRoflResponse response = stream.Finish();

  return response.id();
}

rofls::api::Rofl RoflsClient::GetRofl(int id) {
  rofls::api::GetRoflRequest request;
  request.set_id(std::move(id));

  auto context = std::make_unique<grpc::ClientContext>();                                                                                                                            
  context->set_deadline(
      userver::engine::Deadline::FromDuration(std::chrono::seconds{20}));

  auto stream = client_.GetRofl(request, std::move(context));

  rofls::api::GetRoflResponse response = stream.Finish();

  return response.rofl();
}

void RoflsClient::UpdateRofl(rofls::api::Rofl rofl) {
  if (rofl.razryvnaya().size() > kMaxStringLength) {
    throw std::invalid_argument("razryvnaya is too long");
  }
  rofls::api::UpdateRoflRequest request;
  request.set_rofl(rofl.rofl());

  auto context = std::make_unique<grpc::ClientContext>();                                                                                                                            
  context->set_deadline(
      userver::engine::Deadline::FromDuration(std::chrono::seconds{20}));

  client_.UpdateRofl(request, std::move(context));
}

void RoflsClient::DeleteRofl(int id) {
  rofls::api::DeleteRoflRequest request;
  request.set_id(std::move(id));

  auto context = std::make_unique<grpc::ClientContext>();                                                                                                                            
  context->set_deadline(
      userver::engine::Deadline::FromDuration(std::chrono::seconds{20}));

  client_.DeleteRofl(request, std::move(context));
}

userver::yaml_config::Schema RoflsClient::GetStaticConfigSchema() {
  return userver::yaml_config::MergeSchemas<
      userver::components::LoggableComponentBase>(R"(
type: object
description: >
    a user-defined wrapper around api::RoflsServiceClient that provides
    a simplified interface.
additionalProperties: false
properties:
    endpoint:
        type: string
        description: >
            RoflsService endpoint.
)");
}

void AppendRoflsClient(userver::components::ComponentList& component_list) {
  component_list.Append<RoflsClient>();
}

}  // namespace simple_db_calls
