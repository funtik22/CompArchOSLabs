#!/usr/bin/env bats

setup() {
    test_dir=$(mktemp -d)
}
teardown() {
    rm -rf "$test_dir"
}


@test "Wrong path" {
  run ./check.sh /wrong/directory
  [[ "$output" == "Invalid path to directory" ]]
}

@test "Input is a number" {
  run ./check.sh 1
  [[ "$output" == "Invalid path to directory" ]]
}

@test "Input is a file" {
  run ./check.sh check.sh
  [[ "$output" == "check.sh is a file, but a directory was expected" ]]
}

@test "No arguments" {
  run ./check.sh 
  [[ "$output" == "No arguments" ]]
}

@test "Second parameter is not a number" {
  run ./check.sh $test_dir a 1
  [[ "$output" == "a is not a number." ]]
}

@test "Third parameter is not a number" {
  run ./check.sh $test_dir 1 a
  [[ "$output" == "a is not a number." ]]
}
