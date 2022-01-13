<?php

$str = new String("123456");
echo $str->insert_head("--bbBBBBBCCC--")->substr(2)->insert_tail("--hello")->replace("hello","notlala")->lower()->value();