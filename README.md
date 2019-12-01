# Closest-Pair assignment
## Setup
from the root directory use the following command
~~~
/Closest-Pair/make
~~~
This should compile three programs, _create_, _bruteforce_, and _divideconquer_.

## How to use
Before we can run either algorithm we must create files with random points. To create these files run the following command:
~~~
/Closest-Pair/create 10 100 500 <size of output>
~~~
You can create a single output file by adding a single int argument or you can create a few at a time by adding more arguments separated by spaces. These output text files will be saved in
~~~
/Closest-Pair/pointsData/
~~~
To run wither of the algorithm you must call it with an input size as an argument. For example after using `./create 100` we call the algorithm as follows:
~~~
/Closest-Pair/bruteforce 100
~~~
or
~~~
/Closest-Pair/dividconquer 100
~~~

## Other usages
You can use the make command to clean up the directory
~~~
/Closest-Pair/make clean
~~~
Will remove the three executable files
~~~
/Closest-Pair/make clean-points
~~~
Will remove all .txt files within the points directory
~~~
/Closest-Pair/make clean-all
~~~
Will run both of the previous clean commands.