INSERT INTO workers_schema.workers(position)
VALUES ('Senior Latte Drinker')
ON CONFLICT (position)
DO NOTHING;
