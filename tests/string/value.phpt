--TEST--
Check for tools presence
--SKIPIF--
<?php if (!extension_loaded("tools")) print "skip"; ?>
--FILE--
<?php
      $str = new String("123456ZAaa");
      echo $str->value();
?>
--EXPECT--
123456ZAaa