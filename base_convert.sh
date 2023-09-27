
#!/bin/bash

#1.check if there are valid number of input
#2.check if the given input base and output base are valid
#3.now process the input numbers for conversion
#4.function to convert a number from one base to another

#checking correct number of arguments
if [ $# -ne 1 ]; then
  echo "Usage:$0<input.txt"
  exit 1
fi

#create output file
output="output.txt"
touch "$output"

#function to convert the input into expected base
converter(){
    local input_number="$1"
    local from_base="$2"
    local to_base="$3"
    local result=""
    if [ "$from_base" -eq 10 ]; then 
     result="$input_number"
     else 
     result=$(echo "ibase=$from_base;$input_number"|bc)
     fi
     if [ "$to_base" -ne 10 ];then
     result=$(echo "obase=$to_base;$result"|bc)
     fi
     
    echo "$result"
}

#checking input base and output base
while read -r input_number base_of_input base_of_output; do
echo "Read: input_number=$input_number, base_of_input=$base_of_input, base_of_output=$base_of_output"
  if ! [[ "$base_of_input" =~ ^([2-9]|[1-9][0-9]*)$ ]] || ! [[ "$base_of_output" =~ ^([2-9]|[1-9][0-9]*)$ ]]; then
       echo "invalid input or output base"
       continue
  fi
  converted=$(converter "$input_number" "$base_of_input" "$base_of_output")
  echo "$input_number $base_of_input $base_of_output $converted">>"$output"
done <"$1" 

echo "conversion completeD"
