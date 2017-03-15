--------------------------------------------------------
--  File created - Saturday-December-03-2016   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Trigger TRIG_DELETE_ENROLLMRNTS_LOGS
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "SYSTEM"."TRIG_DELETE_ENROLLMRNTS_LOGS" 
  after DELETE on enrollments
  for each row
  begin
     insert into logs values(logs_seq.nextval,user,sysdate,'enrollments','delete',:old.B# || ',' ||:old.classid);
  end;
/
ALTER TRIGGER "SYSTEM"."TRIG_DELETE_ENROLLMRNTS_LOGS" ENABLE;
