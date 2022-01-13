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
  $str = new String("123456");
    
  //1. substr string behavior [ substr(int start,int length) ] 
  echo $str->substr(0,3)->value();//output:123
  echo $str->substr(1,3)->value();//output:23

  //2. replace string behavior [ replace(string search,string replace) ] 
  echo $str->replace('23',"bbb")->value();//output:1bbb456

  //3.  insert content to string tail behavior [ insert_tail(string tailString) ] 
  echo $str->insert_tail("--hello world")->value();//output:123456--hello world

  //4. insert content to string head behavior [ insert_head(string headString) ]
  echo $str->insert_head("--bb--")->value();//output:--bb--123456
```

## contact
e-mail: 2426594859@qq.com 

Welcome to join