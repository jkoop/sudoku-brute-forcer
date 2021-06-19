#! /usr/bin/php
<?php

$sudoku = [
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
];

$setSudoku = $sudoku;
solveSudoku($sudoku, $setSudoku);
printSudoku($sudoku, $setSudoku);

function solveSudoku(&$sudoku, $setSudoku){
    $forward = true;

    for($i=0; $i<81; $i++){
        $x = $i % 9;
        $y = floor($i / 9);

        for($j=0; $j<10; $j++){
            if($forward && $setSudoku[$y][$x] > 0) break;
            if(!$forward && $setSudoku[$y][$x] > 0) {
                $i = $i - 2;
                break;
            }

            if($sudoku[$y][$x] >= 9){
                if($i == 0){
                    echo "\e[1;31mNot solvable\e[0m\n";
                    return;
                }

                $forward = false;
                $sudoku[$y][$x] = $setSudoku[$y][$x];
                $i = $i - 2;
                break;
            }

            $forward = true;
            $sudoku[$y][$x]++;

            if(checkSudoku($sudoku)) break;
        }
    }
}

function checkSudoku($sudoku): bool {
    // check rows
    foreach($sudoku as $row){
        $counts = array_count_values($row);
        foreach($counts as $key => $count){
            if($key == 0) continue;
            if($count > 1) return false;
        }
    }

    // check cols
    for($i=0; $i<9; $i++){
        $col = [];

        for($j=0; $j<9; $j++){
            $col[] = $sudoku[$j][$i];
        }

        $counts = array_count_values($col);
        foreach($counts as $key => $count){
            if($key == 0) continue;
            if($count > 1) return false;
        }
    }

    // check blocks
    for($h=0; $h<3; $h++){
        for($i=0; $i<3; $i++){
            $block = [];

            for($j=0; $j<3; $j++){
                for($k=0; $k<3; $k++){
                    $block[] = $sudoku[$h * 3 + $j][$i * 3 + $k];
                }
            }

            $counts = array_count_values($block);
            foreach($counts as $key => $count){
                if($key == 0) continue;
                if($count > 1) return false;
            }
        }
    }

    return true;
}

function printSudoku($sudoku, $setSudoku, $overwrite = false){
    if($overwrite) echo "\e[1;1H";

    foreach($sudoku as $k => $a){
        foreach($a as $l => $b){
            if($b == 0){
                echo '-';
            }else{
                if($setSudoku[$k][$l] > 0){
                    echo "\e[1;36m" . $b . "\e[0m";
                }else{
                    echo $b;
                }
            }

            echo ' ';
        }

        echo "\n";
    }
}
