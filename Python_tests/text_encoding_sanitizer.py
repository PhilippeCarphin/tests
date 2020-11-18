# https://github.com/gplv2/PHP-Swiss-Knife/blob/master/classes/class.latin1utf8.php
# class Latin1UTF8 {
# 
#    private $latin1_to_utf8;
#    private $utf8_to_latin1;
# 
#    public function __construct() {
#       for($i=32; $i<=255; $i++) {
#          $this->latin1_to_utf8[chr($i)] = utf8_encode(chr($i));
#          $this->utf8_to_latin1[utf8_encode(chr($i))] = chr($i);
#       }
#    }
# 
#    public function mixed_to_latin1($text) {
#       foreach( $this->utf8_to_latin1 as $key => $val ) {
#          $text = str_replace($key, $val, $text);
#       }
#       return $text;
#    }
# 
#    public function mixed_to_utf8($text) {
#       return utf8_encode($this->mixed_to_latin1($text));
#    }
# }

class Sanitizer:
    def __init__(self):
        self.latin1_to_utf8_map = {}
        self.utf8_to_latin1_map = {}
        for i in range(32, 255):
            self.latin1_to_utf8_map[chr(i).encode('iso8859-1')] = chr(i).encode('utf-8')
            self.utf8_to_latin1_map[chr(i).encode('utf-8')] = chr(i).encode('iso8859-1')
        with open('mixed.cpp', 'rb') as f:
            text_b = f.read()

        for k, v in self.utf8_to_latin1_map.items():
            print(k, v)
            text_b = text_b.replace(k, v)

        with open('iso8859-1.cpp', 'wb+') as f:
            f.write(text_b)

        

s = Sanitizer()


