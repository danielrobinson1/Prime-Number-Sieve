Prime Number Sieve
==================
A C++ program to generate all prime numbers up to a specified integer, using the Sieve of Eratosthenes algorithm.

The user is prompted to enter an integer, for example 50.
![Screenshot1](/docs/screenshots/screenshot1.jpg)
All integers from 2 to 50 are then printed to the console.
![Screenshot2](/docs/screenshots/screenshot2.jpg)
The first integer in the list 2, is taken as the pivot and all multiples of 2 are removed from the list. In fact we change them to zeroes rather than deleting them, in order to help keep track of what we are doing.
![Screenshot3](/docs/screenshots/screenshot3.jpg)
Now, the next non-zero integer in the list 3 is set as the new pivot. It is prime since it is not divisible by 2. (If it were divisible by 2, it would have been changed to a zero in the previous step). This time all multiples of 3 are removed from the list.
![Screenshot4](/docs/screenshots/screenshot4.jpg)
This process continues taking the next non-zero integer in the list as the new pivot and deleting all multiples of the pivot from the list, until the pivot reached the square root of the original integer provided by the user.
At this point, only the prime numbers remain
![Screenshot5](/docs/screenshots/screenshot5.jpg) 