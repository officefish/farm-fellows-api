CREATE EXTENSION IF NOT EXISTS "uuid-ossp";
CREATE EXTENSION IF NOT EXISTS "pgcrypto";

CREATE TABLE members (
    id                      varchar (36)     PRIMARY KEY,
    memberName              varchar (256)    NOT NULL,
    email                   varchar (70)     NOT NULL,
    passwordHash            varchar (256)    NOT NULL,
    memberRole              integer,

    CONSTRAINT              UK_USERS_USERNAME UNIQUE (memberName),
    CONSTRAINT              UK_USERS_EMAIL UNIQUE (email)
);

INSERT INTO members
(id, memberName, email, passwordHash, memberRole) 
    VALUES ('4bb48865-1a84-49c7-94eb-148ed2f9d7a5', 
            'admin', 
            'admin@domain.com', 
            crypt('admin', gen_salt('bf', 8)),
            1);

