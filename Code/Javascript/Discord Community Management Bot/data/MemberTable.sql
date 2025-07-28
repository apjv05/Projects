-- WARNING: This schema is for context only and is not meant to be run.
-- Table order and constraints may not be valid for execution.

CREATE TABLE public.member (
  UserID text NOT NULL,
  CONSTRAINT member_pkey PRIMARY KEY (UserID),
  Div character varying DEFAULT 'None'::character varying,
  Rank character varying,
  WildWest boolean,
  ArcaneOdyssey boolean,
  Deepwoken boolean,
  GameNight boolean,
  Region character varying,
  EventsAttended smallint DEFAULT '0'::smallint,
  LastAttendanceDate date,
  LastContactDate date,
  LastContactPerson text,
  Activity text,
  Comments text
);