# PHP tool functions  

This is an extension of various common tools in PHP

## Requirement
- PHP 7.0+  (master branch))

## Install
```shell
phpize
./configure --with-php-config=/path/to/php-config 
make && make install
echo "extension=geohash.so" >> /etc/php.ini
```
### Example: 

#### String Object 

`string object` The supplementary PHP string does not have the defect of behavior  

```php
<?php
  $str = new String("123456");
    
  //Intercepting string behavior
  echo $str->substr(0,3)->dd();//output:12
  echo $str->substr(1,3)->dd();//output:234
```

## contact
e-mail: 2426594859@qq.com