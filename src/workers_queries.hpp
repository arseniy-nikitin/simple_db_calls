#pragma once

#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/query.hpp>

namespace simple_db_calls {
  
  const userver::storages::postgres::Query kCreateWorkerQuery {
      "INSERT INTO workers_schema.workers(position) VALUES($1) "
      "ON CONFLICT (position) "
      "DO NOTHING "
      "RETURNING workers.id",
      userver::storages::postgres::Query::Name{"create_worker_query"}};

  const userver::storages::postgres::Query kGetWorkerQuery {
      "SELECT workers.position "
      "FROM workers_schema.workers "
      "WHERE workers.id = $1",
      userver::storages::postgres::Query::Name{"get_worker_query"}};

  const userver::storages::postgres::Query kUpdateWorkerQuery {
      "UPDATE workers_schema.workers "
      "SET workers.position = $1 "
      "WHERE workers.id = $2 "
      "RETURNING workers.id",
      userver::storages::postgres::Query::Name{"update_worker_query"}};

  const userver::storages::postgres::Query kDeleteWorkerQuery {
      "DELETE FROM workers_schema.workers "
      "WHERE workers.id = $1 "
      "RETURNING workers.position",
      userver::storages::postgres::Query::Name{"delete_worker_query"}};

}  // namespace simple_db_calls
