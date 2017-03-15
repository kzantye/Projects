CS542 Design Patterns
Spring 2016
PROJECT Assignment5 README FILE

Due Date: Sunday, May 8, 2016
Submission Date: Sunday, May 8, 2016
Grace Period Used This Project: 0 Days
Grace Period Remaining: 0 Days
Author(s): Kunal Zantye
e-mail(s): kzantye11@binghamton.edu


PURPOSE:

The purpose of this assignment is to create a generic library to serialize and deserialize objects. The code allow's the conversion of objects into a wire format. The code is designed using dynamic proxies and reflection so that addition of new objects or serialization formats causes minimal changes (reduces the ripple effect).

PERCENT COMPLETE:

100

PARTS THAT ARE NOT COMPLETE:
None

BUGS:
None

FILES:
Included with this project are following files:

Driver
Driver.java
StoreRestoreI.java
StoreI.java 
RestoreI.java 
MyAllTypesFirst.java 
MyAllTypesSecond.java 
ProxyCreator.java 
SerializableObject.java
StoreRestoreHandler.java
DeserializeTypes.java
SerializeTypes.java
SerStrategy.java
XMLDeSerialization.java
XMLSerialization.java
README, the text file you are presently reading

SAMPLE OUTPUT:

For SERDESER Mode

<DPSerialization> 
 <complexType xsi:type="genericCheckpointing.util.MyAllTypesFirst">
 <myInt xsi:type="xsd:int">2</myInt>
 <myLong xsi:type="xsd:long">2</myLong>
 <myString xsi:type="xsd:string">2</myString>
 <myBool xsi:type="xsd:boolean">true</myBool>
 </complexType>
</DPSerialization>
<DPSerialization> 
 <complexType xsi:type="genericCheckpointing.util.MyAllTypesSecond">
 <myDoubleT xsi:type="xsd:double">2.0</myDoubleT>
 <myFloatT xsi:type="xsd:float">2.0</myFloatT>
 <myShortT xsi:type="xsd:short">2</myShortT>
 <myCharT xsi:type="xsd:char">a</myCharT>
 </complexType>
</DPSerialization>
<DPSerialization> 
 <complexType xsi:type="genericCheckpointing.util.MyAllTypesFirst">
 <myInt xsi:type="xsd:int">3</myInt>
 <myLong xsi:type="xsd:long">3</myLong>
 <myString xsi:type="xsd:string">3</myString>
 <myBool xsi:type="xsd:boolean">true</myBool>
 </complexType>
</DPSerialization>
<DPSerialization> 
 <complexType xsi:type="genericCheckpointing.util.MyAllTypesSecond">
 <myDoubleT xsi:type="xsd:double">3.0</myDoubleT>
 <myFloatT xsi:type="xsd:float">3.0</myFloatT>
 <myShortT xsi:type="xsd:short">3</myShortT>
 <myCharT xsi:type="xsd:char">a</myCharT>
 </complexType>
</DPSerialization>

   [java] 0 mismatched objects

For DESER Mode
 
  [java] Class Name:MyAllTypesFirst 
     [java]  myInt:2
     [java]  myLong:2
     [java]  myString:2
     [java]  myBool:true
     [java] Class Name:MyAllTypesSecond 
     [java]  myDoubleT:2.0
     [java]  myFloatT:2.0
     [java]  myShortT:2
     [java]  myCharT:a
     [java] Class Name:MyAllTypesFirst 
     [java]  myInt:3
     [java]  myLong:3
     [java]  myString:3
     [java]  myBool:true
     [java] Class Name:MyAllTypesSecond 
     [java]  myDoubleT:3.0
     [java]  myFloatT:3.0
     [java]  myShortT:3
     [java]  myCharT:a
      


TO CLEAN:
ant -buildfile build.xml clean

To COMPILE: 
ant -buildfile build.xml all

To run by specifying arguments from command line

ant -buildfile build.xml run -Darg0=input.txt -Darg11=2 

To create tarball for submission
ant -buildfile build.xml tarzip

TO UNTAR:
tar -zxvf kunal_zantye_assign5.tar.gz

Justification for data structure:

Data structure used is vector as the time complexity of inserting an element in vector and iterating through vector is O(1)

EXTRA CREDIT:
N/A


BIBLIOGRAPHY:


ACKNOWLEDGEMENT:
Prof. Madhusudhan Govindaraju


Assuming you are in the directory containing this README:

