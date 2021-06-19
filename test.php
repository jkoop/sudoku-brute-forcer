<?php

system("stty -icanon");
$c = 0;

while(true){
    $k = fread(STDIN, 1);

    if(is_numeric($k)){
        if($k == 0){
            echo "\x08-"; // \x08 == \b
        }

        echo " ";
        $c++;

        if($c % 9 == 0){
            echo "\n";
        }

        if($c == 81){
            break;
        }
    }else{
        echo "\x08";
    }
}
