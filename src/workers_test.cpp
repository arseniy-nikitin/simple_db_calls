#include "workers.hpp"

#include <userver/utest/utest.hpp>

UTEST(CreateWorker, Basic) {
  using simple_db_calls::CreateWorker;

  workers::api::Worker worker;
  worker.set_id(1);
  worker.set_position("Senior Latte Drinker");

  workers::api::CreateWorkerRequest request;
  request.set_allocated_worker(&worker);

  workers::api::CreateWorkerResponse response;
  CreateWorker(request, &response);

  EXPECT_EQ(response.id(), 1);
}

UTEST(GetWorker, Basic) {
  using simple_db_calls::GetWorker;

  workers::api::GetWorkerRequest request;
  request.set_id(1);

  workers::api::GetWorkerResponse response;
  GetWorker(request, &response);

  EXPECT_EQ(response.worker().id(), 1);
  EXPECT_EQ(response.worker().position(), "Senior Latte Drinker");
}

UTEST(UpdateWorker, Basic) {
  using simple_db_calls::UpdateWorker;

  workers::api::Worker worker;
  worker.set_id(1);
  worker.set_position("Junior Latte Drinker");

  workers::api::UpdateWorkerRequest request;
  request.set_allocated_worker(&worker);

  workers::api::UpdateWorkerResponse response;
  UpdateWorker(request, &response);

  EXPECT_EQ(response.id(), 1);
}

UTEST(DeleteWorker, Basic) {
  using simple_db_calls::DeleteWorker;

  workers::api::DeleteWorkerRequest request;
  request.set_id(1);

  workers::api::DeleteWorkerResponse response;
  DeleteWorker(request, &response);

  EXPECT_EQ(response.worker().id(), 1);
  EXPECT_EQ(response.worker().position(), "Junior Latte Drinker");
}