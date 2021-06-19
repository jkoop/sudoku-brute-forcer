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
        if(!isAllUnique($row)){
            return false;
        }
    }

    // check cols
    for($i=0; $i<9; $i++){
        $col = [];

        for($j=0; $j<9; $j++){
            $col[] = $sudoku[$j][$i];
        }

        if(!isAllUnique($col)){
            return false;
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

            if(!isAllUnique($block)){
                return false;
            }
        }
    }

    return true;
}

function printSudoku($sudoku, $setSudoku){
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

function isAllUnique($row){
    $count = [0,0,0,0,0,0,0,0,0,0];

    for($i = 0; $i < 9; $i++){
        if($row[$i] != 0 && $count[$row[$i]] > 0){
            return false;
        }else{
            $count[$row[$i]]++;
        }
    }

    return true;
}
