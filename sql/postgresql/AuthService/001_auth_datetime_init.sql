CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE TABLE auth_datetime (
    id                      varchar(36) PRIMARY KEY,
    memberId                varchar(36) NOT NULL, 
    signupDatetime          timestamptz NOT NULL,
    signinDatetime          timestamptz,
    lastVisitDatetime       timestamptz                                 
);

INSERT INTO auth_datetime
(id, memberId, signupDatetime)
    VALUES (uuid_generate_v4(),
            '4bb48865-1a84-49c7-94eb-148ed2f9d7a5',
            now());
   