/*    Nick Gentile    Project 1  ng358492     2/15/13     */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define stringSize 16


struct node
  {
    char token[stringSize];
    struct node *next; 
  };

//----------------Prototypes---------------------//

  int nodeCounter(struct node **hashArray, int hashSize);
  int maxNodes(struct node **hashArray, int filledNodes, int hashSize);
  int minNodes(struct node **hashArray, int filledNodes, int hashSize, int maxEntries); 
  int totalNode(struct node **hashArray2, int filledNodes, int hashSize); 

int main (int argc, char *argv[])
{

 
/*---------------- Declarations -------------- */
	
  FILE *infile;
  FILE *outfile;
  int hashSize = 0;  			           //size of the hash array
  int hashSize2 = 0;
  struct node **hashArray;			   //array of pointers		   
  struct node **hashArray2;		           //second array of pointers
  char buffer[stringSize];			  //buffer of size 16
  struct node *nextNode;			  //node to insert into linked list
  int hashLocation = 0;				  //index location
  int hashLocation2 = 0;			  //index location in second array
  int i = 0;

//--------------for print statements---------//
  int filledNodes = 0;
  float avgEntries = 0; 
  int maxEntries = 0;
  int minEntries = 0;
  double totalNodes = 0;

  //temp vars
  struct node* temp;
	
  if(argc !=3)
  {
    exit(1);
  }
	
  //close if there is no input file

  if((infile = fopen(argv[1], "r")) == NULL)					//open file
  {
    fprintf(stderr, "Could not open this file for reading.\n");
    exit(1);
  }
  
  if((outfile = fopen(argv[2], "w")) == NULL)
  {
    fprintf(stderr, "Could not open this file for writing.\n");
    exit(1);
  }

//-------------------------------Create first hash array-----------------------------------//

    fscanf(infile, "%d", &hashSize);							//reads the first line and sets hashSize to the size of the array
    hashArray = (struct node **) malloc((sizeof(struct node *)* hashSize));		//Malloc a new node for each location in array     
  
      while(fscanf(infile, "%s", buffer) != EOF)					 //while there is a line to read
      {
         hashLocation = hash_example_one(buffer, hashSize);   			         //set hashLocation to the hash number
	 nextNode =  malloc ((sizeof(struct node *) * stringSize)); 		        //malloc a node 
         strcpy(nextNode->token, buffer); 			      			//fill nextNode with string 
      
//	 printf("buff %s\n", buffer);
	 if (hashArray[hashLocation] == NULL)						//If the index is empty
	 {
         hashArray[hashLocation] = nextNode; 						//insert node into list at hashLocation
         }
	      else if (hashArray[hashLocation] != NULL)					//in case of a collison 
              {
//		printf("%d: %s\n", hashLocation, hashArray[hashLocation]->token);
                temp = hashArray[hashLocation];						//set temp to the collison index
		 for(;;)			 
		 {
		    if(temp->next == NULL)						//when temp hits the end of the linked list
		    {
			temp->next = nextNode;						//point it to nextNode which points to null
                        break;								//end the for loop
	            } 
                    temp = temp->next;
		 } 
	      }
//        fprintf(stderr, "index: %d\nstring:%s\n\n", hashLocation, hashArray[hashLocation]->token);
      }
	fclose(infile);								//close file 
		

//------------------------Create second hash array------------------------------------//


  if((infile = fopen(argv[1], "r")) == NULL)					//open file
  {
    fprintf(stderr, "Could not open this file for reading.\n");
    exit(1);
  }

    fscanf(infile, "%d", &hashSize2);							//reads the first line and sets hashSize to the size of the array
    hashArray2 = (struct node **) malloc((sizeof(struct node *)* hashSize2));		//Malloc a new node for each location in array     
  
      while(fscanf(infile, "%s", buffer) != EOF)					 //while there is a line to read
      {
         hashLocation2 = hash_example_two(buffer, hashSize2);  			         //set hashLocation to the hash number
	 nextNode =  malloc ((sizeof(struct node *) * stringSize)); 		        //malloc a node 
         strcpy(nextNode->token, buffer); 			      			//fill nextNode with string 
      
//	 printf("buff %s\n", buffer);
	 if (hashArray2[hashLocation2] == NULL)						//If the index is empty
	 {
         hashArray2[hashLocation2] = nextNode; 						//insert node into list at hashLocation
         }
	      else if (hashArray2[hashLocation2] != NULL)					//in case of a collison 
              {
//		printf("%d: %s\n", hashLocation2, hashArray2[hashLocation2]->token);
                temp = hashArray2[hashLocation2];						//set temp to the collison index
		 for(;;)			 
		 {
		    if(temp->next == NULL)						//when temp hits the end of the linked list
		    {
			temp->next = nextNode;						//point it to nextNode which points to null
                        break;								//end the for loop
	            } 
                    temp = temp->next;
		 } 
	      }
  //     fprintf(stderr, "index: %d\nstring:%s\n\n", hashLocation2, hashArray2[hashLocation2]->token);
      }
		


//---------------------------print statements----------------------------------//

  fprintf(outfile, "Results for Hash Function I \n");
  fflush(stdout);

  fprintf(outfile, "---------------------------\n");
  fflush(stdout);

  fprintf(outfile, "Hash table size: %d\n", hashSize);
  fflush(stdout);

  filledNodes = nodeCounter(hashArray, hashSize);

  fprintf(outfile, "Number of non-empty lists: %d\n", filledNodes);
  fflush(stdout); 

  maxEntries = maxNodes(hashArray, filledNodes, hashSize);     

  fprintf(outfile, "Maximum number of entries in a list: %d\n", maxEntries);
  fflush(stdout);

  minEntries = minNodes(hashArray, filledNodes, hashSize, maxEntries);

  fprintf(outfile, "Minimum number of entries in a non-empty list: %d\n", minEntries);
  fflush(stdout);

  totalNodes = totalNode(hashArray, filledNodes, hashSize);

  avgEntries = totalNodes / filledNodes;     

  fprintf(outfile, "Average number of entries in a non-empty list: %.02f\n\n", avgEntries);
  fflush(stdout); 

  filledNodes = 0;			//reset values just in case
  maxEntries = 0;
  minEntries = 0; 
  avgEntries = 0;

  fprintf(outfile, "Results for Hash Function II \n");
  fflush(stdout);

  fprintf(outfile, "---------------------------\n");
  fflush(stdout);

  fprintf(outfile, "Hash table size: %d\n", hashSize);
  fflush(stdout);

  fprintf(outfile, "The second hash array is this large: %d\n", hashSize2);
  fflush(stdout);

  filledNodes = nodeCounter(hashArray2, hashSize2);

  fprintf(outfile, "Number of non-empty lists in the second hash table: %d\n", filledNodes);
  fflush(stdout); 

  maxEntries = maxNodes(hashArray2, filledNodes, hashSize2);     

  fprintf(outfile, "The largest list in the second array is this long: %d\n", maxEntries);
  fflush(stdout);

  minEntries = minNodes(hashArray2, filledNodes, hashSize2, maxEntries);     

  fprintf(outfile, "The shortest list in the second array is this long: %d\n", minEntries);
  fflush(stdout);

  totalNodes = totalNode(hashArray2, filledNodes, hashSize2);

  avgEntries = totalNodes / filledNodes;     

  fprintf(outfile, "Average size of non-empty lists in the second array: %.02f\n", avgEntries);
  fflush(stdout); 


}	//end of main




//-----------------------------------------------Counts filled nodes-------------------------------//

  int nodeCounter(struct node **hashArray, int hashSize)		
  {
    int filledNodes = 0; 
    
    for (; hashSize >= 0; hashSize--)
    {
      if (hashArray[hashSize] != NULL)					//if theres a value in the spot 
      {
        filledNodes++;							//increment counter
      }
    }
    return filledNodes;
  }  


//--------------------------------------Finds largest linked list-----------------------------------//

  int maxNodes(struct node **hashArray, int filledNodes, int hashSize)
  {
   int nodeCounter = 0;							//counter for number of nodes in list
   int maxEntries = 0; 							//maximum found
   int i = 0; 
   struct node* temp;

    for (i=0; i<hashSize; i++)
    {
    temp = hashArray[i];						//goes through index
	
	if(temp != NULL)						//enter linked list
        {

		while(temp != NULL)					//goes through linked list
		{
			nodeCounter++; 					//increment for every node found
			temp = temp->next;
		}
			if (nodeCounter > maxEntries) 			//when nodeCounter is greater then largest list 
			{
	 		 maxEntries = nodeCounter;			//set it to maxEntries
			}
	}
	nodeCounter = 0;
    }
  return maxEntries;
  }
 
//---------------------------------Finds smallest linked list--------------------------------------------//
  int minNodes(struct node **hashArray, int filledNodes, int hashSize, int maxEntries)
  {
    int nodeCounter = 0;
    int minEntries = maxEntries; 					//set minEntries to the maximum number of nodes in the array
    int i = 0;
    struct node* temp;

    
    for (i=0; i<hashSize; i++)
    {
    temp = hashArray[i];						//goes through index
	
	if(temp != NULL)						//enter linked list
        {

		while(temp != NULL)					//goes through linked list
		{
			nodeCounter++; 					//increment for every node found
		// 	printf("node %d\n", nodeCounter);
			temp = temp->next;				//point to next node
		}

			if (nodeCounter <= minEntries && nodeCounter != 0)   //when nodeCounter is less than the number of minEntries
			{
			  minEntries = nodeCounter;				//set minEntries to number of nodes in current list
		//	  printf("min %d\n", minEntries);
			}
	}
	nodeCounter = 0;						//reset counter for next list
    }
     return minEntries; 
  }



//----------------------------------Finds total nodes for avg---------------------------------//

  int totalNode(struct node **hashArray, int filledNodes, int hashSize)
  {
   int totalNodes = 0;							//total number of nodes found
   int i = 0; 
   struct node* temp;

    for (i=0; i<hashSize; i++)
    {
    temp = hashArray[i];						//goes through index
	
	if(temp != NULL)						//enter linked list
        {

		while(temp != NULL)					//goes through linked list
		{
		  totalNodes++; 
		  temp = temp->next;
		}
	}
    }

  return totalNodes;
  }

