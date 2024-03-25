import pathlib
import sys

import pytest
import grpc

from testsuite.databases.pgsql import discover

import handlers.workers_pb2_grpc as workers_services  # noqa: E402, E501

USERVER_CONFIG_HOOKS = ['prepare_service_config']
pytest_plugins = [
    'pytest_userver.plugins.postgresql',
    'pytest_userver.plugins.grpc',
]


@pytest.fixture
def grpc_service(pgsql, grpc_channel, service_client):
    return workers_services.WorkersServiceStub(grpc_channel)


@pytest.fixture(scope='session')
def mock_grpc_workers_session(grpc_mockserver, create_grpc_mock):
    mock = create_grpc_mock(workers_services.WorkersServiceServicer)
    workers_services.add_WorkersServiceServicer_to_server(
        mock.servicer, grpc_mockserver,
    )
    return mock


@pytest.fixture
def mock_grpc_server(mock_grpc_workers_session):
    with mock_grpc_workers_session.mock() as mock:
        yield mock


@pytest.fixture(scope='session')
def prepare_service_config(grpc_mockserver_endpoint):
    def patch_config(config, config_vars):
        components = config['components_manager']['components']
        components['workers-client']['endpoint'] = grpc_mockserver_endpoint

    return patch_config


def pytest_configure(config):
    sys.path.append(str(
        pathlib.Path(__file__).parent.parent / 'proto/handlers/'))


@pytest.fixture(scope='session')
def service_source_dir():
    """Path to root directory service."""
    return pathlib.Path(__file__).parent.parent


@pytest.fixture(scope='session')
def initial_data_path(service_source_dir):
    """Path for find files with data"""
    return [
        service_source_dir / 'postgresql/data',
    ]


@pytest.fixture(scope='session')
def pgsql_local(service_source_dir, pgsql_local_create):
    """Create schemas databases for tests"""
    databases = discover.find_schemas(
        'simple_db_calls',
        [service_source_dir.joinpath('postgresql/schemas')],
    )
    return pgsql_local_create(list(databases.values()))
