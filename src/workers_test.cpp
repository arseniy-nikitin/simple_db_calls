#include "workers.hpp"

#include <userver/utest/utest.hpp>

namespace {

class WorkersTest : public ::testing::Test {
 protected:
  void SetUp() override {
    workers_ = std::make_unique<simple_db_calls::Workers>(
        userver::components::ComponentConfig{},
        userver::components::ComponentContext{});
  }

  simple_db_calls::Workers* workers_ = nullptr;
};

}  // namespace

UTEST_F(WorkersTest, CreateWorker_Basic) {
  workers::api::Worker worker;
  worker.set_id(1);
  worker.set_position("Senior Latte Drinker");

  workers::api::CreateWorkerRequest request;
  request.set_allocated_worker(&worker);

  workers::api::CreateWorkerResponse response;
  workers_->CreateWorker(nullptr, std::move(request), &response);

  EXPECT_EQ(response.id(), 1);
}

UTEST_F(WorkersTest, GetWorker_Basic) {
  workers::api::GetWorkerRequest request;
  request.set_id(1);

  workers::api::GetWorkerResponse response;
  workers_->GetWorker(nullptr, std::move(request), &response);

  EXPECT_EQ(response.worker().id(), 1);
  EXPECT_EQ(response.worker().position(), "Senior Latte Drinker");
}

UTEST_F(WorkersTest, UpdateWorker_Basic) {
  workers::api::Worker worker;
  worker.set_id(1);
  worker.set_position("Junior Latte Drinker");

  workers::api::UpdateWorkerRequest request;
  request.set_allocated_worker(&worker);

  workers::api::UpdateWorkerResponse response;
  workers_->UpdateWorker(nullptr, std::move(request), &response);

  EXPECT_EQ(response.id(), 1);
}

UTEST_F(WorkersTest, DeleteWorker_Basic) {
  workers::api::DeleteWorkerRequest request;
  request.set_id(1);

  workers::api::DeleteWorkerResponse response;
  workers_->DeleteWorker(nullptr, std::move(request), &response);

  EXPECT_EQ(response.worker().id(), 1);
  EXPECT_EQ(response.worker().position(), "Junior Latte Drinker");
}