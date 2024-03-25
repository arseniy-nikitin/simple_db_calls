#include "workers.hpp"

#include <userver/utest/utest.hpp>

UTEST(CreateWorker, Basic) {
  using simple_db_calls::CreateWorker;

  workers::api::Worker worker;
  worker.set_id(1);
  worker.set_position("Senior Latte Drinker");

  int32_t result = CreateWorker(worker);

  EXPECT_EQ(result, 1);
}

UTEST(GetWorker, Basic) {
  using simple_db_calls::GetWorker;

  workers::api::Worker result = GetWorker(1);

  EXPECT_EQ(result.id(), 1);
  EXPECT_EQ(result.position(), "Senior Latte Drinker");
}

UTEST(UpdateWorker, Basic) {
  using simple_db_calls::UpdateWorker;

  workers::api::Worker worker;
  worker.set_id(1);
  worker.set_position("Junior Latte Drinker");

  int32_t result = UpdateWorker(worker);

  EXPECT_EQ(result, 1);
}

UTEST(DeleteWorker, Basic) {
  using simple_db_calls::DeleteWorker;

  workers::api::Worker result = DeleteWorker(1);

  EXPECT_EQ(result.id(), 1);
  EXPECT_EQ(result.position(), "Junior Latte Drinker");
}