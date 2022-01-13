# PHP tool functions  
This is an extension of various common tools in PHP,New fun features will be added step by step,Look forward to it!!!

## Requirement
- PHP 7.0+  (PHP8 is not included))

## Install
```shell
phpize
./configure --with-php-config=/path/to/php-config 
make && make install
echo "extension=tools.so" >> /etc/php.ini
```
### Example: 

#### String Object 

`string object` The supplementary PHP string does not have the defect of behavior  

```php
<?php

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
```

## contact
e-mail: 2426594859@qq.com 

Welcome to join