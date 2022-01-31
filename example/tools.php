<?php
  $ac  = range(1, 500000);

  $start = time();
  $a = thread_run(function($a){
  $a = $a+2;
  return $a;
  },6,$ac);

print_r($a);
  $end = time();
  $ab = $end - $start;
  print_r("\nthread_run={$ab}");
  die;

  //1. substr string behavior [ substr(int start,int length) ]
  $str = new String("123456ZAaa");
  echo $str->substr(0,3)->value().PHP_EOL;//output:123
  echo $str->substr(1,3)->value().PHP_EOL;//output:23

  //2. replace string behavior [ replace(string search,string replace) ]
  $str = new String("123456ZAaa");
  echo $str->replace('23',"bbb")->value().PHP_EOL;//output:1bbb456ZAaa

  //3.  insert content to string tail behavior [ insert_tail(string tailString) ]
  $str = new String("123456ZAaa");
  echo $str->insert_tail("--hello world")->value().PHP_EOL;//output:123456ZAaa--hello world

  //4. insert content to string head behavior [ insert_head(string headString) ]
  $str = new String("123456ZAaa");
  echo $str->insert_head("--bb--")->value().PHP_EOL;//output:--bb--123456ZAaa

 //5. take string exchange to Lowercase character[ lower() ]
  $str = new String("123456ZAaa");
  echo $str->lower()->value().PHP_EOL;//output:123456zaaa

 //6. take string exchange to Uppercase character [ upper() ]
  $str = new String("123456ZAaa");
  echo $str->upper()->value().PHP_EOL;//output:123456ZAAA