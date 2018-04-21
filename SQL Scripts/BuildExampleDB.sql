set autocommit = 0;
start transaction;
-- drop database ar;
create database ar;
use ar;
set time_zone = "+00:00";

create table if not exists user
(
  id int(10) unsigned not null auto_increment,
  name varchar(128) collate utf8mb4_unicode_ci not null,
  password varchar(256) collate utf8mb4_unicode_ci not null,
  created datetime not null default current_timestamp,
  primary key (id),
  unique key name_uniq (name)
) engine=innodb default charset=utf8mb4 collate=utf8mb4_unicode_ci;

commit;