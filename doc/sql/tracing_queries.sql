-- -*- mode: sql; sql-product: postgres; -*-

-- \pset pager off
-- \copy to get data in
-- \copy country FROM '/usr1/proj/bray/sql/country_data';
-- \copy traces(data) from '/home/marco/Development/DomainDrivenConsulting/masd/dogen/integration/build/output/clang7/Release/stage/bin/masd.dogen.byproducts/cli.generate.masd.dogen.generation.csharp.dia/tracing/002-orchestration.transforms.code_generation_chain/001-orchestration.transforms.extraction_model_production_chain/006-generation.transforms.model_generation_chain/016-generation.transforms.model_generation_chain-cff8c49f-cd51-4eee-94d4-04fd2af430d6-output.json';

select jsonb_pretty(
    jsonb_array_elements(
        jsonb_array_elements(data)->'elements')->'data'->'__parent_0__'->'name'->'qualified'->'dot'
    )
   as name,
   jsonb_pretty(
       jsonb_array_elements(
           jsonb_array_elements(data)->'elements')->'data'->'__parent_0__'->'decoration'->'data'
   )
   as decoration
from traces
limit 10;

CREATE VIEW vista AS
select jsonb_pretty(
jsonb_array_elements(
jsonb_array_elements(data)->'elements')->'data'->'__parent_0__'->'name'->'qualified'->'dot'
)
as name,
jsonb_pretty(
jsonb_array_elements(
jsonb_array_elements(data)->'elements')->'data'->'__parent_0__'->'decoration'->'data'
)
as decoration
from traces
where id = 2;

select name
from vista
where upper(name) like upper('masd%')
limit 3;

select name, decoration
from vista
where upper(name) like upper('"masd.dogen.generation.csharp.formattables.locator_configuration%')
limit 3;

select name
from vista
order by name;

-- how many models
select jsonb_pretty(jsonb_array_elements(data)->'name')
as model_name
from traces
limit 10;

-- elements
select jsonb_pretty(
           jsonb_array_elements(
           jsonb_array_elements(data)->'elements')->'data'->'__parent_0__'->'name'->'qualified'->'dot'
       )
from traces
where id = 2;
