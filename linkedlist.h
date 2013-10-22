#DEFINE maxSize 16


//creates a node with a size of maxSize 

struct node{ 
	char token [maxSize];
	struct node next;
}

struct node *head = NULL;

int count_nodes(struct node *);
void insert (char *);

