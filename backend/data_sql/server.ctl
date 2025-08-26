LOAD DATA
INFILE 'server.csv'
INTO TABLE TABLE_SERVER
TRUNCATE
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '"'
TRAILING NULLCOLS
(
    id_,
    name_,
    host_,
    created_at_,
    number_of_day_in_effect_ ,
    min_quantity_                ,
    max_quantity_ ,
    price_for_unit_,
    state_            ,
    service_id_              

)