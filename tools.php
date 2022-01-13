<?php

$str = new String("123456");
echo $str->insert_head("--bb--")->substr(2)->insert_tail("--hello")->replace("hello","notlala")->value();
//   echo $str->substr(1,3)->dump().PHP_EOL;//output:123
//   echo $str->replace('23',"bbb")->dump();//1bbb456
//   echo $str->substr(1,3)->dump();//output:23