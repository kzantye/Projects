NAME:- KUNAL ZANTYE, PRASHANT KOLHE
CS542 Design Patterns
Spring 2016
ASSIGNMENT 4- IMPLEMENTATION OF VISITOR PATTERN

Due Date: Thursday, April 21, 2016
Submission Date: Thursday, April 21, 2016
Grace Period Used This Project: 0 Days
Grace Period Remaining: 0 Days
Author(s): KUNAL ZANTYE
e-mail(s): kzantye1@binghamton.edu pkolhe1@binghamton.edu


PURPOSE:

  Using visitors with trees.

PERCENT COMPLETE: 100%

PARTS THAT ARE NOT COMPLETE: N/A

BUGS: N/A

FILES:

  Included with this assignment are 10 files:

  build.xml, file used by ANT  
  Driver.java, the file which contains the main(..) method.
  FileProcessor.java
  Node.java
  BST.java
  WordCountVisitor
  GrepVisitor.java
  PopulateVisitor.java
  TreeProcessingVisitorI.java
  README.txt, the text file you are presently reading


SAMPLE OUTPUT:

   [java] 
     [java] 10

   OUTPUT TO THE FILE
	The most frequently used word is: of
	The frequency of the most frequently used word is: 248
	The total number of words is: 6752
	The number of characters (without whitespaces) is: 36577
	The word <the> occurs the following times: 242



TO UNTAR

  -tar xvf kolhe_prashant_kunal_zantye_assign4.tar

TO COMPILE:

  -ant -buildfile build.xml clean
  -ant -buildfile build.xml all

TO RUN:

  -ant -buildfile build.xml run -Darg0=firstarg -Darg1=secondarg -Darg2=thirdarg  
  For example:  ant -buildfile build.xml run -Darg0=input.txt -Darg1=out.txt -Darg2=10 -Darg3=the

EXTRA CREDIT: 
  NA

DATA STRUCTURE:
  
  Tree used for populating the string is BST. 
  The insertion and searching time complexity of BST is O(log n).
  There is one insertion operation performed while Populate Tree visitor.
  The BST is populated based on hash code comparison.
  The WordCount visitor searches the word based on hash code of the string.
  As comparison based on hash code is much easier than string operation.
  The GrepVisitor also uses the hash code based comparison to find the given word.
  The inOrder traversing of BST is O(n).

  The node class stores the word, hash code of the word, 
   frequency of word and the characters in the word.

  To store the multiple max occurring element 
  i.e. the element with max frequency is stored in Hash Map
  The time complexity of adding data to HashMap is O(1).
  The time complexity of iterating through values is O(n).
  Required a key value data structure to store the nodes as keys and frequency




BIBLIOGRAPHY:


ACKNOWLEDGEMENT:

 Prof. Madhusudhan Govindaraju 
