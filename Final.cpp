       /************************************************************/
      /*			DATA STRUCTURES AND ALGORITHMS		 	  	  */
     /*					Project Team:						  	 */
    /*					Aditya Ramesh						    */
   /*					Abhay Sharma 						   */
  /*					Nitesh Dhital				      	  */	
 /*			Dynamic Two-Dimensional Data Representation		 */
/************************************************************/

#include<stdio.h>
#include<stdlib.h>

struct chain{
	int data;
	struct chain* link;
};

struct super{
	struct chain* top;	//Top corresponding to mini-stack branching out from main-chain
	struct super* next;	//Pointer corresponding to next node on main chain
};

struct super* utop=NULL; //Top corresponding to stack of stacks

int ct=0;


//Function to display all elements in the data-grid
void displayall(){	
	struct super* temp=utop;
		while(temp!=NULL){
			struct chain* t=temp->top;
			
			while(t!=NULL){
				printf("%d",t->data);
				if(t->link!=NULL)
					printf("-->");
				t=t->link;
			}
			
			if(temp->next!=NULL)
				printf("\n|\n");
			temp=temp->next;
		}
		printf("\n\n");
}


//Function to delete specific item from a specific branch dynamically
void deletefrom(int branch, int item){
		struct super*temp = utop;
		struct super*parent = NULL;
		
		//Traversing to the branch where deletion must be done
		while(branch--){
			parent=temp;
			temp=temp->next;
		}
		
		//Initializing local top
		struct chain*t=temp->top;
		struct chain*p=NULL;
		int len=0;
		struct chain*trav=temp->top;
		
		//Calculating length of mini-stack
		while(trav!=NULL){
			trav=trav->link;
			len++;
		}
		
		//if the element is directly attached to main chain and its deletion removes a mini-stack
		if(len==1 && t->data==item&&parent!=NULL){
			struct chain*hold=t;
			temp->top=t->link;
			free(hold);
			struct super* h=temp;
			parent->next=temp->next;
			free(h);
			ct--;
		}
		
		//if the element is directly attached to main chain and level is top and its deletion removes a mini-stack
		else if(len==1 && t->data==item&&parent==NULL){	
			struct super*hold=temp;
			utop=temp->next;
			free(hold);
			ct--;
		}	
		
		//if element is directly attached to the main chain
		else if(t->data==item){
			struct chain*hold=t;
			temp->top=t->link;
			free(hold);
		}	
		
		//if standard element
		else while(t!=NULL){
			struct chain*p=t;
			t=t->link;
			if(t!=NULL && t->data==item){
				struct chain*hold=t;
				p->link=t->link;
				free(hold);
			}
		}
		
}
	

int main(){
	int ch;
	
	do{
	printf("Enter choice: \n1.Add Item to existing branch.\n2.Add item to a new branch.\n3.Display Branch.\n4.Display all.\n5.Delete specific Item from specific branch.\n6.Delete branch.\n7.Delete first occurrence of item from all branches\n8.Find Item.\n9.Exit\n");
	scanf("%d",&ch);
	if(ch<=0||ch>9)printf("Invalid input, retry.\n");
	//Addition of item to existing branch
	else if(ch==1){
		
		//If zero branches are present
		if(ct==0){	
		utop=(struct super*)(malloc(sizeof(struct super)));
		utop->top=(struct chain*)(malloc(sizeof(struct chain)));
		utop->next=NULL;
		int item;
		printf("Enter data to be input in the branch: ");
		scanf("%d",&item);
		utop->top->data=item;
		utop->top->link=NULL;
		ct++;
		}
		
		//if branches are pre-existent
		else{
			struct chain* temp = (struct chain*)(malloc(sizeof(struct chain)));
			printf("Enter which chain to add data in, between 0 (top) to %d :",ct-1);
			int x;
			scanf("%d",&x);
			
			//RTE Handling
			while(x<0 || x>ct){printf("Error, re-input valid data.\n");scanf("%d",&x);}
			
			struct super* trav=utop;
			int tmp=0;	
			while(tmp!=x){
				trav=trav->next;
				tmp++;	
			}
			printf("Enter data to be inserted: ");
			int item;
			scanf("%d",&item);
			temp->data=item;
			temp->link=trav->top;
			trav->top=temp;
		}
		
		printf("Updated contents: \n");
		displayall();
		
		}
	
	//Addition of item to new branch
	else if(ch==2){
		struct super* n=(struct super*)(malloc(sizeof(struct super)));
		n->top=(struct chain*)(malloc(sizeof(struct chain)));
		
		printf("Enter data to be inserted: ");
		int item;
		scanf("%d",&item);
		
		//Assigning input as top of mini-stack
		n->top->data=item;
		n->top->link=NULL;
		
		//Assigning overall top to the new mini-stack
		n->next=utop;
		utop=n;
		
		ct++;
		
		printf("Updated contents: \n");
		displayall();
		
		}
		
	//Displaying contents of specific branch
	else if(ch==3){
		printf("Enter branch number whose contents are to be displayed (0 to %d): ",ct-1);
		int no;
		scanf("%d",&no);
		while(no<0 || no>=ct){printf("Error, re-input valid data.\n");scanf("%d",&no);}
			
		struct super* trav=utop;
		int x=0;
		while(x!=no){
			x++;
			trav=trav->next;
		}
		
		struct chain* t=trav->top;
		while(t!=NULL){
			printf("%d",t->data);
			if(t->link!=NULL)
				printf("-->");
			t=t->link;
		}
		
		printf("\n\n");
				
		}
	
	//Displaying all contents stored since runtime
	else if(ch==4){
		printf("Displaying all data:\n\n");
		displayall();
		}
	
	//Deletion of specific item in specific branch
	else if(ch==5){
		printf("Enter branch number to consider: ");
		int no;
		scanf("%d",&no);
		
		//RTE Handling
		while(no<0||no>=ct){printf("Invalid input, retry. ");scanf("%d",&no);}
		
		printf("Enter item to be deleted: ");
		int item;
		scanf("%d",&item);
		deletefrom(no,item);
		
		printf("Updated contents: \n");
		displayall();
		
		}
		
	//Deletion of branch entirely
	else if(ch==6){
		printf("Enter branch number to be deleted: ");
		int x;
		scanf("%d",&x);
		
		//RTE Handling
		while(x<0||x>=ct){printf("Invalid input, retry. ");scanf("%d",&x);}
		
		struct super*t=utop;
		struct super*p=NULL;
		if(x==0)utop=t->next;
		
		else{
			while(x--){
				p=t;
				t=t->next;
			}
			struct super*hold=t;
			p->next=t->next;
			free(hold);
		}
		
		printf("Updated contents: \n");
		displayall();
		
		ct--;
	}
	
	//Deletion of first occurrence of element in all branches
	else if(ch==7){
		int no=0;
		int cpy=ct;
		printf("Enter item to be deleted: ");
		int item;
		scanf("%d",&item);
		
		while(no<ct){
		cpy=ct;		
		deletefrom(no,item);
		if(cpy==ct)no++;
		}
		printf("Updated contents: \n");
		displayall();
	}
	
	//Locate item in data-grid
	else if(ch==8){
		
		//check if search even needs to be done
		if(ct==0)
			printf("No data present.\n\n");
			
		else{
			int item;
			int save;
			int curno=0;
			printf("Enter item to be scanned for: ");
			scanf("%d",&item);
			struct super *t=utop;
			struct chain*tmp=t->top;
				
			int ok=0;
		
			//scanning through all items in all branches
			while(t!=NULL&&ok==0){
				struct chain*tmp=t->top;
				while(tmp!=NULL){
					if(tmp->data==item){
						printf("Item found at branch %d.\n\n",curno);
						ok=1;
						save=curno;
					}
					tmp=tmp->link;
				}
				t=t->next;
				curno++;
			}

		//if item was found
		if(ok){
			struct super* trav=utop;
			int x=0;
			while(x!=save){
				x++;
				trav=trav->next;
			}	
		
			struct chain* tt=trav->top;
			while(tt!=NULL){
				printf("%d",tt->data);
				if(tt->link!=NULL)
					printf("-->");
				tt=tt->link;
			}
			printf("\n\n");
		}
		
		//if item was not found
		else printf("\nNot found in data grid.\n\n");}
	
	}
	//End of all cases
	}while(ch!=9);
	
	return 0;
}
