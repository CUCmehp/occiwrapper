------------------------------------------
-- Export file for user OCCIWRAPPER     --
-- Created by hup on 2012-8-6, 23:21:15 --
------------------------------------------

spool occiwrapper.log

prompt
prompt Creating table LOG_F_TEST4
prompt ==========================
prompt
create table OCCIWRAPPER.LOG_F_TEST4
(
  P_IN_VALUE1 INTEGER,
  P_IN_VALUE2 VARCHAR2(256),
  P_IN_VALUE3 DATE,
  P_IN_VALUE4 FLOAT,
  P_IN_VALUE5 NUMBER(22,8)
)
;

prompt
prompt Creating table TBL_TEST1
prompt ========================
prompt
create table OCCIWRAPPER.TBL_TEST1
(
  X INTEGER
)
;

prompt
prompt Creating table TBL_TEST2
prompt ========================
prompt
create table OCCIWRAPPER.TBL_TEST2
(
  X INTEGER,
  Y INTEGER
)
;

prompt
prompt Creating table TEST_BATCHED_TABLE
prompt =================================
prompt
create table OCCIWRAPPER.TEST_BATCHED_TABLE
(
  FLOAT_VALUE  FLOAT,
  STRING_VALUE VARCHAR2(1024),
  DATE_VALUE   DATE,
  INT_VALUE    INTEGER,
  NUMBER_VALUE NUMBER
)
;

prompt
prompt Creating table TEST_DATE
prompt ========================
prompt
create table OCCIWRAPPER.TEST_DATE
(
  DATE_VAL DATE not null
)
;

prompt
prompt Creating table TEST_NUMBER
prompt ==========================
prompt
create table OCCIWRAPPER.TEST_NUMBER
(
  ID           INTEGER not null,
  NUMBER_VALUE NUMBER
)
;

prompt
prompt Creating table TEST_STRING
prompt ==========================
prompt
create table OCCIWRAPPER.TEST_STRING
(
  ID         INTEGER not null,
  STRING_VAL VARCHAR2(100)
)
;

prompt
prompt Creating function F_INS_TBL_TEST1
prompt =================================
prompt
create or replace function occiwrapper.f_ins_tbl_test1( p_value in number) return number is
begin
  insert into tbl_test1(x) values( p_value );
  commit;
  return 1;
exception
  when others then
  rollback;
  return -1;
end f_ins_tbl_test1;
/

prompt
prompt Creating function F_TEST2
prompt =========================
prompt
create or replace function occiwrapper.f_test2( p_value in number, p_out_value1 out number ) return number is
begin
  p_out_value1 := 10;
  return 20;
exception
  when others then
  rollback;
  return -1;
end f_test2;
/

prompt
prompt Creating function F_TEST3
prompt =========================
prompt
create or replace function occiwrapper.f_test3(
 p_out_value1 in out int,
 p_out_value2 out varchar2,
 p_out_value3 out date,
 p_out_value4 out float,
 p_out_value5 out number )
return number is
begin
   p_out_value1 := p_out_value1 + 1;
   p_out_value2 := 'hello world';
   p_out_value3 := sysdate;
   p_out_value4 := 1.5;
   p_out_value5 := 123123;
   return 1;
exception
  when others then
  rollback;
  return -1;
end f_test3;
/

prompt
prompt Creating function F_TEST4
prompt =========================
prompt
create or replace function occiwrapper.f_test4(
         p_in_value1 in int,
         p_in_value2 in varchar2,
         p_in_value3 in date,
         p_in_value4 in float,
         p_in_value5 in number,
         p_out_msg   out varchar2)
return number 
is
  v_log_count   number;
  v_sql         varchar2( 32767 );
begin
  -- create log table for f_test4
  select count(*) into v_log_count from user_tables t where t.table_name = 'LOG_F_TEST4';
  if v_log_count = 0 then
    v_sql := 'create table LOG_F_TEST4( p_in_value1 int, p_in_value2 varchar2(256), p_in_value3 date, p_in_value4 float, p_in_value5 number(22,8) )';
    execute immediate v_sql;
  else
    v_sql := 'truncate table LOG_F_TEST4';
    execute immediate v_sql;
  end if;
  v_sql := 'insert into log_f_test4(p_in_value1, p_in_value2, p_in_value3, p_in_value4, p_in_value5) values '
             || '(' || p_in_value1 || ',''' || p_in_value2 || ''', to_date(''' ||  to_char( p_in_value3, 'yyyymmdd hh24:mi:ss') || ''',''yyyymmdd hh24:mi:ss''),' || p_in_value4 || ',' || p_in_value5 || ')';
  execute immediate v_sql;        
  commit;     
  return 1;
exception
  when others then
  p_out_msg := 'f_test4 failed, error code:' || SQLCODE || ', message:' || SQLERRM;
  rollback;
  return -1;
end;
/

prompt
prompt Creating procedure P_TEST_PROCEDURE
prompt ===================================
prompt
CREATE OR REPLACE PROCEDURE OCCIWRAPPER.P_TEST_PROCEDURE(
       PAR_INT_IN          IN   NUMBER,
       PAR_OUT_STRING      OUT  VARCHAR2
       ) IS
BEGIN
    PAR_OUT_STRING := to_char( par_int_in );
EXCEPTION
  WHEN OTHERS THEN
    PAR_OUT_STRING := 'exception occurs, error code:' || SQLCODE || ', message: ' || SQLERRM ;
    RETURN;
END P_TEST_PROCEDURE;
/


spool off
