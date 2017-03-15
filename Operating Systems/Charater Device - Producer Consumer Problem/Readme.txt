NAME:- KUNAL ZANTYE & PRASHANT KOLHE
CS550 Operating System
Spring 2016
ASSIGNMENT 3-Producer Consumer Problem

Due Date: Friday, April 08, 2016
Submission Date: Friday, April 08, 2016

Author(s): KUNAL ZANTYE & PRASHANT KOLHE
e-mail(s): kzantye1@binghamton.edu pkolhe1@binghamton.edu



PURPOSE:

  TO implement a kernel-level pipe for exchanging strings among user-level processes.

PERCENT COMPLETE: 100%


FILES:

  Included with this assignment are 6 files:
  Kernel Makefile
  mydevice.c, Kernel Character Device
  consumer.c
  producer.c
  User Makefile
  README.txt, the text file you are presently reading

TO COMPILE:

  Place the files of kernel folder inside the ~/linux4.4.3/kernel/
  Compile the kernel file my device.c using the provided kernel Makefile.
  Use the provided user files to implement the producer and consumer.
  Compile the User files using gcc or with the given Makefile.

TO RUN:

     Register Device:
			make
			sudo insmod mydevice.ko
			sudo chmod a+w+r /dev/mydevice
     Unregister Device: 
			sudo rmmod mydevice.ko
     User Files:
			make (User Makefile)
     			./producer (to run producer)
     			./consumer (to run the consumer)

NOTE:
 The Code works for the following:

  Code works for one producer and one consumer.
  Code works for multiple concurrent producers and consumers. We may test for up to 5 of each.
  No deadlocks. All producers and consumers make progress as long as at least one of each is running.
  No race conditions. Each string that is written by producers is read EXACTLY once by one consumer. No string is lost. No string is read more than once.
  Producers block on write when pipe is full
  Consumers block on read when pipe is empty
  Blocked producers are not woken up by other producers. Blocked consumers are not woken up by other consumers.
  Blocked producers and consumers can be terminated using Ctrl-C
    
	
