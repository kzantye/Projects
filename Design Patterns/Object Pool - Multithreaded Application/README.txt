NAME:- KUNAL ZANTYE
CS542 Design Patterns
Spring 2016
ASSIGNMENT 1-Simple multi-threaded application

Due Date: Monday, February 29, 2016
Submission Date: Monday, February 29, 2016
Grace Period Used This Project: 0 Days
Grace Period Remaining: 0 Days
Author(s): KUNAL ZANTYE
e-mail(s): kzantye1@binghamton.edu


PURPOSE:

  The purpose of this assignment is Application of design principles for a simple multi-threaded application.
PERCENT COMPLETE: 100%

PARTS THAT ARE NOT COMPLETE: N/A

BUGS: N/A

FILES:

  Included with this assignment are 7 files:

  Driver.java, the file which contains the main(..) method.
  FileProcessor.java, the file responsible for reading one line from the XML document and return it as a String.
  CreateWorkers,Creates number of thread
  WorkerThread,To invoke a method in the FileProcessor to read one line as a string,Checks for the prime number, Store the prime number
  Results,Calculates the sum of the prime numbers
  StdoutDisplayInterface,This interface has method writeSumToScreen: to print the sum  ALso it as the method check prime
  README.txt, the text file you are presently reading


SAMPLE OUTPUT:

Kunals-MacBook-Pro:primeThreads KUNAL$ ant -buildfile src/build.xml run -Darg0="input.txt" -Darg1=3 -Darg2=1
Buildfile: /Users/KUNAL/Documents/workspace/primeThreads/src/build.xml

jar:

run:
     [java] The sum of all the prime numbers is: 9

TO UNTAR

-tar xvf kunal_zantye_assign2.tar

TO COMPILE:

## To clean:
ant -buildfile src/build.xml clean

## To compile: 
ant -buildfile src/build.xml all



TO RUN:

 Place sample.txt(or any file) in the directory containing this README:
Execute following command:
ant -buildfile src/build.xml run -Darg0=sample.txt -Darg1=2 -Darg2=2 


EXTRA CREDIT: 
  
 NA

DATA STRUCTURE:
  
  
  Data Structure used is Vector.
  The time complexity of adding data to add data is O(1).
  The time complexity of iterating through values is O(1).
  Vector data structure is synchronised. 
  Thus using Vector is suitable for this assignment. 

BIBLIOGRAPHY:


ACKNOWLEDGEMENT:

 Prof. Madhusudhan Govindaraju 

Assuming you are in the directory containing this README:
## To run by specifying arguments from command line [similarly for the 2nd argument and so on ...]
## We will use this to run your code
ant -buildfile src/build.xml run -Darg0=firstarg -Darg1=secondarg -Darg2=thirdarg

## To run by specifying args in build.xml (just for debugging, not for submission)
ant -buildfile src/build.xml run

## To create tarball for submission
ant -buildfile src/build.xml tarzip


