#pragma once

#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/query.hpp>

namespace simple_db_calls {
  
  const storages::postgres::Query kCreateRoflQuery {
      "INSERT INTO xd_schema.rofls(razryvnaya) VALUES($1)"
      "ON CONFLICT (razryvnaya)"
      "DO NOTHING"
      "RETURNING rofls.id",
      storages::postgres::Query::Name{"create_rofl_query"}};

  const storages::postgres::Query kGetRoflQuery {
      "SELECT *"
      "FROM xd_schema.rofls"
      "WHERE rofls.id = $1",
      storages::postgres::Query::Name{"get_rofl_query"}};

  const storages::postgres::Query kUpdateRoflQuery {
      "UPDATE xd_schema.rofls"
      "SET rofls.razryvnaya = $1"
      "WHERE rofls.id = $2"
      "RETURNING rofls.id",
      storages::postgres::Query::Name{"update_rofl_query"}};

  const storages::postgres::Query kDeleteRoflQuery {
      "DELETE FROM xd_schema.rofls"
      "WHERE rofls.id = $1"
      "RETURNING rofls.id",
      storages::postgres::Query::Name{"delete_rofl_query"}};

}  // namespace simple_db_calls
