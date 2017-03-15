package studentRecordsBackup.driver;



import studentRecordsBackup.util.BSTBuilder;

/** Description of Driver Class
* @author KUNAL ZANTYE
* @description Main file also contain main(..)
* 			   Displays the three tree inOrder
* 			   Prints the sum of the tree
* 			   Calls the method to Update the tree
* @args reads the command line argument, input file and update value
*/
public class Driver {
	
	public static void main(String[] args) {
		int updateval=0;
		if(args.length < 2 || args.length > 2)
		{
			System.out.println("Enter Filename and Update value");
			System.exit(1);
		}
		else
		{
			try{
			updateval=Integer.parseInt(args[1]);
			}catch(Exception e)
			{
				System.out.println("Improper Input");
				System.exit(1);
			}
		
		BSTBuilder b= new BSTBuilder();
		//b.readLineFromFile("bstInput.txt");
		b.readLineFromFile(args[0]);
		
		System.out.println("\n------------------Before Updating-----------------------------\n");
		b.display();
		b.sumNode();
		
		System.out.println("\n\n------------------After Updating-----------------------------\n");
		b.updateBST(updateval);
		
		b.display();
		b.sumNode();
		}
		
	}

}
