import pytest

import handlers.workers_pb2 as workers_protos  # noqa: E402, E501
import handlers.workers_pb2_grpc as workers_services  # noqa: E402, E501

# Start the tests via `make test-debug` or `make test-release`

@pytest.mark.asyncio
async def test_grpc_client(mock_grpc_server, grpc_service):
    @mock_grpc_server('CreateWorker')
    async def mock_create_worker(request, context):
        assert request.worker
        return workers_protos.CreateWorkerResponse(
            id=request.worker.id,
        )

    worker = workers_protos.Worker(id=1, position='Senior Latte Drinker')
    request = workers_protos.CreateWorkerRequest(worker=worker)
    response = await grpc_service.CreateWorker(request)
    assert response.id == 1
    assert mock_create_worker.times_called == 1

@pytest.mark.asyncio
async def test_get_worker(grpc_service):
    request = workers_protos.GetWorkerRequest(id=1)
    response = await grpc_service.GetWorker(request)
    assert response.worker.id == 1
    assert response.worker.position == 'Senior Latte Drinker'

@pytest.mark.asyncio
async def test_update_worker(grpc_service):
    worker = workers_protos.Worker(id=1, position='Junior Latte Drinker')
    request = workers_protos.UpdateWorkerRequest(worker=worker)
    response = await grpc_service.UpdateWorker(request)
    assert response.id == 1

@pytest.mark.asyncio
async def test_delete_worker(grpc_service):
    request = workers_protos.DeleteWorkerRequest(id=1)
    response = await grpc_service.DeleteWorker(request)
    assert response.worker.id == 1
    assert response.worker.position == 'Junior Latte Drinker'

@pytest.mark.pgsql('db', files=['initial_data.sql'])
@pytest.mark.asyncio
async def test_db_initial_data(grpc_service):
    request = workers_protos.GetWorkerRequest(id=1)
    response = await grpc_service.GetWorker(request)
    assert response.worker.id == 1
    assert response.worker.position == 'Senior Latte Drinker'