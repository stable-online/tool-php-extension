--TEST--
Check for tools presence
--SKIPIF--
<?php if (!extension_loaded("tools")) print "skip"; ?>
--FILE--
<?php
      $str = new String("123456ZAaa");
      echo $str->replace(1,3)->value();
?>
--EXPECT--
323456ZAaa