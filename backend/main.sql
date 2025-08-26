-- FUNCTION -- 

CREATE OR REPLACE FUNCTION generate_uuid RETURN VARCHAR2
DETERMINISTIC
IS
BEGIN
  RETURN REGEXP_REPLACE(
           RAWTOHEX(SYS_GUID()),
           '(.{8})(.{4})(.{4})(.{4})(.{12})',
           '\1-\2-\3-\4-\5'
         );
END;
/

-- CREATE TALBE -- 



create or replace type type_booking as object (
      id_   number(10),
      name_ varchar2(1000)
)
/
create table table_booking of type_booking (
   primary key ( id_ ),
   constraint nn_booking_name check(name_ is not null)
)
/
drop sequence seq_booking_id
/
create sequence seq_booking_id start with 1 increment by 1 nocache
nocycle;
/
create or replace trigger trg_booking_bi before
   insert on table_booking
   for each row
begin
   if :new.id_ is null then
      :new.id_ := seq_booking_id.nextval;
   end if;
end;
/
create or replace type type_client as object (
      id_            number(10),
      phone_number_  varchar2(11),
      email_         varchar2(100),
      balance_       number(
         20,
         3
      ),
      register_date_ date,
      password_      varchar2(100)
)
/
create table table_client of type_client (
   primary key ( id_ ),
   constraint uq_client_phone unique ( phone_number_ ),
   constraint uq_client_email unique ( email_ ),
   constraint password_length check(6 <= length(password_) and length(password_) <= 18),
   constraint nn_client_register_date check(register_date_ is not null)

)
/
drop sequence seq_client_id
/
create sequence seq_client_id start with 1 increment by 1 nocache
nocycle;
/
create or replace trigger trg_client_bi before
   insert on table_client
   for each row
begin
   if :new.id_ is null then
      :new.id_ := seq_client_id.nextval;
   end if;
end;
/

create or replace type type_service as object (
      id_         number(10),
      name_       varchar2(1000),
      booking_id_ number(10)
)
/
create table table_service of type_service (
   primary key ( id_ ),
   foreign key ( booking_id_ )
      references table_booking ( id_ ),
   constraint nn_service_name check(name_ is not null),
   constraint nn_service_booking_id check(booking_id_ is not null)
)
/
drop sequence seq_service
/
create sequence seq_service start with 1 increment by 1 nocache
nocycle;
/
create or replace trigger trg_service_bi before
   insert on table_service
   for each row
begin
   if :new.id_ is null then
      :new.id_ := seq_service.nextval;
   end if;
end;
/
create or replace type type_server as object (
      id_                      number(10),
      name_                    varchar2(1000),
      host_                    varchar2(1000),
      created_at_              varchar2(1000),
      number_of_day_in_effect_ number(10),
      min_quantity_                number(10),
      max_quantity_                number(10),
      price_for_unit_   number(
         20,
         3
      ),
      state_                   number(3), -- 0 active, 1 inactive, 2 maintenance, 3 death
      service_id_              number(10)
)

/

create table table_server of type_server (
   primary key ( id_ ),
   foreign key ( service_id_ )
      references table_service ( id_ ),
   constraint nn_server_name check(name_ is not null),
   constraint nn_server_host check(host_ is not null),
   constraint nn_server_created_at check(created_at_ is not null),
   constraint nn_server_number_of_day_in_effect check(number_of_day_in_effect_ is not null),
   constraint nn_server_quantity check(min_quantity_ is not null),
   constraint nn_server_max_quantity check(max_quantity_ is not null),
   constraint nn_server_price_for_unit check(price_for_unit_ is not null),
   constraint nn_server_state check(state_ in (0, 1, 2, 3))
)
/
drop sequence seq_server_id
/
create sequence seq_server_id start with 1 increment by 1 nocache
nocycle;
/
create or replace trigger trg_server_bi before
   insert on table_server
   for each row
begin
   if :new.id_ is null then
      :new.id_ := seq_server_id.nextval;
   end if;
end;
/
create or replace type type_transaction as object (
      id_              varchar2(36),
      amount_          number(
         20,
         3
      ),
      currency_        varchar2(3),
      type_            number(3),  -- 0 Topup, 1 Withdrawal, 2 Purchase, 3 Refund
      status_          number(3), -- 0 Initial, 1 Pending, 2 Processing, 3 Failed, 4 Refunded, 5 Success
      created_at_      date,
      approved_at_     date,
      payment_method_  number(3), -- 0 Bank Transfer, 1 Credit Card, 2 Momo, 3 ZaloPay
      idempotency_key_ varchar2(36),
      client_id_       number(10)
)
/
create table table_transaction of type_transaction (
   primary key ( id_ ),
   foreign key ( client_id_ )
      references table_client ( id_ ),
   constraint uq_transaction_idempotency_key unique ( idempotency_key_ ),
   constraint nn_transaction_amount check(amount_ is not null),
   constraint nn_transaction_client_id check(client_id_ is not null),
   constraint nn_transaction_type check(type_ in (0, 1, 2, 3)),
   constraint nn_transaction_status check(status_ in (0, 1, 2, 3, 4, 5)),
   constraint nn_transaction_payment_method check(payment_method_ in (0, 1, 2, 3))
)
/
CREATE OR REPLACE TRIGGER trg_transaction_bi
BEFORE INSERT ON table_transaction
FOR EACH ROW
BEGIN
   IF :new.id_ IS NULL THEN
      :new.id_ := generate_uuid();
   END IF;
END;
/

-- ORDER TYPE AND TABLE --
create or replace type type_order as object (
      id_                       varchar2(36),
      link_                     varchar2(1000),
      quantity_order_           number(10),
      quantity_executed_        number(10),
      discount_rate_            number(
         1,
         2
      ),
      discount_amount_in_order_ number(
         20,
         3
      ),
      tax_rate_                 number(2),
      price_per_unit_           number(
         20,
         3
      ),
      state_                    number(3), -- 0 initial, 1 pending, 2 processing, 3 error, 4 success
      created_at_               date,
      client_id_                number(10),
      server_id_                number(10),
      transaction_id_           varchar2(36)
)
/
create table table_order of type_order ( 
   primary key ( id_ ),
   foreign key ( client_id_ )
      references table_client ( id_ ),
   foreign key ( server_id_ )
      references table_server ( id_ ),
   foreign key ( transaction_id_ )
      references table_transaction ( id_ ),
   constraint nn_order_link check(link_ is not null),
   constraint nn_order_quantity_order check(quantity_order_ is not null),
   constraint ct_discount_rate check(0 <= discount_rate_ and discount_rate_ <= 1),
   constraint non_negative_discount_amount check(discount_amount_in_order_ >= 0),
   constraint non_negative_tax_rate check(tax_rate_ >= 0),
   constraint nn_and_non_negative_order_price_per_unit check(price_per_unit_ is not null and price_per_unit_ >= 0),
   constraint nn_order_state check(state_ in (0, 1, 2, 3, 4)),
   constraint nn_order_created_at check(created_at_ is not null),
   constraint nn_order_client_id check(client_id_ is not null),
   constraint nn_order_server_id check(server_id_ is not null),
   constraint nn_order_transaction_id check(transaction_id_ is not null)
)