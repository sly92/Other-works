rapper -c -i turtle /home/jupyter/Notebooks/results.ttl

cat /data/virtuoso.ini | grep DirsAllowed

isql 1111 dba dba exec="SELECT * from DB.DBA.load_list;"

isql 1111 dba dba exec="DELETE FROM DB.DBA.load_list;"

isql 1111 dba dba exec="SPARQL CLEAR GRAPH <http://example.com/results>"

isql 1111 dba dba exec="ld_dir('/home/jupyter/Notebooks','results.ttl','http://example.com/results');"
isql 1111 dba dba exec="rdf_loader_run();" & wait
isql 1111 dba dba exec="checkpoint;"

isql 1111 dba dba exec="SPARQL SELECT * WHERE { GRAPH <http://example.com/results> {?o ?p ?v}} LIMIT 10"

