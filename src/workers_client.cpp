#include "workers_client.hpp"

#include <fmt/format.h>

#include <userver/yaml_config/merge_schemas.hpp>

namespace simple_db_calls {

int32_t WorkersClient::CreateWorker(workers::api::Worker worker) {
  workers::api::CreateWorkerRequest request;
  request.set_id(std::move(worker.id()));
  request.set_position(std::move(worker.position()));

  auto context = std::make_unique<grpc::ClientContext>();                                                                                                                            
  context->set_deadline(
      userver::engine::Deadline::FromDuration(std::chrono::seconds{20}));

  auto stream = client_.CreateWorker(request, std::move(context));

  workers::api::CreateWorkerResponse response = stream.Finish();

  return response.id();
}

workers::api::Worker WorkersClient::GetWorker(int32_t id) {
  workers::api::GetWorkerRequest request;
  request.set_id(std::move(id));

  auto context = std::make_unique<grpc::ClientContext>();                                                                                                                            
  context->set_deadline(
      userver::engine::Deadline::FromDuration(std::chrono::seconds{20}));

  auto stream = client_.GetWorker(request, std::move(context));

  workers::api::GetWorkerResponse response = stream.Finish();

  return response.worker();
}

int32_t WorkersClient::UpdateWorker(workers::api::Worker worker) {
  workers::api::UpdateWorkerRequest request;
  request.set_id(std::move(worker.id()));
  request.set_position(std::move(worker.position()));

  auto context = std::make_unique<grpc::ClientContext>();                                                                                                                            
  context->set_deadline(
      userver::engine::Deadline::FromDuration(std::chrono::seconds{20}));

  auto stream = client_.UpdateWorker(request, std::move(context));

  workers::api::UpdateWorkerResponse response = stream.Finish();

  return response.id();
}

workers::api::Worker WorkersClient::DeleteWorker(int32_t id) {
  workers::api::DeleteWorkerRequest request;
  request.set_id(std::move(id));

  auto context = std::make_unique<grpc::ClientContext>();                                                                                                                            
  context->set_deadline(
      userver::engine::Deadline::FromDuration(std::chrono::seconds{20}));

  auto stream = client_.DeleteWorker(request, std::move(context));

  workers::api::DeleteWorkerResponse response = stream.Finish();

  return response.worker();
}

userver::yaml_config::Schema WorkersClient::GetStaticConfigSchema() {
  return userver::yaml_config::MergeSchemas<
      userver::components::LoggableComponentBase>(R"(
type: object
description: >
    a user-defined wrapper around api::WorkersServiceClient that provides
    a simplified interface.
additionalProperties: false
properties:
    endpoint:
        type: string
        description: >
            WorkersService endpoint.
)");
}

void AppendWorkersClient(userver::components::ComponentList& component_list) {
  component_list.Append<WorkersClient>();
}

}  // namespace simple_db_calls
