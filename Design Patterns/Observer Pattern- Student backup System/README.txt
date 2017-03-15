NAME:- KUNAL ZANTYE
CS542 Design Patterns
Spring 2016
ASSIGNMENT 3- Backup System for Student Records

Due Date: Tuesday, March 22, 2016
Submission Date: Tuesday, March 23, 2016
Grace Period Used This Project: 0 Days
Grace Period Remaining: 0 Days
Author(s): KUNAL ZANTYE
e-mail(s): kzantye1@binghamton.edu


PURPOSE:

  The purpose of this assignment is to build a Backup System for Student Records using the Design Pattern Learned in class.

PERCENT COMPLETE: 100%

PARTS THAT ARE NOT COMPLETE: N/A

BUGS: N/A

FILES:

  Included with this assignment are 11 files:

  build.xml, file used by ANT  
  Driver.java, the file which contains the main(..) method.
  BSTBuilder.java, file to read the data from input file and create a BST
  OddEvenFilterI.java, Interface for the filter
  EvenFilterImpl.java, File that checks even number and Implements OddEvenFilterI interface.
  OddFilterImpl.java, File that checks odd number and Implements OddEvenFilterI interface.
  Node.java, File consisting of Node class
  SubjectI.java, File with subject interface
  ObserverI.java, File with observer interface
  BST.java, File to build the BST
  Logger.java, Used for debuging
  README.txt, the text file you are presently reading


SAMPLE OUTPUT:

  [java] 
     [java] ------------------Before Updating-----------------------------
     [java] 
     [java] 
     [java] Printing Tree Inorder:
     [java]  
     [java] Orignal Tree: 
     [java]  1 2 3 4 5 6 7 8 9
     [java] Backup1 Tree: 
     [java]  1 2 3 4 5 6 7 8 9
     [java] Backup2 Tree: 
     [java]  1 2 3 4 5 6 7 8 9
     [java] 
     [java] Printing SUM:
     [java]  
     [java] Sum of Orignal Tree: 45
     [java] Sum of Backup1 Tree: 45
     [java] Sum of Backup2 Tree: 45
     [java] 
     [java] ------------------After Updating-----------------------------
     [java] 
     [java] 
     [java] Printing Tree Inorder:
     [java]  
     [java] Orignal Tree: 
     [java]  4 5 6 7 8 9 10 11 15
     [java] Backup1 Tree: 
     [java]  1 2 3 4 5 6 7 8 9
     [java] Backup2 Tree: 
     [java]  4 5 6 7 8 9 10 11 12
     [java] 
     [java] Printing SUM:
     [java]  
     [java] Sum of Orignal Tree: 75
     [java] Sum of Backup1 Tree: 45
     [java] Sum of Backup2 Tree: 72




TO UNTAR

  -tar xvf kunal_zantye_assign3.tar

TO COMPILE:

  -ant -buildfile src/build.xml clean
  -ant -buildfile src/build.xml all

TO RUN:

  -ant -buildfile src/build.xml run -Darg0=firstarg -Darg1=secondarg -Darg2=thirdarg  
  For example:  ant -buildfile src/build.xml run -Darg0=bstInput.txt -Darg1=3 

EXTRA CREDIT: 
  NA

DATA STRUCTURE:
  
  
  Data Structure used is HashMap.
  The time complexity of adding data to HashMap is O(1).
  The time complexity of iterating through values is O(n).
  Required a key value data structure to store the nodes as keys and filter as value
  Thus using HashMap is suitable for this assignment. 

BIBLIOGRAPHY:


ACKNOWLEDGEMENT:

 Prof. Madhusudhan Govindaraju 
